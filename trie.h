#ifndef __TRIE_H__
#define __TRIE_H__

#define SYMBOL_SIZE	256

typedef enum { false = 0, true } bool;
typedef unsigned char uchar;

//// trie node
typedef struct node
{
	uchar symbol;
	bool isEnd;
    
    struct node *failure;

	struct node *child_vector[SYMBOL_SIZE];

} node;

//// trie function
node *CreateNode(char symbol, bool isEnd);

void CraeteTrie(node** root);
int InsertTrie(node **root, char *key);

node *SearchTrie(node **root, const char *key);
void DestroyTrie(node *root);


//// aho corasick algorithm

void MakeFailure(node** root);

bool PatternMatching(node **root, char *string);
#endif