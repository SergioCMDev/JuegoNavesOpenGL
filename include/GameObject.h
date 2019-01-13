#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "Model.h"


class GameObject {

public:
	Model *model;
	Shader &shader;
	vec3 position;
};
#endif