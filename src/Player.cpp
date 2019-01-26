#include "Player.h"
float lastTimeShooted = 0.0f;
Player::Player() {

}


Player::Player(Shader & shader, glm::vec3 position)
{
	_shader = shader;
	position = position;
	SetModel(Model(pathToModel));
	SetPosition(position);
	SetVelocity(2.5f);
	SetType(Constants::TIPO_PLAYER);
	SetScale(glm::vec3(0.1f));
	Activate();
}

Player::~Player() {
	//delete this;
}

uint32_t Player::GetLastMissileUsed()
{
	return _lastMissileUsed;
}

void Player::SumLastMissileUsed()
{
	_lastMissileUsed++;
}

bool Player::Shooting()
{
	return _disparando;
}

void Player::NoShooting()
{
	_disparando = false;
}

void Player::RemoveMissileUsed()
{
	_lastMissileUsed--;
}

GameObject* Player::GetUsableMissile() {
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

void Player::Disparar() {

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

void Player::Render(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 model = mat4(1.0f);
	model = glm::translate(model, GetPosition());
	//model = glm::rotate(model, (float)glm::radians(0.0f), vec3(0.0f, 1.0f, 0.0f));

	model = glm::scale(model, GetScale());

	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", model);
	GetModel().Draw(_shader);
}

void Player::Mover(const Movement movement, const float deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	switch (movement) {
	case Movement::Forward:
		SetPosition(GetPosition() + GetUpVector() * actualVelocity); break;
	case Movement::Backward:
		SetPosition(GetPosition() - GetUpVector() * actualVelocity); break;
	case Movement::Left:
		SetPosition(GetPosition() + GetRightVector() * actualVelocity); break;
	case Movement::Right:
		SetPosition(GetPosition() - GetRightVector() * actualVelocity); break;
	}
}
