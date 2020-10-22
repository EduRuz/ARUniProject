#pragma once
#include "GameObject.h"
#include <graphics/mesh_instance.h>
#include <graphics/primitive.h>
#include <graphics\material.h>
#include <graphics/mesh.h>
#include <graphics/scene.h>

class Character :
	public GameObject
{
public:
	Character();
	~Character();

	//virtual void update(float deltaTime) {}
	void sharedUpdate();
	void cleanUp();

	int getMarkerCode() { return markerCode; }
	bool getMarkerFound() { return markerFound; }
	void setMarkerFound(bool flag);

	gef::Matrix44 getMarkerTransform() { return markertransform; }
	void setMarkerTransform(gef::Matrix44 matrix) { markertransform = matrix; }
	
	void dealDamage(float damage) { currHealth -= damage; }
	void restoreHealth(float heal) { currHealth += heal; }


private:

protected:
	float level = 1;

	float maxHealth;
	float shield;
	float attackVal;
	float healingPerRound;
	float speed;

	float currHealth;
	float currShield;
	float currAttackVal;
	float currHealingPerRound;
	float currSpeed;

	float currVitality;
	bool alive;

	gef::Material* colourMaterial;

	bool markerFound;
	int markerCode;
	gef::Matrix44 markertransform;

	void setUpCurrentVals();

	gef::Scene* model;
	class gef::Mesh* sceneMesh;
	gef::Mesh* getFirstMesh(gef::Scene* scene, gef::Platform& platform);
public:
	//Getter & Setters

	float getLevel() { return level; }

	float getCurrHealth() { return currHealth; }//New and better
	float getCurrAttack() { return currAttackVal; }
	float getCurrHealing() { return currHealingPerRound; }

	float getCurrVitality() { return currVitality; }
	void setCurrHealth(float health) { currHealth = health; }

	float getMaxHealth() { return maxHealth; }
	void setMaxHealth(float max) { maxHealth = max; }

	float getShield() { return shield; }
	void setShield(float shield_) { shield = shield_; }

	float getAttack() { return attackVal;}
	void setAttack(float att) { attackVal = att; }

	float getHealing() { return healingPerRound; }
	void setHealing(float heal) { healingPerRound = heal; }

	float getSpeed() { return speed; }
	void setSpeed(float spd) { speed = spd; }

	float getAlive() { return alive; }
	void setAlive(bool flag) { alive = flag; }

};

