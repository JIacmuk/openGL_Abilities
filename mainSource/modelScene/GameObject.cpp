#include "GameObject.h"

GameObject::GameObject()
{

}

void GameObject::setGraphicObject(const GraphicObject& graphicObject)
{
	this->graphicObject = graphicObject;
}

void GameObject::setPosition(int x, int y)
{
	this->position = vec2(x, y);
	graphicObject.setPosition(vec3(x - 10, 0, y - 10));
}

void GameObject::setPosition(ivec2 position)
{
	this->position = position;
	graphicObject.setPosition(vec3(position[0] - 10, 0, position[1] - 10));
}

ivec2 GameObject::getPosition()
{
	return ivec2();
}

void GameObject::draw(void)
{
	graphicObject.draw();
}
