#include "Node.h"

Node::Node()
{
}

Node::Node(GameObject* gameObject)
{
	_gameObject = gameObject;
}

void Node::Delete()
{
	delete  this;
}
bool Node::Seen() {
	return _seen;
}

void Node::DeleteChilds()
{
	for (size_t i = 0; i < 10; i++)
	{
		_childrens[i]->Delete();
	}
}

GameObject* Node::GetGameObject() {
	return _gameObject;
}

bool Node::HasChildren() {
	return _hasChildren;
}


void Node::AddChildren(Node* node) {
	if (_hasChildren) {
		_lastChildren++;
	}
	else {
		_hasChildren = true;
	}
	_childrens[_lastChildren] = node;
}
uint32_t Node::GetNumberChildren() {
	return _lastChildren + 1;
}

Node* Node::GetChildren(uint32_t idChildren) {
	return _childrens[idChildren];
}