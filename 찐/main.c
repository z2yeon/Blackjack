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
int n_user;									//number of users 

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0;
int roundIndex = 0;							//game end flag

//This acts as scanf()
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}


//------ card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	
	int n;
	cardnum=CardTray[n];
	
	switch(cardnum%13+1)
	{
		case 1:
			if(sum<=10)
			 return 11;
			else if(sum>10)
			 return 1;
			break;
			
		case 10:
		case 11:
		case 12:
		case 13:
			return 10;
			break;
				
		default:
			return (cardnum%13+1);	 
	}
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	
	int n;
	cardnum=CardTray[n];
	
	switch(cardnum/13)
	{
		case 0:
			printf("��");
		case 1:
			printf("��");
		case 2:
			printf("��");
		case 3:
			printf("��");
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


//------ card array controllers -------------------------------

//mix the card sets and put in the array
void mixCardTray(void){

	int i;
	int j;
	int rn;//�������� 
	srand( (unsigned)time(NULL));
	
	
	for(i=0;i<100;i++)
	{
		for(j=0;j<N_CARDSET*N_CARD;j++)
	    {
		 CardTray[j]=j;
		 rn=rand()%N_CARDSET*N_CARD;
		 swap(CardTray[j],CardTray[rn]);
	    }
	}
	

	
}

//get one card from the tray
int pullCard(void) {
	
	 int i;
	 i=CardTray[cardIndex];
	 cardIndex++;	 
	 
	 if(cardIndex==N_CARDSET*N_CARD)  //Ran out of Card Tray 
		return gameEnd; //gameEnd!!
	 else
		return i;
	 
}


//------playing game functions -----------------------------

//player settiing
int configUser(void) {
	
	printf("input a number of player(MAX:%d): ",N_MAX_USER);
	n_user=getIntegerInput();
	
	if (n_user>N_MAX_USER||n_user<=0)
	 printf("The number of players must be from 1 to %d",N_MAX_USER);
	else
	 printf("---> cards are mixed& putted into tray\n");	
}

//betting
int betDollar(void){
	
	int bet=0;//player ���� �ݾ� 
	int rn_bet=0;//�ٸ� player�� ���ñݾ�(����) 
	int i;

	srand((unsigned)time(NULL));
	
	dollar[0]=N_DOLLAR-bet;//player ���� ���ñݾ� 
		
	printf("----------BETTING STEP---------\n");
	printf("--->your betting(total:%d): ",dollar[0]);
	scanf("%d",&bet[0]);
	
	if(bet[0]>dollar[0]||bet[0<0])
	 printf("You have $%d.Bet again plz.",dollar[0]);
	else
	{
		for(i=1;i<=n_user;i++)
	    {
	     rn_bet=rand()%50+1;
	     dollar[i]=N_DOLLAR-rn_bet;
		 printf("--->player %d:$%d\n",i,rn_bet);
	    }
	}
	//���п� ���� ���ñݾ� ��ȭ ����� 
}

//offering initial 2 cards
void offerCards(void) {
	
	int i;
	
	
	cardhold[n_user][0]=pullCard();//give first card for dealer
	cardhold[n_user][1]=pullCard();//give second card for dealer
	
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0]=pullCard();
		cardhold[i][1]=pullCard();
	}
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	

	
}

//getAction, Hit or Stay
int getAction(void) {
	
	int act; //Hit or Stay
	
	printf("\t�ƢƢ�Action: Hit(0) or Stay(others)");
	act=getIntegerInput;
	
	if(act==0)
	 return 0;
	else //���� 
	
	return act; 
}

//literally...
void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t �ƢƢ� ");
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
	int i;
	
	printf("----------ROUND%d RESULT\n",roundIndex);
	printf("--->your result: ");
	
	for(i=1;i<=n_user;i++)
	{
		printf("--->player%d result: ",i);
	}
}

int checkResult() {
	
}

int checkWinner() {
	
}

int sumCard(int cardnum,int i) {
	
	if(cardnum%13==1)							//A is 1 or 11
		
		cardSum[i]+=1;
		
	else if(cardnum%13==11||card%13==12||card%13==0)	//J,Q,K==10 
		cardSum[i]+=10;

	else if(cardnum%13>=2 && card%13<=10)	
		cardSum[i]+=card%13;
		

		
}

int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	

	
	 
	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for () //each player
		{
			while () //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}

int main(int argc, char *argv[]) {
	
	//���ӽ���
	while(gameEnd!=0){ 
	
	int n_round=1;
	n_round++;
		
	printf("-----------------------------------\n");
	printf("------ROUND %d(card index:%d)------\n",n_round,cardIndex); 
	printf("-----------------------------------\n");
	
	betDollar();
	midCardTray();
	}

	return 0;
}
