#pragma once
#include "GameObject.h"

const int CHIP_WIDTH = 80;
const int CHIP_HEIGHT = 70;

class Chip : public GameObject
{
public:
	Chip(int xPos, int yPos);
	~Chip();

	void update() override;
	void render() override;
};

