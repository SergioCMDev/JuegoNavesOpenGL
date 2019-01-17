#include "Meteor.h"
#include<GLFW/glfw3.h>

vec3 positions[5]{
	vec3(5.0f, 0.0f,  10.0f), //X invertida
	vec3(0.0f, 0.0f,  10.0f),
	vec3(-4.0f, 0.0f, 10.0f),
	vec3(2.0f, 0.0f,  10.0f),
	vec3(2.0f,0.0f,   10.0f),
};


Meteor::Meteor() {

}
Meteor::Meteor(Shader & shader, glm::vec3 position)
{
	_model = Model(pathToModel);
	_shader = shader;
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
	_velocity = 0.2f;
	_type = 2;
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