#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STEP 0.025f
#define ROTATESTEP 0.25f

class CGraphicsAPI;

/**	\struct CameraDesc
*	\brief Structure which defines the required attributes to initialize a Camera
*/
struct CameraDesc
{
	// Minimum variables required to generate camera's VM
	glm::vec3 Pos;		/**< Vec3 for Position */
	// Variables to generate PM
	float FOV;			/**< float Field Of View value */
	float Width;		/**< float variable */
	float Height;		/**< float variable */
};

/** \class CCamera
*	\brief Class which contains functions and members for camera creation/usage.
*/
class CCamera
{
public:

	CCamera();
	~CCamera();

	int init(CameraDesc Ref);
	/** \fn void init(CameraDesc Ref)
	*	\brief Receives a CameraDesc to copy its values and calculate new vectors.
	*	@param[in] Ref CameraDesc with the desired information.
	*	\return a int indicating if the operation was succesfull.
	*/
	//Setters

	void setPos(glm::vec3 rPos);
	/** \fn void setPos(glm::vec3 rPos)
	*	\brief Sets Camera position vector value
	*	@param[in] rPos Vec3 with data
	*/

	void setLAt(glm::vec3 rLAt);
	/** \fn setLAt(glm::vec3 rLAt)
	*	\brief Sets Camera look at vector value
	*	@param[in] rLAt Vec3 with data
	*/

	void setUp(glm::vec3 rUp);
	/** \fn void setUp(glm::vec3 rUp)
	*	\brief Sets Camera reference up vector value
	*	@param[in] rUp Vec3 with data
	*/

	void setFront(glm::vec3 rAt, glm::vec3 rPos);
	/** \fn void setFront(glm::vec3 rAt, glm::vec3 rPos)
	*	\brief Calculates Camera front vector and sets it
	*	@param[in] rAt Vec3 with LookAt vector value
	*	@param[in] rPos Vec3 with Position vector value
	*/

	void setRight(glm::vec3 rUp, glm::vec3 rFront);
	/** \fn void setRight(glm::vec3 rUp, glm::vec3 rFront)
	*	\brief Calculates Camera Right vector and sets it
	*	@param[in] rUp Vec3 with Up vector value
	*	@param[in] rFront Vec3 with Front vector value
	*/

	void setUp(glm::vec3 rFront, glm::vec3 rRight);
	/** \fn void setUp(glm::vec3 rFront, glm::vec3 rRight)
	*	\brief Calculates true Up vector and sets it
	*	@param[in] rFront Vec3 with Front vector value
	*	@param[in] rRight Vec3 with Right vector value
	*/

	void setFOV(float rFOV);
	/** \fn void setFOV(float rFOV)
	*	\brief Sets Camera FOV
	*	@param[in] rFOV float with value
	*/

	void setWidth(float rWidth);
	/** \fn void setWidth(float rWidth)
	*	\brief Sets Camera Width for PM
	*	@param[in] rWidth float with value
	*/

	void setHeigth(float rHeigth);
	/** \fn void setHeigth(float rHeigth)
	*	\brief Sets Camera Height for PM
	*	@param[in] rHeight float with value
	*/

	void setNear(float rNear);
	/** \fn void setNear(float rNear)
	*	\brief Sets Camera Near Plane for PM
	*	@param[in] rNear float with value
	*/

	void setFar(float rFar);
	/** \fn void setFar(float rFar)
	*	\brief Sets Camera Far Plane for PM
	*	@param[in] rFar float with value
	*/

	/**	\fn void setInitPos(glm::vec3 rPosition)
	*	\brief Stores the cursor initial position onscreen.
	*	@param[in] rPosition glm::vec3 with value.
	*/
	void setInitPos(glm::vec3 rPosition);

	/** \fn void setEndPos(glm::vec3 rPosition)
	*	\brief Stores the cursor final position onscreen.
	*	@param[in] rPosition glm::vec3 with value.
	*/
	void setEndPos(glm::vec3 rPosition);

	/** \fn void setClicked(float rClick)
	*	\brief Stores the cursor clicked state.
	*	@param[in] rClick bool with value.
	*/
	void setClicked(float rClick);

	//Getters

	glm::vec3 getPos();
	/** \fn glm::vec3 getPos()
	*	\brief Obtains Position
	*	\return a Vec3 with Camera's position
	*/

	glm::vec3 getLAt();
	/** \fn glm::vec3 getLAt()
	*	\brief Obtains Look At
	*	\return a Vec3 with Camera's Look At vector
	*/

	glm::vec3 getUp();
	/** \fn glm::vec3 getUp()
	*	\brief Obtains real Up
	*	\return a Vec3 with Camera's Up vector
	*/

	glm::vec3 getFront();
	/** \fn glm::vec3 getFront()
	*	\brief Obtains Front
	*	\return a Vec3 with Camera's Front vector
	*/

	glm::vec3 getRight();
	/** \fn glm::vec3 getRight()
	*	\brief Obtains Right
	*	\return a Vec3 with Camera's Right vector
	*/

	float getFOV();
	/** \fn float getFOV()
	*	\brief Obtains FOV
	*	\return a float with Camera's FOV value for PM
	*/

	float getWidth();
	/** \fn float getWidth()
	*	\brief Obtains Width
	*	\return a float with Camera's Width value for PM
	*/

