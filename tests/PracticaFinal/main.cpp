#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<cstdint>
#include<stdio.h>

#include "Node.h"
#include "Constants.h"
#include "Shader.h"
#include "Utils.h"

#include "Window.h"
#include "Camera.h"
#include "GameObject.h"

#include "Player.h"
#include "Meteor.h"
#include "Enemy.h"
#include "Missile.h"
#include "Cube.h"
#include "GameControl.h"


const vec3 posCamera = glm::vec3(0.0f, 20.0f, 0.0f);

Camera camera(posCamera);
#pragma region Variables Globales
const float M_PI = 3.14f;
const vec3 posSuelo = vec3(0.0f, -16.0f, 0.0f);
const vec3 posPlayer = vec3(5.0f, 0.0f, 0.0f);
const float screen_width = 800.0f, screen_height = 600.0f;
float lastY = (float)screen_height / 2.0f;
float lastX = (float)screen_width / 2.0f;

bool debug = true;
float lastFrame = 0.0f;
bool firstMouse = true;

Window window;
#pragma endregion


#pragma region Comments

//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//
//glm::vec3 spotLightPositions[] = {
//	glm::vec3(2.7f, 3.2f, 2.0f),
//	glm::vec3(-2.7f, 3.2f, -5.0f),
//
//};




float verticesQuad[] = {
	-0.5f,  0.5f,  0.5f,       0.0f, 0.0f,    //top
	  0.5f,  0.5f,  0.5f,       1.0f, 0.0f,
	  0.5f,  0.5f,  -0.5f,       1.0f, 1.0f,
	  -0.5f,  0.5f,  -0.5f,       0.0f, 1.0f };
#pragma endregion
struct Sphere {
	float* vertices;
	float* normals;
	float* textCoords;
	uint32_t* elementos;
	uint32_t numeroVertices;
	uint32_t numeroElementos;
	uint32_t numeroNormales;
	uint32_t numeroTexturas;
	uint32_t* VAO;
	Shader *shader;
	uint32_t numeroIndices = 121 * 8;
	vec3 scale = glm::vec3(1.4f);
	vec3 color = vec3(1.0f);
	vec3 position = posCamera;

};

struct Quad {

	uint32_t numeroElementosVerticesQuad = 20;
	uint32_t numeroIndicesQuad = 6;

	uint32_t textures[3];
	Shader *shader;
	uint32_t* VAO;

	uint32_t indicesQuad[6]{
	0, 1, 2, 0, 2, 3 //Front
	};
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
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		player->Mover(Player::Movement::Left, deltaTime);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		player->Mover(Player::Movement::Right, deltaTime);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
		player->Mover(Player::Movement::Forward, deltaTime);
	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		player->Mover(Player::Movement::Backward, deltaTime);
	}
}

void AccionesJugador(Player* player) {
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		player->Disparar();
	}
}


void HandlerInput(const double deltaTime, Node* node) {
	MovimientoCamara(deltaTime);
	if (node->GetChildren(0)->GetGameObject()->GetType() == Constants::TIPO_PLAYER) {
		Player* player = GetPlayerReference(node->GetChildren(0)->GetGameObject());
		MovimientoJugador(deltaTime, player);
		AccionesJugador(player);

	}
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window.GetWindow(), true);
	}
}
#pragma endregion



#pragma region Metodos

#pragma region Generacion esfera

