#include "Enemy.h"

Enemy::Enemy() {

}
//Enemy::Enemy(Shader & shader, glm::vec3 position)
//{
//	shader.Use();
//	position = vec3(0.0f, 0.0f, 5.0f);
//	_model = Model(pathToModel);
//	_shader = shader;
//	SetPosition(position);
//	_velocity = 2.5f;
//	_type = Constants::TIPO_ENEMIGO;
//	_scale = glm::vec3(0.3f);
//}

Enemy::Enemy(glm::vec3 position)
{
	Shader shaderNaveEnemiga = Utils::GetFullShader("Shaders/NaveEnemyVS.vs", "Shaders/NaveEnemyFS.fs");
	shaderNaveEnemiga.Use();
	position = vec3(0.0f, 0.0f, 5.0f);
	SetModel(Model(pathToModel));
	_shader = shaderNaveEnemiga;
	SetPosition(position);
	SetVelocity(0.2f);
	SetType(Constants::TIPO_ENEMIGO);
	SetScale(glm::vec3(0.3f));
	Deactivate();
}

Enemy::~Enemy() {
	//delete this;
}

void Enemy::Disparar() {
	//Missile missile(_position, this);
	cout << "disparo" << endl;
}


void Enemy::Render(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 model = mat4(1.0f);

	_shader.Use();
	model = glm::translate(model, GetPosition());

	model = glm::scale(model, GetScale());

	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", model);
	GetModel().Draw(_shader);
}

void Enemy::Mover(const Movement movement, const float deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	switch (movement) {
	case Movement::Forward:
		SetPosition(GetPosition() + GetUpVector() * actualVelocity); break;
	case Movement::Backward:
		SetPosition(GetPosition() - GetUpVector() * actualVelocity); break;

		//_position -= GetUpVector() * actualVelocity; break;
	case Movement::Left:
		SetPosition(GetPosition() + GetRightVector() * actualVelocity); break;

		//_position += GetRightVector() * actualVelocity; break;
	case Movement::Right:
		SetPosition(GetPosition() - GetRightVector() * actualVelocity); break;
		//_position -= GetRightVector() * actualVelocity; break;
	}
}

