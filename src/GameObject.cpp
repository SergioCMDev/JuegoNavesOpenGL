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

//GameObject::~GameObject()
//{
//	delete this;
//}



Node* GameObject::GetActualNode() {
	return _actualNode;
}
//
void GameObject::SetActualNode(Node * node) {
	_actualNode = node;
}

vec3 GameObject::GetScale()
{
	return _scale;
}

void GameObject::SetScale(vec3 scale)
{
	_scale = scale;
}

uint32_t GameObject::GetType()
{
	return _type;
}

void GameObject::SetType(uint32_t type)
{
	_type = type;
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

void GameObject::SetVelocity(float velocity)
{
	_velocity = velocity;
}

Model GameObject::GetModel() {
	return _model;
}

void GameObject::SetModel(Model model) {
	_model = model;
}

bool GameObject::Rendered()
{
	return _active;
}

void GameObject::Activate()
{
	_active = true;
}

void GameObject::Deactivate()
{
	_active = false;
}
