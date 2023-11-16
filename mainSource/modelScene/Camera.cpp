#include "Camera.h"
#define CORRECTION 3.14159265 / 180
Camera::Camera()
{
	setPosition(vec3(0, 0, 0));
}

Camera::Camera(vec3 position)
{
	setPosition(position);
}

Camera::Camera(float x, float y, float z)
{
	setPosition(vec3(x, y, z));
}

void Camera::setPosition(vec3 position)
{
	//пересчитываем сфеерические координаты
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(position);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = 90 - degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}

vec3 Camera::getPosition()
{
	return this->position;
}

void Camera::rotateLeftRight(float degree)
{
	angleX += degree;
	if (angleX >= 360) angleX -= 360;
	if (angleX <= -360) angleX += 360;
	recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{	
	angleY -= degree;
	if (angleY < 5) angleY = 5;
	if (angleY > 90) angleY = 90;	 
	recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
	r -= distance;
	recalculatePosition();
}

void Camera::apply()

{
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalculatePosition()
{
	position.x = r * sin(angleY * CORRECTION) * cos(angleX * CORRECTION);
	position.z = r * sin(angleY * CORRECTION) * sin(angleX * CORRECTION);
	position.y = r * cos(angleY * CORRECTION);
	//cout << position.x << " " << position.y << " " << position.z << endl;
}