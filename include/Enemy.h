#pragma once

#ifndef ENEMY_H
#define ENEMY_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "GameObject.h"
#include "Constants.h"
#include "Missile.h"
#include "Node.h"
#include<GLFW/glfw3.h>
class Enemy : public GameObject {

public:
	Enemy();
	Enemy(Shader& shader);
	//float GetVelocity();
	void Mover(const float deltaTime);
	void Disparar();
	GameObject * GetUsableMissile();

	//Enemy(glm::vec3 position);
	~Enemy();
	void Render(glm::mat4 &projection, glm::mat4 &view);
	void SetRandomPosition();
	static uint32_t GetNumberPositions();
	static vec3 GetEnemyPosition(uint32_t index);

	bool Shooting();
	uint32_t GetTypeShip();
private:
	uint32_t _typeShip = 0;
	bool _disparando = false;
	const char* pathToModel = "../assets/obj/UFO/Low_poly_UFO.obj";
	const char* pathToModel2 = "../assets/obj/E-45-Aircraft/E 45 Aircraft_obj.obj";
};
#endif