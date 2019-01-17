#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<cstdint>
#include<stdio.h>

#include "Constants.h"
#include "Shader.h"
#include "Utils.h"

#include "Window.h"
#include "Camera.h"
#include "GameObject.h"

#include "Player.h"
#include "Meteor.h"
#include "Enemy.h"


const vec3 posCamera = glm::vec3(0.0f, 20.0f, 0.0f);

Camera camera(posCamera);
#pragma region Variables Globales
const float M_PI = 3.14f;
const vec3 posSuelo = vec3(0.0f, -16.0f, 0.0f);
const vec3 posPlayer = vec3(5.0f, 0.0f, 0.0f);
const float screen_width = 800.0f, screen_height = 600.0f;
float lastY = (float)screen_height / 2.0f;
float lastX = (float)screen_width / 2.0f;


float lastFrame = 0.0f;
bool firstMouse = true;

Window window;
#pragma endregion


#pragma region Comments

//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//glm::vec3 pointLightPositions[] = {
//	glm::vec3(0.7f, 0.2f, 2.0f),
//	glm::vec3(2.3f, -3.3f, -4.0f)
//};
//
//glm::vec3 spotLightPositions[] = {
//	glm::vec3(2.7f, 3.2f, 2.0f),
//	glm::vec3(-2.7f, 3.2f, -5.0f),
//
//};






glm::vec3 MeteorOriginPositions[] = {
 glm::vec3(0.0f,  0.0f, 15.0f), //z == arriba/abajo, X derecha/izq invertida
 glm::vec3(5.0f,  0.0f, 15.0f),
 glm::vec3(8.0f, 0.0f, 15.0f),
 glm::vec3(-5.0f,  0.0f, 15.0f),
 glm::vec3(-8.0f, 0.0f, 15.0f),
};


glm::vec3 EnemyShipOriginPositions[] = {
 glm::vec3(12.0f,  0.0f, 10.0f), // X derecha/izq invertida //z == arriba/abajo,
 glm::vec3(-12.0f,  0.0f, 10.0f),
 //glm::vec3(18.0f,  0.0f, 10.0f),
 //glm::vec3(15.0f, 0.0f, 12.0f),
 //glm::vec3(18.0f, 0.0f, 10.0f),
};


#pragma endregion
float verticesCubo[] = {  //vertices      //uvs     //normals
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

float verticesQuad[] = {
	-0.5f,  0.5f,  0.5f,       0.0f, 0.0f,    //top
	  0.5f,  0.5f,  0.5f,       1.0f, 0.0f,
	  0.5f,  0.5f,  -0.5f,       1.0f, 1.0f,
	  -0.5f,  0.5f,  -0.5f,       0.0f, 1.0f };
#pragma endregion



struct Quad {
	float* vertices;
	float* normals;
	float* textCoords;
	uint32_t* elementos;
	uint32_t numeroVertices;
	uint32_t numeroElementos;
	uint32_t numeroElementosVerticesQuad = 20;
	uint32_t numeroElementosParaDibujar;
	uint32_t numeroIndicesQuad = 6;
	uint32_t numeroNormales;
	uint32_t numeroTexturas;
	uint32_t textures[3];
	Shader *shader;
	uint32_t* VAO;

	uint32_t indicesQuad[6]{
	0, 1, 2, 0, 2, 3 //Front
	};
};


struct Cube {
	float* vertices;
	float* normals;
	float* textCoords;
	uint32_t* elementos;
	uint32_t numeroVertices;
	uint32_t numeroElementos;
	uint32_t numeroElementosParaDibujar;
	uint32_t numeroIndices = 36;
	vec3 color;
	Shader *shader;
	uint32_t numeroElementosVerticesCubo = 192;
	uint32_t* VAO;
	
	uint32_t indicesCubo[36]{
		0, 1, 2, 0, 2, 3 //Front
		,4, 5, 6, 4, 6, 7 //Right
		,8, 9, 10, 8, 10, 11 //Back
		,12, 13, 14, 12, 14, 15 //Left
		,16, 17, 18, 16, 18, 19 //Bottom
		,20, 21, 22, 20, 22, 23 //Top
	};
};



struct TransferObjects {
	const uint32_t maximoModelos = Constants::MaximoObjectosTransferencia;
	uint32_t numeroModelos;
	GameObject *modelos[10];
};


using namespace std;

Player* GetPlayerReference(GameObject* objectPlayer) {
	GameObject *g = objectPlayer;
	Player* player = static_cast<Player*>(objectPlayer);
	return player;
}

#pragma region Eventos

void OnChangeFrameBufferSize(GLFWwindow* window, const int32_t width, const int32_t height) {
	//redimension de pantalla 
	//Cambio de clip scene a view scene
	glViewport(0, 0, width, height);
}

void OnMouse(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		firstMouse = false;
		lastX = xpos;
		lastY = ypos;
	}

	double xoffset = xpos - lastX;
	double yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;
	camera.handleMouseMovement(xoffset, yoffset);
}

