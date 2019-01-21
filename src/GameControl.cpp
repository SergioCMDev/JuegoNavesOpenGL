#include "GameControl.h"

GameControl::GameControl(Node* player, Node* enemyships, Node* meteors) {
	_player = player;
	_enemyShips = enemyships;
	_meteors = meteors;
}


void GameControl::PlayerKilled() {
	_player->GetGameObject()->Deactivate();
	_playerAlive = false;
}

void GameControl::ActivateGameObject(GameObject * object)
{
	object->Activate();

}

void GameControl::GameObjectDestroyed(GameObject* object) {
	object->Deactivate();
}



void GameControl::CheckCollisions()
{
	//Check Player vs EnemyShips
	for (size_t i = 0; i < _enemyShips->GetNumberChildren(); i++)
	{
		if (_enemyShips->GetChildren(i)->GetGameObject()->Rendered()) {

			if (CheckCollisionsGameObjects(_player->GetGameObject(), _enemyShips->GetChildren(i)->GetGameObject())) {

				PlayerKilled();
			}
		}
	}
	//Check Player vs Meteors

	for (size_t i = 0; i < _meteors->GetNumberChildren(); i++)
	{
		if (_meteors->GetChildren(i)->GetGameObject()->Rendered()) {

			if (CheckCollisionsGameObjects(_player->GetGameObject(), _meteors->GetChildren(i)->GetGameObject())) {

				PlayerKilled();

			}
		}
	}

	//Check Player vs EnemyMissiles
	for (size_t enemyShip = 0; enemyShip < _enemyShips->GetNumberChildren(); enemyShip++)
	{
		Node* enemyShipNode = _enemyShips->GetChildren(enemyShip);
		//for (size_t enemyMissile = 0; enemyMissile < _enemyShips->GetChildren(enemyShip)->GetNumberChildren(); enemyMissile++)
		if (enemyShipNode->HasChildren()) {
			for (size_t enemyMissile = 0; enemyMissile < enemyShipNode->GetNumberChildren(); enemyMissile++)
			{
				if (enemyShipNode->GetChildren(enemyMissile)->GetGameObject()->Rendered()) {

					if (CheckCollisionsGameObjects(_player->GetGameObject(), enemyShipNode->GetChildren(enemyMissile)->GetGameObject())) {

						PlayerKilled();
					}
				}
			}
		}
	}

	//Check Missiles  player vs EnemyShips

	Node* poolMisilesPlayer = _player->GetChildren(0);
	for (size_t i = 0; i < poolMisilesPlayer->GetNumberChildren(); i++)
	{
		for (size_t enemyShip = 0; enemyShip < _enemyShips->GetNumberChildren(); enemyShip++)
		{
			if (poolMisilesPlayer->GetChildren(i)->GetGameObject()->Rendered() && _enemyShips->GetChildren(enemyShip)->GetGameObject()->Rendered()) {

				if (CheckCollisionsGameObjects(poolMisilesPlayer->GetChildren(i)->GetGameObject(), _enemyShips->GetChildren(enemyShip)->GetGameObject())) {

					GameObjectDestroyed(_enemyShips->GetChildren(enemyShip)->GetGameObject());
					GameObjectDestroyed(poolMisilesPlayer->GetChildren(i)->GetGameObject());
				}
			}
		}
	}

	//Check Missiles  player vs Meteors

	for (size_t i = 0; i < poolMisilesPlayer->GetNumberChildren(); i++)
	{
		for (size_t meteor = 0; meteor < _meteors->GetNumberChildren(); meteor++)
		{
			if (poolMisilesPlayer->GetChildren(i)->GetGameObject()->Rendered() && _meteors->GetChildren(meteor)->GetGameObject()->Rendered()) {

				if (CheckCollisionsGameObjects(_player->GetChildren(i)->GetGameObject(), _meteors->GetChildren(meteor)->GetGameObject())) {

					GameObjectDestroyed(_meteors->GetChildren(meteor)->GetGameObject());
					GameObjectDestroyed(poolMisilesPlayer->GetChildren(i)->GetGameObject());

				}
			}
		}
	}
}

