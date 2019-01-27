#include "Sphere.h"
#include "Utils.h"

Sphere::Sphere()
{
}
Sphere::Sphere(Shader& shader, vec3 position, float radius)
{
	//Shader shaderCube = Utils::GetFullShader("Shaders/CubeVS.vs", "Shaders/CubeFS.fs");
	_shader = &shader;
	_VAO = createSphere(radius);
	_position = position;
}

void Sphere::RenderSphere(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 model = glm::mat4(1.0f);
	_shader->Use();
	_shader->Set("color", _color);

	model = glm::translate(model, _position);
	model = glm::scale(model, _scale);

	_shader->Set("projection", projection);
	_shader->Set("view", view);
	_shader->Set("model", model);
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _numeroElementos, GL_UNSIGNED_INT, 0);
}



void Sphere::generateVerts(float * verts, float * norms, float * tex, unsigned int * el, const uint32_t slices, const uint32_t stacks, const uint32_t radius) {
	float theta, phi;       // Generate positions and normals
	float thetaFac = (float)((2.0 * M_PI) / slices);
	float phiFac = (float)(M_PI / stacks);
	float nx, ny, nz, s, t;
	uint32_t idx = 0, tIdx = 0;
	for (uint8_t i = 0; i <= slices; i++) {
		theta = i * thetaFac;
		s = (float)i / slices;
		for (uint8_t j = 0; j <= stacks; j++) {
			phi = j * phiFac;
			t = (float)j / stacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			verts[idx] = radius * nx;
			verts[idx + 1] = radius * ny;
			verts[idx + 2] = radius * nz;
			norms[idx] = nx;
			norms[idx + 1] = ny;
			norms[idx + 2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx + 1] = t;
			tIdx += 2;
		}
	}

	idx = 0;                      // Generate the element list
	for (uint8_t i = 0; i < slices; i++) {
		uint32_t stackStart = i * (stacks + 1);
		uint32_t nextStackStart = (i + 1) * (stacks + 1);
		for (uint8_t j = 0; j < stacks; j++) {
			if (j == 0) {
				el[idx] = stackStart;
				el[idx + 1] = stackStart + 1;
				el[idx + 2] = nextStackStart + 1;
				idx += 3;
			}
			else if (j == stacks - 1) {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j;
				idx += 3;
			}
			else {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j + 1;
				el[idx + 3] = nextStackStart + j;
				el[idx + 4] = stackStart + j;
				el[idx + 5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}
}

uint32_t Sphere::createSphere(const float radius) {
	constexpr int slices = 10;
	constexpr int stacks = 10;



	constexpr uint32_t nVerts = (slices + 1) * (stacks + 1); //121
	constexpr uint32_t elements = (slices * 2 * (stacks - 1)) * 3; //540

	float v[3 * nVerts];        // Verts      363 elementos
	float n[3 * nVerts];        // Normals    363 elementos
	float tex[2 * nVerts];      // Tex coords    242 elementos
	uint32_t el[elements];      // Elements

	generateVerts(v, n, tex, el, slices, stacks, radius);
	_vertices = v;
	_textCoords = tex;
	_elementos = el;
	_normals = n;
	_numeroVertices = nVerts * 3;
	_numeroNormales = nVerts * 3;
	_numeroTexturas = 2 * nVerts;
	_numeroElementos = elements;

	const int sizeTotal = (_numeroVertices + _numeroNormales + _numeroTexturas);

	//vector<float> newVertice2(sizeTotal);
	float newVertice2[3 * nVerts + 3 * nVerts + 2 * nVerts];

	for (size_t i = 0; i < _numeroVertices / 3; i++)
	{
		newVertice2[0 + 8 * i] = _vertices[3 * i];
		newVertice2[1 + 8 * i] = _vertices[3 * i + 1];
		newVertice2[2 + 8 * i] = _vertices[3 * i + 2];

		newVertice2[3 + 8 * i] = _normals[3 * i];
		newVertice2[4 + 8 * i] = _normals[3 * i + 1];
		newVertice2[5 + 8 * i] = _normals[3 * i + 2];

		newVertice2[6 + 8 * i] = _textCoords[2 * i];
		newVertice2[7 + 8 * i] = _textCoords[2 * i + 1];
	}

	uint32_t VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	//Generamos 2 buffer, elementos y objetos
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bindeamos el VAO
	glBindVertexArray(VAO);

	//Bindeamos buffer vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Subida de vertices al buffer

	glBufferData(GL_ARRAY_BUFFER, sizeof(newVertice2), &newVertice2, GL_STATIC_DRAW);


	//Bindeo buffer indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(el), el, GL_STATIC_DRAW);

	//Vertices de posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);

	////Vertices de normales
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(3 * (sizeof(float))));
	glEnableVertexAttribArray(1);

	//Vertices de textura
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(6 * (sizeof(float))));
	glEnableVertexAttribArray(2);


	//desbindeamos buffer objetos
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desbindeo
	glBindVertexArray(0);

	//desbindeamos buffer elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return VAO;

}

Sphere::~Sphere() {
	//glDeleteVertexArrays(1, &_VAO);

}

