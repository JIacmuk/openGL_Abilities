#pragma once
#include "graphicObject/GraphicObject.h"

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ДЕКАЛИ
class Decal
{
public:
	// функция инициализации статических полей:
	// загрузка меша, загрузка текстуры и создание материала
	static void init();
	// конструкторы: по-умолчанию и с указание логических координат
	Decal();
	Decal(ivec2 position);
	// установка и получение логических координат
	void setPosition(ivec2 position);
	ivec2 getPosition();
	// вывод декали
	void draw();
	
private:
	// графический объект для представления декали
	GraphicObject graphicObject;
	// логическая позиция декали
	ivec2 position;
	// общий материал для всех декалей
	static shared_ptr <PhongMaterialWithTexture> material;
	// общий меш для всех декалей
	static shared_ptr <Mesh> mesh;
};



