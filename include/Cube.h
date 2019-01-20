#pragma once
#ifndef CUBE_H     
#define  CUBE_H
#include "Shader.h"
class Cube {
public:
	Cube();
	Cube(Shader& shader);
	Shader *_shader;
	glm::vec3 _position;
	void Cube::Render(glm::mat4 projection, glm::mat4 view, vec3 position);
	glm::uint32_t CreateVAO();
	uint32_t _numeroIndices = 36;
	glm::vec3 _color;
	uint32_t _numeroElementosVerticesCubo = 192;
	glm::uint32_t _VAO;
	vec3 _scale = vec3(1.0f);


private:
};
#endif