bool GameControl::CheckCollisionsGameObjects(GameObject* x, GameObject* y) {
	bool collision = false;
	float posX1 = x->GetPosition().x + x->_collider->_scale.x;
	bool collisionColliderX1 = posX1 >= y->GetPosition().x		&&		y->GetPosition().x >= x->GetPosition().x;
	//bool collisionColliderX2 = posX1 == y->GetPosition().x		&&		y->GetPosition().x == x->GetPosition().x;
	//bool collisionColliderX3 = posX1 <= y->GetPosition().x		&&		y->GetPosition().x <= x->GetPosition().x;


	//bool collisionX1 = x->GetPosition().x + 2 >= y->GetPosition().x;
	//bool collisionX2 = x->GetPosition().x + 2 == y->GetPosition().x;
	//bool collisionX2 = x->GetPosition().x + 2 <= y->GetPosition().x;

	float posZ1 = x->GetPosition().z + x->_collider->_scale.z;
	bool collisionColliderZ1 = posZ1 >= y->GetPosition().z		&&		y->GetPosition().z >= x->GetPosition().z;
	//bool collisionColliderZ2 = posZ1 == y->GetPosition().z		&&		y->GetPosition().z == x->GetPosition().z;
	//bool collisionColliderZ3 = posZ1 <= y->GetPosition().z		&&		y->GetPosition().z <= x->GetPosition().z;

	if (collisionColliderZ1 && collisionColliderX1) {
		//cout << "KO" << endl;
		collision = true;

	}


	return collision;
}
Player* GameControl::GetPlayerReference(GameObject* objectPlayer) {
	GameObject *g = objectPlayer;
	Player* player = static_cast<Player*>(objectPlayer);
	return player;
}

void GameControl::MoveMeteors(const double deltaTime)
{
	for (size_t i = 0; i < _meteors->GetNumberChildren(); i++)
	{
		GameObject *g = _meteors->GetChildren(i)->GetGameObject();
		Meteor* meteor = static_cast<Meteor*>(g);
		if (meteor->Rendered()) {
			meteor->Mover(deltaTime);
		}

	}
}

void GameControl::MoveEnemyShips(const double deltaTime)
{
	for (size_t i = 0; i < _enemyShips->GetNumberChildren(); i++)
	{
		GameObject *g = _enemyShips->GetChildren(i)->GetGameObject();
		Enemy* enemyship = static_cast<Enemy*>(g);
		if (enemyship->Rendered()) {
			enemyship->Mover(GameObject::Movement::Backward, deltaTime);
		}

	}
}



void GameControl::MoveMissiles(const double deltaTime)
{
	for (size_t ship = 0; ship < _enemyShips->GetNumberChildren(); ship++)
	{
		if (_enemyShips->GetChildren(ship)->HasChildren()) {

			for (size_t missil = 0; missil < _enemyShips->GetChildren(ship)->GetNumberChildren(); missil++)
			{
				GameObject *g = _enemyShips->GetChildren(ship)->GetChildren(missil)->GetGameObject();
				Missile* missile = static_cast<Missile*>(g);
				if (missile->Rendered()) {
					missile->Mover(GameObject::Movement::Backward, deltaTime);
				}

			}
		}
	}
	Node* poolMisilesPlayer = _player->GetChildren(0);
	if (poolMisilesPlayer->HasChildren()) {

		for (size_t missil = 0; missil < poolMisilesPlayer->GetNumberChildren(); missil++)
		{
			GameObject *g = poolMisilesPlayer->GetChildren(missil)->GetGameObject();
			Missile* missile = static_cast<Missile*>(g);
			if (missile->Rendered()) {
				missile->Mover(GameObject::Movement::Backward, deltaTime);
			}
		}
	}
}




void GameControl::MoveObjects(const double deltaTime) {

	MoveMeteors(deltaTime);
	MoveEnemyShips(deltaTime);
	MoveMissiles(deltaTime);
}