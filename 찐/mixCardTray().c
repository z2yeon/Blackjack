#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50

#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


void mixCardTray(void){
	int CardTray[N_CARDSET*N_CARD];
	int i;
	int j;
	int rn;//·£´ý¼ýÀÚ 
	srand( (unsigned)time(NULL));
	
	rn=rand()%N_CARDSET*N_CARD;
	
	for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		CardTray[i]=i;
	}
	for(j=0;j<N_CARDSET*N_CARD;j++)
	{
		swap(CardTray[j],CardTray[rn]);
	}
	
}
