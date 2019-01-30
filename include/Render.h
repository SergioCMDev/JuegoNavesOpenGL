#pragma once
#ifndef RENDER_H
#define RENDER_H
#include"Node.h"
#include "Player.h"
#include "Meteor.h"
#include "Enemy.h"
#include "Missile.h"
#include "Camera.h"
#include "Shader.h"
#include "Cube.h"
#include "Quad.h"
#include "Sphere.h"
#include "GameControl.h"

static class Render {

public:
	Render::Render(Node * node, bool debug, Camera* camera);

	void RenderScene(Quad quadSuelo, Sphere sphere, Cube cube);
	void RenderGame(Node * _root, Shader &shaderModels, Shader& depthShader, pair<uint32_t, uint32_t> fboRes);
	void RenderGameObjects(Node * _root, Shader &shader);
	void RenderLights(Shader& shaderModels);
	pair<uint32_t, uint32_t> createFBO();
	void RenderPlayer(glm::mat4 &projection, glm::mat4 &view, Shader &shader, Player* player);
	void RenderMeteor(glm::mat4 &projection, glm::mat4 &view, Shader &shader, Meteor* meteor);
	void RenderEnemy(glm::mat4 &projection, glm::mat4 &view, Shader &shader, Enemy* enemy);
	void RenderMissile(glm::mat4 &projection, glm::mat4 &view, Shader &shader, Missile* missile);

private:
	bool _debug = false;
	Sphere _sphere; 
	Quad _quadSuelo;
	Node* _node;
	Node* _player;
	Camera* _camera;
};
#endif