#include "Decal.h"

//загружаем статические поля декаля
shared_ptr <PhongMaterialWithTexture> Decal::material;
shared_ptr <Mesh> Decal::mesh;

void Decal::init()
{
	//создаем материал
	material = make_shared<PhongMaterialWithTexture>("../AdditionalData/materials.json", 8);
	//создаем текстуру
	shared_ptr <Texture> tempTexture(new Texture("../AdditionalData/textures/decal.png"));
	(*material).setTexture(tempTexture);
	//создаем мэши
	mesh = make_shared<Mesh>("../AdditionalData/meshes/Decal.obj");
}

Decal::Decal()
{
	GraphicObject tempGraphicObject;
	tempGraphicObject.setMaterial(material);
	tempGraphicObject.setMesh(mesh);
	graphicObject = tempGraphicObject;
}

Decal::Decal(ivec2 position)
{
	this->position = position;
	GraphicObject tempGraphicObject;
	tempGraphicObject.setMaterial(material);
	tempGraphicObject.setMesh(mesh);
	tempGraphicObject.setPosition(vec3(position.x - 10, -0.49, position.y - 10));
	graphicObject = tempGraphicObject;
}

void Decal::setPosition(ivec2 position)
{
	this->position = position;
	graphicObject.setPosition(vec3(position.x - 10, -0.49, position.y - 10));

}

ivec2 Decal::getPosition()
{
	return position;
}
void Decal::draw()
{
	// включаем режим цветового наложения
	glEnable(GL_BLEND);
	// устанавливаем факторы источника и приемника
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	graphicObject.draw();
	//отключаем текстурирование 
	Texture::disableAll();
	glDisable(GL_BLEND);
}
