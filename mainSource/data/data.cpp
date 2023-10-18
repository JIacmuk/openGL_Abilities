#include "data.h"

// список игровых объектов 
shared_ptr<GameObject> mapObjects[21][21];
// список графических объектов
vector<GraphicObject> graphicObjects;
//список указателей на материалы объектов
vector<shared_ptr<PhongMaterial>> materials;
//используемые меши 
vector<shared_ptr<Mesh>> meshes;
// используемая камера
Camera camera(0, -50, -30);
// используем свет
Light light(20, 25, 15);
//время симуляции
double simTime;
//данные скорости
double speedHorizontal;
double speedVertical;
double speedZoom;
//Путь к папке с материалами
string pathToMaterial = "../AdditionalData/materials.json";
//Необходимые материалы
vector <int> materialId = {7, 6, 5, 8};
//Путь к папке с мэшами ( полигоны вершин )
string pathToMesh = "..//AdditionalData/meshes/";
//Необходимые меши 
vector <string> meshNames = { "Box", "ChamferBox", "SimplePlane" };
//карта проходимости для теста игрового движка 
int passabilityMap[21][21] = {
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

void initData() 
{
	// ИНИЦИАЛИЗАЦИЯ ДАННЫХ, НЕОБХОДИМЫХ ДЛЯ РАБОТЫ ПРОГРАММЫ:
	speedHorizontal = 90;
	speedVertical = 45;
	speedZoom = 5;

	//источник света
	light.setDiffuse(vec4(0.9, 0.9, 0.9, 1)); // цвет
	light.setAmbient(vec4(0, 0, 0, 0)); // отражение лучей от других объектов (затемнение)
	light.setSpecular(vec4(0.5, 0.5, 0.5, 1)); // блики? но я чет разницы не вижу

	//считываем необходимые меши из папки с данными
	for (int i = 0; i < meshNames.size(); i++) {
		shared_ptr<Mesh> tempMesh(new Mesh(pathToMesh + meshNames[i] + ".obj"));
		meshes.push_back(tempMesh);
	}

	//считываем материалы из папки с данными
	for (int i = 0; i < materialId.size(); i++) {
		shared_ptr<PhongMaterial> tempPhongMaterial(new PhongMaterial(pathToMaterial, materialId[i] - 1));
		materials.push_back(tempPhongMaterial);
	}
	
	// инициализация графических объектов
	GraphicObject tempGraphicObject;
	//для лекции
	/*tempGraphicObject.setPosition(vec3(0, 0, 0));
	tempGraphicObject.setMaterial(materials[3]);
	graphicObjects.push_back(tempGraphicObject);*/

	//1 плоскость 
	tempGraphicObject.setPosition(vec3(0, -0.5, 0));
	tempGraphicObject.setMaterial(materials[3]);
	tempGraphicObject.setMesh(meshes[2]);
	graphicObjects.push_back(tempGraphicObject);
	//2 Первый игровой куб - желтый "мягкий" кубик (ChamferBox)
	tempGraphicObject.setPosition(vec3(-5, 0, 0));
	tempGraphicObject.setMaterial(materials[2]);
	tempGraphicObject.setMesh(meshes[1]);
	graphicObjects.push_back(tempGraphicObject);
	//3 второй игровой куб - серый обычный кубик 
	tempGraphicObject.setPosition(vec3(0, 0, 5));
	tempGraphicObject.setMaterial(materials[1]);
	tempGraphicObject.setMesh(meshes[0]);
	graphicObjects.push_back(tempGraphicObject);
	//4 третий игровой куб - черный обычный кубик
	tempGraphicObject.setPosition(vec3(0, 0, -5));
	tempGraphicObject.setMaterial(materials[0]);
	tempGraphicObject.setMesh(meshes[0]);
	graphicObjects.push_back(tempGraphicObject);
	
	// инициализация объектов игры
	int type;
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			shared_ptr<GameObject> tempGameObject(new GameObject);
			type = passabilityMap[i][j];
			if (type != 0) {
				(*tempGameObject).setGraphicObject(graphicObjects[passabilityMap[i][j]]);
				(*tempGameObject).setPosition(j, i);
				mapObjects[i][j] = tempGameObject;
			}
			else mapObjects[i][j] = nullptr;
		}
	}
}
