
#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "trie.h"
int capacity=1024;

Node * allocate_node(void) {
    Node *root = (Node*) malloc(sizeof(Node));
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return (Node *)NULL;
    }
    for(int i = 0; i < 26; i++){
        root->Children[i] = (Node*)NULL;
    }
    root->end = false;
    
    return root;
}
void Trie_Insert(Node** root, char* key) {
    if (strlen(key) ==0){
        (*root)->end = true;
        return ;
    }
    Node* ptr = *root;
    int index = (int)(*key) - (int)'a';
    if (ptr->Children[index] == NULL) {
        ptr->Children[index] = allocate_node();
        ptr->Children[index]->value = *key;

    }
    ptr = ptr->Children[index];
    Trie_Insert(&ptr,key+1);
    
}
bool isLastnode(Node *node) {
    for(int i = 0 ; i<26;i++){
        if(node->Children[i]) return false ;
    }
    return true;
}
void suggestionsRec(struct Node* root,
                    char * currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->end)
        printf("\n%s\n",currPrefix);
 
    for (int i = 0; i < 26; i++)
        if (root->Children[i]) {
            // child node character value
            char child = 'a' + i;
            char newPrefix[capacity];
            snprintf(newPrefix, sizeof(newPrefix), "%s%c", currPrefix, child);
            suggestionsRec(root->Children[i], newPrefix);
        }
}
int printAutoSuggestions(Node* root, char  * query)
{
    struct Node* pCrawl = root;
    for (int  i=0; i<strlen(query);i++) {
        char c = query[i];
        int ind = c - 'a';
 
        // no string in the Trie has this prefix
        if (!pCrawl->Children[ind])
            return 0;
 
        pCrawl = pCrawl->Children[ind];
    }
    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isLastnode(pCrawl)) {
        printf("\n %s \n");
        return -1;
    }
    suggestionsRec(pCrawl, query);
    return 1;
}
// write project to parse pseudo code into c code 
bool    TrieFind(Node * root , char * key){
    if (root == NULL) return  false ;
    Node * ptr = root ;
    for (int  i = 0 ; i< strlen(key);i++) {
        char k = (unsigned char) key[i];
        if (ptr->Children[k] ==NULL)  return  false;
        ptr = ptr->Children[(unsigned char)key[i]];
        
    }
    return true ;
    
}

void print_trie_dot(Node *root, FILE *file) {
    static int node_id = 0;

    if (root == NULL) return;

    int current_id = node_id++;

    // Label the node
    fprintf(file, "  node%d [label=\"%c\"];\n", current_id, root->value ? root->value : ' ');

    for (int i = 0; i < 26; i++) {
        if (root->Children[i] != NULL) {
            int child_id = node_id;
            fprintf(file, "  node%d -> node%d;\n", current_id, child_id);
            print_trie_dot(root->Children[i], file);
        }
    }
}
void generate_dot(Node *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "digraph Trie {\n");
    fprintf(file, "  node [shape=circle];\n");
    print_trie_dot(root, file);
    fprintf(file, "}\n");

    fclose(file);
}