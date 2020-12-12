#include "CDXGraphicsAPI.h"
#include "COGLGraphicsAPI.h"
#include "CCamera.h"
#include "CModel.h"

struct Matrices
{
	glm::mat4 World;
	glm::vec4 Color;
};

struct ViewCB
{
	glm::mat4 View;
};

struct ProjectionCB
{
	glm::mat4 Projection;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Load(CGraphicsAPI* api, HWND hWnd);
void Render(CGraphicsAPI* api);
void Clear();
void Update(CGraphicsAPI* api);

CBuffer* cbMatrices = nullptr;
CBuffer* cbView = nullptr;
CBuffer* cbProj = nullptr;
CShaderProgram* sp = nullptr;
CShaderProgram* sp2 = nullptr;
CInputLayout* layout = nullptr;
CTexture* rtv = nullptr;
CTexture* depthTex = nullptr;
CVertexShader* defaultVS = nullptr;
CPixelShader* redPS = nullptr;
CPixelShader* posPS = nullptr;
CSamplerState* sampler = nullptr;
CModel* myModel = nullptr;
CCamera Cam;
CGraphicsAPI* graphicsAPI = nullptr;

unsigned int widthWindow = 800;
unsigned int heightWindow = 600;

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
		widthWindow,
		heightWindow,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (hwnd == NULL)
	{
		return -1;
	}

	ShowWindow(hwnd, nCmdShow);

