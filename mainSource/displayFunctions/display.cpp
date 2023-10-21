#include "display.h"

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay

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
	
	(*player).draw();
	(*field).draw();
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if(mapObjects[i][j] != nullptr) (*mapObjects[i][j]).draw();
		}
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
};