#include "Player.h"

Player::Player() {

}
Player::Player(Shader & shader, glm::vec3 position)
{
	position = vec3(0.0f, 0.0f, 5.0f);
	_model = Model(pathToModel);
	_shader = shader;
	SetPosition(position);
	_velocity = 2.5f;
	_type = Constants::TIPO_PLAYER;
}

Player::~Player() {
	//delete(;
}



void Player::Render(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view)
{

	_shader.Use();
	model = glm::translate(model, _position);
	//model = glm::rotate(model, (float)glm::radians(0.0f), vec3(0.0f, 1.0f, 0.0f));

	model = glm::scale(model, glm::vec3(0.1f));

	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", model);
	_model.Draw(_shader);
}

void Player::Mover(const Movement movement, const float deltaTime)
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
