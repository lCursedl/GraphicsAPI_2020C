#include "CDXGraphicsAPI.h"
#include "CDXTexture.h"
#include "CDXRTV.h"
#include "CDXBuffer.h"
#include "CDXShaderProgram.h"

bool CDXGraphicsAPI::init(HWND window)
{
	m_DriverType = D3D_DRIVER_TYPE_NULL;
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	m_Device = NULL;
	m_DeviceContext = NULL;
	m_SwapChain = NULL;

	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(window, &rc);

	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = window;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_DriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL,
			m_DriverType,
			NULL,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_SwapChain,
			&m_Device,
			&m_FeatureLevel,
			&m_DeviceContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
	{
		return false;
	}

	//Create RTV
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_BackBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	hr = m_Device->CreateRenderTargetView(m_BackBuffer, NULL, &m_RTV);
	if (FAILED(hr))
	{
		return false;
	}

	//Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_Device->CreateTexture2D(&descDepth, NULL, &m_DepthStencil);
	if (FAILED(hr))
	{
		return false;
	}

	//Create depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_Device->CreateDepthStencilView(m_DepthStencil, &descDSV, &m_DSV);
	if (FAILED(hr))
	{
		return false;
	}

	//Set main RTV and DSV by default
	m_DeviceContext->OMSetRenderTargets(1, &m_RTV, m_DSV);

	//Set Viewport
	setViewport(width, height);

	return true;
}

bool CDXGraphicsAPI::createRTV(CRTV* rtv, CTexture* tex)
{
	if (m_Device != nullptr)
	{
		HRESULT hr;
		hr = m_Device->CreateRenderTargetView(
			dynamic_cast<CDXTexture*>(tex)->m_pTexture,
			NULL,
			&dynamic_cast<CDXRTV*>(rtv)->m_pRTV);
		if (FAILED(hr))
		{
			return false;
		}
		return true;
	}
	return false;
}

bool CDXGraphicsAPI::createTexture(CTexture* tex, CRTV* rtv)
{
	if (m_Device != nullptr)
	{
		//Cast abstract type to specific
		CDXTexture* T = dynamic_cast<CDXTexture*>(tex);
		//Create 2D texture
		HRESULT hr = m_Device->CreateTexture2D(&T->m_Desc, NULL, &T->m_pTexture);
		//Check for errors in texture creation
		if (FAILED(hr))
		{
			return false;
		}
		return true;
	}	
	return false;
}

bool CDXGraphicsAPI::compileAndCreateShader(WCHAR* filename,
	CShaderProgram* program,
	LPCSTR entrypoint,
	LPCSTR shaderModel,
	SHADER_TYPE type)
{
	CDXShaderProgram* sp = dynamic_cast<CDXShaderProgram*>(program);
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* ErrorBlob;
	HRESULT hr;
	switch (type)
	{
	case VERTEX_SHADER:
		hr = D3DX11CompileFromFile(filename,
			NULL,
			NULL,
			entrypoint,
			shaderModel,
			dwShaderFlags,
			0,
			NULL,
			&sp->m_pVertexShader->m_Blob,
			&ErrorBlob,
			NULL);
		break;
	case PIXEL_SHADER:
		hr = D3DX11CompileFromFile(filename,
			NULL,
			NULL,
			entrypoint,
			shaderModel,
			dwShaderFlags,
			0,
			NULL,
			&sp->m_pPixelShader->m_Blob,
			&ErrorBlob,
			NULL);
		break;
	}

	if (FAILED(hr))
	{
		if (ErrorBlob != NULL)
		{
			OutputDebugStringA((char*)ErrorBlob->GetBufferPointer());
			
		}
		if (ErrorBlob)
		{
			ErrorBlob->Release();
		}
		return false;
	}
	if (ErrorBlob)
	{
		ErrorBlob->Release();
	}
	return true;
}

bool CDXGraphicsAPI::compileAndCreateVertexShader(WCHAR* filename,
	CVertexShader* shader,
	LPCSTR entryPoint,
	LPCSTR shaderModel)
{
	CDXVertexShader* VS = dynamic_cast<CDXVertexShader*>(shader);

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	ID3DBlob* ErrorBlob;
	HRESULT hr = D3DX11CompileFromFile(
		filename,
		NULL,
		NULL,
		entryPoint,
		shaderModel,
		dwShaderFlags,
		0,
		NULL,
		&VS->m_Blob,
		&ErrorBlob,
		NULL);
	if (FAILED(hr))
	{
		if (ErrorBlob != NULL)
		{
			OutputDebugStringA((char*)ErrorBlob->GetBufferPointer());
		}
		if (ErrorBlob)
		{
			ErrorBlob->Release();
		}
		return false;
	}
	if (ErrorBlob)
	{
		ErrorBlob->Release();
	}

	hr = m_Device->CreateVertexShader(VS->m_Blob,
		VS->m_Blob->GetBufferSize(),
		NULL,
		&VS->m_VS);

	if (FAILED(hr))
	{
		VS->m_Blob->Release();
		return false;
	}

	return true;
}

bool CDXGraphicsAPI::compileAndCreatePixelShader(WCHAR* filename,
	CPixelShader* shader,
	LPCSTR entryPoint,
	LPCSTR shaderModel)
{
	CDXPixelShader* PS = dynamic_cast<CDXPixelShader*>(shader);

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	ID3DBlob* ErrorBlob;
	HRESULT hr = D3DX11CompileFromFile(
		filename,
		NULL,
		NULL,
		entryPoint,
		shaderModel,
		dwShaderFlags,
		0,
		NULL,
		&PS->m_Blob,
		&ErrorBlob,
		NULL);
	if (FAILED(hr))
	{
		if (ErrorBlob != NULL)
		{
			OutputDebugStringA((char*)ErrorBlob->GetBufferPointer());
		}
		if (ErrorBlob)
		{
			ErrorBlob->Release();
		}
		return false;
	}
	if (ErrorBlob)
	{
		ErrorBlob->Release();
	}

	hr = m_Device->CreatePixelShader(PS->m_Blob,
		PS->m_Blob->GetBufferSize(),
		NULL,
		&PS->m_PS);

	if (FAILED(hr))
	{
		PS->m_Blob->Release();
		return false;
	}

	return true;
}

CBuffer* CDXGraphicsAPI::createBuffer(const void* data,
	unsigned int size,
	BUFFER_TYPE type)
{
	CDXBuffer* DXBuffer = new CDXBuffer();

	DXBuffer->m_Desc.Usage = D3D11_USAGE_DEFAULT;
	DXBuffer->m_Desc.ByteWidth = size;
	DXBuffer->m_Desc.CPUAccessFlags = 0;

	switch (type)
	{
	case VERTEX_BUFFER:
		DXBuffer->m_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		break;
	case INDEX_BUFFER:
		DXBuffer->m_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		break;
	case CONST_BUFFER:
		DXBuffer->m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		break;
	}

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = data;
	HRESULT hr = m_Device->CreateBuffer(
		&DXBuffer->m_Desc,
		&InitData,
		&DXBuffer->m_Buffer);
	if (FAILED(hr))
	{
		return nullptr;
	}
	return DXBuffer;
}

void CDXGraphicsAPI::setBackBuffer()
{
	m_DeviceContext->OMSetRenderTargets(1, &m_RTV, m_DSV);
}

void CDXGraphicsAPI::setViewport(int width, int height)
{
	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;
	m_DeviceContext->RSSetViewports(1, &vp);
}