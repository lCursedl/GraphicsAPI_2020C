#include "CDXGraphicsAPI.h"
#include "COGLGraphicsAPI.h"
#include "CCamera.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 Texcoord;
};

struct Matrices
{
	glm::mat4 World;
	glm::mat4 Projection;
	glm::vec4 Color;
};

struct ViewCB
{
	glm::mat4 View;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Load(CGraphicsAPI* api);
void Render(CGraphicsAPI* api);
void Clear();
void Update(CGraphicsAPI* api);

CBuffer* vb = nullptr;
CBuffer* ib = nullptr;
CBuffer* cbMatrices = nullptr;
CBuffer* cbView = nullptr;
CShaderProgram* sp = nullptr;
CShaderProgram* sp2 = nullptr;
CInputLayout* layout = nullptr;
CTexture* rtv = nullptr;
CTexture* depthTex = nullptr;
CCamera Cam;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	//Register window class
	WNDCLASS wc = { };

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"graphicsapi";

	RegisterClass(&wc);

	//Create window

	HWND hwnd = CreateWindowEx(
		0,
		L"graphicsapi",
		L"GraphicsAPI_2020C",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	CGraphicsAPI* graphicsAPI = new COGLGraphicsAPI();
	graphicsAPI->init(hwnd);
	Load(graphicsAPI);

	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update(graphicsAPI);
			Render(graphicsAPI);
		}
	}
	Clear();
	graphicsAPI->shutdown();
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		Cam.getKeyPress(wParam);
		break;
	case WM_KEYUP:
		Cam.getKeyRelease(wParam);
		break;
	case WM_RBUTTONDOWN:
		POINT MousePoint;
		GetCursorPos(&MousePoint);
		Cam.mInitPos = { MousePoint.x, MousePoint.y, 0.f };
		Cam.mIsClicked = true;
		break;
	case WM_RBUTTONUP:
		Cam.mIsClicked = false;
		break;
	case WM_MOUSEMOVE:		
		if (Cam.mIsClicked)
		{
			POINT EndPoint;
			GetCursorPos(&EndPoint);
			Cam.mEndPos = { EndPoint.x, EndPoint.y, 0.f };
			SetCursorPos(Cam.mInitPos.x, Cam.mInitPos.y);
			Cam.mDir = Cam.mInitPos - Cam.mEndPos;
			Cam.rotate(Cam.mDir);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Clear()
{
	delete vb;
	delete ib;
	delete cbMatrices;
	delete cbView;
	delete layout;
	delete rtv;
	delete depthTex;
	delete sp;
	delete sp2;
}

void Load(CGraphicsAPI* api)
{
	//Create rt for offscreen rendering
	rtv = api->createTexture(800, 600, RENDER_TARGET, RGBA16_FLOAT);
	depthTex = api->createTexture(800, 600, DEPTH_STENCIL, D24_S8);
	//Compile and create vertex / pixel shader
	sp = api->createShaderProgram(L"VS", L"PS");
	sp2 = api->createShaderProgram(L"VS", L"PS2");
	//Define input layout
	LAYOUT_DESC lDesc;
	lDesc.addToDesc(POSITION, RGB32_FLOAT, 0, 3);
	lDesc.addToDesc(TEXCOORD, RG32_FLOAT, 12, 2);
	//Create input layout
	layout = api->createInputLayout(sp, lDesc);
	//Define vertex buffer
	std::vector<Vertex>vertices;
	vertices.push_back({ glm::vec3(-1.0f, 1.0f, -1.0f),	glm::vec2(0.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, 1.0f, -1.0f),	glm::vec2(1.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f) });
	vertices.push_back({ glm::vec3(-1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f) });

	vertices.push_back({ glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec2(0.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, -1.0f, -1.0f),	glm::vec2(1.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, -1.0f, 1.0f),	glm::vec2(1.0f, 1.0f) });
	vertices.push_back({ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f) });

	vertices.push_back({ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
	vertices.push_back({ glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec2(1.0f, 0.0f) });
	vertices.push_back({ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) });
	vertices.push_back({ glm::vec3(-1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f) });

	vertices.push_back({ glm::vec3(1.0f, -1.0f, 1.0f),	glm::vec2(0.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, 1.0f, -1.0f),	glm::vec2(1.0f, 1.0f) });
	vertices.push_back({ glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f) });

	vertices.push_back({ glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec2(0.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, 1.0f, -1.0f),	glm::vec2(1.0f, 1.0f) });
	vertices.push_back({ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f) });

	vertices.push_back({ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, -1.0f, 1.0f),	glm::vec2(1.0f, 0.0f) });
	vertices.push_back({ glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f) });
	vertices.push_back({ glm::vec3(-1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f) });
	//Define index buffer
	std::vector<unsigned int>indices;
	indices.push_back(3); indices.push_back(1); indices.push_back(0);
	indices.push_back(2); indices.push_back(1); indices.push_back(3);

	indices.push_back(6); indices.push_back(4); indices.push_back(5);
	indices.push_back(7); indices.push_back(4); indices.push_back(6);

	indices.push_back(11); indices.push_back(9); indices.push_back(8);
	indices.push_back(10); indices.push_back(9); indices.push_back(11);

	indices.push_back(14); indices.push_back(12); indices.push_back(13);
	indices.push_back(15); indices.push_back(12); indices.push_back(14);

	indices.push_back(19); indices.push_back(17); indices.push_back(16);
	indices.push_back(18); indices.push_back(17); indices.push_back(19);

	indices.push_back(22); indices.push_back(20); indices.push_back(21);
	indices.push_back(23); indices.push_back(20); indices.push_back(22);
	//Create vertex buffer
	vb = api->createBuffer(vertices.data(), sizeof(Vertex) * 24, VERTEX_BUFFER);
	//Create index buffer
	ib = api->createBuffer(indices.data(), sizeof(unsigned int) * 36, INDEX_BUFFER);
	//Create constant buffer
	cbMatrices = api->createBuffer(nullptr, sizeof(Matrices), CONST_BUFFER);
	cbView = api->createBuffer(nullptr, sizeof(ViewCB), CONST_BUFFER);
	//Initialize VM and PM of camera
	CameraDesc desc;
	desc.Pos = { 0.f, 3.f, -6.f };
	desc.LAt = { 0.f, 1.f, 0.f };
	desc.Up = { 0.f, 1.f, 0.f };
	desc.FOV = 0.785398f;
	desc.Width = 800.f;
	desc.Height = 600.f;
	desc.NearPlane = 0.01f;
	desc.FarPlane = 100.f;

	Cam.setAPIMatrix(api);
	Cam.init(desc);
	
	//Create structure to update CB
	Matrices mat;
	//Assign world matrix as identity
	mat.World = glm::mat4(1.0f);
	//Generate Projection matrix
	mat.Projection = Cam.getProjection();
	mat.Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	api->updateBuffer(cbMatrices, &mat);

	api->setInputLayout(layout);
	api->setVertexBuffer(vb, sizeof(Vertex));
	api->setIndexBuffer(ib);

	api->setConstantBuffer(0, cbMatrices, VERTEX_SHADER);
	api->setConstantBuffer(1, cbView, VERTEX_SHADER);
	api->setConstantBuffer(0, cbMatrices, PIXEL_SHADER);
}

void Render(CGraphicsAPI* api)
{
	api->setRenderTarget(rtv, depthTex);
	api->clearRenderTarget(rtv, {1.f, 1.f, 1.f, 1.f});
	api->clearDepthStencil(depthTex);	
	api->setShaders(sp2);
	api->drawIndexed(36);

	api->setBackBuffer();
	api->clearBackBuffer({ 0.0f, 0.125f, 0.3f, 1.0f });	
	api->setShaders(sp);
	api->drawIndexed(36);

	api->swapBuffer();
}

void Update(CGraphicsAPI* api)
{
	Cam.move();
	Cam.rotate();
	ViewCB vm;
	vm.View = Cam.getView();
	api->updateBuffer(cbView, &vm);
}