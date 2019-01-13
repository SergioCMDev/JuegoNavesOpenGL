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
	void MoverJugador(const Movement movement, const float deltaTime);
	static Player* Instance(Shader & shader, glm::vec3 position);
	static Player* GetInstance();
	Player(Shader & shader, glm::vec3 position);
	~Player();
private:
	static Player* _instance;
	//float _velocity = 0.5f;
	const char* pathToModel = "../assets/obj/Freighter/Freigther_BI_Export.obj";

};
#endif