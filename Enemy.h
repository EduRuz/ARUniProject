#pragma once
#include "Character.h"
#include "primitive_builder.h"

class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();

	void initFirstBoss(PrimitiveBuilder* primitiveBuilder, gef::Platform& platform);
	
private:
	void initBossVariables();


};

