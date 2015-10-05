//
//  main.c
//  trie
//
//  Created by jangsoo on 2015. 10. 2..
//  Copyright © 2015년 jangsoo. All rights reserved.
//

#include <stdio.h>

#include "trie.h"
int main(int argc, const char * argv[]) {

    node *root;
    
    CraeteTrie(&root);
    
    InsertTrie(&root, "take");
    InsertTrie(&root, "fast");
    InsertTrie(&root, "sofa");
    
    MakeFailure(&root);
    
    PatternMatching(&root, "aasosofab");
    DestroyTrie(root);
    return 0;
}
