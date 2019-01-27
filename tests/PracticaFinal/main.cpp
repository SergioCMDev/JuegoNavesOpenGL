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
#include "Quad.h"
#include "GameControl.h"
#include "Render.h"
#include "Sphere.h"

const vec3 posCamera = glm::vec3(0.0f, 20.0f, 0.0f);

Camera camera(posCamera);
#pragma region Variables Globales
const vec3 posSuelo = vec3(0.0f, -16.0f, 0.0f);
const vec3 posPlayer = vec3(0.0f, 0.0f, 0.0f);
const vec3 posLuz = vec3(0.0f, Constants::ALTURA_LUZ, 0.0f);

const float screen_width = 1280, screen_height = 720;
float lastY = (float)screen_height / 2.0f;
float lastX = (float)screen_width / 2.0f;

bool debug = false;
float lastFrame = 0.0f;
bool firstMouse = true;

Window window;
#pragma endregion




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
	if (debug) {

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
	if (debug) {
		glfwSetCursorPosCallback(window.GetWindow(), OnMouse);
	}
	glfwSetFramebufferSizeCallback(window.GetWindow(), OnChangeFrameBufferSize);
	glfwSetScrollCallback(window.GetWindow(), OnScroll);
	glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 1;
};


//void ColliderPlayer(Player * player, Cube *cube)
//{
//	vec3 position = player->GetPosition();
//	glm::mat4 view = camera.GetViewMatrix();
//	glm::mat4 projection = glm::perspective(glm::radians(camera.GetFOV()), screen_width / screen_height, 0.1f, 60.0f);
//	cube->_scale = vec3(3.0f, 4.0f, 5.5f);
//	cube->_color = vec3(1.0f);
//	cube->_position = position;
//
//	player->_collider = cube;
//	//cube->Render(projection, view, position, 0.0f);
//}
//
//void RenderColliders(Node * node, Cube *cube) {
//	Player* player = GetPlayerReference(node->GetChildren(0)->GetGameObject());
//	ColliderPlayer(player, cube);
//
//}


