#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt/inc/btree.h"
#include <ncurses.h>

#include "model_lib.h"
#include "extio.h"

#define MAX_LEN_WORD 40
#define MAX_LEN_MEAN 2000
#define MAX 2000

void findSuggestion(BTA *soundExTree, char *word) {
	
	char suggestion_str[10][MAX_LEN_WORD];

	int size = suggestion(soundExTree, word, suggestion_str);

	if (size > 0)
	{
		printf("Do you mean: \n");
		for (int i = 0; i < size; i++)
		{
			printf("%s\n",suggestion_str[i] );
		}
	}
	else printf("No suggetion found\n");
}

void searchWord(BTA *dict, BTA *soundExTree, char *word, char *mean) {
	int val;
	val = findWord(dict, word, mean);

	if(val == 1) printf("%s\n", mean);

	else findSuggestion(soundExTree, word);

}

void search(BTA *dict, BTA *soundExTree) {
	char result[MAX_LEN_WORD];
	char word[MAX_LEN_WORD];
	char mean[MAX_LEN_MEAN];
	word[0] = '\0';
	int mode;
	mode = get_word(word);
	
	if(mode == 2) {
		int val = autoComplete(soundExTree,word, result);
		if (val > 0) {
			printf("%s\n", result);
			getchar();
			searchWord(dict, soundExTree, result, mean);
		}
		else  {
			printf("%s\n",word);
			getchar();
			searchWord(dict, soundExTree, word, mean);
		}
	}

	if (mode == 1)
	{	
		printf("%s\n",word);
		getchar();
		searchWord(dict, soundExTree, word, mean);
	}
}

void add(BTA *dict, BTA *soundExTree) {
	char word[MAX_LEN_WORD];
	char mean[MAX_LEN_MEAN];
	printf("Word: \n");
	
	int checkEmptyWord = getStr(word);
	if(checkEmptyWord == 0) {
		printf("Exit\n");
		return;
	}

	int exist = findWord(dict, word, mean);

	if(exist == 1) printf("Word '%s' exist \n", word);

	else {
		printf("Meaning: \n");
		
		while(getStr(mean) == 0);

		int adddict = addToDict(dict, word, mean);
		int addSound = addToSoundExTree(soundExTree, word);
		if (adddict == 0 ) printf("Added '%s' to dictionary\n",word);
		else printf("Insertion error to dictionary\n");
		if(addSound == 0 ) printf("Added '%s' to soundExTree\n",word);
		else printf("Insertion error to soundExTree\n");
		
	}
}

void delete(BTA *dict, BTA *soundExTree) {
	char word[MAX_LEN_WORD];
	char mean[MAX_LEN_MEAN];

	printf("Delete word: ");
	getStr(word);

	int exist = findWord(dict, word, mean);

	if (exist == 0) printf("Word not found\n");

	else {
		int deleteDict = deleteInDict(dict, word);
		int deleteSoundExTree = deleteInSoundExTree(soundExTree, word);

		if(deleteDict == 0) printf("%s deleted in dictionary\n",word);
		else printf("Delete in dictionary error\n");

		if (deleteSoundExTree == 0) printf("%s deleted in soundExTree\n",word );
		else printf("Delete in soundExTree error\n");
	}

}
