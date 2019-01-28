#include "Meteor.h"
#include<GLFW/glfw3.h>

glm::vec3 positions[] = {
 glm::vec3(0.0f,  0.0f, Constants::MAX_POSITION_Y), //z == arriba/abajo, X derecha/izq invertida
 glm::vec3(5.0f,  0.0f, Constants::MAX_POSITION_Y),
 glm::vec3(8.0f, 0.0f, Constants::MAX_POSITION_Y),
 glm::vec3(-5.0f,  0.0f, Constants::MAX_POSITION_Y),
 glm::vec3(-8.0f, 0.0f, Constants::MAX_POSITION_Y),
};


uint32_t Meteor::GetNumberPositions() {
	return sizeof(positions) / sizeof(glm::vec3);
}

vec3 Meteor::GetMeteorPosition(uint32_t index)
{
	return positions[index];
}


Meteor::Meteor() {

}


Meteor::Meteor(Shader & shader)
{

	SetModel(Model(pathToModel));
	_shader = shader;
	srand(rand());
	const uint32_t initialPositionIndex = rand() % 5;
	SetPosition(vec3(0.0f));
	SetVelocity(1.0f);
	SetType(Constants::TIPO_METEOR);
	Deactivate();

}

Meteor::~Meteor() {
	//delete this;
}

void Meteor::SetRandomPosition()
{
	srand(rand());
	uint32_t initialPositionIndex = -1;
	do {
		initialPositionIndex = rand() % GetNumberPositions();
	} while (initialPositionIndex <0 || initialPositionIndex >GetNumberPositions());

	vec3 positionInitial = positions[initialPositionIndex];
	SetPosition(positionInitial);
}

vec3 Meteor::GetScale() {
	return _scale;
}

void Meteor::Mover(const float& deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	SetPosition(GetPosition() - GetUpVector() * actualVelocity);
}