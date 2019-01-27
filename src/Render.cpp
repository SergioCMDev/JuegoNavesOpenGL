#include "Render.h"



vec3 posLuz;
const vec3 posSuelo = vec3(0.0f, -16.0f, 0.0f);
const float screen_width = 1280, screen_height = 720;
const float shadow_width = 1024, shadow_height = 1024;

//Player* GetPlayerReference(GameObject* objectPlayer) {
//	GameObject *g = objectPlayer;
//	Player* player = static_cast<Player*>(objectPlayer);
//	return player;
//}


#pragma endregion


void Render::RenderScene(Quad quadSuelo, Sphere sphere, Cube cube) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 view = _camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(_camera->GetFOV()), screen_width / screen_height, 0.1f, 60.0f);

	quadSuelo.Render(projection, view, posSuelo);
	//Dibujamos Suelo
	if (_debug) {

		//Dibujamos sphera luz
		sphere.RenderSphere(projection, view);
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

		//dibujamos cubos limites
		cube._color = vec3(1.0f, 1.0f, 0.0f);
		cube._shader->Set("color", cube._color);
		cube.Render(projection, view, vec3(Constants::MAX_POSITION_X, 0.0f, 0.0f), 1.0f);

		cube.Render(projection, view, vec3(Constants::MIN_POSITION_X, 0.0f, 0.0f), 1.0f);

		cube.Render(projection, view, vec3(0.0f, 0.0f, Constants::MIN_POSITION_Y), 1.0f);

		cube.Render(projection, view, vec3(0.0f, 0.0f, Constants::MAX_POSITION_Y), 1.0f);

	}

	glBindVertexArray(0);
}



Render::Render(Node * node, bool debug) {

	_node = node;
	_debug = debug;
	GameObject *g = node->GetGameObject();;
	Camera* camera = static_cast<Camera*>(g);
	_camera = camera;
	//Shader shaderQuad = Utils::GetFullShader("Shaders/QuadVS.vs", "Shaders/QuadFS.fs");
	//Shader shaderSphere = Utils::GetFullShader("Shaders/LightVS.vs", "Shaders/LightFS.fs");
	//cout << "Creacion Geometrias " << endl;
	//Quad quadSuelo = Quad(shaderQuad);
	//_sphere = Sphere();
	//uint32_t textureSuelo = Model::GetTexture("Textures/texture3.png", true);
	//uint32_t SphereVAO = createSphere(1);

	//_sphere.shader = &shaderSphere;

	//quadSuelo.textures[0] = textureSuelo;

	//_sphere.VAO = &SphereVAO;
}

//void Render::RenderGame(Shader & shaderModels, Shader & depthShader)
//{
//}
//
//
//void ColliderPlayer(Player * player, Cube *cube)
//{
//	//vec3 position = player->GetPosition();
//	//glm::mat4 view = _camera->GetViewMatrix();
//	//glm::mat4 projection = glm::perspective(glm::radians(camera.GetFOV()), screen_width / screen_height, 0.1f, 60.0f);
//	//cube->_scale = vec3(3.0f, 4.0f, 5.5f);
//	//cube->_color = vec3(1.0f);
//	//cube->_position = position;
//
//	//player->_collider = cube;
//	//cube->Render(projection, view, position, 0.0f);
//}

//void RenderColliders(Node * node, Cube *cube) {
//	Player* player = GetPlayerReference(node->GetChildren(0)->GetGameObject());
//	ColliderPlayer(player, cube);
//
//}
