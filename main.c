#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt/inc/btree.h"

#include "Bdict.h"
#include "model_lib.h"

#define MAX_LEN_WORD 40
#define MAX_LEN_MEAN 2000
#define MAX 2000


int main()
{
	int select = 1;
	btinit();

	BTA *dict = btopn("dict.dat",0,0);
	BTA *soundExTree = btopn("soundExTree.dat",0,0);
	

	while (select != 0) {
		printf("1. Search \n");
		printf("2. Add\n");
		printf("3. Delete\n");
		printf("0. Quit \n");
		scanf("%d",&select);
		while( getchar() != '\n' );

		switch(select) {
			case 1: 
				search(dict, soundExTree);
				break;
			case 2: 
				add(dict, soundExTree);
				break;
			case 3: 
				delete(dict, soundExTree);
				break;
			case 0: 
				break; 
		}

		printf("\n\n\n");
	} 

	btcls(dict);
	btcls(soundExTree);
	return 0;
}