#pragma once
#ifndef QUAD_H     
#define  QUAD_H
#include "Shader.h"
class QuadClasss {
public:
	QuadClasss();
	QuadClasss(Shader& shader);
	Shader *_shader;
	glm::vec3 _position;
	void Render(glm::mat4 projection, glm::mat4 view, vec3 posSuelo);
	uint32_t numeroElementosVerticesQuad = 20;
	glm::uint32_t CreateVAO();
	uint32_t numeroIndicesQuad = 6;
	uint32_t textures[3];
	glm::uint32_t _VAO;
	vec3 _scale = vec3(30.0f);
	void SetTexture(uint32_t texture);
	~QuadClasss();


private:

};
#endif