void generateVerts(float * verts, float * norms, float * tex, unsigned int * el, const uint32_t slices, const uint32_t stacks, const uint32_t radius) {
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

uint32_t createSphere(const float radius) {
	constexpr int slices = 10;
	constexpr int stacks = 10;

	Sphere sphere;

	constexpr uint32_t nVerts = (slices + 1) * (stacks + 1); //121
	constexpr uint32_t elements = (slices * 2 * (stacks - 1)) * 3; //540

	float v[3 * nVerts];        // Verts      363 elementos
	float n[3 * nVerts];        // Normals    363 elementos
	float tex[2 * nVerts];      // Tex coords    242 elementos
	uint32_t el[elements];      // Elements

	generateVerts(v, n, tex, el, slices, stacks, radius);
	sphere.vertices = v;
	sphere.textCoords = tex;
	sphere.elementos = el;
	sphere.normals = n;
	sphere.numeroVertices = nVerts * 3;
	sphere.numeroNormales = nVerts * 3;
	sphere.numeroTexturas = 2 * nVerts;
	sphere.numeroElementos = elements;

	const int sizeTotal = (sphere.numeroVertices + sphere.numeroNormales + sphere.numeroTexturas);

	//vector<float> newVertice2(sizeTotal);
	float newVertice2[3 * nVerts + 3 * nVerts + 2 * nVerts];

	for (size_t i = 0; i < sphere.numeroVertices / 3; i++)
	{
		newVertice2[0 + 8 * i] = sphere.vertices[3 * i];
		newVertice2[1 + 8 * i] = sphere.vertices[3 * i + 1];
		newVertice2[2 + 8 * i] = sphere.vertices[3 * i + 2];

		newVertice2[3 + 8 * i] = sphere.normals[3 * i];
		newVertice2[4 + 8 * i] = sphere.normals[3 * i + 1];
		newVertice2[5 + 8 * i] = sphere.normals[3 * i + 2];

		newVertice2[6 + 8 * i] = sphere.textCoords[2 * i];
		newVertice2[7 + 8 * i] = sphere.textCoords[2 * i + 1];
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
	sphere.VAO = &VAO;
	return VAO;

	//return sphere;

}
#pragma endregion

int Inicializacion() {
	if (!glfwInit()) {
		cout << "Error initializing GLFW" << endl;
		glfwTerminate();
		return -1;
	}
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

#pragma region Render Figures

void RenderFigureMain(const Shader & shader, glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model, const uint32_t &VAO, const uint32_t &numeroElementos)
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
	RenderFigureMain(*quad.shader, projection, view, model, *quad.VAO, quad.numeroIndicesQuad);
}


void RenderSphere(Sphere &sphere, glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 model = glm::mat4(1.0f);
	sphere.shader->Use();
	sphere.shader->Set("color", sphere.color);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::translate(model, sphere.position);
	model = glm::scale(model, sphere.scale);

	RenderFigureMain(*sphere.shader, projection, view, model, *sphere.VAO, sphere.numeroIndices);

}
#pragma endregion


void RenderScene(Quad quad, Sphere sphere, Cube cube) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.GetFOV()), screen_width / screen_height, 0.1f, 60.0f);


	//Dibujamos Suelo
	RenderQuadSuelo(quad, projection, view);
	if (debug) {

		//Dibujamos sphera luz
		RenderSphere(sphere, projection, view);

		//Dibujamos Cubos Meteoritos
		cube._color = vec3(1.0f);
		cube._scale = vec3(1.0f);
		for (size_t i = 0; i < Meteor::GetNumberPositions(); i++)
		{
			cube.Render(projection, view, Meteor::GetMeteorPosition(i), 1.0f);
		}

		//dibujamos cubos naves
		cube._color = vec3(1.0f, 0.0f, 0.0f);
		for (size_t i = 0; i < Enemy::GetNumberPositions(); i++)
		{
			cube._shader->Set("color", cube._color);
			cube.Render(projection, view, Enemy::GetEnemyPosition(i), 1.0f);

		}
	}

	glBindVertexArray(0);
}