void OnScroll(GLFWwindow* window, double xoffset, double yoffset) {
	camera.handleMouseScroll(yoffset);
}

void MovimientoCamara(const double &deltaTime)
{
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		camera.HandleKeyboard(Camera::Movement::Forward, deltaTime);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		camera.HandleKeyboard(Camera::Movement::Backward, deltaTime);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		camera.HandleKeyboard(Camera::Movement::Left, deltaTime);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		camera.HandleKeyboard(Camera::Movement::Right, deltaTime);
	}
}

void MovimientoJugador(const float &deltaTime, Player* player)
{
	//Player player = ((Player)*objects.modelos[0]);
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		//player->_position += vec3(1.0f, 0.0f, 0.0f) * deltaTime;
		player->Mover(Player::Movement::Left, deltaTime);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//player->_position -= vec3(1.0f, 0.0f, 0.0f) * deltaTime;
		player->Mover(Player::Movement::Right, deltaTime);

	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
		//player->_position += vec3(0.0f, 0.0f, 1.0f) * deltaTime;
		player->Mover(Player::Movement::Forward, deltaTime);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		//player->_position -= vec3(0.0f, 0.0f, 1.0f) * deltaTime;
		player->Mover(Player::Movement::Backward, deltaTime);
	}
}

void HandlerInput(const double deltaTime, TransferObjects objects) {
	MovimientoCamara(deltaTime);
	if (objects.modelos[0]->_type == Constants::TIPO_PLAYER) {
		Player* player = GetPlayerReference(objects.modelos[0]);
		MovimientoJugador(deltaTime, player);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window.GetWindow(), true);
	}

}
#pragma endregion



#pragma region Metodos

#pragma region Generacion esfera



