/*
	Basic Camera Class for 3D Scenes. Needs much implemented.
	@Author Ruaraidh Canaway
*/
#include "CameraRu.h"

Camera::Camera()
{

}


Camera::~Camera()
{
}

/**
	initializes camera variables to default.
	TODO Make Overloaded version that lets user input values.
*/
void Camera::init()
{
	lookAtVector.set_value(0.0f, 0.0f, 0.0f);
	eyeVector.set_value(0.0f, 0.0f, 750.0f);
	upVector.set_value(0.0f, 1.0f, 0.0f);

	fov = gef::DegToRad(45.0f);
	nearPlane = 0.01f;
	farPlane = 100.f;
}

/**
	Updates the camera variables for movement.
*/
void Camera::update()
{
	forwardVector.set_x((lookAtVector.x() - eyeVector.x()));
	forwardVector.set_y((lookAtVector.y() - eyeVector.y()));
	forwardVector.set_z((lookAtVector.z() - eyeVector.z()));

	strafeVector = forwardVector.CrossProduct(upVector);
}

/**
	Move the Camera left.
*/
void Camera::moveLeft(float movementSpeed)
{
	eyeVector -= strafeVector * movementSpeed;
	lookAtVector -= strafeVector * movementSpeed;
}

/**
	Move the Camera right.
*/
void Camera::moveRight(float movementSpeed)
{
	eyeVector += strafeVector * movementSpeed;
	lookAtVector += strafeVector * movementSpeed;
}

/**
	Move the Camera Forward.
*/
void Camera::moveForward(float movementSpeed)
{
	eyeVector += forwardVector * movementSpeed;
	lookAtVector += forwardVector * movementSpeed;
}

/**
	Move the Camera Backwards.
*/
void Camera::moveBackwards(float movementSpeed)
{
	eyeVector -= forwardVector * movementSpeed;
	lookAtVector -= forwardVector * movementSpeed;
}

