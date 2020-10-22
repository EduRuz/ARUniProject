#pragma once
#include "Character.h"
#include "primitive_builder.h"
#include <vector>
//#include "TeamCharacter.h"

class TeamCharacter;

class Player :
	public Character
{
public:
	Player();
	~Player();

	void initPlayer(PrimitiveBuilder* primitiveBuilder, gef::Platform& platform);
	void updatePlayer(std::vector<TeamCharacter*> teamChars, float fps);
	void initVariables();
	void resetBuffs();
	void buffPlayer();

private:
	float buffedHealth = 0;
	float buffedShield = 0;
	float buffedAttackVal = 0;
	float buffedHealingPerRound = 0;
	float buffedSpeed = 0;


public:



	float getBuffedHealth() { return buffedHealth; }
	void setBuffedHealth(float val) { buffedHealth = val; }

	float getBuffedShield() { return buffedShield; }
	void setBuffedShield(float val) { buffedShield = val; }

	float getBuffedAttack() { return buffedAttackVal; }
	void setBuffedAttack(float val) { buffedAttackVal = val; }

	float getBuffedHealing() { return buffedHealingPerRound; }
	void setBuffedHealing(float val) { buffedHealingPerRound = val; }

	float getBuffedSpeed() { return buffedSpeed; }
	void setBuffedSpeed(float val) { buffedSpeed = val; }

};

