#pragma once
#include "Material.h"
#include "Texture.h"

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterialWithTexture : public Material
{
public:
	// конструктор по умолчанию
	PhongMaterialWithTexture(string filename, int materialId);
	// задание параметров материала
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// установка используемой текстуры
	void setTexture(shared_ptr<Texture> texture);
	// загрузка параметров материала из внешнего текстового файла
	void load(string filename, int materialId);
	// установка всех параметров материала
	void apply();
private:
	// фоновая составляющая
	vec4 ambient;
	// диффузная составялющая
	vec4 diffuse;
	// зеркальная составляющая
	vec4 specular;
	// самосвечение
	vec4 emission;
	// степень отполированности
	float shininess;
	// используемая текстура
	std::shared_ptr<Texture> texture;
};
