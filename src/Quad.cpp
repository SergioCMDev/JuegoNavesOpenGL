//#include "Quad.h"
//#include "Utils.h"
//
//Quad::Quad()
//{
//}
//Quad::Quad(Shader& shader)
//{
//	Shader shaderCube = Utils::GetFullShader("Shaders/CubeVS.vs", "Shaders/CubeFS.fs");
//	_shader = &shaderCube;
//	_VAO = CreateVAO();
//
//}
//
////uint32_t createVertexDataQuad(const float* vertices, const uint32_t n_verts, const uint32_t* indices, const uint32_t n_indices, const uint32_t numberOfElementsPerLine) {
////	unsigned int VAO, VBO, EBO;
////
////	glGenVertexArrays(1, &VAO);
////	//Generamos 2 buffer, elementos y objetos
////	glGenBuffers(1, &VBO);
////	glGenBuffers(1, &EBO);
////
////	//Bindeamos el VAO
////	glBindVertexArray(VAO);
////
////	uint32_t _numberOfElementsPerLine = numberOfElementsPerLine;
////	uint32_t stride = 3;
////
////	//Bindeamos buffer vertices
////	glBindBuffer(GL_ARRAY_BUFFER, VBO);
////	//Subida de vertices al buffer
////	glBufferData(GL_ARRAY_BUFFER, n_verts * sizeof(float) * _numberOfElementsPerLine, vertices, GL_STATIC_DRAW);
////
////	//Bindeo buffer indices
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
////	glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(float), indices, GL_STATIC_DRAW);
////
////	//vertices del triangulo 6 por que hay 6 elementos hasta el proximo inicio de linea
////	uint32_t atributteNumber = 0;
////
////	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)0);
////	glEnableVertexAttribArray(0);
////
////	//Vertices de textura
////	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)(stride * sizeof(float)));
////	glEnableVertexAttribArray(1);
////	stride += 2;
////
////
////	//desbindeamos buffer objetos
////	glBindBuffer(GL_ARRAY_BUFFER, 0);
////
////	//Desbindeo
////	glBindVertexArray(0);
////
////	//desbindeamos buffer elements
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
////
////	return VAO;
////}
//
//
//void Quad::Render(glm::mat4 projection, glm::mat4 view, vec3 position, float transparency)
//{
//
//	glm::mat4 model = mat4(1.0f);
//	_shader->Use();
//	_shader->Set("color", _color);
//	model = glm::translate(model, position);
//	model = glm::scale(model, _scale);
//	_shader->Set("projection", projection);
//	_shader->Set("view", view);
//	_shader->Set("model", model);
//	_shader->Set("transparency", transparency);
//	glBindVertexArray(_VAO);
//	glDrawElements(GL_TRIANGLES, numeroIndicesQuad, GL_UNSIGNED_INT, 0);
//}
//
//glm::uint32_t Quad::CreateVAO() {
//	unsigned int VAO, VBO, EBO;
//	float verticesQuad[20] = {
//		-0.5f,  0.5f,  0.5f,       0.0f, 0.0f,    //top
//		  0.5f,  0.5f,  0.5f,       1.0f, 0.0f,
//		  0.5f,  0.5f,  -0.5f,       1.0f, 1.0f,
//		  -0.5f,  0.5f,  -0.5f,       0.0f, 1.0f };
//
//	uint32_t _indicesCubo[36]{
//	0, 1, 2, 0, 2, 3 //Front
//
//	};
//
//	glGenVertexArrays(1, &VAO);
//	//Generamos 2 buffer, elementos y objetos
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	//Bindeamos el VAO
//	glBindVertexArray(VAO);
//
//	uint32_t _numberOfElementsPerLine = 5;
//	uint32_t stride = 3;
//
//	//Bindeamos buffer vertices
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//Subida de vertices al buffer
//	glBufferData(GL_ARRAY_BUFFER, numeroElementosVerticesQuad * sizeof(float) * _numberOfElementsPerLine, verticesQuad, GL_STATIC_DRAW);
//
//	//Bindeo buffer indices
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numeroIndicesQuad * sizeof(float), _indicesCubo, GL_STATIC_DRAW);
//
//	//vertices del triangulo 6 por que hay 6 elementos hasta el proximo inicio de linea
//	uint32_t atributteNumber = 0;
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	//Vertices de textura
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)(stride * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	stride += 2;
//	//Vertices normal
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)(stride * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	//desbindeamos buffer objetos
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	//Desbindeo
//	glBindVertexArray(0);
//
//	//desbindeamos buffer elements
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	return VAO;
//}
//
//Quad::~Quad() {
//	//glDeleteVertexArrays(1, &_VAO);
//
//}
//
