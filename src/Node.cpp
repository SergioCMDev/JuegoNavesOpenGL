#include "Node.h"

Node::Node()
{
}

Node::Node(Node* parent)
{
	_parent = parent;
	_gameObject = NULL;

}

Node::Node(GameObject* gameObject)
{
	_gameObject = gameObject;
	_gameObject->SetActualNode(this);
}


Node::Node(GameObject* gameObject, Node* parent)
{
	_gameObject = gameObject;
	_parent = parent;
	if (gameObject != NULL) {
		_gameObject->SetActualNode(this);
	}
}

Node::~Node()
{
	//GetGameObject()->~GameObject();
	//DeleteChilds();
	//delete this;
}


void Node::DeleteChilds()
{
	if (this != NULL) {
		if (HasChildren()) {
			for (size_t i = 0; i < GetNumberChildren() - 1; i++)
			{
				_childrens[i]->~Node();
			}
		}
	}
}

GameObject* Node::GetGameObject() {
	return _gameObject;
}

bool Node::HasChildren() {
	return _hasChildren;
}

Node* Node::GetParent() {
	return _parent;
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


void Node::ResetChildren()
{
	for (size_t idChildren = 0; idChildren < GetNumberChildren(); idChildren++)
	{
		GetChildren(idChildren)->GetGameObject()->Deactivate();
	}
}

Node* Node::GetChildren(uint32_t idChildren) {
	return _childrens[idChildren];
}