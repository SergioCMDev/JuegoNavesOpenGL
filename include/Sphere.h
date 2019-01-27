#pragma once
#ifndef SPHERE_H     
#define  SPHERE_H
#include "Shader.h"
const float M_PI = 3.14f;

class Sphere2 {
public:
	Sphere2();
	Sphere2(Shader& shader, vec3 position, float radius);
	void Sphere2::RenderSphere(glm::mat4 &projection, glm::mat4 &view);
	Shader *_shader;
	glm::vec3 _position;
	glm::vec3 _color = vec3(1.0f);
	glm::uint32_t _VAO;
	vec3 _scale = vec3(2.4f);
	~Sphere2();
	float* _vertices;
	float* _normals;
	float* _textCoords;
	uint32_t* _elementos;
	uint32_t _numeroVertices;
	uint32_t _numeroElementos;
	uint32_t _numeroNormales;
	uint32_t _numeroTexturas;
	uint32_t _numeroIndices = 121 * 8;

private:
	uint32_t createSphere(const float radius);
	void generateVerts(float * verts, float * norms, float * tex, unsigned int * el, const uint32_t slices, const uint32_t stacks, const uint32_t radius);
};
#endif