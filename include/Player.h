#ifndef UTILS_H
#define UTILS_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "GameObject.h"
#include "Constants.h"

class Player : GameObject{

public:
	enum class Movement { //Possible options for camera movement
		Forward = 0,
		Backward = 1,
		Left = 2,
		Right = 3,
	};
	void MoverJugador(const Movement movement, const GameObject model, const float deltaTime);

private:
	vec3 _right = vec3(1.0f, 0.0f, 0.0f);
	vec3 _up = vec3(0.0f, 0.0f, 1.0f);
	const char* pathToModel = "../assets/obj/Freighter/Freigther_BI_Export.obj";
};
#endif