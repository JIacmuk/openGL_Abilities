#include "simulation.h"


double getSimulationTime();
void setWindowFPS();
void StartCounter();
int getFPS();
void cameraSimulation(float simulationTime);
void gameObjectSimulation(float simulationTime);
void movePlayer();
void movePlayerWithLightBlock(MoveDirection direction, int playerPositionX, int playerPositionY);
//Задаем переменные для работы со времем
double PCFreq = 0.0;
__int64 CounterStart = 0;
double summ = 0;

void simulation() {
	float simTime = getSimulationTime();
	cameraSimulation(simTime);
	gameObjectSimulation(simTime);


	setWindowFPS();

	movePlayer();
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

double getSimulationTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	simTime = double(li.QuadPart - CounterStart) / PCFreq;
	StartCounter();
	return simTime;
}

int getFPS()
{
	return (int)(1000 / simTime);
}

void movePlayer()
{
	// получаем позицию игрока
	vec2 playerPosition = (*player).getPosition();
	int playerPositionX = playerPosition[0];
	int playerPositionY = playerPosition[1];
	// проверяем на возможность прохождения
	if (GetAsyncKeyState('W'))
	{	
		if (passabilityMap[playerPositionX][playerPositionY - 1] == 0) (*player).move(MoveDirection::UP);
		if (passabilityMap[playerPositionX][playerPositionY - 1] == 1 && (passabilityMap[playerPositionX][playerPositionY - 2] == 0)) {
			movePlayerWithLightBlock(MoveDirection::UP, playerPositionX, playerPositionY);
		}
	}
	if (GetAsyncKeyState('A'))
	{
		if (passabilityMap[playerPositionX - 1][playerPositionY] == 0)(*player).move(MoveDirection::LEFT);
		if (passabilityMap[playerPositionX - 1][playerPositionY] == 1 && (passabilityMap[playerPositionX - 2][playerPositionY] == 0)) {
			movePlayerWithLightBlock(MoveDirection::LEFT, playerPositionX, playerPositionY);
		}
	}
	if (GetAsyncKeyState('S'))
	{
		if (passabilityMap[playerPositionX][playerPositionY + 1] == 0)(*player).move(MoveDirection::DOWN);
		if (passabilityMap[playerPositionX][playerPositionY + 1] == 1 && (passabilityMap[playerPositionX][playerPositionY + 2] == 0)) {
			movePlayerWithLightBlock(MoveDirection::DOWN, playerPositionX, playerPositionY);
		}
	}
	if (GetAsyncKeyState('D'))
	{
		if (passabilityMap[playerPositionX + 1][playerPositionY] == 0)(*player).move(MoveDirection::RIGHT);
		if (passabilityMap[playerPositionX + 1][playerPositionY] == 1 && (passabilityMap[playerPositionX + 2][playerPositionY] == 0)) {
			movePlayerWithLightBlock(MoveDirection::RIGHT, playerPositionX, playerPositionY);
		}
	}
}
void movePlayerWithLightBlock(MoveDirection direction, int playerPositionX, int playerPositionY) {

	ivec2 nextPosition;
	switch (direction)
	{
	case MoveDirection::STOP:
		nextPosition = ivec2(0, 0);
		break;
	case MoveDirection::LEFT:
		nextPosition = ivec2(-1, 0);
		break;
	case MoveDirection::RIGHT:
		nextPosition = ivec2(1, 0);
		break;
	case MoveDirection::UP:
		nextPosition = ivec2(0, -1);
		break;
	case MoveDirection::DOWN:
		nextPosition = ivec2(0, 1);
		break;
	}
	ivec2 nextDoublePosition = nextPosition * 2;

	(*player).move(direction);
	(*mapObjects[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]]).move(direction);

	if ((*mapObjects[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]]).isMoving() == false) {
		//изменяем карту проходимости 
		passabilityMap[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]] = 0;
		passabilityMap[playerPositionX + nextDoublePosition[0]][playerPositionY + nextDoublePosition[1]] = 1;
		//изменяем обьекты карты
		mapObjects[playerPositionX + nextDoublePosition[0]][playerPositionY + nextDoublePosition[1]] = mapObjects[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]];
		mapObjects[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]] = nullptr;
	}
}

void cameraSimulation(float simulationTime) {
	float currentSpeedHorizontal = speedHorizontal * simulationTime / 1000;
	float currentSpeedVertical = speedVertical * simulationTime / 1000;
	float currentSpeedZoom = speedZoom * simulationTime / 1000;

	if (GetAsyncKeyState(VK_RIGHT))
	{
		camera.rotateLeftRight(-currentSpeedHorizontal);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		camera.rotateLeftRight(currentSpeedHorizontal);
	}
	if (GetAsyncKeyState(VK_UP))
	{
		camera.rotateUpDown(currentSpeedVertical);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		camera.rotateUpDown(-currentSpeedVertical);
	}
	if (GetAsyncKeyState(VK_ADD))
	{
		camera.zoomInOut(currentSpeedZoom);
	}
	if (GetAsyncKeyState(VK_SUBTRACT))
	{
		camera.zoomInOut(-currentSpeedZoom);
	}
}

void gameObjectSimulation(float simulationTime)
{
	(*player).simulate(simulationTime);
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (passabilityMap[i][j] == 1) (*mapObjects[i][j]).simulate(simulationTime);
		}
	}
}

void setWindowFPS() {
	//формируем фпс
	summ += simTime;
	if (summ >= 1000) {
		summ -= 1000;
		int currentFPS = getFPS();
		glutSetWindowTitle(("fps: " + to_string(currentFPS)).c_str());
	}
}
