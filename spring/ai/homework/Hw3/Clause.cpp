#include "Clause.h"
void Clause::insert_literal(Node& node)
{
	Node* tmp = &node;
	this->literals.push_back(tmp);
	this->size++;
}

