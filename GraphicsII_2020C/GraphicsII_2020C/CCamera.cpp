#include "CCamera.h"
#include "CDXGraphicsAPI.h"

CCamera::CCamera()
{
	mIsClicked = false;
	mForward = false;
	mBack = false;
	mLeft = false;
	mRight = false;
	mUp = false;
	mDown = false;
	mRotateLeft = false;
	mRotateRight = false;
}

CCamera::~CCamera() {}

int CCamera::init(CameraDesc Ref)
{
	//Set common values
	setPos(Ref.Pos);
	setLAt(Ref.LAt);
	setUp(Ref.Up);
	setFOV(Ref.FOV);
	setWidth(Ref.Width);
	setHeigth(Ref.Height);
	setNear(Ref.NearPlane);
	setFar(Ref.FarPlane);

	//Set Front, Right & Up

	createVM();
	updateVM();
	updatePM();

	return 0;
}

void CCamera::setPos(glm::vec3 rPos)
{
	Pos = rPos;
}

void CCamera::setLAt(glm::vec3 rLAt)
{
	LAt = rLAt;
}

void CCamera::setUp(glm::vec3 rUp)
{
	Up = rUp;
}

void CCamera::setFront(glm::vec3 rAt, glm::vec3 rPos)
{
	Front = glm::normalize(LAt - Pos);
}

void CCamera::setRight(glm::vec3 rUp, glm::vec3 rFront)
{
	Right = glm::normalize(glm::cross(Up, Front));
}

void CCamera::setUp(glm::vec3 rFront, glm::vec3 rRight)
{
	Up = glm::normalize(glm::cross(Front, Right));
}

void CCamera::setFOV(float rFOV)
{
	FOV = rFOV;
}

void CCamera::setWidth(float rWidth)
{
	Width = rWidth;
}

void CCamera::setHeigth(float rHeigth)
{
	Height = rHeigth;
}

void CCamera::setNear(float rNear)
{
	NearPlane = rNear;
}

void CCamera::setFar(float rFar)
{
	FarPlane = rFar;
}

glm::vec3 CCamera::getPos()
{
	return Pos;
}

glm::vec3 CCamera::getLAt()
{
	return LAt;
}

glm::vec3 CCamera::getUp()
{
	return Up;
}

float CCamera::getFOV()
{
	return FOV;
}

float CCamera::getWidth()
{
	return Width;
}

float CCamera::getHeigth()
{
	return Height;
}

float CCamera::getNear()
{
	return NearPlane;
}

float CCamera::getFar()
{
	return FarPlane;
}

glm::vec3 CCamera::getFront()
{
	return Front;
}

glm::vec3 CCamera::getRight()
{
	return Right;
}

void CCamera::updateVM()
{
	Right = { View[0][0], View[0][1], View[0][2] };
	Up =	{ View[1][0], View[1][1], View[1][2] };
	Front = { View[2][0], View[2][1], View[2][2] };
	LAt = Front + Pos;
}

void CCamera::updatePM()
{
	Proj = glm::perspectiveFovLH(FOV, Width, Height, NearPlane, FarPlane);
}

void CCamera::move()
{
	if (mForward)
	{
		Pos += (getFront() * STEP);
	}
	if (mBack)
	{
		Pos += (getFront() * -STEP);
	}

	if (mLeft)
	{
		Pos += (getRight() * -STEP);
	}
	if (mRight)
	{
		Pos += (getRight() * STEP);
	}

	if (mUp)
	{
		Pos += (Up * STEP);
	}
	if (mDown)
	{
		Pos += (Up * -STEP);
	}

	glm::mat4 Axis
	{
		Right.x, Right.y, Right.z,	0,
		Up.x,	 Up.y,	  Up.z,		0,
		Front.x, Front.y, Front.z,	0,
		0,		 0,		  0,		1
	};

	glm::mat4 Position
	{
		1, 0, 0, -Pos.x,
		0, 1, 0, -Pos.y,
		0, 0, 1, -Pos.z,
		0, 0, 0, 1
	};

	Position *= Axis;

	View = Position;

	updateVM();
}

