#include "data/data.h"
#include "displayFunctions/display.h"
#include "displayFunctions/simulation.h"

int main(int argc, char** argv) 
{
	setlocale(LC_ALL, "ru");
	//задаем начальное время
	StartCounter();
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	

	// инициализация библиотеки DevIL для загрузки изображений
	ilInit();
	iluInit();
	ilutInit();

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(250, 10);
	// 2. устанавливаем размер окна
	glutInitWindowSize(1000, 800);
	// 3. создаем окно
	glutCreateWindow("Laba_04");

	//Подключаем расширерение openGl
	GLenum err = glewInit();

	//инициализируем данные
	initData();

	// устанавливаем общую фоновую освещенность
	GLfloat globalAmbientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);

	

	// включаем режим расчета освещения
	glEnable(GL_LIGHTING);
	// включаем первый источник света
	glEnable(GL_LIGHT0);
	
	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// вызываем функцию по готовности системы
	glutIdleFunc(simulation);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
	return 0;
};