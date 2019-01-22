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
	//float GetVelocity();
	void Mover(const Movement movement, const float deltaTime);
	void Disparar();
	Enemy(glm::vec3 position);
	~Enemy();
	void Render(glm::mat4 &projection, glm::mat4 &view);
	void SetRandomPosition();
	static uint32_t GetNumberPositions();
	static vec3 GetEnemyPosition(uint32_t index);
	uint32_t GetLastMissileUsed();
	void SumLastMissileUsed();
	bool Shooting();
	void NoShooting();
private:
	bool _disparando = false;
	uint32_t _lastMissileUsed = 0;
	const char* pathToModel = "../assets/obj/E-45-Aircraft/E 45 Aircraft_obj.obj";
};
#endif