//void generateVerts(float * verts, float * norms, float * tex, unsigned int * el, const uint32_t slices, const uint32_t stacks, const uint32_t radius) {
//	float theta, phi;       // Generate positions and normals
//	float thetaFac = (float)((2.0 * M_PI) / slices);
//	float phiFac = (float)(M_PI / stacks);
//	float nx, ny, nz, s, t;
//	uint32_t idx = 0, tIdx = 0;
//	for (uint8_t i = 0; i <= slices; i++) {
//		theta = i * thetaFac;
//		s = (float)i / slices;
//		for (uint8_t j = 0; j <= stacks; j++) {
//			phi = j * phiFac;
//			t = (float)j / stacks;
//			nx = sinf(phi) * cosf(theta);
//			ny = sinf(phi) * sinf(theta);
//			nz = cosf(phi);
//			verts[idx] = radius * nx;
//			verts[idx + 1] = radius * ny;
//			verts[idx + 2] = radius * nz;
//			norms[idx] = nx;
//			norms[idx + 1] = ny;
//			norms[idx + 2] = nz;
//			idx += 3;
//
//			tex[tIdx] = s;
//			tex[tIdx + 1] = t;
//			tIdx += 2;
//		}
//	}
//
//	idx = 0;                      // Generate the element list
//	for (uint8_t i = 0; i < slices; i++) {
//		uint32_t stackStart = i * (stacks + 1);
//		uint32_t nextStackStart = (i + 1) * (stacks + 1);
//		for (uint8_t j = 0; j < stacks; j++) {
//			if (j == 0) {
//				el[idx] = stackStart;
//				el[idx + 1] = stackStart + 1;
//				el[idx + 2] = nextStackStart + 1;
//				idx += 3;
//			}
//			else if (j == stacks - 1) {
//				el[idx] = stackStart + j;
//				el[idx + 1] = stackStart + j + 1;
//				el[idx + 2] = nextStackStart + j;
//				idx += 3;
//			}
//			else {
//				el[idx] = stackStart + j;
//				el[idx + 1] = stackStart + j + 1;
//				el[idx + 2] = nextStackStart + j + 1;
//				el[idx + 3] = nextStackStart + j;
//				el[idx + 4] = stackStart + j;
//				el[idx + 5] = nextStackStart + j + 1;
//				idx += 6;
//			}
//		}
//	}
//}

//uint32_t createSphere(const float radius) {
//	constexpr int slices = 10;
//	constexpr int stacks = 10;
//
//	Sphere sphere;
//
//	constexpr uint32_t nVerts = (slices + 1) * (stacks + 1); //121
//	constexpr uint32_t elements = (slices * 2 * (stacks - 1)) * 3; //540
//
//	float v[3 * nVerts];        // Verts      363 elementos
//	float n[3 * nVerts];        // Normals    363 elementos
//	float tex[2 * nVerts];      // Tex coords    242 elementos
//	uint32_t el[elements];      // Elements
//
//	generateVerts(v, n, tex, el, slices, stacks, radius);
//	sphere.vertices = v;
//	sphere.textCoords = tex;
//	sphere.elementos = el;
//	sphere.normals = n;
//	sphere.numeroVertices = nVerts * 3;
//	sphere.numeroNormales = nVerts * 3;
//	sphere.numeroTexturas = 2 * nVerts;
//	sphere.numeroElementos = elements;
//
//	const int sizeTotal = (sphere.numeroVertices + sphere.numeroNormales + sphere.numeroTexturas);
//
//	//vector<float> newVertice2(sizeTotal);
//	float newVertice2[3 * nVerts + 3 * nVerts + 2 * nVerts];
//
//	for (size_t i = 0; i < sphere.numeroVertices / 3; i++)
//	{
//		newVertice2[0 + 8 * i] = sphere.vertices[3 * i];
//		newVertice2[1 + 8 * i] = sphere.vertices[3 * i + 1];
//		newVertice2[2 + 8 * i] = sphere.vertices[3 * i + 2];
//
//		newVertice2[3 + 8 * i] = sphere.normals[3 * i];
//		newVertice2[4 + 8 * i] = sphere.normals[3 * i + 1];
//		newVertice2[5 + 8 * i] = sphere.normals[3 * i + 2];
//
//		newVertice2[6 + 8 * i] = sphere.textCoords[2 * i];
//		newVertice2[7 + 8 * i] = sphere.textCoords[2 * i + 1];
//	}
//
//	uint32_t VAO, VBO, EBO;
//
//	glGenVertexArrays(1, &VAO);
//	//Generamos 2 buffer, elementos y objetos
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	//Bindeamos el VAO
//	glBindVertexArray(VAO);
//
//	//Bindeamos buffer vertices
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//Subida de vertices al buffer
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(newVertice2), &newVertice2, GL_STATIC_DRAW);
//
//
//	//Bindeo buffer indices
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(el), el, GL_STATIC_DRAW);
//
//	//Vertices de posicion
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	////Vertices de normales
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(3 * (sizeof(float))));
//	glEnableVertexAttribArray(1);
//
//	//Vertices de textura
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(6 * (sizeof(float))));
//	glEnableVertexAttribArray(2);
//
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
//
//	//return sphere;
//
//}
#pragma endregion


