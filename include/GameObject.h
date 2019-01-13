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
	enum class Movement { //Possible options for gameobject movement
		Forward = 0,
		Backward = 1,
		Left = 2,
		Right = 3,
	};
	Model _model;
	Shader &_shader = Shader();
	vec3 _position;

	//GameObject();
	//GameObject(Model * model, Shader& shader, glm::vec3 position);
	//GameObject(const char* pathToModel, Shader& shader, glm::vec3 position);

private:
	vec3 _right = vec3(1.0f, 0.0f, 0.0f);
	vec3 _up = vec3(0.0f, 0.0f, 1.0f);
};
#endif