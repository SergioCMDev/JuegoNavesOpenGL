#include "Enemy.h"

Enemy::Enemy() {

}
Enemy::Enemy(Shader & shader, glm::vec3 position)
{
	position = vec3(0.0f, 0.0f, 5.0f);
	_model = Model(pathToModel);
	_shader = shader;
	SetPosition(position);
	_velocity = 2.5f;
	_type = Constants::TIPO_ENEMIGO;
	_scale = glm::vec3(0.3f);
}

Enemy::Enemy(glm::vec3 position)
{
	Shader shaderNaveEnemiga = Utils::GetFullShader("Shaders/NavePlayerVS.vs", "Shaders/NavePlayerFS.fs");

	position = vec3(0.0f, 0.0f, 5.0f);
	_model = Model(pathToModel);
	_shader = shaderNaveEnemiga;
	SetPosition(position);
	_velocity = 2.5f;
	_type = Constants::TIPO_ENEMIGO;
	_scale = glm::vec3(0.3f);
}

Enemy::~Enemy() {

}

void Enemy::Disparar() {
	//Missile missile(_position, this);
	cout << "disparo" << endl;
}


void Enemy::Render(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 model = mat4(1.0f);

	_shader.Use();
	model = glm::translate(model, _position);

	model = glm::scale(model, _scale);

	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", model);
	_model.Draw(_shader);
}

void Enemy::Mover(const Movement movement, const float deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	float prev_y = _position.y;
	switch (movement) {
	case Movement::Forward:
		_position += GetUpVector() * actualVelocity; break;
	case Movement::Backward:
		_position -= GetUpVector() * actualVelocity; break;
	case Movement::Left:
		_position += GetRightVector() * actualVelocity; break;
	case Movement::Right:
		_position -= GetRightVector() * actualVelocity; break;
	}
}