int Inicializacion() {
	if (!glfwInit()) {
		cout << "Error initializing GLFW" << endl;
		glfwTerminate();
		return -1;
	}
	//Window window1 = Window(screen_width, screen_height);
	window = *Window::GetInstance(screen_width, screen_height);
	//window.AddCamera(camera);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Error initializing GLAD" << endl;
		return -1;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//cuando la ventana cambie de tamaño
	//glfwSetCursorPosCallback(window.GetWindow(), &Window::OnMouse);
	glfwSetCursorPosCallback(window.GetWindow(), OnMouse);
	glfwSetFramebufferSizeCallback(window.GetWindow(), OnChangeFrameBufferSize);
	glfwSetScrollCallback(window.GetWindow(), OnScroll);
	glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 1;
};

void MoveObjects(const double deltaTim, TransferObjects transfer) {
	for (size_t i = 0; i < transfer.numeroModelos; i++)
	{
		if (transfer.modelos[i]->_type == Constants::TIPO_METEOR)
		{
			GameObject *g = transfer.modelos[i];
			Meteor* meteor = static_cast<Meteor*>(g);

			meteor->Mover(deltaTim);
		}
	}
}

#pragma region Render Figures

void RenderFigure(const Shader & shader, glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model, const uint32_t &VAO, const uint32_t &numeroElementos)
{
	shader.Set("projection", projection);
	shader.Set("view", view);
	shader.Set("model", model);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numeroElementos, GL_UNSIGNED_INT, 0);
}

void RenderQuadSuelo(Quad &quad, glm::mat4 &projection, glm::mat4 &view)
{
	glActiveTexture(GL_TEXTURE4);	glBindTexture(GL_TEXTURE_2D, quad.textures[0]);

	quad.shader->Use();
	quad.shader->Set("quadTexture", 4);
	glm::mat4 model = mat4(1.0f);
	model = glm::translate(model, posSuelo);
	model = glm::scale(model, vec3(20.0f));
	RenderFigure(*quad.shader, projection, view, model, *quad.VAO, quad.numeroElementosParaDibujar);
}

void RenderCube(Cube &cube, glm::mat4 &projection, glm::mat4 &view, vec3 position)
{

	cube.shader->Use();
	cube.shader->Set("quadTexture", 4);
	cube.shader->Set("color", cube.color);
	glm::mat4 model = mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, vec3(1.0f));
	RenderFigure(*cube.shader, projection, view, model, *cube.VAO, cube.numeroElementosParaDibujar);
}

#pragma endregion