void MoveObjects(const double deltaTime, Node* node) {
	if (node->HasChildren()) {
		for (size_t i = 0; i < node->GetNumberChildren(); i++)
		{
			MoveObjects(deltaTime, node->GetChildren(i));
		}
	}
	if (node->GetGameObject() != NULL) {
		if (node->GetGameObject()->GetType() == Constants::TIPO_PLAYER) {

			Player* player = GetPlayerReference(node->GetGameObject());
			MovimientoJugador(deltaTime, player);
		}
		else if (node->GetGameObject()->GetType() == Constants::TIPO_METEOR)
		{
			GameObject *g = node->GetGameObject();
			Meteor* meteor = static_cast<Meteor*>(g);
			if (meteor->Rendered()) {
				meteor->Mover(deltaTime);
			}
		}
		else if (node->GetGameObject()->GetType() == Constants::TIPO_ENEMIGO) {
			GameObject *g = node->GetGameObject();
			Enemy* enemyShip = static_cast<Enemy*>(g);
			if (enemyShip->Rendered()) {
				enemyShip->Mover(GameObject::Movement::Backward, deltaTime);
			}
		}
		else if (node->GetGameObject()->GetType() == Constants::TIPO_MISIL) {
			GameObject *g = node->GetGameObject();
			Missile* missile = static_cast<Missile*>(g);
			if (missile->Rendered()) {
				missile->Mover(GameObject::Movement::Backward, deltaTime);
			}
		}
	}
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

void ColliderPlayer(Player * player, Cube *cube)
{
	vec3 position = player->GetPosition();
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.GetFOV()), screen_width / screen_height, 0.1f, 60.0f);
	cube->_scale = vec3(3.0f, 4.0f, 5.5f);
	cube->_color = vec3(1.0f);
	cube->_position = position;

	player->_collider = cube;
	//cube->Render(projection, view, position, 0.0f);
}

void RenderColliders(Node * node, Cube *cube) {
	Player* player = GetPlayerReference(node->GetChildren(0)->GetGameObject());
	ColliderPlayer(player, cube);

}

