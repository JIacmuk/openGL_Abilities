#include "Light.h"

Light::Light()
{
	setPosition(vec3(20, 20, 20));
}

Light::Light(vec3 position)
{
	setPosition(position);
}

Light::Light(float x, float y, float z)
{
	setPosition(vec3(x, y, z));
}

void Light::setPosition(vec3 position)
{
	this->position = vec4(position , 1);
}

void Light::setAmbient(vec4 color)
{
	this->ambient = color;
}

void Light::setDiffuse(vec4 color)
{
	this->diffuse = color;
}

void Light::setSpecular(vec4 color)
{
	this->specular = color;
}

void Light::apply(GLenum LightNumber)
{	
	// включаем первый источник света
	glEnable(LightNumber);
	// направленный источник света
	glLightfv(LightNumber, GL_AMBIENT, value_ptr(ambient));
	glLightfv(LightNumber, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(LightNumber, GL_SPECULAR, value_ptr(specular));
}
