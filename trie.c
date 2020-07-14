#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>

#define MAX_CHAR 26

struct trieNODE
{
	bool isWord;
	struct trieNODE *character[MAX_CHAR];
};

typedef struct trieNODE trieNODE;

trieNODE *newtrieNODE(void)
{
	trieNODE *newtrieNODE = (trieNODE*)malloc(sizeof(trieNODE));
	
	if(newtrieNODE)
	{
		newtrieNODE->isWord = false;

		for(int Count = 0; Count < MAX_CHAR; Count++)
			newtrieNODE->character[Count] = NULL;
	}

	return newtrieNODE;
}

void trieINSERT(trieNODE *rootNODE, char* word)
{
	trieNODE* node = rootNODE;
	while(*word)
	{
		if(node->character[*word - 'a'] == NULL)
		{
			node->character[*word - 'a'] = newtrieNODE();
			node = node->character[*word - 'a'];
		} else {
			node = node->character[*word - 'a'];
		}
		word++;
	}

	node->isWord = true;
}

bool trieSEARCH(trieNODE *rootNODE, char* word)
{
	if(rootNODE == NULL)
	{
		return false;
	}

	trieNODE* node = rootNODE;
	while(*word)
	{
		node = node->character[*word - 'a'];

		if(node == NULL)
			return false;
		word++;
	}
	return node->isWord;
}

bool checksubNODES(trieNODE* node)
{
	for(int Count = 0; Count < MAX_CHAR; Count++)
		if(node->character[Count] != NULL)
			return true;

	return false;
}


/*
 * DELETE function
 */
bool trieDELETE(trieNODE *rootNODE, char* word)
{


	trieNODE* NODE = rootNODE;
	if(NODE != NULL && NODE->character[*word - 'a'] != NULL) {
		 if(trieDELETE(NODE->character[*word - 'a'], word+1)) {
			 if(NODE->isWord == false) {
				 if(!checksubNODES(NODE)) {
					 free(NODE);
					 NODE = NULL;
					 return true;
				 } else {
					 return false;
				 }
			 }
		 }
	}

	if((*word) == '\0' && (NODE)->isWord == true) {
		if(!checksubNODES(NODE)) {
			free(NODE);
			NODE = NULL;
			return true;
		} else {
			NODE->isWord = false;
			return false;
		}
	}
}

/*
 * CONCAT retrieved word
 */
char* trieCONCAT(char *lchar, char sChar) {
	u_int8_t len = strlen(lchar);
	char *word = (char*) malloc(len+2);
	u_int8_t cnt = 0;

	while(lchar[cnt] != '\0') {
		word[cnt] = lchar[cnt];
		cnt++;
	}

	word[cnt++] = sChar;
	word[cnt] = '\0';

	return word;
}

/*
 * Seperate recursive function for ease
 */
bool trieAUTO(trieNODE *NODE, char* lchar) {
	if(NODE == NULL)
		return false;

	if(NODE->isWord)
	       printf("AUTO-complete suggestions: %s\n", lchar);	

	for(int cnt = 0; cnt < MAX_CHAR; cnt++) {
		if(NODE->character[cnt] != NULL) {
			trieAUTO(NODE->character[cnt], trieCONCAT(lchar, cnt+'a'));
		}
	}
}


/*
 * Wrapper for auto completion
 */
bool trieSearchComp(trieNODE* rootNODE, char* word) {

	trieNODE* NODE = rootNODE;

	char lchar = 0;

	if(NODE == NULL){
		return false;
	}

	
	while(*word) {
		NODE = NODE->character[*word - 'a'];
		word++;
	} 

	if(*word == '\0') {
		trieAUTO(NODE, &lchar);
	}
}



int main()
{
	trieNODE *root = newtrieNODE();

/*
 * INSERT TESTS
 */
	trieINSERT(root, "hi");
	trieINSERT(root, "hijyft");
        trieINSERT(root, "hihg");

	trieINSERT(root, "hello");
	trieINSERT(root, "he");	   
	
	trieINSERT(root, "okpp");

	trieINSERT(root, "okoa");
	trieINSERT(root, "okob");
        trieINSERT(root, "okoc");
        trieINSERT(root, "okod");
        trieINSERT(root, "okoe");
        trieINSERT(root, "okof");


	trieINSERT(root, "okajmdgmd");
        trieINSERT(root, "okakdjsajokajs");
        
	trieINSERT(root, "oduiikokajs");
	
	
/*
 * DELETE TEST
 */
	trieDELETE(root, "okoa");
	if(trieSEARCH(root, "okoa") == true)
                printf("FOUND\n");
        else
                printf("NOT FOUND\n");
/*
 * SEARCH TESTS
 */
	if(trieSEARCH(root, "okoe") == true)
		printf("FOUND\n");
	else
		printf("NOT FOUND\n");

	if(trieSEARCH(root, "hello") == true)
       		printf("FOUND\n");
        else
                printf("NOT FOUND\n");

/*
 * AUTO COMPLETION TEST
 */
	trieSearchComp(root, "od");
	trieSearchComp(root, "oko");
        trieSearchComp(root, "hi");
        trieSearchComp(root, "he");

	return 0;
}