int main(int argc, char* argv[]) {
	if (!Inicializacion()) {
		return -1;
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	cout << "Creacion Shaders " << endl;
	Shader shaderlight = Utils::GetFullShader("Shaders/LightVS.vs", "Shaders/LightFS.fs");
	Shader shaderCube = Utils::GetFullShader("Shaders/CubeVS.vs", "Shaders/CubeFS.fs");
	Shader shaderQuad = Utils::GetFullShader("Shaders/QuadVS.vs", "Shaders/QuadFS.fs");
	Shader shaderSphere = Utils::GetFullShader("Shaders/SphereVS.vs", "Shaders/SphereFS.fs");

	cout << "Creacion Textures " << endl;
	uint32_t textureSuelo = Model::GetTexture("Textures/texture3.png", true);

	cout << "Creacion Player " << endl;
	Player player(posPlayer);


	cout << "Creacion Enemigo " << endl;
	vec3 posEnemigo = vec3(2.0f, 0.0f, 15.0f);
	Enemy enemyGameObject(posEnemigo);
	Enemy enemyGameObject1(posEnemigo);
	Enemy enemyGameObject2(posEnemigo);
	Enemy enemyGameObject3(posEnemigo);
	Enemy enemyGameObject4(posEnemigo);
	Enemy enemyGameObject5(posEnemigo);

	cout << "Creacion Meteorito " << endl;
	Shader shaderMeteorito = Utils::GetFullShader("Shaders/MetorVS.vs", "Shaders/MetorFS.fs");
	Meteor meteorGameObject1 = Meteor(shaderMeteorito);
	Meteor meteorGameObject2 = Meteor(shaderMeteorito);
	Meteor meteorGameObject3 = Meteor(shaderMeteorito);
	Meteor meteorGameObject4 = Meteor(shaderMeteorito);
	Meteor meteorGameObject5 = Meteor(shaderMeteorito);
	Meteor meteorGameObject6 = Meteor(shaderMeteorito);

	cout << "Creacion Misiles " << endl;
	Shader shaderMissile = Utils::GetFullShader("Shaders/MissileVS.vs", "Shaders/MissileFS.fs");
	Missile missilePlayer = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer1 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer2 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer3 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer4 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer5 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer6 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer7 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer8 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer9 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer10 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer11 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer12 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer13 = Missile(shaderMissile, vec3(0.0f), &player);
	Missile missilePlayer14 = Missile(shaderMissile, vec3(0.0f), &player);

	Node missilePool(NULL);
	Node missile1(&missilePlayer);
	Node missile2(&missilePlayer1);
	Node missile3(&missilePlayer2);
	Node missile4(&missilePlayer3);
	Node missile5(&missilePlayer4);
	Node missile6(&missilePlayer5);
	Node missile7(&missilePlayer6);
	Node missile8(&missilePlayer7);
	Node missile9(&missilePlayer8);
	Node missile10(&missilePlayer9);
	Node missile11(&missilePlayer10);

	missilePool.AddChildren(&missile1);
	missilePool.AddChildren(&missile2);
	missilePool.AddChildren(&missile3);
	missilePool.AddChildren(&missile4);
	missilePool.AddChildren(&missile5);
	missilePool.AddChildren(&missile6);
	missilePool.AddChildren(&missile7);
	missilePool.AddChildren(&missile8);
	missilePool.AddChildren(&missile9);
	missilePool.AddChildren(&missile10);

	//1 level
	Node root(&camera);
	//2 level
	Node playerNode(&player);
	playerNode.AddChildren(&missilePool);
	//Enemies
	Node enemiesParentNode(NULL);
	Node enemies(&enemyGameObject);
	Node enemies1(&enemyGameObject1);
	Node enemies2(&enemyGameObject2);
	Node enemies3(&enemyGameObject3);
	Node enemies4(&enemyGameObject4);
	Node enemies5(&enemyGameObject5);

	enemiesParentNode.AddChildren(&enemies);
	enemiesParentNode.AddChildren(&enemies2);
	enemiesParentNode.AddChildren(&enemies3);
	enemiesParentNode.AddChildren(&enemies4);
	enemiesParentNode.AddChildren(&enemies5);

	//Meteors
	Node MeteorsParentNode(NULL);
	Node meteor(&meteorGameObject1);
	Node meteor1(&meteorGameObject2);
	Node meteor2(&meteorGameObject3);
	Node meteor3(&meteorGameObject4);
	Node meteor4(&meteorGameObject5);
	Node meteor5(&meteorGameObject6);


	MeteorsParentNode.AddChildren(&meteor);
	MeteorsParentNode.AddChildren(&meteor1);
	MeteorsParentNode.AddChildren(&meteor2);
	MeteorsParentNode.AddChildren(&meteor3);
	MeteorsParentNode.AddChildren(&meteor4);
	MeteorsParentNode.AddChildren(&meteor5);

	root.AddChildren(&playerNode);
	root.AddChildren(&enemiesParentNode);
	root.AddChildren(&MeteorsParentNode);

	Cube cubeClasss = Cube(shaderCube);
	Quad quad = Quad();
	Sphere sphere = Sphere();

	uint32_t SphereVAO = createSphere(1);
	uint32_t QuadVAO = createVertexDataQuad(verticesQuad, quad.numeroElementosVerticesQuad, quad.indicesQuad, quad.numeroIndicesQuad, 5);

	cout << "Creacion Geometrias " << endl;

	quad.shader = &shaderQuad;
	sphere.shader = &shaderSphere;

	quad.VAO = &QuadVAO;
	quad.textures[0] = textureSuelo;

	sphere.VAO = &SphereVAO;
	cout << "Inicio GameLoop" << endl;

	//GameControl control(&playerNode, &enemiesParentNode, &MeteorsParentNode);
	GameControl control(&playerNode, &enemiesParentNode, &MeteorsParentNode, &camera, &root);


	//Bucle inicial donde se realiza toda la accion del motor
	while (!glfwWindowShouldClose(window.GetWindow()) && control._playerAlive) {
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		RenderScene(quad, sphere, cubeClasss);
		//RenderColliders(&root, &cubeClasss);
		HandlerInput(deltaTime, &root);
		control.CheckCollisions();
		control.MoveObjects(deltaTime);
		control.ActivacionGameObjects();
		control.RenderGameObjects(&root);
		//MoveObjects(deltaTime, &root);


		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}
	cout << "Fin GameLoop" << endl;

	//Si se han linkado bien los shaders, los borramos ya que estan linkados
	glDeleteVertexArrays(1, &QuadVAO);
	glDeleteVertexArrays(1, &SphereVAO);
	glDeleteVertexArrays(1, &cubeClasss._VAO);


	glfwTerminate();
	return 0;
}
#pragma endregion

