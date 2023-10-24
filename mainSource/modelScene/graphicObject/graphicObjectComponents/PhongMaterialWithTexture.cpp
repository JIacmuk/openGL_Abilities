#include "PhongMaterialWithTexture.h"
#include "nlohmann/json.hpp"
#include <fstream>
PhongMaterialWithTexture::PhongMaterialWithTexture(string filename, int materialId)
{
	load(filename, materialId);
}

void PhongMaterialWithTexture::setAmbient(vec4 color)
{
	this->ambient = color;
}

void PhongMaterialWithTexture::setDiffuse(vec4 color)
{
	this->diffuse = color;
}

void PhongMaterialWithTexture::setSpecular(vec4 color)
{
	this->specular = color;
}

void PhongMaterialWithTexture::setEmission(vec4 color)
{
	this->emission = color;
}

void PhongMaterialWithTexture::setShininess(float p)
{
	this->shininess = p;
}

void PhongMaterialWithTexture::setTexture(shared_ptr<Texture> texture)
{
	this->texture = texture;
}

void PhongMaterialWithTexture::load(string filename, int materialId)
{
	//txt файлы меня не интересуют, поэтому сделаем в одном json файлике 
	using json = nlohmann::json;
	ifstream f(filename);
	if (!f.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}
	json data = json::parse(f);
	//Считываем данные из файла
	for (int i = 0; i < 4; i++) {
		this->diffuse[i] = data["material"][materialId]["diffuse"][i];
		this->ambient[i] = data["material"][materialId]["ambient"][i];
		this->emission[i] = data["material"][materialId]["emission"][i];
		this->specular[i] = data["material"][materialId]["specular"][i];
	}
	this->shininess = data["material"][materialId]["shininess"];
}

void PhongMaterialWithTexture::apply()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, value_ptr(specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, value_ptr(emission));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

	//применяем текстуру
	// выбираем активный текстурный блок
	glActiveTexture(GL_TEXTURE0);
	// разрешаем текстурирование в выбранном элементе текстурного блока
	glEnable(GL_TEXTURE_2D);
	// привязываем текстуру к ранее выбранному текстурному блоку
	(*texture).apply();
	// указываем режим наложения текстуры (GL_MODULATE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
