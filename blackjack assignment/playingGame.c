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

//------playing game functions -----------------------------

extern n_user;
extern dollar[N_MAX_USER];	
extern cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];
extern bet[N_MAX_USER];
extern cardSum[N_MAX_USER];
extern roundIndex;
extern cardCNT[N_MAX_USER];

//player settiing
int configUser(void) {
	
	do{
	printf("input a number of player(MAX:%d): ",N_MAX_USER);
	n_user=getIntegerInput();
	
	if(n_user>N_MAX_USER||n_user<=0)
	 printf("The number of players must be from 1 to %d\n",N_MAX_USER);
	}while(n_user>N_MAX_USER||n_user<=0);
	 
	printf("---> cards are mixed& putted into tray\n\n");	
}

//betting
int betDollar(void){
	
	int i; 
	int betting;
	
	srand((unsigned)time(NULL));
				
	printf("---------- BETTING STEP ----------\n");
	
	do{

	 printf("--->your betting(total:$%d): ",dollar[0]);
	 betting=getIntegerInput();	
	 
	 if(betting<=0 || betting>dollar[0])
	 {
	 	printf("Invalid Input.\n");
		printf("You have $%d.Bet again.\n",dollar[0]);
	 }
 	
	}while(betting<=0 || betting>dollar[0]); //if we get valid input, escape this loop
	

	
	if (0<betting&&betting<=dollar[0])
	{
		bet[0]=betting;				//user's betting
		
		for(i=1;i<n_user;i++)		//other players betting(random)
		{
	     bet[i]=(rand()%N_MAX_BET)+1;
	     
	     if(bet[i]<dollar[i])
		  printf("--->player%d:$%d\n",i,bet[i]);
		 
		 else if(bet[i]>dollar[i]) //when the betting is bigger than the rest 
		 {
		 	bet[i]=rand()%dollar[i]+1;
		    printf("--->player%d:$%d\n",i,bet[i]);
		 }
		 
		}	
	}
}

//offering initial 2 cards
void offerCards(void) {
	
	int i;
	
	printf("\n\n---------- CARD OFFERING ----------\n");
	
	cardhold[n_user][0]=pullCard();//give first card to dealer
	cardhold[n_user][1]=pullCard();//give second card to dealer
	
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0]=pullCard();	//give first card to each players
		cardhold[i][1]=pullCard();	//give second card to each players
	}
	
}

//print initial card status
void printCardInitialStatus(void) {

	int i;
	
	//dealer's status
	printf("--- dealer      : X ");
	printCard(cardhold[n_user][1]);
	printf("\n");
	
	//user's status
	printf("  -> you        : ");
	printCard(cardhold[0][0]);
	printf("   ");
	printCard(cardhold[0][1]);
	printf("\n");
	
	//other palyers' status
	for(i=1;i<n_user;i++)
	{	
		printf("  -> player %d   : ",i);
		printCard(cardhold[i][0]);
		printf("   ");
		printCard(cardhold[i][1]); 
		printf("\n");		 
	}

}

//getAction, Hit or Stay
int getAction(void) {
	
	int act; //Hit or Stay
	
	printf("Action? Hit(0) or Stay(others): ");
	act=getIntegerInput();
	
	if(act==0)
	 return 0;
	else 
	 return 1; 

}

//literally...
void printUserCardStatus(int user, int cardcnt) {
	
	int i;	

	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ▒▒▒ ");
	
	
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user,int cardcnt) {
	
	int i;
	int sum;
	

	for(i=0;i<cardcnt;i++)
	{
		sum+=getCardNum(cardhold[user][i]);
		cardSum[i]=sum;
	}
	
	return sum; 
}