void CCamera::rotate()
{
	if (mRotateLeft)
	{
		rotateFront({ 0.f, 0.f, ROTATESTEP });
	}
	if (mRotateRight)
	{
		rotateFront({ 0.f, 0.f, -ROTATESTEP });
	}
}

void CCamera::rotate(glm::vec3 mouseDir)
{
	rotateUp(mouseDir);
	rotateRight(mouseDir);
}

void CCamera::rotateUp(glm::vec3 Dir)
{
	float camcos = cosf(Dir.x / 100.f);
	float camsin = sinf(Dir.x / 100.f);

	glm::mat4 RotX
	{
		camcos,  0.f, camsin,	0.f,
		0.f,	 1.f, 0.f,		0.f,
		-camsin, 0.f, camcos,	0.f,
		0.f,	 0.f, 0.f,		1.f
	};
	View *= RotX;
	updateVM();
}

void CCamera::rotateRight(glm::vec3 Dir)
{
	float camcos = cosf(Dir.y / 100.f);
	float camsin = sinf(Dir.y / 100.f);

	glm::mat4 RotY
	{
		1.f, 0.f,	  0.f,	  0.f,
		0.f, camcos, -camsin, 0.f,
		0.f, camsin, camcos,  0.f,
		0.f, 0.f,	 0.f,	  1.f
	};
	View *= RotY;
	updateVM();
}

void CCamera::rotateFront(glm::vec3 Dir)
{
	float camcos = cosf(Dir.z / 100.f);
	float camsin = sinf(Dir.z / 100.f);

	glm::mat4 RotZ
	{
		camcos, -camsin,	0,	0.f,
		camsin, camcos, 0.f,0.f,
		0.f, 0.f,1.f, 0.f,
		0.f, 0.f,	0.f,	1.f
	};
	View *= RotZ;
	updateVM();
}

void CCamera::getKeyPress(unsigned int key)
{
	//Z Movement
	if (key == 'W')
	{
		mForward = true;
	}
	else if (key == 'S')
	{
		mBack = true;
	}
	//X Movement
	if (key == 'A')
	{
		mLeft = true;
	}
	else if (key == 'D')
	{
		mRight = true;
	}
	//Y Movement
	if (key == 'Q')
	{
		mUp = true;
	}
	else if (key == 'E')
	{
		mDown = true;
	}
	if (key == 37)
	{
		mRotateLeft = true;
	}
	else if (key == 39)
	{
		mRotateRight = true;
	}
}

void CCamera::getKeyRelease(unsigned int key)
{
	if (key == 'W')
	{
		mForward = false;
	}
	else if (key == 'S')
	{
		mBack = false;
	}
	if (key == 'A')
	{
		mLeft = false;
	}
	else if (key == 'D')
	{
		mRight = false;
	}
	if (key == 'Q')
	{
		mUp = false;
	}
	else if (key == 'E')
	{
		mDown = false;
	}
	if (key == 37)
	{
		mRotateLeft = false;
	}
	else if (key == 39)
	{
		mRotateRight = false;
	}
}

void CCamera::setAPIMatrix(CGraphicsAPI* api)
{
	if (api)
	{
		CDXGraphicsAPI* pApi = dynamic_cast<CDXGraphicsAPI*>(api);
		mRowMajor = pApi == nullptr ? false : true;
	}
	else
	{
		OutputDebugStringA("Invalid GraphicsAPI received");
	}
}

glm::mat4 CCamera::getProjection()
{
	if (mRowMajor)
	{
		return glm::transpose(Proj);
	}
	return Proj;
}

glm::mat4 CCamera::getView()
{
	if (!mRowMajor)
	{
		return glm::transpose(View);
	}
	return View;
}

void CCamera::createVM()
{
	setFront(getLAt(), getPos());
	setRight(getUp(), getFront());
	setUp(getFront(), getRight());

	glm::mat4 Axis{
		Right.x, Right.y, Right.z,	0,
		Up.x,	 Up.y,	  Up.z,		0,
		Front.x, Front.y, Front.z,	0,
		0,		 0,		  0,		1
	};

	glm::mat4 Position{
		1, 0, 0, -Pos.x,
		0, 1, 0, -Pos.y,
		0, 0, 1, -Pos.z,
		0, 0, 0, 1
	};
	View = Position * Axis;
}