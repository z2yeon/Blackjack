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

	int i=1;
	int rn;//·£´ý¼ýÀÚ 
	srand( (unsigned)time(NULL));
	
	rn=rand()%52
	
	for(i=0;i<52;i++)
	{
		swap(CardTray[i],CardTray[rn]);
	}
	
}
