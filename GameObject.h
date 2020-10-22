#pragma once
#include <graphics/mesh_instance.h>


namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class Scene;
	class Skeleton;
	class InputManager;
}

class GameObject : public gef::MeshInstance
{
public:
	GameObject();
	~GameObject();

	void init();
	void update(float deltaTime);

	
	gef::Vector4 getVelocity() { return velocity; }
	void setVelocity(float x, float y, float z);
	void resetVelocity();

	void setPosition(float x, float y, float z);
	gef::Vector4 getPosition() { return position; }

	void setScale(float x, float y, float z);
	gef::Vector4 getScale() { return scale; }

	void movement(gef::InputManager* input_manager_);

	void moveLeft(float movementSpeed, float deltaTime);
	void moveRight(float movementSpeed, float deltaTime);
	void moveUp(float movementSpeed, float deltaTime);
	void moveDown(float movementSpeed, float deltaTime);

	void buildTransform();

	bool isAlive() { return isObjectAlive; }
	void setIsAlive(bool flag) { isObjectAlive = flag; }

	void setLocalTransform(gef::Matrix44 transform) { localTransform = transform; }
	gef::Matrix44 getLocalTransform() { return localTransform; }

private:
	
	gef::Vector4 velocity;
	gef::Vector4 position;
	gef::Vector4 scale;
	gef::Vector4 rotation;

	gef::Matrix44 localTransform;

	bool isObjectAlive;

protected:


};

