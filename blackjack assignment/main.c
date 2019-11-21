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


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardCNT[N_MAX_USER];
int cardIndex = 0;

//player info 
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users 

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0;							//game end flag
int roundIndex = 1;							//round Index

int main(int argc, char *argv[]) {
	
	int i;
	int getActionReturn; //getAction
	
	srand((unsigned)time(NULL));
	
	//player settiing
	configUser();
	
	 
	//Game initialization --------
	//1. players' dollar
	for(i=0;i<n_user;i++)
	{
		dollar[i]=N_DOLLAR;
	}
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
	printf("-----------------------------------\n");
	printf("------ROUND %d(card index:%d)------\n",roundIndex,cardIndex); 
	printf("-----------------------------------\n\n");	
	
	for(i=0;i<n_user;i++)
	{
		cardCNT[i]=2;
		cardSum[i]=0;
	} 
		
	betDollar();
	offerCards(); //1. give cards to all the players
	printCardInitialStatus();

	
	printf("\n------------------ GAME START --------------------------\n");
		
	//user's turn
	printf(">>>my turn\n");
	
	while(1){
		printUserCardStatus(0,cardCNT[0]);
		calcStepResult(0,cardCNT[0]);
	
        if(cardSum[0]==21&&cardCNT[0]==2)			//blackjack, win
	    {
	  		dollar[0]+=bet[0];
	  		printf("Blackjack! Win.\t--->$%d\n",dollar[0]);
	  		break;
	    }
	    
	    /*else if(cardSum[0]>21)						//Overflow, Lose
	    {
	    	dollar[0]-=bet[0];
	    	printf("Overflow! Lose.\t--->#%d\n",dollar[0]);
	    	break;
		}*/
		
		
		getActionReturn=getAction();
		
		if(getActionReturn==0)
	    {
	    	if(cardSum[0]>21)						//Overflow, Lose
	    	{
	    	 dollar[0]-=bet[0];
	    	 printf("Overflow! Lose.(Sum:%d)\t--->$%d\n",cardSum[0],dollar[0]);
	    	 break;
	    	}
	    	
	    	cardhold[0][cardCNT[0]]=pullCard();
	   		cardCNT[0]++;
	   		calcStepResult(0,cardCNT[0]);
	    }
	    
		else if (getActionReturn==1)
		{		
			calcStepResult(0,cardCNT[0]);
			break;
		} 
	}
	
	
	
	//each player's turn	
	//do until the player dies or player says stop
	for(i=1;i<n_user;i++) 
	{	
	  cardCNT[i]=2;
	  
	  printf(">>>player%d's turn\n",i);
	  printUserCardStatus(i,cardCNT[i]);	//print current card status printUserCardStatus();
	  calcStepResult(i,cardCNT[i]);
	  
	  if(cardSum[i]==21&&cardCNT[i]==2)			//blackjack, win
	  {
	  		dollar[0]+=bet[0];
	  		printf("Blackjack! Win.\t--->$%d\n",dollar[i]);
	  		break;
	  }
	  
	  else if(cardSum[i]>21)						//Overflow, Lose
	  {
	    	dollar[0]-=bet[0];
	    	printf("Overflow! Lose.(Sum:%d)\t--->$%d\n",cardSum[i],dollar[i]);
	    	break;
     }
		
	  else if(cardSum[i]<N_MAX_GO)
	  {
	  	printf("\tGo!");
	    cardhold[i][cardCNT[i]]=pullCard();
	    cardCNT[i]++;
	  }
	  
	  else if(cardSum[i]>N_MAX_GO)
	  {
	  	printf("\tStop!");
		calcStepResult(i,cardCNT[i]);
		break;
	  }
	  
	}
	
	//check result of all
	checkResult(cardCNT[i]);

	
	checkWinner();
	
	roundIndex++;

	if(cardIndex==N_CARDSET*N_CARD) //Ran out of Card Tray 
	{
	 	printf("\tNo more card! GAME END------ ");
		gameEnd==0;
	}
	
	
}while(gameEnd==0);

	return 0;
}
