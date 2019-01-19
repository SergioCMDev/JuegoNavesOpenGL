#include "Model.h"

#include "GameObject.h"

GameObject::GameObject()
{
}

//GameObject::GameObject(Model * model, Shader & shader, glm::vec3 position)
//{
//	_model = *model;
//	_shader = shader;
//	_position = position;
//}
//
//GameObject::GameObject(const  char * pathToModel, Shader & shader, glm::vec3 position)
//{
//	_model = Model(pathToModel);
//	_shader = shader;
//	_position = position;
//}

glm::vec3 GameObject::GetPosition()
{
	return _position;
}

void GameObject::SetPosition(glm::vec3 position)
{
	_position = position;
}

bool GameObject::HasChildren() {
	return _hasChildren;
}

glm::vec3 GameObject::GetUpVector()
{
	return _up;
}

uint32_t GameObject::GetNumberChildren() {
	return _lastChildren+1;
}

void GameObject::AddChildren(GameObject* objectChildren) {
	if (_hasChildren) {
		_lastChildren++;
	}
	else {
		_hasChildren = true;
	}
	_children[_lastChildren] = objectChildren;
}

GameObject* GameObject::GetChildren(uint32_t idChildren) {
	return _children[idChildren];
}

glm::vec3 GameObject::GetRightVector()
{
	return _right;
}

float GameObject::GetVelocity()
{
	return _velocity;
}