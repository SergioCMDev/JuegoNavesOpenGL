#ifndef METEOR_H
#define METEOR_H
#include<iostream>
#include "string.h"
#include "Shader.h"
#include "GameObject.h"
#include "Constants.h"

class Meteor : public GameObject{

public:
	Meteor();

	void Mover(const float& deltaTime);
	Meteor(Shader & shader);
	Meteor(Shader & shader, glm::vec3 position);
	~Meteor();
	vec3 _scale = vec3(1.0f);
	void Render(glm::mat4 &projection, glm::mat4 &view);

private:

	//float _velocity = 0.5f;
	const char* pathToModel = "../assets/obj/Meteor/Meteor.obj";

};
#endif