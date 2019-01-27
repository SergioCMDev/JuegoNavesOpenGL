#include "Quad.h"
#include "Utils.h"

QuadClasss::QuadClasss()
{
}
QuadClasss::QuadClasss(Shader& shader)
{
	_shader = &shader;
	_VAO = CreateVAO();

}


void QuadClasss::Render(glm::mat4 projection, glm::mat4 view, vec3 position)
{

	glm::mat4 model = mat4(1.0f);
	glActiveTexture(GL_TEXTURE4);	glBindTexture(GL_TEXTURE_2D, textures[0]);
	_shader->Use();
	_shader->Set("quadTexture", 4);
	model = glm::translate(model, position);
	model = glm::scale(model, _scale);
	_shader->Set("projection", projection);
	_shader->Set("view", view);
	_shader->Set("model", model);
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

glm::uint32_t QuadClasss::CreateVAO() {
	unsigned int VAO, VBO, EBO;
	float verticesQuad[] = {
		-0.5f,  0.5f,  0.5f,       0.0f, 0.0f,    //top
		  0.5f,  0.5f,  0.5f,       1.0f, 0.0f,
		  0.5f,  0.5f,  -0.5f,       1.0f, 1.0f,
		  -0.5f,  0.5f,  -0.5f,       0.0f, 1.0f };

	uint32_t indicesQuad[6]{
	0, 1, 2, 0, 2, 3 //Front
	};

	glGenVertexArrays(1, &VAO);
	//Generamos 2 buffer, elementos y objetos
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bindeamos el VAO
	glBindVertexArray(VAO);

	uint32_t _numberOfElementsPerLine = 5;
	uint32_t stride = 3;

	//Bindeamos buffer vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Subida de vertices al buffer
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float) * _numberOfElementsPerLine, verticesQuad, GL_STATIC_DRAW);

	//Bindeo buffer indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indicesQuad, GL_STATIC_DRAW);

	//vertices del triangulo 6 por que hay 6 elementos hasta el proximo inicio de linea
	uint32_t atributteNumber = 0;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Vertices de textura
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)(stride * sizeof(float)));
	glEnableVertexAttribArray(1);
	stride += 2;


	//desbindeamos buffer objetos
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desbindeo
	glBindVertexArray(0);

	//desbindeamos buffer elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return VAO;
}

QuadClasss::~QuadClasss() {
	//glDeleteVertexArrays(1, &_VAO);

}