void Render(const Shader& shaderlight,
	uint32_t texture1, uint32_t texture2,
	Quad quad, TransferObjects transfer, Cube cube) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//uint32_t elementosParaDibujarEsfera = 121 * 8;

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.GetFOV()), screen_width / screen_height, 0.1f, 60.0f);

	{
		//shaderlight.Use();
		//mat4 model = mat4(1.0f);
		//shaderlight.Set("color", vec3(0.45f, 0.45f, 0.1f));
		//model = translate(model, pointLightPositions[0]);
		//model = scale(model, vec3(0.2f));

		//RenderFigure(shaderlight, projection, view, model, SphereVAO, elementosParaDibujarEsfera);

		//model = mat4(1.0f);
		//shaderlight.Set("color", vec3(0.1f, 0.1f, 1.1f));
		//model = translate(model, pointLightPositions[1]);
		//model = scale(model, vec3(0.2f));

		//RenderFigure(shaderlight, projection, view, model, SphereVAO, elementosParaDibujarEsfera);


		//model = mat4(1.0f);
		//shaderlight.Set("color", vec3(0.2f, 1.0f, 0.1f));
		//model = translate(model, spotLightPositions[0]);
		//model = scale(model, vec3(0.4f));

		//RenderFigure(shaderlight, projection, view, model, SphereVAO, elementosParaDibujarEsfera);


	}

	//Dibujamos Suelo
	RenderQuadSuelo(quad, projection, view);
	//glm::mat4 model = mat4(1.0f);


	//Dibujamos Cubos Meteoritos
	cube.color = vec3(1.0f);
	for (size_t i = 0; i < sizeof(MeteorOriginPositions) / sizeof(glm::vec3); i++)
	{
		RenderCube(cube, projection, view, MeteorOriginPositions[i]);
	}

	//dibujamos cubos naves
	cube.color = vec3(1.0f, 0.0f, 0.0f);
	for (size_t i = 0; i < sizeof(EnemyShipOriginPositions) / sizeof(glm::vec3); i++)
	{
		cube.shader->Set("color", vec3(1.0f, 0.0f, 0.0f));
		RenderCube(cube, projection, view, EnemyShipOriginPositions[i]);
	}



	for (size_t i = 0; i < transfer.numeroModelos; i++)
	{
		if (transfer.modelos[i]->_type == Constants::TIPO_PLAYER) {

			Player* player = GetPlayerReference(transfer.modelos[0]);

			player->Render(projection, view);
		}
		else if (transfer.modelos[i]->_type == Constants::TIPO_METEOR)
		{
			//glm::mat4 model = mat4(1.0f);
			GameObject *g = transfer.modelos[i];
			Meteor* meteor = static_cast<Meteor*>(g);

			meteor->Render(projection, view);
		}
		else if (transfer.modelos[i]->_type == Constants::TIPO_ENEMIGO) {
			GameObject *g = transfer.modelos[i];
			Enemy* enemyShip = static_cast<Enemy*>(g);

			enemyShip->Render(projection, view);
		}
	}



	{

		//modelObjs[0].Draw();
		////Dibujamos los cubos 
		//shaderCube.Use();
		//shaderCube.Set("projection", projection);
		//shaderCube.Set("view", view);

		//shaderCube.Set("viewPos", camera.GetPosition());

		////DirectionalLight 1
		//shaderCube.Set("dirLight.direction", -0.2f, -0.1f, -0.3f);
		//shaderCube.Set("dirLight.ambient", 0.1f, 0.6f, 0.6f);
		//shaderCube.Set("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
		//shaderCube.Set("dirLight.specular", 0.5f, 0.5f, 0.5f);


		////PointLight 0
		//shaderCube.Set("pointLights[0].position", pointLightPositions[0]);
		//shaderCube.Set("pointLights[0].ambient", 0.45f, 0.45f, 0.1f);
		//shaderCube.Set("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
		//shaderCube.Set("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		//shaderCube.Set("pointLights[0].constant", 1.0f);
		//shaderCube.Set("pointLights[0].linear", 0.09f);
		//shaderCube.Set("pointLights[0].cuadratic", 0.032f);

		////PointLight 1
		//shaderCube.Set("pointLights[1].position", pointLightPositions[1]);
		//shaderCube.Set("pointLights[1].ambient", 0.1f, 0.1f, 1.1f);
		//shaderCube.Set("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f);
		//shaderCube.Set("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		//shaderCube.Set("pointLights[1].constant", 1.0f);
		//shaderCube.Set("pointLights[1].linear", 0.09f);
		//shaderCube.Set("pointLights[1].cuadratic", 0.032f);


		////SpotLight 0
		//shaderCube.Set("spotLights[0].position", spotLightPositions[0]);
		//shaderCube.Set("spotLights[0].direction", -1.0f, 0.0f, -1.0f);
		//shaderCube.Set("spotLights[0].cutOff", cos(radians(20.0f)));
		//shaderCube.Set("spotLights[0].outerCutOff", cos(radians(25.0f)));
		//shaderCube.Set("spotLights[0].linear", 0.09f);
		//shaderCube.Set("spotLights[0].constant", 1.0f);
		//shaderCube.Set("spotLights[0].cuadratic", 0.032f);
		//shaderCube.Set("spotLights[0].direction", -1.0f, 0.0f, -1.0f);
		//shaderCube.Set("spotLights[0].ambient", 0.2f, 1.0f, 0.1f);
		//shaderCube.Set("spotLights[0].diffuse", 0.5f, 0.5f, 0.5f);
		//shaderCube.Set("spotLights[0].specular", 1.0f, 1.0f, 1.0f);

		////SpotLight 1
		//shaderCube.Set("spotLights[1].position", spotLightPositions[1]);
		//shaderCube.Set("spotLights[1].direction", -1.0f, 0.0f, -1.0f);
		//shaderCube.Set("spotLights[1].cutOff", cos(radians(20.0f)));
		//shaderCube.Set("spotLights[1].outerCutOff", cos(radians(25.0f)));
		//shaderCube.Set("spotLights[1].direction", -1.0f, 0.0f, -1.0f);
		//shaderCube.Set("spotLights[1].ambient", 1.0f, 0.15f, 0.1f);
		//shaderCube.Set("spotLights[1].diffuse", 0.5f, 0.5f, 0.5f);
		//shaderCube.Set("spotLights[1].constant", 1.0f);
		//shaderCube.Set("spotLights[1].linear", 0.09f);
		//shaderCube.Set("spotLights[1].cuadratic", 0.032f);

		//glActiveTexture(GL_TEXTURE0);		//glBindTexture(GL_TEXTURE_2D, texture1);		//glActiveTexture(GL_TEXTURE1);		//glBindTexture(GL_TEXTURE_2D, texture2);
		//shaderCube.Set("material.diffuse", 1);
		//shaderCube.Set("material.specular", 2);
		//shaderCube.Set("material.shininess", 25.6f);

		//int numeroRepeticionesElemento = 10;

		//for (uint32_t i = 0; i < numeroRepeticionesElemento; i++) {
		//	glm::mat4 model = glm::mat4(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	float angle = 10.0f + (cos(glfwGetTime()) + (sin(glfwGetTime())));
		//	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
		//	glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
		//	shaderCube.Set("normalMat", normalMat);
		//	RenderFigure(shaderCube, projection, view, model, CubeVAO, 36);
		//}
	}

	glBindVertexArray(0);
}


