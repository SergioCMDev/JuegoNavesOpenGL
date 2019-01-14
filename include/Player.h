#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "GameObject.h"
#include "Constants.h"

class Player : public GameObject{

public:
	Player();
	//float GetVelocity();
	void Mover(const Movement movement, const float deltaTime);

	Player(Shader & shader, glm::vec3 position);
	~Player();
	void Render(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view);
private:
	const char* pathToModel = "../assets/obj/Freighter/Freigther_BI_Export.obj";
	};
#endif