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
	//float GetVelocity();
	void Mover(const Movement movement, const float deltaTime);
	//static Player* Instance(Shader & shader, glm::vec3 position);
	//static Player* GetInstance();
	Meteor(Shader & shader, glm::vec3 position);
	~Meteor();
	void Render(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view);
private:
	//static Player* _instance;
	//float _velocity = 0.5f;
	const char* pathToModel = "../assets/obj/Freighter/Freigther_BI_Export.obj";

};
#endif