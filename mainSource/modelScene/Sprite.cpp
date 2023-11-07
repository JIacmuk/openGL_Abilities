#include "Sprite.h"

shared_ptr <Mesh> Sprite::mesh;

Sprite::Sprite()
{

}

void Sprite::init()
{
	//создаем мэш
	mesh = make_shared<Mesh>("../AdditionalData/meshes/Sprite.obj");
}

void Sprite::setTexture(shared_ptr<Texture> texture)
{
	this->texture = texture;
}

void Sprite::draw(float left, float bottom, float width, float height) {

	// корректируем масштаб
	width *= 10;
	height *= 10;



	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	//отключаем освещение
	//glDisable(GL_LIGHTING);
	//отключаем отсечение нелицевых граней
	//glDisable(GL_CULL_FACE);
	//glDisable(GL_POLYGON_OFFSET_FILL);
	//включаем наложение и альфа канал
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//создаем матрицу моделей для спрайта
	GLfloat modelMatrix[16] = {
		1.0, 0.0, 0.0, 0.0, // ось Ox
		0.0, 1.25, 0.0, 0.0, // ось Oy
		0.0, 0.0, 1.0, 0.0, // ось Oz
		0.0, 0.75, 0.0, 0.0  // позиция объекта (начало системы координат)
	};
	

	// применяем текстуру
	// выбираем активный текстурный блок
	glActiveTexture(GL_TEXTURE0);
	// разрешаем текстурирование в выбранном элементе текстурного блока
	glEnable(GL_TEXTURE_2D);
	
	// указываем режим наложения текстуры (GL_REPLACE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// привязываем текстуру к ранее выбранному текстурному блоку
	(*texture).apply();

	//Начинаем вывод
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelMatrix);
	//заполнямем мэш
	if (mesh != nullptr) {
		mesh->draw();
	}

	//включаем освещение
	//glEnable(GL_LIGHTING);
	//включаем отсечение нелицевых граней
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	//отключаем наложение
	//glDisable(GL_BLEND);
	//отключаем текстуру
	glDisable(GL_TEXTURE_2D);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)1000 / 800, 0.2, 70.0);

}
