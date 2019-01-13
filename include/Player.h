#ifndef UTILS_H
#define UTILS_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "Model.h"
#include "ObjectModel.h"


class Player {

public:
	enum class Movement { //Possible options for camera movement
		Forward = 0,
		Backward = 1,
		Left = 2,
		Right = 3,
	};
	void MoverJugador(const Movement movement, const ObjectModel model, const float deltaTime);

private:
	vec3 _right = vec3(1.0f, 0.0f, 0.0f);
	vec3 _up = vec3(0.0f, 0.0f, 1.0f);
	vec3 position;
};
#endif