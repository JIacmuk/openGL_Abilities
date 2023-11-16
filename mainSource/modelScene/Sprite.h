#pragma once
#include "graphicObject/GraphicObject.h"

// КЛАСС ДЛЯ РАБОТЫ СО СПРАЙТОМ
class Sprite
{
public:
	// конструктор по умолчанию
	Sprite();
	// функция инициализации статических полей - загрузка меша для спрайта
	static void init();
	// задание текстуры
	void setTexture(shared_ptr<Texture> texture);
	// функция для вывода спрайта: нижний левый угол и размеры
	// указываются в относительных единицах (0.0 - 1.0)
	void draw(float left, float bottom, float width, float height);
private:
	// общий меш для всех спрайтов
	static shared_ptr <Mesh> mesh;
	// текстура, используемая для данного спрайта
	shared_ptr <Texture> texture;
};