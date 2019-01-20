#pragma once
#ifndef NODE_H
#define NODE_H
#include "GameObject.h"
#include "string.h"
#include "Shader.h"
#include "Missile.h"
#include "Enemy.h"
#include "Constants.h"

class Node {
public:
	Node();
	Node(GameObject* gameObject);
	GameObject* GetGameObject();
	~Node();
	void DeleteChilds();
	void AddChildren(Node* node);
	bool HasChildren();
	Node* GetChildren(uint32_t idChildren);
	uint32_t GetNumberChildren();
	uint32_t GetNumberChildrenActives();

	bool Seen();
private:
	Node* _childrens[10];
	uint32_t _lastChildren = 0;
	bool _hasChildren = false;
	GameObject* _gameObject;
	bool _seen = false;
};
#endif