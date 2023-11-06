#include "display.h"

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay

void drawField();

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
	// рисуем монстров
	for (int i = 0; i < 3; i++) {
		if (monsters[i] != nullptr) (*monsters[i]).draw();
	}
	// рисуем игрока если он есть на поле 
	if(player != nullptr) (*player).draw();
	
	// рисуем бомбу 
	if (bomb != nullptr) {
		(*bomb).draw();
	}
	// рисуем поле
	(*field).draw();
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if(mapObjects[i][j] != nullptr) (*mapObjects[i][j]).draw();
		}
	}
	
	for (Decal item : decals) item.draw();
	
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

void drawField() {
	// выбираем активный текстурный блок
	glActiveTexture(GL_TEXTURE0);
	// разрешаем текстурирование в выбранном элементе текстурного блока
	glEnable(GL_TEXTURE_2D);
	// привязываем текстуру к ранее выбранному текстурному блоку
	//planeTexture.apply();
	// указываем режим наложения текстуры (GL_MODULATE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// выводим плоскость
	(*field).draw();
	// отключаем текстурирование (чтобы все остальные объекты выводились без текстур)
	Texture::disableAll();
}