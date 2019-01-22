#include "Enemy.h"
glm::vec3 EnemyShipOriginPositions[] = {
 glm::vec3(12.0f,  0.0f, 10.0f), // X derecha/izq invertida //z == arriba/abajo,
 glm::vec3(-12.0f,  0.0f, 10.0f),
 //glm::vec3(18.0f,  0.0f, 10.0f),
 //glm::vec3(15.0f, 0.0f, 12.0f),
 //glm::vec3(18.0f, 0.0f, 10.0f),
};


uint32_t Enemy::GetNumberPositions() {
	return sizeof(EnemyShipOriginPositions) / sizeof(glm::vec3);
}

vec3 Enemy::GetEnemyPosition(uint32_t index)
{
	return EnemyShipOriginPositions[index];
}

Enemy::Enemy() {

}


Enemy::Enemy(glm::vec3 position)
{
	Shader shaderNaveEnemiga = Utils::GetFullShader("Shaders/NaveEnemyVS.vs", "Shaders/NaveEnemyFS.fs");
	shaderNaveEnemiga.Use();
	//position = vec3(0.0f, 0.0f, 15.0f);
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

void Enemy::SetRandomPosition()
{
	srand(rand());
	 uint32_t initialPositionIndex = -1;
	do {
		initialPositionIndex = rand() % GetNumberPositions();
	} while (initialPositionIndex <0 || initialPositionIndex >GetNumberPositions());

	vec3 positionInitial = EnemyShipOriginPositions[initialPositionIndex];
	SetPosition(positionInitial);
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

