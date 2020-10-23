#include "CDXGraphicsAPI.h"
#include "CDXTexture.h"
#include "CDXRTV.h"
#include "CDXBuffer.h"
#include "CDXShaderProgram.h"
#include "CDXInputLayout.h"

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

CTexture* CDXGraphicsAPI::createTexture(int width, int height)
{
	if (m_Device != nullptr)
	{
		CDXTexture* DXTexture = new CDXTexture();

		//Create texture descriptor
		D3D11_TEXTURE2D_DESC Desc;
		ZeroMemory(&Desc, sizeof(Desc));

		Desc.Width = width;
		Desc.Height = height;
		Desc.MipLevels = 1;
		Desc.ArraySize = 1;
		Desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.Usage = D3D11_USAGE_DEFAULT;
		Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		Desc.MiscFlags = 0;

		//Create texture with descriptor
		HRESULT hr = m_Device->CreateTexture2D(&Desc, NULL, &DXTexture->m_pTexture);
		if (FAILED(hr))
		{
			delete DXTexture;
			return nullptr;
		}

		//Create RTV from texture
		hr = m_Device->CreateRenderTargetView(
			DXTexture->m_pTexture,
			NULL,
			&DXTexture->m_pRTV);
		if (FAILED(hr))
		{
			delete DXTexture;
			return nullptr;
		}

		//Create Depthstencil texture
		Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		hr = m_Device->CreateTexture2D(&Desc, NULL, &DXTexture->m_pDepthTexture);

		if (FAILED(hr))
		{
			delete DXTexture;
			return nullptr;
		}

		//Create Depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		hr = m_Device->CreateDepthStencilView(
			DXTexture->m_pDepthTexture,
			&descDSV,
			&DXTexture->m_pDSV);

		if (FAILED(hr))
		{
			delete DXTexture;
			return nullptr;
		}

		return DXTexture;
	}
}

CShaderProgram* CDXGraphicsAPI::createShaderProgram(std::wstring vsfile,
	std::wstring psfile)
{

	CDXVertexShader* VS = new CDXVertexShader();
	
	//Compile vertex shader file and check for errors
	if (FAILED(compileShaderFromFile(vsfile, "vs_4_0", &VS->m_Blob)))
	{
		VS->clear();
		delete VS;
		return nullptr;
	}

	//Create vertex shader from compilation and check errors
	if (FAILED(m_Device->CreateVertexShader(
							VS->m_Blob->GetBufferPointer(),
							VS->m_Blob->GetBufferSize(),
							NULL,
							&VS->m_VS)))
	{
		VS->clear();
		delete VS;
		return nullptr;
	}

	CDXPixelShader* PS = new CDXPixelShader();

	//Compile pixel shader file and check for errors
	if (FAILED(compileShaderFromFile(psfile, "ps_4_0", &PS->m_Blob)))
	{
		VS->clear();
		delete VS;
		PS->clear();
		delete PS;
		return nullptr;
	}

	//Create pixel shader from compilation and check for errors
	if (FAILED(m_Device->CreatePixelShader(
						PS->m_Blob->GetBufferPointer(),
						PS->m_Blob->GetBufferSize(),
						NULL,
						&PS->m_PS)))
	{
		VS->clear();
		delete VS;
		PS->clear();
		delete PS;
		return nullptr;
	}

	CDXShaderProgram* ShaderProgram = new CDXShaderProgram();
	ShaderProgram->setVertexShader(VS);
	ShaderProgram->setPixelShader(PS);

	return ShaderProgram;

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

CInputLayout* CDXGraphicsAPI::createInputLayout(CShaderProgram* program,
	LAYOUT_DESC desc)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;

	unsigned int texcoordindex = 0;
	unsigned int positionindex = 0;
	unsigned int normalindex = 0;
	unsigned int binormalindex = 0;
	unsigned int tangentindex = 0;

	D3D11_INPUT_ELEMENT_DESC D;

	for (int i = 0; i < desc.v_Layout.size(); i++)
	{
		//SEMANTIC NAME & INDEX
		switch (desc.v_Layout[i].s_Semantic)
		{
		case POSITION:
			D.SemanticName = "POSITION";
			D.SemanticIndex = positionindex;
			positionindex++;
			break;
		case TEXCOORD:
			D.SemanticName = "TEXCOORD";
			D.SemanticIndex = texcoordindex;
			texcoordindex++;
			break;
		case NORMAL:
			D.SemanticName = "NORMAL";
			D.SemanticIndex = normalindex;
			normalindex++;
			break;
		case BINORMAL:
			D.SemanticName = "BINORMAL";
			D.SemanticIndex = binormalindex;
			binormalindex++;
			break;
		case TANGENT:
			D.SemanticName = "TANGENT";
			D.SemanticIndex = tangentindex;
			tangentindex++;
			break;
		}
		//FORMAT
		switch (desc.v_Layout[i].s_Format)
		{
		case VEC_F:
			D.Format = DXGI_FORMAT_R32_FLOAT;
			break;
		case VEC_2F:
			D.Format = DXGI_FORMAT_R32G32_FLOAT;
			break;
		case VEC_3F:
			D.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case VEC_4F:
			D.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		}

		D.InputSlot = 0;
		D.AlignedByteOffset = desc.v_Layout[i].s_Offset;
		D.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		D.InstanceDataStepRate = 0;

		layout.push_back(D);
	}

	CDXVertexShader* VS = dynamic_cast<CDXVertexShader*>(program->getVertexShader());

	CDXInputLayout* ILayout = new CDXInputLayout();	

	if (FAILED(m_Device->CreateInputLayout(layout.data(),
		layout.size(),
		VS->m_Blob->GetBufferPointer(),
		VS->m_Blob->GetBufferSize(),
		&ILayout->m_InputLayout)))
	{
		delete ILayout;
		return nullptr;
	}

	return ILayout;
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

void CDXGraphicsAPI::setShaders(CShaderProgram* program)
{
	CDXVertexShader* VS = dynamic_cast<CDXVertexShader*>(program->getVertexShader());
	CDXPixelShader* PS = dynamic_cast<CDXPixelShader*>(program->getPixelShader());

	m_DeviceContext->VSSetShader(VS->m_VS, NULL, 0);
	m_DeviceContext->PSSetShader(PS->m_PS, NULL, 0);
}

void CDXGraphicsAPI::draw(unsigned int indices)
{
	m_DeviceContext->DrawIndexed(indices, 0, 0);
}

void CDXGraphicsAPI::clearBackBuffer(float red, float green, float blue)
{
	float Color[4] = { red, green, blue, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RTV, Color);
	m_DeviceContext->ClearDepthStencilView(m_DSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

HRESULT CDXGraphicsAPI::compileShaderFromFile(std::wstring fileName,
	std::string shaderModel,
	ID3DBlob** ppBlobOut)
{
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pErrorBlob;
	
	HRESULT hr = D3DX11CompileFromFile(fileName.c_str(),
		NULL,
		NULL,
		"main",
		shaderModel.c_str(),
		dwShaderFlags,
		0,
		NULL,
		ppBlobOut,
		&pErrorBlob,
		NULL);

	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
		{
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			pErrorBlob->Release();
			return hr;
		}
	}
	if (pErrorBlob)
	{
		pErrorBlob->Release();
	}

	return S_OK;
}