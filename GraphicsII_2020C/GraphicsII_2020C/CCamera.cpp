#include "CCamera.h"
#include "CDXGraphicsAPI.h"

CCamera::CCamera()
{
	m_bIsClicked = false;
	m_bForward = false;
	m_bBack = false;
	m_bLeft = false;
	m_bRight = false;
	m_bUp = false;
	m_bDown = false;
	m_bRotateLeft = false;
	m_bRotateRight = false;
}

CCamera::~CCamera() {}

int CCamera::init(CameraDesc Ref)
{
	//Set common values
	setPos(Ref.Pos);
	setLAt({0.f, 2.f, -5.f});
	setUp({0.f, 1.f, 0.f});
	setFOV(glm::radians(std::clamp<float>(Ref.FOV, 40.f, 90.f)));
	setWidth(Ref.Width);
	setHeigth(Ref.Height);
	setNear(0.01f);
	setFar(100.f);

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
	Up = glm::cross(Front, Right);
}

void CCamera::setFOV(float rFOV)
{
	m_fFOV = rFOV;
}

void CCamera::setWidth(float rWidth)
{
	m_fWidth = rWidth;
}

void CCamera::setHeigth(float rHeigth)
{
	m_fHeight = rHeigth;
}

void CCamera::setNear(float rNear)
{
	m_fNearPlane = rNear;
}

void CCamera::setFar(float rFar)
{
	m_fFarPlane = rFar;
}

void CCamera::setInitPos(glm::vec3 rPosition)
{
	mInitPos = rPosition;
}

void CCamera::setEndPos(glm::vec3 rPosition)
{
	mEndPos = rPosition;
}

void CCamera::setClicked(float rClick)
{
	m_bIsClicked = rClick;
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
	return m_fFOV;
}

float CCamera::getWidth()
{
	return m_fWidth;
}

float CCamera::getHeigth()
{
	return m_fHeight;
}

float CCamera::getNear()
{
	return m_fNearPlane;
}

float CCamera::getFar()
{
	return m_fFarPlane;
}

glm::vec3 CCamera::getFront()
{
	return Front;
}

glm::vec3 CCamera::getRight()
{
	return Right;
}

glm::vec3 CCamera::getInitPos()
{
	return mInitPos;
}

glm::vec3 CCamera::getEndPos()
{
	return mEndPos;
}

bool CCamera::getClicked()
{
	return m_bIsClicked;
}

void CCamera::updateVM()
{
	Right = { m_View[0][0], m_View[1][0], m_View[2][0] };
	Up =	{ m_View[0][1], m_View[1][1], m_View[2][1] };
	Front = { m_View[0][2], m_View[1][2], m_View[2][2] };
	LAt = Front + Pos;
}

void CCamera::updatePM()
{
	m_Proj = glm::perspectiveFovLH(m_fFOV,
		m_fWidth,
		m_fHeight,
		m_fNearPlane,
		m_fFarPlane);
}

void CCamera::move()
{
	if (m_bForward)
	{
		Pos += (Front * STEP);
	}
	if (m_bBack)
	{
		Pos += (Front * -STEP);
	}

	if (m_bLeft)
	{
		Pos += (Right * -STEP);
	}
	if (m_bRight)
	{
		Pos += (Right * STEP);
	}

	if (m_bUp)
	{
		Pos += (Up * STEP);
	}
	if (m_bDown)
	{
		Pos += (Up * -STEP);
	}

	glm::mat4 Axis{
		Right.x, Up.x, Front.x,	0,
		Right.y, Up.y, Front.y,	0,
		Right.z, Up.z, Front.z,	0,
		0,		 0,	   0,		1
	};

	glm::mat4 Position{
		1,		0,		0,		0,
		0,		1,		0,		0,
		0,		0,		1,		0,
		-Pos.x, -Pos.y, -Pos.z, 1
	};

	m_View = Axis * Position;

	updateVM();
}

