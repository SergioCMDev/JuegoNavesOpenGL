#include "Player.h"

Player::Player() {

}

Player::Player(glm::vec3 position)
{
	Shader shaderNavePlayer = Utils::GetFullShader("Shaders/NavePlayerVS.vs", "Shaders/NavePlayerFS.fs");
	shaderNavePlayer.Use();
	position = vec3(0.0f, 0.0f, 0.0f);
	SetModel(Model(pathToModel));
	_shader = shaderNavePlayer;
	SetPosition(position);
	SetVelocity(2.5f);
	SetType(Constants::TIPO_PLAYER);
	SetScale(glm::vec3(0.3f));
	Activate();

}

Player::Player(Shader & shader, glm::vec3 position)
{
	shader.Use();
	_shader = shader;

	position = vec3(0.0f, 0.0f, 0.0f);
	SetModel(Model(pathToModel));
	SetPosition(position);
	SetVelocity(2.5f);
	SetType(Constants::TIPO_PLAYER);
	SetScale(glm::vec3(0.3f));
	Activate();
}

Player::~Player() {
	//delete this;
}

uint32_t Player::GetLastMissileUsed()
{
	return _lastMissileUsed;
}

void Player::SumLastMissileUsed()
{
	_lastMissileUsed++;
}

bool Player::Shooting()
{
	return _disparando;
}

void Player::Disparar() {

	if (_lastMissileUsed < 5) {
		_disparando = true;

		Node* poolMissilNode = GetActualNode()->GetChildren(0);
		GameObject* missileGameObject = poolMissilNode->GetChildren(_lastMissileUsed)->GetGameObject();
		Missile* missile = static_cast<Missile*>(missileGameObject);
		missile->SetPosition(this->GetPosition());
		missile->Activate();
		this->SumLastMissileUsed();
		cout << "disparo" << endl;
	}
	cout << "disparo erroneo" << endl;
}

void Player::Render(glm::mat4 &projection, glm::mat4 &view)
{
	glm::mat4 model = mat4(1.0f);
	_shader.Use();
	model = glm::translate(model, GetPosition());
	//model = glm::rotate(model, (float)glm::radians(0.0f), vec3(0.0f, 1.0f, 0.0f));

	model = glm::scale(model, GetScale());

	_shader.Set("projection", projection);
	_shader.Set("view", view);
	_shader.Set("model", model);
	GetModel().Draw(_shader);
}

void Player::Mover(const Movement movement, const float deltaTime)
{
	float actualVelocity = GetVelocity() * deltaTime;
	switch (movement) {
	case Movement::Forward:
		SetPosition(GetPosition() + GetUpVector() * actualVelocity); break;
	case Movement::Backward:
		SetPosition(GetPosition() - GetUpVector() * actualVelocity); break;
	case Movement::Left:
		SetPosition(GetPosition() + GetRightVector() * actualVelocity); break;
	case Movement::Right:
		SetPosition(GetPosition() - GetRightVector() * actualVelocity); break;
	}
}
