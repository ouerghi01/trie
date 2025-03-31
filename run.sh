gcc -o test test.c src/trie.c
./test
dot -Tpng trie.dot -o trie.png

rm trie.dot
