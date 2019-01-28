#include "GameControl.h"
//const float screen_width = 800.0f, screen_height = 600.0f;
const float screen_width = 1280, screen_height = 720;
const float shadow_width = 1024, shadow_height = 1024;
const float shadow_near = 1.0f;
const float shadow_far = 7.5f;
float lasHitPlayer = 0.0f;

GameControl::GameControl(Node* player, Node* enemyships, Node* meteors, Camera* camera, Node* root) {
	_player = player;
	_enemyShips = enemyships;
	_meteors = meteors;
	_camera = camera;
	_root = root;
}

uint32_t GameControl::GetPuntuacion() {
	return _puntuacion;
}

void GameControl::PlayerKilled() {
	float currentFrame = glfwGetTime();
	if (currentFrame > (lasHitPlayer + 5.0f)) {
		lasHitPlayer = currentFrame;
		vidas--;
		cout << "VIDAS " << vidas << endl;
	}

	if (vidas <= 0) {
		_player->GetGameObject()->Deactivate();
		_playerAlive = false;
	}
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
		if (_enemyShips->GetChildren(i)->GetGameObject()->Active()) {

			if (CheckCollisionsGameObjects(_player->GetGameObject(), _enemyShips->GetChildren(i)->GetGameObject())) {

				PlayerKilled();
			}
		}
	}
	//Check Player vs Meteors

	for (size_t i = 0; i < _meteors->GetNumberChildren(); i++)
	{
		if (_meteors->GetChildren(i)->GetGameObject()->Active()) {

			if (CheckCollisionsGameObjects(_player->GetGameObject(), _meteors->GetChildren(i)->GetGameObject())) {

				PlayerKilled();

			}
		}
	}

	//Check Player vs EnemyMissiles
	for (size_t enemyShip = 0; enemyShip < _enemyShips->GetNumberChildren(); enemyShip++)
	{
		Node* enemyShipNode = _enemyShips->GetChildren(enemyShip);
		if (enemyShipNode->HasChildren()) {
			Node* enemyShipMissilePoolNode = enemyShipNode->GetChildren(0);
			if (enemyShipMissilePoolNode->HasChildren()) {
				for (size_t enemyMissile = 0; enemyMissile < enemyShipMissilePoolNode->GetNumberChildren(); enemyMissile++)
				{
					if (enemyShipMissilePoolNode->GetChildren(enemyMissile)->GetGameObject()->Active()) {

						if (CheckCollisionsGameObjects(_player->GetGameObject(), enemyShipMissilePoolNode->GetChildren(enemyMissile)->GetGameObject())) {
							PlayerKilled();
						}
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
			if (poolMisilesPlayer->GetChildren(i)->GetGameObject()->Active() && _enemyShips->GetChildren(enemyShip)->GetGameObject()->Active()) {

				if (CheckCollisionsGameObjects(poolMisilesPlayer->GetChildren(i)->GetGameObject(), _enemyShips->GetChildren(enemyShip)->GetGameObject())) {
					//En caso de tener un pool de misiles y misiles los reseteamos
					Node * enemyShipPool = _enemyShips->GetChildren(enemyShip)->GetChildren(0);
					if (enemyShipPool->HasChildren())
					{
						enemyShipPool->ResetChildren();
					}
					_puntuacion++;
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
			if (poolMisilesPlayer->GetChildren(i)->GetGameObject()->Active() && _meteors->GetChildren(meteor)->GetGameObject()->Active()) {

				if (CheckCollisionsGameObjects(poolMisilesPlayer->GetChildren(i)->GetGameObject(), _meteors->GetChildren(meteor)->GetGameObject())) {
					GameObjectDestroyed(poolMisilesPlayer->GetChildren(i)->GetGameObject());
				}
			}
		}
	}
}

bool GameControl::CheckCollisionsGameObjects(GameObject* x, GameObject* y) {
	bool collision = false;
	//float posX1 = x->GetPosition().x + x->_collider->_scale.x;
	float posX1 = x->GetPosition().x + 1;
	bool collisionColliderX1 = posX1 >= y->GetPosition().x		&&		y->GetPosition().x >= x->GetPosition().x;
	//bool collisionColliderX2 = posX1 == y->GetPosition().x		&&		y->GetPosition().x == x->GetPosition().x;
	//bool collisionColliderX3 = posX1 <= y->GetPosition().x		&&		y->GetPosition().x <= x->GetPosition().x;


	//bool collisionX1 = x->GetPosition().x + 2 >= y->GetPosition().x;
	//bool collisionX2 = x->GetPosition().x + 2 == y->GetPosition().x;
	//bool collisionX2 = x->GetPosition().x + 2 <= y->GetPosition().x;

	//float posZ1 = x->GetPosition().z + x->_collider->_scale.z;
	float posZ1 = x->GetPosition().z + 1;
	bool collisionColliderZ1 = posZ1 >= y->GetPosition().z		&&		y->GetPosition().z >= x->GetPosition().z;
	//bool collisionColliderZ2 = posZ1 == y->GetPosition().z		&&		y->GetPosition().z == x->GetPosition().z;
	//bool collisionColliderZ3 = posZ1 <= y->GetPosition().z		&&		y->GetPosition().z <= x->GetPosition().z;

	if (collisionColliderZ1 && collisionColliderX1) {
		//cout << "KO" << endl;
		collision = true;

	}


	return collision;
}

void GameControl::MoveMeteors(const double deltaTime)
{
	for (size_t i = 0; i < _meteors->GetNumberChildren(); i++)
	{
		GameObject *g = _meteors->GetChildren(i)->GetGameObject();
		Meteor* meteor = static_cast<Meteor*>(g);
		if (meteor->Active()) {
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
		if (enemyship->Active()) {

			enemyship->Mover(deltaTime);
		}
	}
}

void GameControl::MoveMissiles(const double deltaTime)
{
	for (size_t ship = 0; ship < _enemyShips->GetNumberChildren(); ship++)
	{
		if (_enemyShips->GetChildren(ship)->HasChildren()) {

			Node* poolEnemyMissiles = _enemyShips->GetChildren(ship)->GetChildren(0);
			if (poolEnemyMissiles->HasChildren()) {
				for (size_t missil = 0; missil < poolEnemyMissiles->GetNumberChildren(); missil++)
				{
					GameObject *g = poolEnemyMissiles->GetChildren(missil)->GetGameObject();
					Missile* missile = static_cast<Missile*>(g);
					if (missile->Active()) {
						missile->Mover(GameObject::Movement::Forward, deltaTime);
					}
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
			if (missile->Active()) {
				missile->Mover(GameObject::Movement::Backward, deltaTime);
			}
		}
	}
}

bool GameControl::GeneracionGameObjects(const float deltaTime, const float frame) {
	srand(rand());
	uint32_t valueGeneration = (rand() * deltaTime) / frame;
	if (valueGeneration % 2 == 0) {
		//cout << "Generamos";
		return true;
	}
	//cout << "No Generamos";
	return false;
}

void GameControl::ActivacionGameObjects(const float deltaTime, const float frame) {
	if (GeneracionGameObjects(deltaTime, frame)) {

		for (size_t ship = 0; ship < _enemyShips->GetNumberChildren(); ship++)
		{
			if (!_enemyShips->GetChildren(ship)->GetGameObject()->Active()) {

				GameObject *g = _enemyShips->GetChildren(ship)->GetGameObject();
				Enemy* EnemyShip = static_cast<Enemy*>(g);
				EnemyShip->SetRandomPosition();
				EnemyShip->Activate();

			}
		}
	}

	for (size_t meteor = 0; meteor < _meteors->GetNumberChildren(); meteor++)
	{
		if (!_meteors->GetChildren(meteor)->GetGameObject()->Active()) {

			GameObject *g = _meteors->GetChildren(meteor)->GetGameObject();
			Meteor* meteorObject = static_cast<Meteor*>(g);
			meteorObject->SetRandomPosition();
			meteorObject->Activate();
		}
	}
}

void GameControl::MoveObjects(const double deltaTime) {

	MoveMeteors(deltaTime);
	MoveEnemyShips(deltaTime);
	MoveMissiles(deltaTime);
}
