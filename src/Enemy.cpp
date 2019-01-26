#include "Enemy.h"
float lastTimeShooted = 0.0f;

glm::vec3 EnemyShipOriginPositions[] = {
 glm::vec3(0.0f,  0.0f, 15.0f), //z == arriba/abajo, X derecha/izq invertida
 glm::vec3(7.0f,  0.0f, 15.0f),
 glm::vec3(4.0f, 0.0f, 15.0f),
 glm::vec3(-5.0f,  0.0f, 15.0f),
 glm::vec3(-6.0f, 0.0f, 15.0f),
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



uint32_t Enemy::GetLastMissileUsed()
{
	return _lastMissileUsed;
}
void Enemy::SumLastMissileUsed()
{
	_lastMissileUsed++;
}

bool Enemy::Shooting()
{
	return _disparando;
}

void Enemy::NoShooting()
{
	_disparando = false;
}

uint32_t Enemy::GetTypeShip()
{
	return _typeShip;
}

Enemy::Enemy(Shader& shader)
//position = vec3(0.0f, 0.0f, 15.0f);
{
	srand(rand());
	uint32_t _typeShip = -1;

	do {
		_typeShip = rand() % GetNumberPositions();
	} while (_typeShip < 0 || _typeShip >2);

	if (_typeShip == 1) {
		SetModel(Model(pathToModel2)); //SPACESHIP
		SetScale(glm::vec3(0.3f));

	}
	else {
		SetModel(Model(pathToModel)); //UFO
		SetScale(glm::vec3(0.03f));

	}
	_shader = shader;
	SetVelocity(1.2f);
	SetType(Constants::TIPO_ENEMIGO);
	Deactivate();

}

Enemy::~Enemy() {
	//delete this;
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
///TODO
void Enemy::Mover(const float deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	//switch (_typeShip) {
	//case 1:
	//	SetPosition(GetPosition() + (-GetRightVector() - GetUpVector()) * actualVelocity); break;
	//case 2:
	//	SetPosition(GetPosition() + (GetRightVector() - GetUpVector()) * actualVelocity); break;


	//}
		SetPosition(GetPosition() - GetUpVector() * actualVelocity);
}
GameObject* Enemy::GetUsableMissile() {
	GameObject* missileGameObject = nullptr;
	Node* poolMissilNode = GetActualNode()->GetChildren(0);
	bool found = false;
	for (size_t missile = 0; missile < poolMissilNode->GetNumberChildren(); missile++)
	{
		if (!poolMissilNode->GetChildren(missile)->GetGameObject()->Rendered()) {
			missileGameObject = poolMissilNode->GetChildren(missile)->GetGameObject();
			break;
		}

	}
	return missileGameObject;
}

void Enemy::Disparar() {

	float currentFrame = glfwGetTime();
	if (currentFrame > (lastTimeShooted + 3.0f)) {
		_disparando = true;
		lastTimeShooted = currentFrame;
		GameObject* missileGameObject = GetUsableMissile();
		if (missileGameObject != nullptr) {
			Missile* missile = static_cast<Missile*>(missileGameObject);
			missile->SetPosition(this->GetPosition());
			missile->Activate();
			SumLastMissileUsed();
		}
	}
}