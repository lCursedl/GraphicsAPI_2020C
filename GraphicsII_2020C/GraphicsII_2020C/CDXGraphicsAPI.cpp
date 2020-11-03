#include "CDXGraphicsAPI.h"
#include "CDXTexture.h"
#include "CDXRTV.h"
#include "CDXBuffer.h"
#include "CDXShaderProgram.h"
#include "CDXInputLayout.h"

bool CDXGraphicsAPI::init(HWND window)
{
	D3D_DRIVER_TYPE m_DriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	m_Device = NULL;
	m_DeviceContext = NULL;
	m_SwapChain = NULL;

	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(window, &rc);

	unsigned int width = rc.right - rc.left;
	unsigned int height = rc.bottom - rc.top;

	unsigned int createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);

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

	for (unsigned int driverTypeIndex = 0;
		driverTypeIndex < numDriverTypes;
		driverTypeIndex++)
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

	CDXTexture* backBuffer = new CDXTexture();

	//Create RTV
	hr = m_SwapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)
		&backBuffer->m_pTexture);
	if (FAILED(hr))
	{
		return false;
	}

	hr = m_Device->CreateRenderTargetView(
		backBuffer->m_pTexture,
		NULL, &backBuffer->m_pRTV);
	if (FAILED(hr))
	{
		return false;
	}

	CDXTexture* depthTexture = new CDXTexture();

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
	hr = m_Device->CreateTexture2D(&descDepth, NULL, &depthTexture->m_pTexture);
	if (FAILED(hr))
	{
		delete backBuffer;
		delete depthTexture;
		return false;
	}

	//Create depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_Device->CreateDepthStencilView(depthTexture->m_pTexture,
		&descDSV,
		&depthTexture->m_pDSV);
	if (FAILED(hr))
	{
		delete backBuffer;
		delete depthTexture;
		return false;
	}

	//Set main RTV and DSV by default
	m_DeviceContext->OMSetRenderTargets(1, &backBuffer->m_pRTV, depthTexture->m_pDSV);

	m_BackBuffer = backBuffer;
	m_DepthStencil = depthTexture;

	//Set Viewport
	setViewport(width, height);

	m_Formats.insert(std::make_pair(R8_SNORM,		DXGI_FORMAT_R8_SNORM));
	m_Formats.insert(std::make_pair(R16_SNORM,		DXGI_FORMAT_R16_SNORM));
	m_Formats.insert(std::make_pair(RG8_SNORM,		DXGI_FORMAT_R8G8_SNORM));
	m_Formats.insert(std::make_pair(RG16_SNORM,		DXGI_FORMAT_R16G16_SNORM));
	m_Formats.insert(std::make_pair(RGB10_A2UI,		DXGI_FORMAT_R10G10B10A2_UINT));
	m_Formats.insert(std::make_pair(R16_FLOAT,		DXGI_FORMAT_R16_FLOAT));
	m_Formats.insert(std::make_pair(RG16_FLOAT,		DXGI_FORMAT_R16G16_FLOAT));
	m_Formats.insert(std::make_pair(RGBA16_FLOAT,	DXGI_FORMAT_R16G16B16A16_FLOAT));
	m_Formats.insert(std::make_pair(R32_FLOAT,		DXGI_FORMAT_R32_FLOAT));
	m_Formats.insert(std::make_pair(RG32_FLOAT,		DXGI_FORMAT_R32G32_FLOAT));
	m_Formats.insert(std::make_pair(RGB32_FLOAT,	DXGI_FORMAT_R32G32B32_FLOAT));
	m_Formats.insert(std::make_pair(RGBA32_FLOAT,	DXGI_FORMAT_R32G32B32A32_FLOAT));
	m_Formats.insert(std::make_pair(RG11B10_FLOAT,	DXGI_FORMAT_R11G11B10_FLOAT));
	m_Formats.insert(std::make_pair(RGB9_E5,		DXGI_FORMAT_R9G9B9E5_SHAREDEXP));
	m_Formats.insert(std::make_pair(R8_INT,			DXGI_FORMAT_R8_SINT));
	m_Formats.insert(std::make_pair(R8_UINT,		DXGI_FORMAT_R8_UINT));
	m_Formats.insert(std::make_pair(R16_INT,		DXGI_FORMAT_R16_SINT));
	m_Formats.insert(std::make_pair(R16_UINT,		DXGI_FORMAT_R16_UINT));
	m_Formats.insert(std::make_pair(R32_INT,		DXGI_FORMAT_R32_SINT));
	m_Formats.insert(std::make_pair(R32_UINT,		DXGI_FORMAT_R32_UINT));
	m_Formats.insert(std::make_pair(RG8_INT,		DXGI_FORMAT_R8G8_SINT));
	m_Formats.insert(std::make_pair(RG8_UINT,		DXGI_FORMAT_R8G8_UINT));
	m_Formats.insert(std::make_pair(RG16_INT,		DXGI_FORMAT_R16G16_SINT));
	m_Formats.insert(std::make_pair(RG16_UINT,		DXGI_FORMAT_R16G16_UINT));
	m_Formats.insert(std::make_pair(RG32_INT,		DXGI_FORMAT_R32G32_SINT));
	m_Formats.insert(std::make_pair(RG32_UINT,		DXGI_FORMAT_R32G32_UINT));
	m_Formats.insert(std::make_pair(RGB32_INT,		DXGI_FORMAT_R32G32B32_SINT));
	m_Formats.insert(std::make_pair(RGB32_UINT,		DXGI_FORMAT_R32G32B32_UINT));
	m_Formats.insert(std::make_pair(RGBA8_INT,		DXGI_FORMAT_R8G8B8A8_SINT));
	m_Formats.insert(std::make_pair(RGBA8_UINT,		DXGI_FORMAT_R8G8B8A8_UINT));
	m_Formats.insert(std::make_pair(RGBA16_INT,		DXGI_FORMAT_R16G16B16A16_SINT));
	m_Formats.insert(std::make_pair(RGBA16_UINT,	DXGI_FORMAT_R16G16B16A16_UINT));
	m_Formats.insert(std::make_pair(RGBA32_INT,		DXGI_FORMAT_R32G32B32A32_SINT));
	m_Formats.insert(std::make_pair(RGBA32_UINT,	DXGI_FORMAT_R32G32B32A32_UINT));
	m_Formats.insert(std::make_pair(R8_UNORM,		DXGI_FORMAT_R8_UNORM));
	m_Formats.insert(std::make_pair(R16_UNORM,		DXGI_FORMAT_R16_UNORM));
	m_Formats.insert(std::make_pair(RG8_UNORM,		DXGI_FORMAT_R8G8_UNORM));
	m_Formats.insert(std::make_pair(RG16_UNORM,		DXGI_FORMAT_R16G16_UNORM));
	m_Formats.insert(std::make_pair(RGB5A1_UNORM,	DXGI_FORMAT_B5G5R5A1_UNORM));
	m_Formats.insert(std::make_pair(RGBA8_UNORM,	DXGI_FORMAT_R8G8B8A8_UNORM));
	m_Formats.insert(std::make_pair(RGB10A2_UNORM,	DXGI_FORMAT_R10G10B10A2_UNORM));
	m_Formats.insert(std::make_pair(RGBA16_UNORM,	DXGI_FORMAT_R16G16B16A16_UNORM));
	m_Formats.insert(std::make_pair(RGBA8_SRGB_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB));
	m_Formats.insert(std::make_pair(D24_S8,			DXGI_FORMAT_D24_UNORM_S8_UINT));

	return true;
}

