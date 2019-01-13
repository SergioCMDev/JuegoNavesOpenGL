#include "Player.h"
#include "Shader.h"
#include "Constants.h"
#include "ObjectModel.h"

void Player::MoverJugador(const Movement movement, const ObjectModel model, const float deltaTime)
{
		//float velocity = k_Speed * deltaTime;
		//float prev_y = _position.y;
		//switch (movement) {
		/*case Movement::Forward:
			model_position += _front * velocity; break;
		case Movement::Backward:
			_position -= _front * velocity; break;
		case Movement::Left:
			_position -= _right * velocity; break;
		case Movement::Right:
			_position += _right * velocity; break;
		}*/


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