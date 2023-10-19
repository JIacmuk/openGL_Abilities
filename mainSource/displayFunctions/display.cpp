#include "display.h"

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay

void keyboardListen();

void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// устанавливаем освещение по заданным параметрам
	light.apply();

	// устанавливаем камеру по заданным параметрам
	camera.apply();
	
	//устанавливаем прослушивание кнопок
	keyboardListen();

	// Выводим все графические объекты
	/*for (GraphicObject& go : graphicObjects) {
		go.draw();
	}*/
	// Выводим все игровые объекты
	//graphicObjects[0].draw();
	(*field).draw();
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if(mapObjects[i][j] != nullptr) (*mapObjects[i][j]).draw();
		}
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
};

void keyboardListen() {
	float currentSpeedHorizontal = speedHorizontal * simTime / 1000;
	float currentSpeedVertical = speedVertical * simTime / 1000;
	float currentSpeedZoom = speedZoom * simTime / 1000;

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