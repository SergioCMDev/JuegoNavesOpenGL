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


bool Player::Shooting()
{
	return _disparando;
}

void Player::NoShooting()
{
	_disparando = false;
}


GameObject* Player::GetUsableMissile() {
	GameObject* missileGameObject = nullptr;
	Node* poolMissilNode = GetActualNode()->GetChildren(0);
	bool found = false;
	for (size_t missile = 0; missile < poolMissilNode->GetNumberChildren(); missile++)
	{
		if (!poolMissilNode->GetChildren(missile)->GetGameObject()->Active()) {
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
		}
	}
}

void Player::Mover(const Movement movement, const float deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	vec3 newPosition = vec3(0.0f);
	switch (movement) {
	case Movement::Forward:
		newPosition = GetPosition() + GetUpVector() * actualVelocity;
		if (newPosition.z < Constants::MAX_POSITION_Y - 5.0f) {
			SetPosition(newPosition); break;
		}
	case Movement::Backward:
		newPosition = GetPosition() - GetUpVector() * actualVelocity;
		if (newPosition.z > Constants::MIN_POSITION_Y + 3.0f) {
			SetPosition(newPosition); break;
		}
	case Movement::Left:
		newPosition = GetPosition() + GetRightVector() * actualVelocity;
		if (newPosition.x < Constants::MAX_POSITION_X) {
			SetPosition(newPosition); break;
		}
	case Movement::Right:
		newPosition = GetPosition() - GetRightVector() * actualVelocity;
		if (newPosition.x > Constants::MIN_POSITION_X) {
			SetPosition(newPosition); break;

		}
	}
	//cout << "newPosition.x " << newPosition.x << endl;
}
