#pragma once
#include "../modelScene/Camera.h"
#include "../modelScene/GameObjectFactory.h"
#include "../modelScene/Light.h"
//матрица игровых объектов
extern shared_ptr<GameObject> mapObjects[21][21];
extern shared_ptr<GameObject> field;

//камера 
extern Camera camera;

//свет
extern Light light;

//время симуляции одного кадра
extern double simTime;

//Задаем константы скорости вращения
extern double speedHorizontal; // град / c 
extern double speedVertical;
extern double speedZoom;

//функция для инициализации
void initData();