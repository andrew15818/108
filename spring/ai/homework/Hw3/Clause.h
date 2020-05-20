#ifndef CLAUSE_H
#define CLAUSE_H

#include<list>

// type of each cell
enum Type
{
	mine,
	hint,
	unassigned,
	safe
};
/*For the status, we can know the status 
of a cell without actually querying it,
so it can be 'mined' since we know its 
status beforehand.*/


struct Node
{
	int x, y; 	  // row and column number, respectively
	int adjacent = 0; // number of adjacent mines
	Type type = unassigned; //at the beginning no nodes have been assigned
	bool truth_value = false;
};

// class to maintain in our knowledge base
class Clause
{
	private:
	
		
		
	public:
		std::list<Node*> literals;
		int size = 0; // how many literals in our clause
		/*Some tentative ideas for clause functionality*/
		void insert_literal(Node&);

};

#endif
