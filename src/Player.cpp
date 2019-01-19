#include "Player.h"

Player::Player() {

}
Player::Player(glm::vec3 position)
{
	Shader shaderNavePlayer = Utils::GetFullShader("Shaders/NavePlayerVS.vs", "Shaders/NavePlayerFS.fs");
	shaderNavePlayer.Use();
	position = vec3(0.0f, 0.0f, 0.0f);
	_model = Model(pathToModel);
	_shader = shaderNavePlayer;
	SetPosition(position);
	_velocity = 2.5f;
	_type = Constants::TIPO_PLAYER;
	_scale = vec3(0.2f);

}

Player::Player(Shader & shader, glm::vec3 position)
{
	shader.Use();
	_shader = shader;

	position = vec3(0.0f, 0.0f, 0.0f);
	_model = Model(pathToModel);
	SetPosition(position);
	_velocity = 2.5f;
	_type = Constants::TIPO_PLAYER;
	_scale = vec3(0.2f);

}

Player::~Player() {
	//delete(;
}
void Player::Disparar() {
	//Missile missile(_position, this);
	cout << "disparo" << endl;
}

//void Player::RenderChildren(glm::mat4 &projection, glm::mat4 &view, GameObject* children[])
//{
//	for (size_t i = 0; i < ; i++)
//	{
//
//	}
//	glm::mat4 model = mat4(1.0f);
//	_shader.Use();
//	model = glm::translate(model, _position);
//	//model = glm::rotate(model, (float)glm::radians(0.0f), vec3(0.0f, 1.0f, 0.0f));
//
//	model = glm::scale(model, _scale);
//
//	_shader.Set("projection", projection);
//	_shader.Set("view", view);
//	_shader.Set("model", model);
//	_model.Draw(_shader);
//}


void Player::Render(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 model = mat4(1.0f);
	_shader.Use();
	model = glm::translate(model, _position);
	//model = glm::rotate(model, (float)glm::radians(0.0f), vec3(0.0f, 1.0f, 0.0f));

	model = glm::scale(model, _scale);

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