CTexture* CDXGraphicsAPI::createTexture(int width,
	int height,
	TEXTURE_BINDINGS binding,
	TEXTURE_FORMATS format)
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
		Desc.Format = m_Formats[format];
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.Usage = D3D11_USAGE_DEFAULT;

		if (binding & SHADER_RESOURCE)
		{
			Desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
		}
		if (binding & RENDER_TARGET)
		{
			Desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
		}
		if (binding & DEPTH_STENCIL)
		{
			Desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
		}
		Desc.MiscFlags = 0;

		//Create texture with descriptor
		HRESULT hr = m_Device->CreateTexture2D(&Desc, NULL, &DXTexture->m_pTexture);
		if (FAILED(hr))
		{
			delete DXTexture;
			return nullptr;
		}

		if (binding & SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
			ZeroMemory(&viewDesc, sizeof(viewDesc));
			viewDesc.Format = Desc.Format;
			viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			viewDesc.Texture2D.MostDetailedMip = 0;
			viewDesc.Texture2D.MipLevels = 1;

			if (FAILED(m_Device->CreateShaderResourceView(
				DXTexture->m_pTexture,
				&viewDesc,
				&DXTexture->m_pSRV)))
			{
				delete DXTexture;
				return nullptr;
			}
		}
		if (binding & RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
			ZeroMemory(&rtvDesc, sizeof(rtvDesc));
			rtvDesc.Format = Desc.Format;
			rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtvDesc.Texture2D.MipSlice = 0;

			if (FAILED(m_Device->CreateRenderTargetView(
				DXTexture->m_pTexture,
				&rtvDesc,
				&DXTexture->m_pRTV)))
			{
				delete DXTexture;
				return nullptr;
			}
		}
		if (binding & DEPTH_STENCIL)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			ZeroMemory(&descDSV, sizeof(descDSV));
			descDSV.Format = Desc.Format;
			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;

			if (FAILED(m_Device->CreateDepthStencilView(
				DXTexture->m_pTexture,
				&descDSV,
				&DXTexture->m_pDSV)))
			{
				delete DXTexture;
				return nullptr;
			}
		}
		return DXTexture;
	}
	else
	{
		OutputDebugStringA("Missing API initialization.");
		return nullptr;
	}
}

