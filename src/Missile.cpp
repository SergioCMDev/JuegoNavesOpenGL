#include "Missile.h"

Missile::Missile() {

}
Missile::Missile(Shader & shader, glm::vec3 position, GameObject parent)
{
	_model = Model(pathToModel);
	_shader = shader;
	SetPosition(position);
	_velocity = 0.2f;
	_type = Constants::TIPO_MISIL;
	//_modelMatrix = mat4(1.0f);
	_scale = vec3(0.4f);
	_parent = &parent;
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
	if (_parent->_type == Constants::TIPO_ENEMIGO) {
		Rotate(_modelMatrix);
	}
	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", _modelMatrix);
	_model.Draw(_shader);
}

void Missile::Rotate(glm::mat4 &_modelMatrix) {
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(180.0f), glm::vec3(1.0f, 1.0f, 0.0f));

}

GameObject* Missile::GetParent() {
	return _parent;
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
