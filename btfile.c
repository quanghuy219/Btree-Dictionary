#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include "soundex.h"
#include "bt/inc/btree.h"

#define MAX_WORD 100
#define MAX_DATA 100000
#define MAX 2000
#define MAX_LEN_WORD 40
#define MAX_LEN_MEAN 2000

void correct(char *str) {
	while (str[strlen(str) - 1] == '\n') str[strlen(str)-1] = '\0';
}

void split_word(char *word, char* mean) {
	int mark = 0;
	size_t i;
	for (i = 0; i < strlen(word); i++)
	{
		if(word[i] == '/') {
			mark = i;
			break;
		} 
	}
	if(mark != 0) {
	 	//strcat(mean,word+mark);
	 	// for (int i = mark; i < strlen(word); i++)
	 	// {
	 	// 	mean[i-mark] = word[i];
	 	// }
	 	word[mark-1] = '\0';
	}
	 
	for (i = 0; i < strlen(word); i++)
	{
		word[i] = word[i+1];
	}
}

int createBdict(FILE* fi,BTA* dict, BTA *soundExTree) {
	int count = 0;
	char word[MAX_WORD];
	char data[MAX_DATA];
	char buff[MAX_DATA];
	char soundex[5];
	int val;

	while(!feof(fi)) {
	
		fgets(buff, MAX_DATA, fi);

		while(buff[0] != '@') {
			strcat(data, buff);
			if(feof(fi)) break;
			fgets(buff, MAX_DATA, fi);
		}

		correct(data);
		if(strlen(word) != 0 && strlen(data) != 0) {
			val = btins(dict, word, data, MAX * sizeof(char));
			SoundEx(soundex, word, 4,1);
			btins(soundExTree, word, soundex, 5 * sizeof(char));
		}
		count++;
		if (buff[0] == '@')
		{
			word[0] = '\0';
			data[0] = '\0';	
			strcpy(word,buff);
			correct(word);
			split_word(word,data);
		}
		buff[0] = '\0';
	}
	return count;
}


int main()
{
	FILE* f1 = fopen("src.txt","r");
	btinit();
	BTA* dict = btcrt("dict.dat",0,0);
	BTA* soundExTree = btcrt("soundExTree.dat",0,0);

	if (dict == NULL)
	{
		printf("Error\n");
		return 0;
	}

	int words = createBdict(f1,dict, soundExTree);
	printf("Words inserted: %d\n", words);

	fclose(f1);
	btcls(dict);
	btcls(soundExTree);
	return 0;
}