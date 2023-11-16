#pragma once
#include "../../Header.h"
#include "../GameObject.h"
#include "map"


// КЛАСС ДЛЯ СОЗДАНИЯ ИГРОВЫХ ОБЪЕКТОВ
class GameObjectFactory
{
public:
	// инициализация фабрики (загрузка мешей и установка параметров материала)
	void init(string filename);
	// создание нового объекта заданного типа
	shared_ptr<GameObject> create(GameObjectType type, int x, int y, float z = 0);
private:
	// меши для каждого типа объекта
	vector<shared_ptr<Mesh>> meshes;
	// материалы для каждого типа объекта
	vector<shared_ptr<Material>> materials;
};