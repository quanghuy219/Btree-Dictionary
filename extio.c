#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int getStr(char *word) {
	fgets(word, MAX, stdin);
	while(word[strlen(word) - 1] == '\n') word[strlen(word) - 1] = '\0';

	if(strlen(word) == 0 || word == NULL) return 0;
	else return 1;
}