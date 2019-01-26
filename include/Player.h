#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include "Shader.h"
#include "Missile.h"
#include "Node.h"
#include "Constants.h"
#include<GLFW/glfw3.h>

class Missile;

class Player : public GameObject {

public:
	Player();
	//float GetVelocity();
	void Mover(const Movement movement, const float deltaTime);
	void Disparar();

	GameObject * GetUsableMissile();
	Player(Shader & shader, glm::vec3 position);
	~Player();
	bool Shooting();
	void Render(glm::mat4 &projection, glm::mat4 &view);
	void NoShooting();
private:
	bool _disparando = false;
	const char* pathToModel = "../assets/obj/Freighter/Freigther_BI_Export.obj";
};
#endif