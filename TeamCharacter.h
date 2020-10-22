#pragma once
#include "Character.h"
#include "primitive_builder.h"
#include "Player.h"


//class Player;
enum CharacterClass {PRIEST, RANGER, WARRIOR, PALADIN, SHAMAN};

class TeamCharacter :
	public Character
{
public:
	TeamCharacter();
	~TeamCharacter();
	Character* playertest;

	void activateOffensiveAbilty();
	void activateDefensiveAbility();
	void initObject(PrimitiveBuilder* primitiveBuilder, gef::Vector4 scale);
	void initPriest(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform);
	void initRanger(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform);
	void initWarrior(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform);
	void initPaladin(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform);
	void initShaman(Player* player_, PrimitiveBuilder* primitiveBuilder, gef::Platform& platform);

private:

	CharacterClass characterClass;
	Player* player;
	bool abilityType; //True for Offensive & false fo Defensive
	gef::Material* colourMaterial2;

	const char * offensiveText;
	const char * defensiveText;
	const char * classText;
	bool offensive;
public:

	bool getOffensive() { return offensive; }
	const char * getOffensiveText() { return offensiveText; }
	const char * getDefensiveText() { return defensiveText; }
	const char * getClassText() { return classText; }
	gef::Material* getColourMaterial() { return colourMaterial; }
};

