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

extern cardIndex;
extern CardTray[];

//------ card array controllers -------------------------------

//mix the card sets and put in the array
void mixCardTray(void){

	int i;
	int j;
	int rn;	//random number

	
	srand( (unsigned)time(NULL));
	
	
	for(i=0;i<100;i++)		//Stabilize the probability sufficiently
	{
		for(j=0;j<N_CARDSET*N_CARD;j++)
	    {
		 CardTray[j]=j;		//initialize array
		 rn=rand()%(N_CARDSET*N_CARD);
		 swap(j,rn);	//swap each other
	    }
	}
	
}

//get one card from the tray
int pullCard(void) {

	int i;

	i=CardTray[cardIndex];
	cardIndex++;	 
	
	return i;
}

