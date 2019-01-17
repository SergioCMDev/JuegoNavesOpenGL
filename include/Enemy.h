#ifndef ENEMY_H
#define ENEMY_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "GameObject.h"
#include "Constants.h"
#include<GLFW/glfw3.h>
class Enemy : public GameObject {

public:
	Enemy();
	//float GetVelocity();
	void Mover(const Movement movement, const float deltaTime);

	Enemy(Shader & shader, glm::vec3 position);
	~Enemy();
	void Render(glm::mat4 &projection, glm::mat4 &view);
private:
	const char* pathToModel = "../assets/obj/E-45-Aircraft/E 45 Aircraft_obj.obj";
};
#endif