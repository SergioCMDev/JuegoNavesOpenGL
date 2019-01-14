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

	void Mover(const Movement movement, const float deltaTime);

	Meteor(Shader & shader, glm::vec3 position);
	~Meteor();
	void Render(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view);
	vec3 _scale = vec3(1.0f);
	void RenderMeteor(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view);

private:

	//float _velocity = 0.5f;
	const char* pathToModel = "../assets/obj/Meteor/Meteor.obj";

};
#endif