#ifndef SYMB_TABLE_H
#define SYMB_TABLE_H
#define MAX_SIZE 10000

struct Entry{
	struct Type* type;	
};
struct symbolTalbe{
	struct Entry **Entries[MAX_SIZE];
};
#endif
