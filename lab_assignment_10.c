#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie *createTrie();

// Trie structure
struct Trie
{	
    int count;
    struct Trie *children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int i = 0;
    while(word[i] != '\0'){
        if (pTrie->children[word[i] - 'a'] == NULL){
            pTrie->children[word[i] - 'a'] = createTrie();
        }
        pTrie = pTrie->children[word[i] - 'a'];
        i++;
    }
    pTrie->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int i = 0;
    while(pTrie != NULL && word[i] != '\0'){
        pTrie = pTrie->children[word[i] - 'a'];
        i++;
    }
    if(pTrie == NULL){
        return(0);
    }else{
        return(pTrie->count);
    }
    
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie != NULL){
        for(int i = 0; i < 26; i++){
            deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return(NULL);
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *new = (struct Trie*)malloc(sizeof(struct Trie));
    new->count = 0;
    for (int i = 0; i < 26; i++){
        new->children[i] = NULL;
    }
    return(new);
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{   
    FILE *file = fopen(filename, "r");
    int words;
    char curr[50];
    fscanf(file, "%d", &words);
    for(int i = 0; i < words; i++){
        fscanf(file, "%s", curr);
        pInWords[i] = strdup(curr);
    }
    fclose(file);
    return(words);
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
    
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}