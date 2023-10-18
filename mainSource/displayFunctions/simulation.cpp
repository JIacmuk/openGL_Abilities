#include "simulation.h"


double getSimulationTime();
void setWindowFPS();
void StartCounter();
int getFPS();


//Задаем переменные для работы со времем
double PCFreq = 0.0;
__int64 CounterStart = 0;

double summ = 0;

void simulation() {
	getSimulationTime();
	setWindowFPS();
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

void setWindowFPS() {
	//формируем фпс
	summ += simTime;
	if (summ >= 1000) {
		summ -= 1000;
		int currentFPS = getFPS();
		glutSetWindowTitle(("fps: " + to_string(currentFPS)).c_str());
	}
}
