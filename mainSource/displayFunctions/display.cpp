#include "display.h"

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay

void keyboardListen();

void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// ������������� ��������� �� �������� ����������
	light.apply();

	// ������������� ������ �� �������� ����������
	camera.apply();
	
	//������������� ������������� ������
	keyboardListen();

	// ������� ��� ����������� �������
	/*for (GraphicObject& go : graphicObjects) {
		go.draw();
	}*/
	// ������� ��� ������� �������
	graphicObjects[0].draw();
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if(mapObjects[i][j] != nullptr) (*mapObjects[i][j]).draw();
		}
	}

	// ����� ��������� � ������� �������
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