	graphicsAPI = new COGLGraphicsAPI();
	graphicsAPI->init(hwnd);
	Load(graphicsAPI, hwnd);

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
	delete graphicsAPI;
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
		Cam.setInitPos({ MousePoint.x, MousePoint.y, 0.f });
		Cam.setClicked(true);
		break;
	case WM_RBUTTONUP:
		Cam.setClicked(false);
		break;
	case WM_MOUSEMOVE:		
		if (Cam.getClicked())
		{
			POINT EndPoint;
			GetCursorPos(&EndPoint);
			Cam.setEndPos({ EndPoint.x, EndPoint.y, 0.f });
			SetCursorPos(Cam.getInitPos().x, Cam.getInitPos().y);
			Cam.rotatePitchYaw();
		}
		break;
	case WM_SIZE:
		if (graphicsAPI)
		{
			RECT rc;
			GetClientRect(hWnd, &rc);

			graphicsAPI->resizeBackBuffer(rc.right, rc.bottom);

			delete rtv;
			delete depthTex;

			rtv = graphicsAPI->createTexture(rc.right,
				rc.bottom,
				TEXTURE_BINDINGS::RENDER_TARGET | TEXTURE_BINDINGS::SHADER_RESOURCE,
				RGBA16_FLOAT);
			depthTex = graphicsAPI->createTexture(rc.right,
				rc.bottom,
				TEXTURE_BINDINGS::DEPTH_STENCIL,
				D24_S8);

			Cam.setWidth(rc.right);
			Cam.setHeigth(rc.bottom);
			Cam.updatePM();

			ProjectionCB P;
			P.Projection = graphicsAPI->matrix4Policy(Cam.getProjection());
			graphicsAPI->updateBuffer(cbProj, &P);

			graphicsAPI->setViewport(0, 0, rc.right, rc.bottom);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Clear()
{
	delete cbMatrices;
	delete cbView;
	delete cbProj;
	delete layout;
	delete rtv;
	delete depthTex;
	delete sp;
	delete sp2;
	delete defaultVS;
	delete redPS;
	delete posPS;
	delete myModel;
}

void Load(CGraphicsAPI* api, HWND hWnd)
{
	api->setTopology(TOPOLOGY::TRIANGLES);
	RECT rc;
	GetClientRect(hWnd, &rc);
	api->setViewport(0, 0, rc.right, rc.bottom);
	//Create rt for offscreen rendering
	rtv = api->createTexture(rc.right, rc.bottom,
		TEXTURE_BINDINGS::RENDER_TARGET | TEXTURE_BINDINGS::SHADER_RESOURCE,
		RGBA16_FLOAT);
	depthTex = api->createTexture(rc.right,
		rc.bottom,
		TEXTURE_BINDINGS::DEPTH_STENCIL,
		D24_S8);
	//Compile and create vertex / pixel shader
	defaultVS = api->createVertexShader(L"VS");
	redPS = api->createPixelShader(L"PS");
	posPS = api->createPixelShader(L"PS2");
	//Create shader program
	sp = api->createShaderProgram();
	sp2 = api->createShaderProgram();
	//Attach shaders to programs
	sp->setVertexShader(defaultVS);
	sp->setPixelShader(redPS);

	sp2->setVertexShader(defaultVS);
	sp2->setPixelShader(posPS);
	//Link shader programs
	sp->linkProgram();
	sp2->linkProgram();
	//Create sampler state
	sampler = api->createSamplerState(FILTER_LINEAR,
		FILTER_LINEAR,
		FILTER_LINEAR,
		0,
		WRAP);
	//Define input layout
	LAYOUT_DESC lDesc;
	lDesc.addToDesc(POSITION, RGB32_FLOAT, 0, 3);
	lDesc.addToDesc(TEXCOORD, RG32_FLOAT, 12, 2);
	lDesc.addToDesc(NORMAL, RGB32_FLOAT, 20, 3);
	lDesc.addToDesc(TANGENT, RGB32_FLOAT, 36, 3);
	lDesc.addToDesc(BINORMAL, RGB32_FLOAT, 48, 3);
	//Create input layout
	layout = api->createInputLayout(sp, lDesc);
	//Create constant buffer
	cbMatrices = api->createBuffer(nullptr, sizeof(Matrices), CONST_BUFFER);
	cbView = api->createBuffer(nullptr, sizeof(ViewCB), CONST_BUFFER);
	cbProj = api->createBuffer(nullptr, sizeof(ProjectionCB), CONST_BUFFER);
	//Initialize VM and PM of camera
	CameraDesc desc;
	desc.Pos = { 0.f, 2.f, -6.f };
	desc.FOV = 40;
	desc.Width = rc.right;
	desc.Height = rc.bottom;

	Cam.init(desc);
	
	//Create structure to update CB
	Matrices mat;
	//Assign world matrix as identity
	mat.World = glm::mat4(1.0f);
	mat.Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	api->updateBuffer(cbMatrices, &mat);

	ProjectionCB project;
	project.Projection = api->matrix4Policy(Cam.getProjection());
	api->updateBuffer(cbProj, &project);

	api->setInputLayout(layout);

	api->setConstantBuffer(0, cbMatrices, VERTEX_SHADER);
	api->setConstantBuffer(1, cbView, VERTEX_SHADER);
	api->setConstantBuffer(2, cbProj, VERTEX_SHADER);
	api->setConstantBuffer(0, cbMatrices, PIXEL_SHADER);

	//initialize model and load it
	myModel = new CModel();
	myModel->load("Models/silly_dancing.fbx", api);
}

void Render(CGraphicsAPI* api)
{
	api->setRenderTarget(rtv, depthTex);
	api->clearRenderTarget(rtv, {1.f, 1.f, 1.f, 1.f});
	api->clearDepthStencil(depthTex);
	api->setShaders(sp2);
	myModel->draw(api);
	
	api->setBackBuffer();
	api->clearBackBuffer({ 0.0f, 0.125f, 0.3f, 1.0f });
	api->setShaders(sp);
	myModel->draw(api);

	api->swapBuffer();
}

void Update(CGraphicsAPI* api)
{
	Cam.move();
	Cam.rotate();
	ViewCB vm;
	vm.View = api->matrix4Policy(Cam.getView());
	api->updateBuffer(cbView, &vm);
}