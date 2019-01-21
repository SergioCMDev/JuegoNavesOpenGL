#include"Node.h"
#include "Player.h"
#include "Meteor.h"
#include "Enemy.h"
#include "Missile.h"
#include "Camera.h"

static class GameControl {

public:
	GameControl(Node* player, Node* enemyShips, Node* Meteors);
	void CheckCollisions();
	bool _playerAlive;
	void MoveObjects(const double deltaTime);
	void ActivateGameObject(GameObject* ship);
	void ActivacionGameObjects();
private:
	void GameObjectDestroyed(GameObject* ship);
	void PlayerKilled();
	bool CheckCollisionsGameObjects(GameObject* x, GameObject* y);
	Node* _player, *_enemyShips, *_meteors;
	Camera* _camera;
	Player* GetPlayerReference(GameObject* objectPlayer);
	void MoveMeteors(const double deltaTime);
	void MoveEnemyShips(const double deltaTime);
	//static void MovePlayer(const double deltaTime);
	void MoveMissiles(const double deltaTime);
};