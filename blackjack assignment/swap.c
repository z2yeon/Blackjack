#include <stdio.h>
#include <stdlib.h>


#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50

#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30

void swap(int a,int b){
	int temp;
	extern CardTray[N_CARDSET*N_CARD];
	
	temp=CardTray[a];
	CardTray[a]=CardTray[b];
	CardTray[b]=temp;
	
}
