#include "Render.h"



const vec3 posSuelo = vec3(0.0f, -16.0f, 0.0f);
const float screen_width = 1280, screen_height = 720;
const float shadow_width = 1024, shadow_height = 1024;
const float shadow_near = 1.0f;
const float shadow_far = 7.5f;


#pragma endregion


void Render::RenderScene(Quad quadSuelo, Sphere sphere, Cube cube) {


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 view = _camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(_camera->GetFOV()), screen_width / screen_height, 0.1f, 40.0f);

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

Render::Render(Node * node, bool debug, Camera* camera) {

	_node = node;
	_debug = debug;
	_camera = camera;
	_player = node->GetChildren(0);
}

pair<uint32_t, uint32_t> Render::createFBO() {
	uint32_t fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	uint32_t depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f,1.0f ,1.0f ,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		cout << "Error loading GL_FRAMEBUFFER" << endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return make_pair(fbo, depthMap);
}

void Render::RenderGame(Node * _root, Shader &shaderModels, Shader& depthShader, pair<uint32_t, uint32_t> fboRes) {
	vec3 lightPos = vec3(0.0f, Constants::ALTURA_LUZ, 0.0f);
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, shadow_near, shadow_far);
	mat4 lightView = lookAt(lightPos, vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	mat4 lightSpaceMatrix = lightProjection * lightView;

	depthShader.Use();
	depthShader.Set("lightSpaceMatrix", lightSpaceMatrix);
	glBindFramebuffer(GL_FRAMEBUFFER, fboRes.first);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, shadow_width, shadow_height); //Cambiamos tama�o de pantalla a pantalla de sombra
	RenderLights(shaderModels);

	RenderGameObjects(_root, depthShader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, screen_width, screen_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Camera* camera = static_cast<Camera*>(_root->GetGameObject());
	lightProjection = glm::perspective(radians(camera->GetFOV()), (float)screen_width / screen_height, 0.1f, 100.0f);
	mat4 view = camera->GetViewMatrix();
	shaderModels.Set("projection", lightProjection);
	shaderModels.Set("view", view);
	shaderModels.Set("viewPos", camera->GetPosition());
	shaderModels.Set("lightPos", lightPos);
	shaderModels.Set("lightSpaceMatrix", lightSpaceMatrix);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, fboRes.second);
	shaderModels.Set("depthMap", 8);

	RenderGameObjects(_root, shaderModels);
}

void Render::RenderPlayer(glm::mat4 &projection, glm::mat4 &view, Shader &shader, Player* player)
{
	glm::mat4 model = mat4(1.0f);
	model = glm::translate(model, player->GetPosition());

	model = glm::scale(model, player->GetScale());

	shader.Set("projection", projection);
	shader.Set("view", view);
	shader.Set("model", model);
	player->GetModel().Draw(shader);
}


void Render::RenderMeteor(glm::mat4 &projection, glm::mat4 &view, Shader &shader, Meteor* meteor)
{
	glm::mat4 model = mat4(1.0f);
	model = glm::translate(model, meteor->GetPosition());
	model = glm::scale(model, meteor->GetScale());
	float angle = glm::radians((40 + glm::cos(45.0f) + glm::sin(90.0f)));
	model = glm::rotate(model, (float)glfwGetTime() *  angle, vec3(1.0f, 1.0f, 0.0f));
	shader.Set("projection", projection);
	shader.Set("view", view);
	shader.Set("model", model);
	meteor->GetModel().Draw(shader);
}

void Render::RenderEnemy(glm::mat4 &projection, glm::mat4 &view, Shader &shader, Enemy* enemy)
{
	glm::mat4 model = mat4(1.0f);

	model = glm::translate(model, enemy->GetPosition());

	model = glm::scale(model, enemy->GetScale());

	shader.Set("projection", projection);
	shader.Set("view", view);
	shader.Set("model", model);
	enemy->GetModel().Draw(shader);
}



void Render::RenderMissile(glm::mat4 &projection, glm::mat4 &view, Shader &shader, Missile* missile)
{
	glm::mat4 _modelMatrix = mat4(1.0f);

	//shader.Use();
	_modelMatrix = glm::translate(_modelMatrix, missile->GetPosition());

	_modelMatrix = glm::scale(_modelMatrix, missile->GetScale());
	if (missile->GetActualNode()->GetParent()->GetParent()->GetGameObject()->GetType() == Constants::TIPO_ENEMIGO) {
		missile->Rotate(_modelMatrix);
	}
	shader.Set("projection", projection);
	shader.Set("view", view);
	shader.Set("model", _modelMatrix);
	missile->GetModel().Draw(shader);
}


void Render::RenderGameObjects(Node * _root, Shader &shader) {
	glm::mat4 view = _camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(_camera->GetFOV()), screen_width / screen_height, 0.1f, 60.0f);
	RenderLights(_player->GetGameObject()->_shader);
	if (_root->HasChildren()) {
		for (size_t i = 0; i < _root->GetNumberChildren(); i++)
		{
			RenderGameObjects(_root->GetChildren(i), shader);
		}
	}
	if (_root->GetGameObject() != NULL) {
		_root->GetGameObject()->_shader = shader;
		if (_root->GetGameObject()->OutsideBoundaries()) {

			_root->GetGameObject()->Deactivate();
		}
		else {
			if (_root->GetGameObject()->GetType() == Constants::TIPO_PLAYER) {
				GameObject *g = _root->GetGameObject();
				Player* player = static_cast<Player*>(g);
				if (player->Active()) {
					RenderPlayer(projection, view, shader, player);
				}
				//cout << "Player " << endl;
			}
			else if (_root->GetGameObject()->GetType() == Constants::TIPO_METEOR)
			{
				GameObject *g = _root->GetGameObject();
				//cout << "Meteor " << endl;
				Meteor* meteor = static_cast<Meteor*>(g);
				if (meteor->Active()) {
					RenderMeteor(projection, view, shader, meteor);
				}
			}
			else if (_root->GetGameObject()->GetType() == Constants::TIPO_ENEMIGO) {
				GameObject *g = _root->GetGameObject();
				//cout << "Enemigo " << endl;

				Enemy* enemyShip = static_cast<Enemy*>(g);
				if (enemyShip->Active()) {
					RenderEnemy(projection, view, shader, enemyShip);

					enemyShip->Disparar();
				}
			}
			else if (_root->GetGameObject()->GetType() == Constants::TIPO_MISIL) {
				GameObject *g = _root->GetGameObject();
				Missile* missile = static_cast<Missile*>(g);
				//cout << "Missil " << endl;
				if (missile->Active()) {
					//RenderMissile(projection, view, shader, missile);
					missile->Render(projection, view);
				}
			}
		}
	}
}

void Render::RenderLights(Shader& shader) {

	shader.Use();
	//Point Light
	shader.Set("light.position", vec3(0.0f, Constants::ALTURA_LUZ, 0.0f));
	shader.Set("light.ambient", 0.2f, 0.2f, 0.2f);
	shader.Set("light.diffuse", 0.3f, 0.3f, 0.3f);
	shader.Set("light.constant", 1.0f);
	shader.Set("light.linear", 0.07f);
	shader.Set("light.cuadratic", 0.017f);

}

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