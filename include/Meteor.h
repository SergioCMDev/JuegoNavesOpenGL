#pragma once

#ifndef METEOR_H
#define METEOR_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "GameObject.h"
#include "Constants.h"

class Meteor : public GameObject {

public:
	Meteor();
	void Mover(const float& deltaTime);
	Meteor(Shader & shader);
	Meteor(glm::vec3 position);
	Meteor(Shader & shader, glm::vec3 position);
	~Meteor();
	static uint32_t GetNumberPositions();
	static vec3 GetMeteorPosition(uint32_t index);
	void SetRandomPosition();
	vec3 GetScale();
	//vec3 GetScale();
private:

	vec3 _scale = vec3(1.0f);
	const char* pathToModel = "../assets/obj/Meteor/Meteor.obj";

};
#endif