uint32_t createVertexData(const float* vertices, const uint32_t n_verts, const uint32_t* indices, const uint32_t n_indices) {
	unsigned int VAO, VBO, EBO;

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
	glBufferData(GL_ARRAY_BUFFER, n_verts * sizeof(float) * _numberOfElementsPerLine, vertices, GL_STATIC_DRAW);

	//Bindeo buffer indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(float), indices, GL_STATIC_DRAW);

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

uint32_t createVertexDataQuad(const float* vertices, const uint32_t n_verts, const uint32_t* indices, const uint32_t n_indices, const uint32_t numberOfElementsPerLine) {
	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	//Generamos 2 buffer, elementos y objetos
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bindeamos el VAO
	glBindVertexArray(VAO);

	uint32_t _numberOfElementsPerLine = numberOfElementsPerLine;
	uint32_t stride = 3;

	//Bindeamos buffer vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Subida de vertices al buffer
	glBufferData(GL_ARRAY_BUFFER, n_verts * sizeof(float) * _numberOfElementsPerLine, vertices, GL_STATIC_DRAW);

	//Bindeo buffer indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(float), indices, GL_STATIC_DRAW);

	//vertices del triangulo 6 por que hay 6 elementos hasta el proximo inicio de linea
	uint32_t atributteNumber = 0;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Vertices de textura
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)(stride * sizeof(float)));
	glEnableVertexAttribArray(1);
	stride += 2;
	////Vertices normal
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, _numberOfElementsPerLine * sizeof(float), (void*)(stride * sizeof(float)));
	//glEnableVertexAttribArray(2);

	//desbindeamos buffer objetos
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desbindeo
	glBindVertexArray(0);

	//desbindeamos buffer elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return VAO;
}

