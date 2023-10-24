#pragma once
#include "../../Header.h"
#include "graphicObjectComponents/Material.h"
#include "graphicObjectComponents/Mesh.h"
#include "graphicObjectComponents/Texture.h"

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject
{
public:
	// Конструктор
	GraphicObject();
	// Установка и получение позиции объекта
	void setPosition(vec3 position);
	vec3 getPosition();
	// Установка и получения угла поворота в градусах
	// поворот осуществляется в горизонтальной плоскости
	// вокруг оси Oy по часовой стрелке
	void setAngle(float grad);
	float getAngle();

	// Установка текущего цвета объекта
	void setСolor(vec3 color);
	vec3 getColor();
	// Установка используемого материала
	void setMaterial(shared_ptr<Material> material);
	// Установка используемого меша

	void setMesh(shared_ptr<Mesh> mesh);
	// Вывести объект
	void draw();
private:
	// Позиция объекта в глобальной системе координат
	vec3 position;
	// Угол поворота в горизонтальной плоскости (в градусах)
	float angle;
	// Цвет модели
	vec3 color;
	// Матрица модели (расположение объекта) - чтоб не вычислять каждый раз
	GLfloat* modelMatrix;
	// Используемый материал
	shared_ptr<Material> material;
	// Используемый мэш
	shared_ptr<Mesh> mesh;
private:
	// расчет матрицы modelMatrix на основе position и angle
	void recalculateModelMatrix();
};
