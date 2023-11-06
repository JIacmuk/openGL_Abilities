#pragma once
#include "../modelScene/Camera.h"
#include "../modelScene/gameObjectTools/GameObjectFactory.h"
#include "../modelScene/Light.h"
#include "../modelScene/Decal.h"

extern GameObjectFactory gameObjectFactory;
//матрица игровых объектов
extern shared_ptr<GameObject> mapObjects[21][21];
extern shared_ptr<GameObject> field;
extern shared_ptr<GameObject> player;
extern shared_ptr<GameObject> monsters[3];
extern shared_ptr<GameObject> bomb;
//камера 
extern Camera camera;

//свет
extern Light light;

//карта проходимости
extern int passabilityMap[21][21];
//описание карты проходимости
// 0 - пустое место
// 1 - легкий объект, который может перемещать игрок, но не могут монстры
// 2 - тяжелый объект
// 4 - монстр
// 5 - бомба 

//время симуляции одного кадра
extern double simTime;

//Задаем константы скорости вращения
extern double speedHorizontal; // град / c 
extern double speedVertical;
extern double speedZoom;

// декали
extern vector<Decal> decals;

//функция для инициализации
void initData();