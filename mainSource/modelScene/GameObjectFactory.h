#pragma once
#include "../Header.h"
#include "GameObject.h"
#include "map"

// Класс для определения типа игрового объекта
enum class GameObjectType {
	FIELD, // игровое поле
	LIGHT_OBJECT, // легкий игровой объект
	HEAVY_OBJECT, // тяжелый игровой объект
	BORDER_OBJECT, // граничный игровой объект
	PLAYER, // игровой объект для представления игрока
	BOMB, // игровой объект для представления бомбы
	MONSTER // игровой объект для представления монстров
};


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