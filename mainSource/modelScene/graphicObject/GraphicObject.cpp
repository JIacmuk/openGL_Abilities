#include "GraphicObject.h"

GraphicObject::GraphicObject()
{

	this->modelMatrix = new GLfloat[16]{
		1.0, 0.0, 0.0, 0.0, // ось Ox
		0.0, 1.0, 0.0, 0.0, // ось Oy
		0.0, 0.0, 1.0, 0.0, // ось Oz
		0.0, 0.0, 0.0, 1.0  // позиция объекта (начало системы координат)
	};

	this->color = vec3(1, 0, 0);
	this->angle = 0;
}


void GraphicObject::setPosition(vec3 position)
{
	this->position = position;
	//по новой расчитываем матрицу 
	recalculateModelMatrix();
}

vec3 GraphicObject::getPosition()
{
	return this->position;
}

void GraphicObject::setAngle(float grad)
{
	this->angle = grad / 180 * 3.1415;//по новой расчитываем матрицу 
	recalculateModelMatrix();
}

float GraphicObject::getAngle()
{
	return this->angle;
}

void GraphicObject::setСolor(vec3 color) {
	this->color = color;
}

vec3 GraphicObject::getColor()
{
	return this->color;
}

void GraphicObject::setMaterial(shared_ptr<PhongMaterial> material)
{
	this->material = material;
}

void GraphicObject::setMesh(shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

void GraphicObject::draw()
{
	

	//заполняем стек моделей
	glColor3f(color.r, color.g, color.b);

	//заполняем материал при наличии
	if (material != nullptr) {
		material->apply();
	}

	glPushMatrix();
	glMultMatrixf(this->modelMatrix);
	//заполнямем мэш
	if (mesh != nullptr) {
		mesh->draw();
	}
	else {
		glutSolidTeapot(1);
	}
	
	glPopMatrix();
}

void GraphicObject::recalculateModelMatrix()
{
	//изменяем позицию 
	for (int i = 0; i < 3; i++) modelMatrix[12 + i] = position[i];
	//расчитываем угол для вращения относи	тельно оси Y
	modelMatrix[0] = cos(angle);
	modelMatrix[2] = sin(angle);
	modelMatrix[8] = -sin(angle);
	modelMatrix[10] = cos(angle);
}

