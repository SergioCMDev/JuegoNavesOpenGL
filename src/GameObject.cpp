#include "Model.h"

#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(Model * model, Shader & shader, glm::vec3 position)
{
	_model = *model;
	_shader = shader;
	_position = position;
}

GameObject::GameObject(const char * pathToModel, Shader & shader, glm::vec3 position)
{
	_model = Model(pathToModel);
	_shader = shader;
	_position = position;
}