	float getHeigth();
	/** \fn float getHeigth()
	*	\brief Obtains Height
	*	\return a float with Camera's Heigth value for PM
	*/

	float getNear();
	/** \fn float getNear()
	*	\brief Obtains Near Plane
	*	\return a float with Camera's Near Plane value for PM
	*/

	float getFar();
	/** \fn float getFar()
	*	\brief Obtains Far Plane
	*	\return a float with Camera's Far Plane value for PM
	*/

	/** \fn glm::vec3 getInitPos()
	*	\brief Obtains the camera's mouse initial position vector
	*	\return A glm::vec3 with position info.
	*/
	glm::vec3 getInitPos();

	/**	\fn glm::vec3 getEndPos()
	*	\breif Obtains the camera's mouse end position vector.
	*	\return A glm::vec3 with position info.
	*/
	glm::vec3 getEndPos();

	/**	\fn bool getClicked()
	*	\brief Obtains the camera's mouse clicked state.
	*	\return A bool with indicates if mouse was clicked or not.
	*/
	bool getClicked();

	//Methods

	virtual void updateVM();
	/** \fn virtual void updateVM()
	*	\brief Updates Free Camera View Matrix
	*/

	void updatePM();
	/** \fn void updatePM()
	*	\brief Updates Free Camera Projection Matrix
	*/

	virtual void move();
	/** \fn virtual void move()
	*	\brief Modifies Pos depending in which direction the Camera is moving
	*
	*	Can move Left, Right, Up, Down, Forward, Backward
	*/

	void rotate();
	/** \fn void rotate()
	*	\brief Rotates the Camera in the Z axis (Roll) depending on the input
	*/

	void rotatePitchYaw();
	/** \fn void rotatePitchYaw()
	*	\brief Rotates the Camera in the X and Y axis (Pitch & Yaw) depending 
	*	on the direction result from substracting mEndPos from mInitPos.
	*/

	void rotateUp(glm::vec3 Dir);
	/** \fn void rotateUp(glm::vec3 Dir)
	*	\brief Rotates the Camera from its Up vector depending on a direction
	*	@param[in] Dir Vec3 with Direction value
	*
	*	Can rotate 360°.
	*/

	virtual void rotateRight(glm::vec3 Dir);
	/** \fn virtual void rotateRight(glm::vec3 Dir)
	*	\brief Rotates the Camera from its Right vector depending on a direction
	*	@param[in] Dir Vec3 with Direction Value
	*
	*	Can rotate 360°.
	*/

	virtual void rotateFront(glm::vec3 Dir);
	/** \fn virtual void rotateFront(glm::vec3 Dir)
	*	\brief Rotates the Camera from its Front vector depending on a direction
	*	@param[in] Dir Vec3 with Direction value
	*
	*	Can rotate 360°.
	*/

	void createVM();
	/** \fn void createVM()
	*	\brief Creates a View Matrix from the required vectors
	*/

	void getKeyPress(unsigned int key);
	/** \fn void getKeyPress(unsigned int key)
	*	\brief Process the pressed key value received and determine corresponding action
	*	@param[in] key Value of key pressed
	*
	*	Detects W, A, S, D, Q, E, Left Arrow & Right Arrow keys.
	*/

	void getKeyRelease(unsigned int key);
	/** \fn void getKeyRelease(unsigned int key)
	*	\brief Process the released key value received and determine corresponding action
	*	@param[in] key Value of key released
	*
	*	Detects W, A, S, D, Q, E, Left Arrow & Right Arrow keys.
	*/


	glm::mat4 getProjection();

	glm::mat4 getView();	

private:

	glm::vec3 Pos;		/**< Vec3 for Position */
	glm::vec3 LAt;		/**< Vec3 for LookAt */
	glm::vec3 Up;		/**< Vec3 for Up */

	glm::vec3 Front;	/**< Vec3 for Front */
	glm::vec3 Right;	/**< Vec3 for Right */
	
	float m_fNearPlane;	/**< float variable */
	float m_fFarPlane;		/**< float variable */
	float m_fFOV;			/**< float Field Of View value */
	float m_fWidth;		/**< float variable */
	float m_fHeight;		/**< float variable */

	glm::mat4 m_View;		/**< Mat4 for View */
	glm::mat4 m_Proj;		/**< Mat4 for Projection */
	
	glm::vec3 mInitPos;	/**< Vec3 for mouse initial position */
	glm::vec3 mEndPos;	/**< Vec3 for mouse final position */
	bool m_bIsClicked;	/**< bool to determine if mouse's right click is pressed */
	glm::vec3 mDir;		/**< Vec3 for mouse direction */
	
	bool m_bForward;		/**< bool to determine if camera is moving forward */
	bool m_bBack;			/**< bool to determine if camera is moving backwards */
	bool m_bLeft;			/**< bool to determine if camera is moving left */
	bool m_bRight;		/**< bool to determine if camera is moving right */
	bool m_bUp;			/**< bool to determine if camera is moving up */
	bool m_bDown;			/**< bool to determine if camera is moving down */
	bool m_bRotateLeft;	/**< bool to determine if camera is rotating counter clock wise*/
	bool m_bRotateRight;	/**< bool to determine if camera is rotating clock wise */
};