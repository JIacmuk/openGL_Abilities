#pragma once
#include "../Header.h"

// КЛАСС ДЛЯ РАБОТЫ С КАМЕРОЙ
class Camera
{
public:
	// конструкторы
	Camera();
	Camera(vec3 positiююon);
	Camera(float x, float y, float z);
	// установка и получение позиции камеры
	void setPosition(vec3 position);
	vec3 getPosition();
	//функции для перемещения камеры
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);
	// функция для установки матрицы камеры
	void apply();
private:
	// перерасчет позиции камеры после поворотов
	void recalculatePosition();
private:
	// сфеерические координаты
	float r; // радиус тут и так ясно
	float angleX; // угол фи
	float angleY; // угол тета
	// декартовые координаты
	vec3 position;
};

