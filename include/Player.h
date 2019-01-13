#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "GameObject.h"
#include "Constants.h"

class Player : public GameObject{

public:
	//float GetVelocity();
	void Player::MoverJugador(const Movement movement, const float deltaTime);
	Player(Shader & shader, glm::vec3 position);
private:
	const float _velocity = 0.5f;
	const char* pathToModel = "../assets/obj/Freighter/Freigther_BI_Export.obj";

};
#endif