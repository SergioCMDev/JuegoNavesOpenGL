#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "Model.h"
#include "Utils.h"
#include "Shader.h"
#include "Constants.h"

class GameObject {

public:
	Model _model;
	Shader &_shader = Shader();
	vec3 _position;

	GameObject();
	GameObject(Model * model, Shader& shader, glm::vec3 position);
	GameObject(const char* pathToModel, Shader& shader, glm::vec3 position);
};
#endif