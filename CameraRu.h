#pragma once
#include <system/platform.h>
#include <maths/math_utils.h>
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}
class Camera
{
public:
	Camera();
	~Camera();

	void init();
	void update();
	

	void setLookAt(gef::Vector4 lookValues) { lookAtvector = lookValues; }
	gef::Vector4 getLookAtVector() { return lookAtVector; }

	void setEye(gef::Vector4 eyeValues) { eyeVector = eyeValues; }
	gef::Vector4 getEyeVector() { return eyeVector; }

	void setUp(gef::Vector4 upValues) { upVector = upValues; }
	gef::Vector4 getUpVector() { return upVector; }

	void moveLeft(float movementSpeed);
	void moveRight(float movementSpeed);
	void moveForward(float movementSpeed);
	void moveBackwards(float movementSpeed);

	void setFOV(float fov_) { fov = fov_; }
	float getFOV() { return fov; }

	void setNearPlane(float nearPlane_) { nearPlane = nearPlane_; }
	float getNearPlane() { return nearPlane; }

	void setFarPlane(float farPlane_) { farPlane = farPlane_; }
	float getFarPlane() { return farPlane; }

private:
	gef::Vector4 lookAtVector;
	gef::Vector4 eyeVector;
	gef::Vector4 upVector;
	gef::Vector4 forwardVector;
	gef::Vector4 strafeVector;

	float fov;
	float nearPlane;
	float farPlane;
};

