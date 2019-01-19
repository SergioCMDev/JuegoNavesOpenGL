#ifndef MISSILE_H
#define MISSILE_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "Utils.h"

#include "GameObject.h"
#include "Constants.h"
#include<GLFW/glfw3.h>
class Missile : public GameObject {

public:
	Missile();
	//float GetVelocity();
	void Mover(const Movement movement, const float deltaTime);
	GameObject* GetParent();
	void Rotate(glm::mat4 &_modelMatrix);
	Missile(Shader & shader, glm::vec3 position, GameObject parent);
	Missile(glm::vec3 position, GameObject* parent);
	~Missile();
	void Render(glm::mat4 &projection, glm::mat4 &view);
private:
	const char* pathToModel = "../assets/obj/Missile/asca.obj";
	glm::mat4 _modelMatrix;
	GameObject* _parent;
};
#endif