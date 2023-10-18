#pragma once
#include "../modelScene/Camera.h"
#include "../modelScene/GameObject.h"
#include "../modelScene/Light.h"
//список графических объектов
extern vector<GraphicObject> graphicObjects;

//список материалов объектов
extern vector<shared_ptr<PhongMaterial>> materials;

//матрица игровых объектов
extern shared_ptr<GameObject> mapObjects[21][21];
//меши 
extern vector<shared_ptr<Mesh>> meshes;

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