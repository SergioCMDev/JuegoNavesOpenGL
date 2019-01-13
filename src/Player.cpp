#include "Player.h"

Player::Player(Shader & shader, glm::vec3 position)
{
	_model = Model(pathToModel);
	_shader = shader;
	//_position = position;
	SetPosition( position);
}

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
			_position -= GetRightVector() * actualVelocity; break;
		case Movement::Right:
			_position += GetRightVector() * actualVelocity; break;
		}


		//updateCameraVectors();

}
//if (glfwGetKey(window.GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
//	objects.modelos[0]->position += _right * deltaTime;
//}
//if (glfwGetKey(window.GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
//	objects.modelos[0]->position -= _right * deltaTime;
//}
//if (glfwGetKey(window.GetWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
//	objects.modelos[0]->position += _up * deltaTime;
//}
//if (glfwGetKey(window.GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
//	objects.modelos[0]->position -= _up * deltaTime;
//}