void CCamera::rotate()
{
	if (m_bRotateLeft)
	{
		rotateFront({ 0.f, 0.f, ROTATESTEP });
	}
	if (m_bRotateRight)
	{
		rotateFront({ 0.f, 0.f, -ROTATESTEP });
	}
}

void CCamera::rotatePitchYaw()
{
	mDir = mInitPos - mEndPos;
	rotateUp(mDir);
	rotateRight(mDir);
}

void CCamera::rotateUp(glm::vec3 Dir)
{
	float camcos = cosf(Dir.x / 100.f);
	float camsin = sinf(Dir.x / 100.f);

	glm::mat4 RotX
	{
		camcos,  0.f, -camsin,	0.f,
		0.f,	 1.f, 0.f,		0.f,
		camsin, 0.f, camcos,	0.f,
		0.f,	 0.f, 0.f,		1.f
	};
	m_View *= RotX;
	updateVM();
}

void CCamera::rotateRight(glm::vec3 Dir)
{
	float camcos = cosf(Dir.y / 100.f);
	float camsin = sinf(Dir.y / 100.f);

	glm::mat4 RotY
	{
		1.f, 0.f,	  0.f,	  0.f,
		0.f, camcos, camsin, 0.f,
		0.f, -camsin, camcos,  0.f,
		0.f, 0.f,	 0.f,	  1.f
	};
	m_View *= RotY;
	updateVM();
}

void CCamera::rotateFront(glm::vec3 Dir)
{
	float camcos = cosf(Dir.z / 100.f);
	float camsin = sinf(Dir.z / 100.f);

	glm::mat4 RotZ
	{
		camcos, camsin,	0,	0.f,
		-camsin, camcos, 0.f,0.f,
		0.f, 0.f,1.f, 0.f,
		0.f, 0.f,	0.f,	1.f
	};
	m_View *= RotZ;
	updateVM();
}

void CCamera::getKeyPress(unsigned int key)
{
	//Z Movement
	if (key == 'W')
	{
		m_bForward = true;
	}
	else if (key == 'S')
	{
		m_bBack = true;
	}
	//X Movement
	if (key == 'A')
	{
		m_bLeft = true;
	}
	else if (key == 'D')
	{
		m_bRight = true;
	}
	//Y Movement
	if (key == 'Q')
	{
		m_bUp = true;
	}
	else if (key == 'E')
	{
		m_bDown = true;
	}
	if (key == 37)
	{
		m_bRotateLeft = true;
	}
	else if (key == 39)
	{
		m_bRotateRight = true;
	}
}

void CCamera::getKeyRelease(unsigned int key)
{
	if (key == 'W')
	{
		m_bForward = false;
	}
	else if (key == 'S')
	{
		m_bBack = false;
	}
	if (key == 'A')
	{
		m_bLeft = false;
	}
	else if (key == 'D')
	{
		m_bRight = false;
	}
	if (key == 'Q')
	{
		m_bUp = false;
	}
	else if (key == 'E')
	{
		m_bDown = false;
	}
	if (key == 37)
	{
		m_bRotateLeft = false;
	}
	else if (key == 39)
	{
		m_bRotateRight = false;
	}
}

glm::mat4 CCamera::getProjection()
{
	return m_Proj;
}

glm::mat4 CCamera::getView()
{
	return m_View;
}

void CCamera::createVM()
{
	setFront(getLAt(), getPos());
	setRight(getUp(), getFront());
	setUp(getFront(), getRight());

	glm::mat4 Axis{
		Right.x, Up.x, Front.x,	0,
		Right.y, Up.y, Front.y,	0,
		Right.z, Up.z, Front.z,	0,
		0,		 0,	   0,		1
	};

	glm::mat4 Position{
		1,		0,		0,		0,
		0,		1,		0,		0,
		0,		0,		1,		0,
		-Pos.x, -Pos.y, -Pos.z, 1
	};

	m_View = Axis * Position;
}