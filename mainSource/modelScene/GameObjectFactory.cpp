#include "GameObjectFactory.h"
#include "nlohmann/json.hpp"
#include <fstream>



void GameObjectFactory::init(string filename)
{
	using json = nlohmann::json;
	ifstream f(filename);
	if (!f.is_open()) {
		cout << "Ошибка открытия файла Игровых Объектов!" << endl;
	}
	json data = json::parse(f);

	string pathToMaterial = data["pathToMaterials"];
	string pathToMesh = data["pathToMesh"];

	for (auto &it : data["objects"].items()) {
		
		string valueMesh = data["objects"][it.key()]["mesh"];
		int valueMaterial = data["objects"][it.key()]["material"];
		shared_ptr<Mesh> tempMesh(new Mesh(pathToMesh + valueMesh + ".obj"));
		meshes.push_back(tempMesh);
		shared_ptr<PhongMaterial> tempPhongMaterial(new PhongMaterial(pathToMaterial, valueMaterial - 1));
		materials.push_back(tempPhongMaterial);
	}
}

shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{   
	int index;
	switch (type)
	{
	case GameObjectType::BOMB:
		index = 0;
		break;
	case GameObjectType::BORDER_OBJECT:
		index = 1;
		break;
	case GameObjectType::FIELD:
		index = 2;
		break;
	case GameObjectType::HEAVY_OBJECT:
		index = 3;
		break;
	case GameObjectType::LIGHT_OBJECT:
		index = 4;
		break;
	case GameObjectType::MONSTER:
		index = 5;
		break;
	case GameObjectType::PLAYER:
		index = 6;
		break;
	}

	GraphicObject tempGraphicObject;
	tempGraphicObject.setMaterial(materials[index]);
	tempGraphicObject.setMesh(meshes[index]);

	shared_ptr<GameObject> tempGameObject(new GameObject);
	(*tempGameObject).setGraphicObject(tempGraphicObject);
	(*tempGameObject).setPosition(x, y);

    return tempGameObject;
}
