#pragma once
#include "../../../Header.h"

struct Vertex
{
	// геометрические координаты
	GLfloat coord[3];
	// вектор нормали
	GLfloat normal[3];
	// текстурные координаты нулевого текстурного блока
	GLfloat texCoord[2];
};

// КЛАСС ДЛЯ РАБОТЫ C МЕШЕМ
class Mesh
{
public:
	// конструктор
	Mesh();
	Mesh(string filename);
	// загрузка меша из файла с указанным именем
	void load(string filename);
	// вывод меша (передача всех вершин в OpenGL)
	void draw();
private:
	// массив вершин полигональной сетки
	vector<Vertex> vertices;
};
