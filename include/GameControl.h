#pragma once
#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include"Node.h"
#include "Player.h"
#include "Meteor.h"
#include "Enemy.h"
#include "Missile.h"
#include "Camera.h"
#include "Shader.h"

static class GameControl {

public:
	GameControl(Node* player, Node* enemyships, Node* meteors, Camera* camera, Node* root);

	void CheckCollisions();
	bool _playerAlive;
	void MoveObjects(const double deltaTime);
	void ActivateGameObject(GameObject* ship);
	void ActivacionGameObjects(const float deltaTime, const float frame);
	uint32_t GetPuntuacion();
private:
	bool GeneracionGameObjects(const float deltaTime, const float frame);
	void GameObjectDestroyed(GameObject* ship);
	void PlayerKilled();
	bool CheckCollisionsGameObjects(GameObject* x, GameObject* y);
	Node* _player, *_enemyShips, *_meteors, * _root;
	Camera* _camera;
	void MoveMeteors(const double deltaTime);
	void MoveEnemyShips(const double deltaTime);
	void MoveMissiles(const double deltaTime);
	uint32_t vidas = Constants::VIDAS;
	uint32_t _puntuacion = 0;
};
#endif