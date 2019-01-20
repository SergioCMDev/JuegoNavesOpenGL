#include "Cube.h"
#include "Utils.h"

Cube::Cube()
{
}
Cube::Cube(Shader& shader)
{
	_shader = &shader;
	_VAO = CreateVAO();

}


void Cube::Render(glm::mat4 projection, glm::mat4 view, vec3 position)
{

	glm::mat4 model = mat4(1.0f);
	_shader->Use();
	_shader->Set("color", _color);
	model = glm::translate(model, position);
	model = glm::scale(model, _scale);
	_shader->Set("projection", projection);
	_shader->Set("view", view);
	_shader->Set("model", model);
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _numeroIndices, GL_UNSIGNED_INT, 0);
}

glm::uint32_t Cube::CreateVAO() {
	unsigned int VAO, VBO, EBO;
	float _verticesCubo[192] = {  //vertices      //uvs     //normals
	  -0.5f,  -0.5f,  0.5f,       0.0f, 0.0f,     0.0f, 0.0f, 1.0f,//front
	  0.5f,  -0.5f,  0.5f,       1.0f, 0.0f,      0.0f, 0.0f, 1.0f,
	  0.5f,  0.5f,  0.5f,       1.0f, 1.0f,       0.0f, 0.0f, 1.0f,
	  -0.5f, 0.5f,  0.5f,       0.0f, 1.0f,       0.0f, 0.0f, 1.0f,

	  0.5f,  -0.5f,  0.5f,       0.0f, 0.0f,      1.0f, 0.0f, 0.0f,//right
	  0.5f,  -0.5f,  -0.5f,       1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
	  0.5f,  0.5f,  -0.5f,       1.0f, 1.0f,      1.0f, 0.0f, 0.0f,
	  0.5f,  0.5f,  0.5f,       0.0f, 1.0f,       1.0f, 0.0f, 0.0f,

	  -0.5f,  -0.5f,  -0.5f,       1.0f, 0.0f,    0.0f, 0.0f, -1.0f,//back
	  -0.5f,  0.5f,  -0.5f,       1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
	  0.5f,  0.5f,  -0.5f,       0.0f, 1.0f,      0.0f, 0.0f, -1.0f,
	  0.5f,  -0.5f,  -0.5f,       0.0f, 0.0f,     0.0f, 0.0f, -1.0f,

	  -0.5f,  -0.5f,  0.5f,       1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,//left
	  -0.5f,  0.5f,  0.5f,       1.0f, 1.0f,      -1.0f, 0.0f, 0.0f,
	  -0.5f,  0.5f,  -0.5f,       0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
	  -0.5f,  -0.5f,  -0.5f,       0.0f, 0.0f,    -1.0f, 0.0f, 0.0f,

	  -0.5f,  -0.5f,  0.5f,       0.0f, 1.0f,     0.0f, -1.0f, 0.0f,//bottom
	  -0.5f,  -0.5f,  -0.5f,       0.0f, 0.0f,    0.0f, -1.0f, 0.0f,
	  0.5f,  -0.5f,  -0.5f,       1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
	  0.5f,  -0.5f,  0.5f,       1.0f, 1.0f,      0.0f, -1.0f, 0.0f,

	  -0.5f,  0.5f,  0.5f,       0.0f, 0.0f,      0.0f, 1.0f, 0.0f,//top
	  0.5f,  0.5f,  0.5f,       1.0f, 0.0f,       0.0f, 1.0f, 0.0f,
	  0.5f,  0.5f,  -0.5f,       1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
	  -0.5f,  0.5f,  -0.5f,       0.0f, 1.0f,     0.0f, 1.0f, 0.0f };

	uint32_t _indicesCubo[36]{
	0, 1, 2, 0, 2, 3 //Front
	,4, 5, 6, 4, 6, 7 //Right
	,8, 9, 10, 8, 10, 11 //Back
	,12, 13, 14, 12, 14, 15 //Left
	,16, 17, 18, 16, 18, 19 //Bottom
	,20, 21, 22, 20, 22, 23 //Top
	};

	glGenVertexArrays(1, &VAO);
	//Generamos 2 buffer, elementos y objetos
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bindeamos el VAO
	glBindVertexArray(VAO);

	uint32_t _numberOfElementsPerLine = 8;
	uint32_t stride = 3;

	//Bindeamos buffer vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Subida de vertices al buffer
	glBufferData(GL_ARRAY_BUFFER, _numeroElementosVerticesCubo * sizeof(float) * _numberOfElementsPerLine, _verticesCubo, GL_STATIC_DRAW);

	//Bindeo buffer indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numeroIndices * sizeof(float), _indicesCubo, GL_STATIC_DRAW);

	//vertices del triangulo 6 por que hay 6 elementos hasta el proximo inicio de linea
	uint32_t atributteNumber = 0;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Vertices de textura
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)(stride * sizeof(float)));
	glEnableVertexAttribArray(1);
	stride += 2;
	//Vertices normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)(stride * sizeof(float)));
	glEnableVertexAttribArray(2);

	//desbindeamos buffer objetos
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desbindeo
	glBindVertexArray(0);

	//desbindeamos buffer elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return VAO;
}

Cube::~Cube() {
	//glDeleteVertexArrays(1, &_VAO);

}