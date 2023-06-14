#include "BaseObject.h"

BaseObject::BaseObject(SDL_Rect* rect) : objRect(rect)
{
	
}

BaseObject::~BaseObject()
{
	delete objRect;
}
