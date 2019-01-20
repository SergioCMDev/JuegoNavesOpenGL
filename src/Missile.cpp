#include "Missile.h"

Missile::Missile() {

}
Missile::Missile(glm::vec3 position, GameObject* parent)
{
	Shader& shaderMissile = Utils::GetFullShader("Shaders/MissileVS.vs", "Shaders/MissileFS.fs");

	shaderMissile.Use();
	SetModel(Model(pathToModel));
	//_model = ;
	//_shader = shaderMissile;
	SetPosition(position);
	SetVelocity(0.2f);
	SetType(Constants::TIPO_MISIL);

	//_type = Constants::TIPO_MISIL;
	SetScale(vec3(0.4f));
	//_parent = parent;
}


Missile::Missile(Shader& shaderMissile, glm::vec3 position, GameObject* parent)
{
	shaderMissile.Use();
	SetModel(Model(pathToModel));
	_shader = shaderMissile;
	SetPosition(position);
	SetVelocity(0.2f);
	SetType(Constants::TIPO_MISIL);
	SetScale(vec3(0.4f));
	//_parent = parent;
}

Missile::Missile(Shader& shaderMissile, glm::vec3 position)
{
	shaderMissile.Use();
	SetModel(Model(pathToModel));
	_shader = shaderMissile;
	SetPosition(position);
	SetVelocity(0.2f);
	SetType(Constants::TIPO_MISIL);
	SetScale(vec3(0.4f));
	//_parent = &parent;
}


Missile::~Missile() {
	//delete this;
}

void Missile::Render(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 _modelMatrix = mat4(1.0f);

	_shader.Use();
	_modelMatrix = glm::translate(_modelMatrix, GetPosition());

	_modelMatrix = glm::scale(_modelMatrix, GetScale());
	//if (_parent->_type == Constants::TIPO_ENEMIGO) {
	//	Rotate(_modelMatrix);
	//}
	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", _modelMatrix);
	GetModel().Draw(_shader);
}


void Missile::Rotate(glm::mat4 &_modelMatrix) {
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(180.0f), glm::vec3(1.0f, 1.0f, 0.0f));

}

//GameObject* Missile::GetParent() {
//	return _parent;
//}

void Missile::Mover(const Movement movement, const float deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	vec3 oldPosition = GetPosition();
	vec3 newPosition = vec3(0.0f);
	switch (movement) {
	case Movement::Backward: //lanzado por enemigo
		newPosition = oldPosition + GetUpVector() * actualVelocity;
		SetPosition(newPosition);
		break;
	case Movement::Forward: //Lanzado por jugador
		newPosition = oldPosition - GetUpVector() * actualVelocity;
		SetPosition(newPosition);
		break;
	}

}
