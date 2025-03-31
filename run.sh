gcc -o test test.c trie.c
./test
dot -Tpng trie.dot -o trie.png

rm trie.dot
