#include<stdio.h>
#include<stdlib.h>
#include "trie.h"

int main(int argc,char * argv[]) {
    Node * root = allocate_node();
    char *words[] = {
        "apple", "apricot", "banana", "band", "bandwidth", "cat", "caterpillar",
        "dog", "dolphin", "elephant", "grape", "graph", "hello", "helmet", "hero",
        "hippo", "house", "java", "javascript", "jungle", "kangaroo", "keyboard",
        "king", "lion", "laptop", "monkey", "mountain", "network", "notebook",
        "ocean", "octopus", "penguin", "python", "queen", "query", "rabbit", "rain",
        "rocket", "science", "server", "signal", "sun", "tiger", "tree", "umbrella",
        "unicorn", "volcano", "water", "whale", "world", "xylophone", "yellow", "zebra"
    };

    for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++) {
        Trie_Insert(&root, words[i]);
    }
    printAutoSuggestions(root,"ba");

    generate_dot(root,"trie.dot");
    

    return 0;
}
//gcc -o main main.c trie.c