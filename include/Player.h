#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "GameObject.h"
#include "Constants.h"

class Player : public GameObject{

public:

	void MoverJugador(const Movement movement, const GameObject model, const float deltaTime);
	Player(Shader & shader, glm::vec3 position);
private:

	const char* pathToModel = "../assets/obj/Freighter/Freigther_BI_Export.obj";
};
#endif