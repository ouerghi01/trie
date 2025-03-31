#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#ifndef TRIE_H
#define TRIE_H
typedef struct Node Node;

struct Node {
    Node *Children[26];
    char value;
    bool end ;
};
Node * allocate_node(void) ;
void Trie_Insert(Node** root, char* key) ;
bool isLastnode(Node *node) ;
void suggestionsRec(struct Node* root,
                    char * currPrefix);
int printAutoSuggestions(Node* root, char  * query);
bool    TrieFind(Node * root , char * key);
void print_trie_dot(Node *root, FILE *file) ;
void generate_dot(Node *root, const char *filename) ;


#endif