int main(int argc, char* argv[]) {
	if (!Inicializacion()) {
		return -1;
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);




	cout << "Creacion Shaders " << endl;
	Shader shaderCube = Utils::GetFullShader("Shaders/CubeVS.vs", "Shaders/CubeFS.fs");
	Shader shaderQuad = Utils::GetFullShader("Shaders/QuadVS.vs", "Shaders/QuadFS.fs");
	Shader shaderSphere = Utils::GetFullShader("Shaders/LightVS.vs", "Shaders/LightFS.fs");
	Shader shaderDepth = Utils::GetFullShader("Shaders/depth.vs", "Shaders/depth.fs");

	Shader shaderModels = Utils::GetFullShader("Shaders/shaderVS.vs", "Shaders/shaderFS.fs");

	cout << "Creacion Textures " << endl;
	uint32_t textureSuelo = Model::GetTexture("Textures/texture3.png", true);

	cout << "Creacion Player " << endl;
	Player player(shaderModels, posPlayer);
	Node playerNode(&player);


	cout << "Creacion Enemigo " << endl;
	//vec3 posEnemigo = vec3(2.0f, 0.0f, 15.0f);
#pragma region generacion GameObjects y Nodos


	Enemy enemyGameObject1(shaderModels);
	Enemy enemyGameObject2(shaderModels);
	Enemy enemyGameObject3(shaderModels);
	Enemy enemyGameObject4(shaderModels);
	Enemy enemyGameObject5(shaderModels);


	Node enemies1(&enemyGameObject1);
	Node enemies2(&enemyGameObject2);
	Node enemies3(&enemyGameObject3);
	Node enemies4(&enemyGameObject4);

	cout << "Creacion Meteorito " << endl;
	//Shader shaderMeteorito = Utils::GetFullShader("Shaders/MetorVS.vs", "Shaders/MetorFS.fs");
	Meteor meteorGameObject1 = Meteor(shaderModels);
	Meteor meteorGameObject2 = Meteor(shaderModels);
	Meteor meteorGameObject3 = Meteor(shaderModels);
	Meteor meteorGameObject4 = Meteor(shaderModels);
	Meteor meteorGameObject5 = Meteor(shaderModels);
	Meteor meteorGameObject6 = Meteor(shaderModels);

	cout << "Creacion Misiles " << endl;
	//Shader shaderMissile = Utils::GetFullShader("Shaders/MissileVS.vs", "Shaders/MissileFS.fs");
	Missile missilePlayer = Missile(shaderModels, vec3(0.0f));
	Missile missilePlayer1 = Missile(shaderModels, vec3(0.0f));
	Missile missilePlayer2 = Missile(shaderModels, vec3(0.0f));
	Missile missilePlayer3 = Missile(shaderModels, vec3(0.0f));
	Missile missilePlayer4 = Missile(shaderModels, vec3(0.0f));
	Missile missilePlayer5 = Missile(shaderModels, vec3(0.0f));

	cout << "Creacion Pool Misiles Player" << endl;

	Node missilePoolPlayer(&playerNode);
	Node missile1(&missilePlayer, &missilePoolPlayer);
	Node missile2(&missilePlayer1, &missilePoolPlayer);
	Node missile3(&missilePlayer2, &missilePoolPlayer);
	Node missile4(&missilePlayer3, &missilePoolPlayer);
	Node missile5(&missilePlayer4, &missilePoolPlayer);
	Node missile6(&missilePlayer5, &missilePoolPlayer);

	missilePoolPlayer.AddChildren(&missile1);
	missilePoolPlayer.AddChildren(&missile2);
	missilePoolPlayer.AddChildren(&missile3);
	missilePoolPlayer.AddChildren(&missile4);
	missilePoolPlayer.AddChildren(&missile5);
	missilePoolPlayer.AddChildren(&missile6);


	cout << "Creacion Misiles Enemigos" << endl;

	cout << "Creacion Pool Misiles Enemigos" << endl;
	////////////////////////////////////////////////////////////////////////
	cout << "Creacion Pool Misiles Enemigo 1" << endl;
	Node missilePoolEnemy1(&enemies1);
	Missile missile1Enemy1 = Missile(shaderModels, vec3(0.0f));
	Missile missile2Enemy1 = Missile(shaderModels, vec3(0.0f));
	Missile missile3Enemy1 = Missile(shaderModels, vec3(0.0f));

	Node missile1Enemy1Node(&missile1Enemy1, &missilePoolEnemy1);
	Node missile2Enemy1Node(&missile2Enemy1, &missilePoolEnemy1);
	Node missile3Enemy1Node(&missile3Enemy1, &missilePoolEnemy1);


	missilePoolEnemy1.AddChildren(&missile1Enemy1Node);
	missilePoolEnemy1.AddChildren(&missile2Enemy1Node);
	missilePoolEnemy1.AddChildren(&missile3Enemy1Node);
	/////////////////////////////////////////////////////////////////////////////////////
	cout << "Creacion Pool Misiles Enemigo 1" << endl;

	Node missilePoolEnemy2(&enemies2);

	Missile missile1Enemy2 = Missile(shaderModels, vec3(0.0f));
	Missile missile2Enemy2 = Missile(shaderModels, vec3(0.0f));
	Missile missile3Enemy2 = Missile(shaderModels, vec3(0.0f));

	Node missile1Enemy2Node(&missile1Enemy2, &missilePoolEnemy2);
	Node missile2Enemy2Node(&missile2Enemy2, &missilePoolEnemy2);
	Node missile3Enemy2Node(&missile3Enemy2, &missilePoolEnemy2);

	missilePoolEnemy2.AddChildren(&missile1Enemy2Node);
	missilePoolEnemy2.AddChildren(&missile2Enemy2Node);
	missilePoolEnemy2.AddChildren(&missile3Enemy2Node);
	////////////////////////////////////////////////////////////////////////////////////
	cout << "Creacion Pool Misiles Enemigo 3" << endl;

	Node missilePoolEnemy3(&enemies3);

	Missile missile1Enemy3 = Missile(shaderModels, vec3(0.0f));
	Missile missile2Enemy3 = Missile(shaderModels, vec3(0.0f));
	Missile missile3Enemy3 = Missile(shaderModels, vec3(0.0f));

	Node missile1Enemy3Node(&missile1Enemy3, &missilePoolEnemy3);
	Node missile2Enemy3Node(&missile2Enemy3, &missilePoolEnemy3);
	Node missile3Enemy3Node(&missile3Enemy3, &missilePoolEnemy3);

	missilePoolEnemy3.AddChildren(&missile1Enemy3Node);
	missilePoolEnemy3.AddChildren(&missile2Enemy3Node);
	missilePoolEnemy3.AddChildren(&missile3Enemy3Node);
	////////////////////////////////////////////////////////////////////////////////////
	cout << "Creacion Pool Misiles Enemigo 4" << endl;

	Node missilePoolEnemy4(&enemies4);

	Missile missile1Enemy4 = Missile(shaderModels, vec3(0.0f));
	Missile missile2Enemy4 = Missile(shaderModels, vec3(0.0f));
	Missile missile3Enemy4 = Missile(shaderModels, vec3(0.0f));

	Node missile1Enemy4Node(&missile1Enemy4, &missilePoolEnemy4);
	Node missile2Enemy4Node(&missile2Enemy4, &missilePoolEnemy4);
	Node missile3Enemy4Node(&missile3Enemy4, &missilePoolEnemy4);

	missilePoolEnemy4.AddChildren(&missile1Enemy4Node);
	missilePoolEnemy4.AddChildren(&missile2Enemy4Node);
	missilePoolEnemy4.AddChildren(&missile3Enemy4Node);
	//////////////////////////////////////////////////////////////////////////////////



	//1 level
	Node root(&camera);
	//2 level
	playerNode.AddChildren(&missilePoolPlayer);
	//Enemies
	Node enemiesParentNode(&root);
	enemies1.AddChildren(&missilePoolEnemy1);
	enemies2.AddChildren(&missilePoolEnemy2);
	enemies3.AddChildren(&missilePoolEnemy3);
	enemies4.AddChildren(&missilePoolEnemy4);


	enemiesParentNode.AddChildren(&enemies1);
	enemiesParentNode.AddChildren(&enemies2);
	enemiesParentNode.AddChildren(&enemies3);
	enemiesParentNode.AddChildren(&enemies4);


	//Meteors
	Node MeteorsParentNode(&root);
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

#pragma endregion
	Cube cubeClasss = Cube(shaderCube);

	Sphere sphere = Sphere(shaderSphere, posLuz, 1);

	Quad quadSuelo = Quad(shaderQuad);


	cout << "Creacion Geometrias " << endl;


	quadSuelo.textures[0] = textureSuelo;
	cout << "Inicio GameLoop" << endl;

	GameControl control(&playerNode, &enemiesParentNode, &MeteorsParentNode, &camera, &root);
	Render render(&root, debug, &camera);
	auto fboRes = render.createFBO();

	//Bucle inicial donde se realiza toda la accion del motor
	while (!glfwWindowShouldClose(window.GetWindow()) && control._playerAlive) {
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//RenderColliders(&root, &cubeClasss);
		HandlerInput(deltaTime, &root);
		control.CheckCollisions();
		control.MoveObjects(deltaTime);
		control.ActivacionGameObjects(currentFrame, deltaTime);

		//render.RenderGame(&root, shaderModels, shaderDepth, fboRes);//Intento de pasarla a la clase Render pero nave player se vuelve invisible
		control.Render(&root, shaderModels, shaderDepth, fboRes);
		render.RenderScene(quadSuelo, sphere, cubeClasss);



		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}
	cout << "Fin GameLoop" << endl;

	//Si se han linkado bien los shaders, los borramos ya que estan linkados
	glDeleteVertexArrays(1, &quadSuelo._VAO);
	glDeleteVertexArrays(1, &sphere._VAO);
	glDeleteVertexArrays(1, &cubeClasss._VAO);


	glfwTerminate();
	return 0;
}
#pragma endregion

