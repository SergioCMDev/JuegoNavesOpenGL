#include "Meteor.h"



Meteor::Meteor() {

}
Meteor::Meteor(Shader & shader, glm::vec3 position)
{
	_model = Model(pathToModel);
	_shader = shader;
	//_position = position;
	SetPosition(position);
	_velocity = 2.5f;
	_type = 2;
}

Meteor::~Meteor() {
	/*_instance = nullptr;*/
}

//Player::

//float Player::GetVelocity()
//{
//	return _playerSpeed;
//}



void Meteor::Render(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view)
{

	_shader.Use();
	model = glm::translate(model, _position);
	model = glm::scale(model, glm::vec3(0.1f));

	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", model);
	_model.Draw(_shader);
}

void Meteor::Mover(const Movement movement, const float deltaTime)
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

void Meteor::RenderMeteor(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view)
{
	model = glm::translate(model, _position);
	model = glm::scale(model, _scale);

	_shader.Use();
	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", model);
	_model.Draw(_shader);
}