int checkResult(int cardcnt) {
	
	int i;
	
	printf("\n\n----------ROUND %d RESULT\n",roundIndex);
	
	for(i=0;i<n_user;i++)
	{
		
	 if(i==0)
	 {
    	printf("--->your result:");
    	
	    if(cardSum[i]==21&&cardCNT[i]==2)			//blackjack, win
	    {
	  		dollar[i]+=bet[i];
	  		printf("Blackjack! Win.\t--->$%d\n",dollar[i]);
	    }
	
	
		else if (cardSum[i]>21)					//overflow, lose
	 	{
	  		dollar[i]-=bet[i];
	  		printf("Overflow! Lose.\t--->$%d\n",dollar[i]);
	 	}

	 	else if((cardCNT[n_user]==2&&cardSum[n_user]==21)&&cardSum[i]<21)	//Dealer blackjack, lose
		{
			dollar[i]-=bet[i];
			printf("Dealer Blackjack! Lose.  --> $%d\n",dollar[i]);
		}
	
	 	else if(cardSum[i]<21&&cardSum[n_user]>21)		//Dealer overflow, win
		{
			dollar[i]+=bet[i];
			printf("Dealer Overflow!Win.  --> $%d\n",dollar[i]);
		}
		
	 	else if(cardSum[i]<21&&cardSum[i]>cardSum[n_user]) 	
		{
			dollar[i]+=bet[i];
			printf("Win!(sum:%d)\t-->$%d\n",cardSum[i],dollar[i]); 
		}
     
     	else if(cardSum[i]<21&&cardSum[i]<cardSum[n_user])
     	{
     		dollar[i]-=bet[i];
     		printf("Lose!(sum:%d)\t-->$%d\n",cardSum[i],dollar[i]);
	 	}
	 }
	 
	 else
	 {
	  printf("--->player%d's result:",i);
    	
	  if(cardSum[i]==21)			//blackjack, win
	  {
			dollar[i]+=bet[i];
	 		printf("Blackjack! Win.\t--->$%d\n",dollar[i]);
	  }
	
	
	  else if (cardSum[i]>21)					//overflow, lose
	  {
	  		dollar[i]-=bet[i];
	  		printf("Overflow! Lose.\t--->$%d\n",dollar[i]);
	  }

	  else if(cardSum[n_user]==21&&cardSum[i]<21)	//Dealer blackjack, lose
	  {
			dollar[i]-=bet[i];
			printf("Dealer Blackjack! Lose.  --> $%d\n",dollar[i]);
	  }
	
	 else if(cardSum[i]<21&&cardSum[n_user]>21)		//Dealer overflow, win
	  {
			dollar[i]+=bet[i];
			printf("Dealer Overflow!Win.  --> $%d\n",dollar[i]);
	  }
		
	 else if(cardSum[i]<21&&cardSum[i]>cardSum[n_user]) 	
	  {
			dollar[i]+=bet[i];
			printf("Win!(sum:%d)\t-->$%d\n",cardSum[i],dollar[i]); 
	  }
     
     else if(cardSum[i]<21&&cardSum[i]<cardSum[n_user])
      {
     		dollar[i]-=bet[i];
     		printf("Lose!(sum:%d)\t-->$%d\n",cardSum[i],dollar[i]);
	  }
	 }
	}	
}

int checkWinner() {

    int winner;         
    int i;
    int max;     
    
  	max=cardSum[0];	//user의 값을 최대라고 가정 
    
    for(i=1;i<n_user;i++)	//call other players and compare들을 차례로 불러와 대소비교
							//if it's bigger than the former,max 변수에 새롭게 저장  
    {
    	if(max<cardSum[i])
    	{
    		max=cardSum[i];
    		winner=i;
		}
	}
	
	printf("\n----------------------------------------\n");
	printf("\n----------------------------------------\n");
	printf("\n----------------------------------------\n");
	printf("GAME OVER!\n");
	
	if(winner==0) 
	 printf("Winner is you!");
	else if(winner>=1&&winner<=N_MAX_USER)
	 printf("Winner is player%d",winner);
	
	
}


