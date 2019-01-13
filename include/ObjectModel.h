#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H
#include<iostream>
#include "string.h"
#include "Shader.h"


class ObjectModel {

public:
	Model *model;
	Shader &shader;
	vec3 position;
};
#endif