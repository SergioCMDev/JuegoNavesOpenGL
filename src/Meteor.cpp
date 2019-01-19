#include "Meteor.h"
#include<GLFW/glfw3.h>

glm::vec3 positions[] = {
 glm::vec3(0.0f,  0.0f, 15.0f), //z == arriba/abajo, X derecha/izq invertida
 glm::vec3(5.0f,  0.0f, 15.0f),
 glm::vec3(8.0f, 0.0f, 15.0f),
 glm::vec3(-5.0f,  0.0f, 15.0f),
 glm::vec3(-8.0f, 0.0f, 15.0f),
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

Meteor::Meteor(Shader & shader, glm::vec3 position) {
	_model = Model(pathToModel);
	_shader = shader;
	//const uint32_t initialPositionIndex = rand() % 2;
	//vec3 positionInitial = positions[initialPositionIndex];
	SetPosition(position);
	_velocity = 1.0f;
	_type = Constants::TIPO_METEOR;
}


Meteor::Meteor(glm::vec3 position)
{
	Shader shaderMeteorito = Utils::GetFullShader("Shaders/MetorVS.vs", "Shaders/MetorFS.fs");

	_model = Model(pathToModel);
	_shader = shaderMeteorito;
	//const uint32_t initialPositionIndex = rand() % 2;
	//vec3 positionInitial = positions[initialPositionIndex];
	SetPosition(position);
	_velocity = 1.0f;
	_type = Constants::TIPO_METEOR;
}


Meteor::Meteor(Shader & shader)
{


	_model = Model(pathToModel);
	_shader = shader;
	srand(rand());
	const uint32_t initialPositionIndex = rand() % 5;
	vec3 positionInitial = positions[initialPositionIndex];
	cout << "Posicion Meteorito " << positionInitial.x << endl;
	SetPosition(positionInitial);
	_velocity = 1.2f;
	_type = Constants::TIPO_METEOR;
}

Meteor::~Meteor() {
	/*_instance = nullptr;*/
}




void Meteor::Render(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 model = mat4(1.0f);
	_shader.Use();
	model = glm::translate(model, _position);
	model = glm::scale(model, _scale);
	float angle = glm::radians((40 + glm::cos(45.0f) + glm::sin(90.0f)));
	model = glm::rotate(model, (float)glfwGetTime() *  angle, vec3(1.0f, 1.0f, 0.0f));
	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", model);
	_velocity += 0.2f;

	_model.Draw(_shader);
}

void Meteor::Mover(const float& deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	_position -= GetUpVector() * actualVelocity;
}