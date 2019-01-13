#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<iostream>
#include "Shader.h"
#include "Model.h"
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

	GameObject();
	float GetVelocity();
	glm::vec3 GetRightVector();
	glm::vec3 GetUpVector();
	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);

	//GameObject(Model * model, Shader& shader, glm::vec3 position);
	//GameObject(const char* pathToModel, Shader& shader, glm::vec3 position);
	vec3 _position;

private:
	const float _velocity = 0.0f;
	const vec3 _right = vec3(1.0f, 0.0f, 0.0f);
	const vec3 _up = vec3(0.0f, 0.0f, 1.0f);
};
#endif