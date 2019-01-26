#include"Node.h"
#include "Player.h"
#include "Meteor.h"
#include "Enemy.h"
#include "Missile.h"
#include "Camera.h"
#include "Shader.h"

static class GameControl {

public:
	GameControl(Node* player, Node* enemyShips, Node* Meteors);
	GameControl(Node* player, Node* enemyships, Node* meteors, Camera* camera, Node* root);

	void CheckCollisions();
	bool _playerAlive;
	void MoveObjects(const double deltaTime);
	void ActivateGameObject(GameObject* ship);
	void ActivacionGameObjects(const float deltaTime, const float frame);
	void RenderGameObjects(Node * _root);
	void RenderLights(Shader& shaderModels);
private:
	void GameObjectDestroyed(GameObject* ship);
	void PlayerKilled();
	bool CheckCollisionsGameObjects(GameObject* x, GameObject* y);
	Node* _player, *_enemyShips, *_meteors, * _root;
	Camera* _camera;
	Player* GetPlayerReference(GameObject* objectPlayer);
	void MoveMeteors(const double deltaTime);
	void MoveEnemyShips(const double deltaTime);
	void MoveMissiles(const double deltaTime);
};