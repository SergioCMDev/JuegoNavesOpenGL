#include "Missile.h"

Missile::Missile() {

}
Missile::Missile(Shader & shader, glm::vec3 position, GameObject parent)
{
	//position = vec3(0.0f, 0.0f, 0.0f);
	_model = Model(pathToModel);
	_shader = shader;
	SetPosition(position);
	_velocity = 2.5f;
	_type = Constants::TIPO_MISIL;
	//_modelMatrix = mat4(1.0f);
	_scale = vec3(0.4f);
	if (parent._type == Constants::TIPO_PLAYER) {
		Rotate();
	}
}

Missile::~Missile() {
	//delete(;
}

void Missile::Render(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 _modelMatrix = mat4(1.0f);

	_shader.Use();
	_modelMatrix = glm::translate(_modelMatrix, _position);

	_modelMatrix = glm::scale(_modelMatrix, _scale);

	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", _modelMatrix);
	_model.Draw(_shader);
}

void Missile::Rotate() {
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	_shader.Set("model", _modelMatrix);

}

void Missile::Mover(const Movement movement, const float deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	switch (movement) {
	case Movement::Backward: //lanzado por enemigo
		_position += GetUpVector() * actualVelocity; break;
	case Movement::Forward: //Lanzado por jugador

		_position -= GetUpVector() * actualVelocity; break;
	}

}
