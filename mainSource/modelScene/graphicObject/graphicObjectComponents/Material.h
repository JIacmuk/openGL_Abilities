#pragma once
#include "../../../Header.h"

// БАЗОВЫЙ КЛАСС ДЛЯ ВСЕХ МАТЕРИАЛОВ
class Material
{
public:
	// "применение" материала
	virtual void apply(void) = 0;
};