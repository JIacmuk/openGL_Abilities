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

void GameObject::setPosition(int x, int y, float z)
{
	this->position = vec2(x, y);
	graphicObject.setPosition(vec3(x - 10, z, y - 10));
}

void GameObject::setPosition(ivec2 position)
{
	this->position = position;
	graphicObject.setPosition(vec3(position[0] - 10, 0, position[1] - 10));
}

ivec2 GameObject::getPosition()
{
	return position;
}

void GameObject::move(MoveDirection direction, float speed)
{	
	//провер€ем, что объект не движетс€
	
	if (isMoving()) return;
	this->sost = direction;
	this->speed = speed;
}

bool GameObject::isMoving()
{
	if(progress > 0) return true;
	return false;
}

void GameObject::simulate(float sec)
{
	//определ€ем скорость передвижени€ 
	float currentMoveSpeed = speed * sec / 1000;
	//определ€ем следующую €чейку дл€ движени€
	vec2 nextPosition;
	switch (sost)
	{
	case MoveDirection::STOP:
		nextPosition = vec2(0, 0);
		break;
	case MoveDirection::LEFT:
		nextPosition = vec2(-1, 0);
		break;
	case MoveDirection::RIGHT:
		nextPosition = vec2(1, 0);
		break;
	case MoveDirection::UP:
		nextPosition = vec2(0, -1);
		break;
	case MoveDirection::DOWN:
		nextPosition = vec2(0, 1);
		break;
	}
	//сохран€ем прогресс
	if(sost != MoveDirection::STOP) progress += currentMoveSpeed;
	//провер€ем заполнение
	if (progress >= 1) {
		position = vec2(position[0] + nextPosition[0], position[1] + nextPosition[1]);
		sost = MoveDirection::STOP;
		progress = 0;
	}
	graphicObject.setPosition(vec3(position[0] + (nextPosition[0] * progress) - 10, 0, position[1] + (nextPosition[1] * progress) - 10));;
}

void GameObject::draw(void)
{
	graphicObject.draw();
}
