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
	string pathToTextures = data["pathToTextures"];

	for (auto &it : data["objects"].items()) {
		string valueMesh = data["objects"][it.key()]["mesh"];
		shared_ptr<Mesh> tempMesh(new Mesh(pathToMesh + valueMesh + ".obj"));
		meshes.push_back(tempMesh);

		int valueMaterial = data["objects"][it.key()]["material"];
		// Проверяем есть ли текстура у игрового объекта
		if (data["objects"][it.key()].contains("texture")) {
			//если есть закгружаем текстурки
			string valueTextures = data["objects"][it.key()]["texture"];
			//создаем материал
			shared_ptr<PhongMaterialWithTexture> tempPhongMaterialWithTexture(new PhongMaterialWithTexture(pathToMaterial, valueMaterial - 1));
			//создаем текстуру
			shared_ptr <Texture> tempTexture(new Texture(pathToTextures + valueTextures));
			(*tempPhongMaterialWithTexture).setTexture(tempTexture);
			materials.push_back(tempPhongMaterialWithTexture);
		}
		else {
			//если нет текстурок, то загружаем материал в обычном режиме
			shared_ptr<PhongMaterial> tempPhongMaterial(new PhongMaterial(pathToMaterial, valueMaterial - 1));
			materials.push_back(tempPhongMaterial);
		}
	}
}

shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y, float z)
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
	(*tempGameObject).setPosition(x, y, z);

    return tempGameObject;
}
