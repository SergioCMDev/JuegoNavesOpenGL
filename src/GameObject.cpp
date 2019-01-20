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

Node* GameObject::GetActualNode() {
	return _actualNode;
}
//
void GameObject::SetActualNode(Node * node) {
	_actualNode = node;
}


glm::vec3 GameObject::GetPosition()
{
	return _position;
}

void GameObject::SetPosition(glm::vec3 position)
{
	_position = position;
}



glm::vec3 GameObject::GetUpVector()
{
	return _up;
}


glm::vec3 GameObject::GetRightVector()
{
	return _right;
}

float GameObject::GetVelocity()
{
	return _velocity;
}