CShaderProgram* CDXGraphicsAPI::createShaderProgram(std::wstring vsfile,
	std::wstring psfile)
{
	CDXShaderProgram* ShaderProgram = new CDXShaderProgram();
	CDXVertexShader* VS = 
		dynamic_cast<CDXVertexShader*>(ShaderProgram->getVertexShader());
	CDXPixelShader* PS =
		dynamic_cast<CDXPixelShader*>(ShaderProgram->getPixelShader());
	
	//Compile vertex shader file and check for errors
	if (FAILED(compileShaderFromFile(vsfile,
		"vs_4_0",
		&VS->m_Blob)))
	{
		delete ShaderProgram;
		return nullptr;
	}

	//Create vertex shader from compilation and check errors
	if (FAILED(m_Device->CreateVertexShader(
							VS->m_Blob->GetBufferPointer(),
							VS->m_Blob->GetBufferSize(),
							NULL,
							&VS->m_VS)))
	{
		delete ShaderProgram;
		return nullptr;
	}

	//Compile pixel shader file and check for errors
	if (FAILED(compileShaderFromFile(psfile, "ps_4_0", &PS->m_Blob)))
	{
		delete ShaderProgram;
		return nullptr;
	}

	//Create pixel shader from compilation and check for errors
	if (FAILED(m_Device->CreatePixelShader(
						PS->m_Blob->GetBufferPointer(),
						PS->m_Blob->GetBufferSize(),
						NULL,
						&PS->m_PS)))
	{
		delete ShaderProgram;
		return nullptr;
	}

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

	m_DeviceContext->OMSetRenderTargets(1,
		&dynamic_cast<CDXTexture*>(m_BackBuffer)->m_pRTV,
		dynamic_cast<CDXTexture*>(m_DepthStencil)->m_pDSV);
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

void CDXGraphicsAPI::drawIndexed(unsigned int indices)
{
	m_DeviceContext->DrawIndexed(indices, 0, 0);
}

void CDXGraphicsAPI::clearBackBuffer(float red, float green, float blue)
{
	float Color[4] = { red, green, blue, 1.0f };
	m_DeviceContext->ClearRenderTargetView(
		dynamic_cast<CDXTexture*>(m_BackBuffer)->m_pRTV,
		Color);
	m_DeviceContext->ClearDepthStencilView(
		dynamic_cast<CDXTexture*>(m_DepthStencil)->m_pDSV,
		D3D11_CLEAR_DEPTH,
		1.0f,
		0);
}

void CDXGraphicsAPI::setInputLayout(CInputLayout* layout)
{
	if (layout)
	{
		CDXInputLayout* dxlayout = dynamic_cast<CDXInputLayout*>(layout);
		if (dxlayout->m_InputLayout)
		{
			m_DeviceContext->IASetInputLayout(dxlayout->m_InputLayout);
		}
		else
		{
			OutputDebugStringA("Input layout invalid.");
		}
		
	}
	else
	{
		OutputDebugStringA("Received null pointer.");
	}
}

void CDXGraphicsAPI::setRenderTarget(CTexture* texture, CTexture* depth)
{
	if (texture)
	{
		ID3D11RenderTargetView* rtv = dynamic_cast<CDXTexture*>(texture)->m_pRTV;
		if (rtv)
		{
			if (depth)
			{
				ID3D11DepthStencilView* dsv = dynamic_cast<CDXTexture*>(depth)->m_pDSV;
				if (dsv)
				{
					m_DeviceContext->OMSetRenderTargets(1, &rtv, dsv);
				}
				else
				{
					OutputDebugStringA("Invalid DepthStencilView.");
				}
			}
			else
			{
				m_DeviceContext->OMSetRenderTargets(1, &rtv, nullptr);
			}
			
		}
		else
		{
			OutputDebugStringA("Invalid RenderTargetView.");
		}
	}
	else
	{
		OutputDebugStringA("Received null pointer for texture.");
	}
}

HRESULT CDXGraphicsAPI::compileShaderFromFile(std::wstring fileName,
	std::string shaderModel,
	ID3DBlob** ppBlobOut)
{
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pErrorBlob;
	
	HRESULT hr = D3DCompileFromFile(fileName.c_str(),
		nullptr,
		nullptr,
		"main",
		shaderModel.c_str(),
		dwShaderFlags,
		0,
		ppBlobOut,
		&pErrorBlob);

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