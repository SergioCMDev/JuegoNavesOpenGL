#include "Player.h"

Player* Player::_instance;

Player::Player() {

}
Player::Player(Shader & shader, glm::vec3 position)
{
	_model = Model(pathToModel);
	_shader = shader;
	//_position = position;
	SetPosition(position);
	_velocity = 2.5f;
	_type = 1;
}

Player::~Player() {
	_instance = nullptr;
}

//Player::

//float Player::GetVelocity()
//{
//	return _playerSpeed;
//}

void Player::MoverJugador(const Movement movement, const float deltaTime)
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

Player * Player::Instance(Shader & shader, glm::vec3 position)
{
	if (_instance == 0) {
		_instance = new Player(shader, position);
	}
	return _instance;
}

Player * Player::GetInstance() {
	return _instance;

}
