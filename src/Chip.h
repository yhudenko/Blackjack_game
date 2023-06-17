#pragma once
#include "GameObject.h"

class Chip : public GameObject
{
public:
	Chip(int xPos, int yPos);
	~Chip();

	void update() override;
	void render() override;
};

