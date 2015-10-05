#include "trie.h"

#include <stdlib.h>

#include "queue.h"

node *CreateNode(char symbol, bool isEnd)
{
	node *_new = (node *)malloc(sizeof(node));
	int i;

	_new->symbol = symbol;
	_new->isEnd = false;
    _new->failure = 0x00;
    
	for(i=0; i<SYMBOL_SIZE; i++)
		_new->child_vector[i] = 0x00;

	return _new;
}

void CraeteTrie(node** root)
{
	*root = CreateNode(0, false);
}


int InsertTrie(node **root, char *key)
{
	node *traversal;

////// when trie isn't initialized exit this function.
	if(*root == 0x00)
	{
		return -1;
	}

////// add word into trie.
	traversal = *root;
	while(*key)
	{
	////// if child which has symbol isn't exist create node.
	////// in other case move to node.
		if(traversal->child_vector[(unsigned)*key] == 0x00)
		{
			traversal->child_vector[(unsigned)*key] = CreateNode(*key, false);
		}
        traversal = traversal->child_vector[(unsigned)*key];
        key++;
	}

	if(traversal->child_vector[(unsigned)*key])
	{
		////// word is already exist
		return -1;
	}
	else
	{
	////// end of word.
        traversal->isEnd = true;
		traversal->child_vector[(unsigned)*key] = CreateNode(*key, true);
	}
    
    return 0;

}


void DestroyTrie(node *root)
{
    int i;
    for(i =0; i < SYMBOL_SIZE; i++)
    {
        if(root->child_vector[i])
        {
            DestroyTrie(root->child_vector[i]);
        }
    }
    free(root);
}


//// aho corasick algorithm
void MakeFailure(node** root)
{
    // queue for BFS(breath first search).
    queue_t queue = {0, 0, 0};
    int i;
    
    // failure function of root is root.
    (*root)->failure = (*root);
    
    // enqueue child node of root.
    // and set it's failure link as root.
    for(i=0; i<SYMBOL_SIZE; i++)
    {
        node *s = (*root)->child_vector[i];
        if(s)
        {
            enqueue(&queue, s);
            s->failure = (*root);
        }
    }
    
    // breath first search.
    while(queue.size)
    {
        node *pop = dequeue(&queue);
        
        for(i=0; i<SYMBOL_SIZE; i++)
        {
            node *s = pop->child_vector[i];
            node *state = 0x00;
            if(s)
            {
                enqueue(&queue, s);
                state = pop->failure;
                
                // search failure function.
                while(state->child_vector[i] == 0x00)
                {
                    state = state->failure;
                    if(state == (*root))
                        break;
                }
                
                // set failure function
                // when same symbol is exist, set this as failure function
                // in other case failure function is root.
                if(state->child_vector[i])
                    s->failure = state->child_vector[i];
                else
                    s->failure = (*root);
            }
        }
    }
}

bool PatternMatching(node **root, char *string)
{
    node *state = (*root);
    
    while(*string)
    {
        // if symbol isn't exist, goto failure function.
        while(state->child_vector[(unsigned)*string] == 0x00)
        {
            state = state->failure;
            if(state == (*root))
                break;
        }
        // move to next symbol
        if(state->child_vector[(unsigned)*string])
        {
            state = state->child_vector[(unsigned)*string];
        }
        
        string++;
        
        // if pattern is exist, return true.
        if(state->isEnd)
            return true;
    }
    // pattern isn't exist in string.
    return false;
}