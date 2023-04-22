#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TrieNode{
    int count;   // number of times this word appears in the dictionary
    struct TrieNode *children[26]; // one child node for each character
}TrieNode;

void insert(TrieNode *root, char *word)
{
    TrieNode *p = root;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int idx = word[i] - 'a';
        if (p->children[idx]==NULL) {
            p->children[idx]=(TrieNode *) malloc(sizeof(TrieNode));
            p->children[idx]->count = 0;
            for (int j = 0; j < 26; j++) {
                p->children[idx]->children[j] = NULL;
            }
        }
        p = p->children[idx];
    }
    p->count++; // increase the occurrence count of the word
}

int numberOfOccurrences(TrieNode *root, char *word)
{
    TrieNode *p= root;
    int n = strlen(word);
    for (int i =0;i<n;i++) {
        int idx = word[i] - 'a';
        if (p->children[idx] ==NULL) {
            return 0; // word not found
        }
        p= p->children[idx];
    }
    return p->count;
}

void deallocateTrie(TrieNode *root)
{
    if (root == NULL) {
        return;
    }
    for (int i=0;i<26;i++) {
        deallocateTrie(root->children[i]);
    }
    free(root);
}

int main(void)
{
    // create a trie and insert words into it
    TrieNode *root=(TrieNode *) malloc(sizeof(TrieNode));
    root->count=0;
    for (int i=0;i<26;i++) {
        root->children[i] = NULL;
    }
    char *pWords[]={"notaword", "ucf", "no", "note", "corg"};
    int n=sizeof(pWords) / sizeof(char *);
    for (int i=0;i<n;i++)
    {
        insert(root, pWords[i]);
    }

    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurrences(root, pWords[i]));
    }
    deallocateTrie(root);

    return 0;
}
