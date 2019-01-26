#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<iostream>
#include "Shader.h"
#include "Model.h"
#include "Constants.h"
#include "Utils.h"
#include "Cube.h"


class Node;

class GameObject {

public:
	enum class Movement { //Possible options for gameobject movement
		Forward = 0,
		Backward = 1,
		Left = 2,
		Right = 3,
	};

	Shader &_shader = Shader();
	~GameObject() {};
	GameObject();
	float GetVelocity();
	void SetVelocity(float velocity);

	glm::vec3 GetRightVector();
	glm::vec3 GetUpVector();

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);

	Node* GetActualNode();
	void SetActualNode(Node * node);
	vec3 GetScale();
	void SetScale(vec3 scale);
	uint32_t GetType();
	void GameObject::SetType(uint32_t type);
	GameObject(Model * model, Shader& shader, glm::vec3 position);
	GameObject(const char* pathToModel, Shader& shader, glm::vec3 position);
	Model GetModel();
	void SetModel(Model model);
	bool Active();
	void Activate();
	void Deactivate();
	Cube *_collider;
	bool OutsideBoundaries();
private:
	Model _model;
	uint32_t _type;
	const vec3 _right = vec3(1.0f, 0.0f, 0.0f);
	const vec3 _up = vec3(0.0f, 0.0f, 1.0f);
	vec3 _scale;
	float _velocity = 0.0f;
	vec3 _position;
	Node * _actualNode;
	bool _active = false;

};
#endif