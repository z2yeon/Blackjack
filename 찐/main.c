#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "swap().c"



#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50

#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;

//player info 
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;	//참여인원 수 


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0;							//game end flag


void mixCardTray(void){

	int i;
	int j;
	int rn;//랜덤숫자 
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

int getCardNum(int cardnum) {
	
		switch(cardnum%13+1)
	{
		case 1:
			if(sum<=0)
			 return 11;
			else if(sum>10)
			 return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		case 5:
			return 5;	
		case 6:
			return 6;
		case 7:
			return 7;
		case 8:
			return 7;	
		case 9:
			return 9;
		case 10,11,12,13:
			return 10;		 
	}
}

void printCard(int cardnum) {
	
	switch(cardnum/13)
	{
		case 0:
			printf("♠");
		case 1:
			printf("◆");
		case 2:
			printf("♣");
		case 3:
			printf("♥");
	}
	
	switch(cardnum%13+1)
	{
		case 1:
			printf("A");
		case 2:
			printf("2");
		case 3:
			printf("3");
		case 4:
			printf("4");
		case 5:
			printf("5");	
		case 6:
			printf("6");	
		case 7:
			printf("7");	
		case 8:
			printf("8");	
		case 9:
			printf("9");	
		case 10:
			printf("10");	
		case 11:
			printf("J");	
		case 12:
			printf("Q");	
		case 13:
			printf("K");			 
	}
	
}

int betDollar(void){
	
	int bet=0;//player 배팅 금액 
	int rn_bet=0;//다른 player의 배팅금액(랜덤) 
	int i;

	srand((unsigned)time(NULL));
	
	dollar[0]=N_DOLLAR-bet;//player 현재 배팅금액 
		
	printf("----------BETTING STEP---------\n");
	printf("--->your betting(total:%d): ",dollar[0]);
	scanf("%d",&bet);
	
	for(i=1;i<=n_user;i++)
	{
	    rn_bet=rand()%50+1;
	    dollar[i]=N_DOLLAR-rn_bet;
		printf("--->player %d:$%d\n",i,rn_bet);
	}
	//승패에 따라 배팅금액 변화 만들기 
}

int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

int pullCard(void) {
	 
	 
	 
	 return ;
}

void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}







int main(int argc, char *argv[]) {
	
	//참여인원 입력 

	printf("input a number of player(MAX:%d): ",N_MAX_USER);
	scanf("%d",&n_user);
	printf("---> cards are mixed& putted into tray\n");
	
	//게임시작
	while(gameend!=0){ //나중에 gameend조건 변수 만들기 
	
	int cardindex=1;
	int n_round=1;
	n_round++;
		
	printf("-----------------------------------\n");
	printf("------ROUND %d(card index:%d)------\n",n_round,cardindex); 
	printf("-----------------------------------\n");
	
	betDollar();
	midCardTray();
	}

	return 0;
}
