#include "data.h"

//фабрика для создания игровых объектов
GameObjectFactory gameObjectFactory;
// список игровых объектов 
shared_ptr<GameObject> mapObjects[21][21];
shared_ptr<GameObject> field;
shared_ptr<GameObject> player;
shared_ptr<GameObject> monsters[3];
shared_ptr<GameObject> bomb;
// используемая камера
Camera camera(0, -50, -30);
// используем свет
Light light(20, 25, 15);
//используем текстуру
//время симуляции
double simTime;
//данные скорости
double speedHorizontal;
double speedVertical;
double speedZoom;
//Путь к папке с игровыми объектами
string pathToGameObjects = "../AdditionalData/GameObjectType.json";
//Путь к изображениям
string pathToTexture = "../AdditionalData/textures/plane.jpg";
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
//местоположение врагов 
ivec2 monsterLocation[3]{ ivec2(5, 3), ivec2(19, 5), ivec2(19, 18) };

void initData() 
{
	//Загрузка фабрики
	gameObjectFactory.init(pathToGameObjects);
	//Создаем поле
	field = gameObjectFactory.create(GameObjectType::FIELD, 10, 10, -0.5);
	//Создаем игрока
	player = gameObjectFactory.create(GameObjectType::PLAYER, 1, 19);
	//Создаем бомбу 
	bomb = nullptr;
	//Создаем монстров
	for (int i = 0; i < 3; i++) {
		monsters[i] = gameObjectFactory.create(GameObjectType::MONSTER, monsterLocation[i].x, monsterLocation[i].y);
	}
	// инициализация объектов сцены
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}

	//Максимальная скорость
	speedHorizontal = 90;
	speedVertical = 45;
	speedZoom = 5;

	//источник света
	light.setDiffuse(vec4(0.5, 0.5, 0.5, 1)); // цвет
	light.setAmbient(vec4(0.2, 0.2, 0.2, 1)); // отражение лучей от других объектов (затемнение)
	light.setSpecular(vec4(0.5, 0.5, 0.5, 1)); // блики? но я чет разницы не вижу

	//заполняем карту проходимости монстрами
	for (int i = 0; i < 3; i++) {
		passabilityMap[monsterLocation[i].x][monsterLocation[i].y] = 3;
	}
}
