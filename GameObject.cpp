#include "GameObject.h"
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>


GameObject::GameObject() :
	MeshInstance()
{
}


GameObject::~GameObject()
{
}

/**
	Initialise the GameObject variables: Position, Scale, Rotation.
*/
void GameObject::init()
{
	resetVelocity();

	position.set_x(0);
	position.set_y(0);
	position.set_z(0);
	position.set_w(0);

	scale.set_x(1);
	scale.set_y(1);
	scale.set_z(1);
	scale.set_w(0);

	isObjectAlive = true;
}

//3078

/**
	The Update function for the objects 
	@param float for delta time, used for frame calculations.
	@warning Not virtual so any child classes must create a new update or an overloaded one.
*/
void GameObject::update(float deltaTime)
{
	position += velocity * deltaTime;
	buildTransform();
	//resetVelocity();
}

/**
	Set the velocity values of the object.
	@param floats for X, Y and Z velocity.
*/
void GameObject::setVelocity(float x, float y, float z)
{
	velocity.set_x(x);
	velocity.set_y(y);
	velocity.set_z(z);
}

/**
	Reset the velocity variables to zero.
*/
void GameObject::resetVelocity()
{
	velocity.set_x(0);
	velocity.set_y(0);
	velocity.set_z(0);
	velocity.set_w(0);
}

/**
	Set the position values of the object.
	@param floats for X, Y and Z position.
*/
void GameObject::setPosition(float x, float y, float z)
{
	position.set_x(x);
	position.set_y(y);
	position.set_z(z);
}

/**
	Set the scale of the object.
	@param floats for the X, Y and Z values for scale.
*/
void GameObject::setScale(float x, float y, float z)
{
	scale.set_x(x);
	scale.set_y(y);
	scale.set_z(z);
}

/**
	movement function for any basic object movement required.
*/
void GameObject::movement(gef::InputManager* input_manager_)
{
	// controller input
	gef::SonyControllerInputManager* controller_manager = input_manager_->controller_input();
	if (controller_manager)
	{
		const gef::SonyController* controller = controller_manager->GetController(0);

		if (controller->buttons_pressed() & gef_SONY_CTRL_LEFT) {
			velocity.set_x(-.005);
		
		}
		else if (controller->buttons_pressed() & gef_SONY_CTRL_RIGHT) {
			velocity.set_x(.005);

		}
		else {
			velocity.set_x(0);
		}
	}
}

/**
	Move the object along X axis by altering the X velocity in the negative.
	@param Float for movement speed.
	@param Float for delta time to be passed in.
*/
void GameObject::moveLeft(float movementSpeed, float deltaTime)
{
	velocity.set_x(-(movementSpeed * deltaTime));
}

/**
	Move the object along X axis by altering the X velocity in the positive.
	@param Float for movement speed.
	@param Float for delta time to be passed in.
*/
void GameObject::moveRight(float movementSpeed, float deltaTime)
{
	velocity.set_x(movementSpeed * deltaTime);
}

/**
	Move the object along the Y axis by altering the Y velocity in the positive.
	@param Float for movement speed.
	@param Float for delta time to be passed in.
*/
void GameObject::moveUp(float movementSpeed, float deltaTime)
{
	velocity.set_y(movementSpeed * deltaTime);
}

/**
	Move the object along the Y axis by altering the Y velocity in the negative.
	@param Float for movement speed.
	@param Float for delta time to be passed in.
*/
void GameObject::moveDown(float movementSpeed, float deltaTime)
{
	velocity.set_y(-(movementSpeed * deltaTime));
}

/**
	Basic build transorm function to build the local tansform matrix. 
*/
void GameObject::buildTransform()
{
	//transform_.SetIdentity();
	//transform_.Scale(scale);
	//transform_.SetTranslation(position);
	
	localTransform.SetIdentity();
	localTransform.Scale(scale);
	localTransform.SetTranslation(position);

	
}


