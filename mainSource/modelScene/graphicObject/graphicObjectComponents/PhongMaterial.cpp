#include "PhongMaterial.h"


PhongMaterial::PhongMaterial()
{
}

PhongMaterial::PhongMaterial(string filename, int materialId)
{
	load(filename, materialId);
}

void PhongMaterial::setAmbient(vec4 color)
{
	this->ambient = color;
}

void PhongMaterial::setDiffuse(vec4 color)
{
	this->diffuse = color;
}

void PhongMaterial::setSpecular(vec4 color)
{
	this->specular = color; 
}

void PhongMaterial::setEmission(vec4 color)
{
	this->emission = color;
}

void PhongMaterial::setShininess(float p)
{
	this->shininess = p;
}

void PhongMaterial::load(string filename, int materialId)
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

void PhongMaterial::apply()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, value_ptr(specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, value_ptr(emission));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
}