int main(int argc, char* argv[]) {
	if (!Inicializacion()) {
		return -1;
	}


	Shader shaderlight = Utils::GetFullShader("Shaders/LightVS.vs", "Shaders/LightFS.fs");
	Shader shaderCube = Utils::GetFullShader("Shaders/CubeVS.vs", "Shaders/CubeFS.fs");
	Shader shaderQuad = Utils::GetFullShader("Shaders/QuadVS.vs", "Shaders/QuadFS.fs");
	Shader shaderNavePlayer = Utils::GetFullShader("Shaders/NavePlayerVS.vs", "Shaders/NavePlayerFS.fs");
	Shader shaderMeteorito = Utils::GetFullShader("Shaders/MetorVS.vs", "Shaders/MetorFS.fs");

	uint32_t texture1 = Model::GetTexture("Textures/albedo.png", true);
	uint32_t texture2 = Model::GetTexture("Textures/specular.png", true);
	uint32_t textureSuelo = Model::GetTexture("Textures/texture3.png", true);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	Player player(shaderNavePlayer, posPlayer);

	vec3 posEnemigo = vec3(3.0f, 0.0f, 0.0f);

	Enemy enemy(shaderNavePlayer, posEnemigo);
	//camera._children[0] = &naves;

	vec3 posMeteorito = vec3(3.0f, 0.0f, 0.0f);
	Meteor meteor = Meteor(shaderMeteorito);
	//Meteor meteor2 = Meteor(shaderMeteorito);
	//Meteor meteor3 = Meteor(shaderMeteorito);
	//Meteor meteor4 = Meteor(shaderMeteorito);
	const uint32_t numeroObjetos = 2;
	GameObject *objectosssArray[numeroObjetos];

	TransferObjects transfer = {
		Constants::MaximoObjectosTransferencia,
		numeroObjetos,
		*objectosssArray,
	};
	transfer.modelos[0] = &player;
	//transfer.modelos[1] = &meteor;
	//transfer.modelos[2] = &meteor2;
	//transfer.modelos[3] = &meteor3;
	transfer.modelos[1] = &enemy;



	Cube cube = Cube();
	Quad quad = Quad();
	uint32_t CubeVAO = createVertexData(verticesCubo, cube.numeroElementosVerticesCubo, cube.indicesCubo, cube.numeroIndices);
	//uint32_t SphereVAO = createSphere(1);
	uint32_t QuadVAO = createVertexDataQuad(verticesQuad, quad.numeroElementosVerticesQuad, quad.indicesQuad, quad.numeroIndicesQuad, 5);

	cube.shader = &shaderCube;
	quad.shader = &shaderQuad;
	quad.VAO = &QuadVAO;
	quad.textures[0] = textureSuelo;
	quad.numeroElementosParaDibujar = 6;

	cube.VAO = &CubeVAO;

	cube.numeroElementosParaDibujar = 36;

	//Bucle inicial donde se realiza toda la accion del motor
	while (!glfwWindowShouldClose(window.GetWindow())) {
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		HandlerInput(deltaTime, transfer);

		MoveObjects(deltaTime, transfer);
		Render(shaderlight, texture1, texture2, quad, transfer, cube);
		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}

	//Si se han linkado bien los shaders, los borramos ya que estan linkados
	//glDeleteVertexArrays(1, &CubeVAO);


	glfwTerminate();
	return 0;
}
#pragma endregion

