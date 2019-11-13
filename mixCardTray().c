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

int main(void){
	
	
	int i,j;
	int rshape,rnum;
	srand(time(NULL));
	
	rsahpe=rand()%4+1;
	rnum=rand()%13+1;
	
	while(i!=4&&j!=13)
	{
		swap(card[i][j],card[rshape][rnum]);
	}
	
}
