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


//------ card processing functions ---------------

//This acts as scanf()
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	
	//actual number of cards
	switch(cardnum%13+1)
	{
		case 1:		//Ace can be 1 or 11
			return 1;
			break;
			
		case 10:		//Jack, Queen, King is 10
		case 11:
		case 12:
		case 13:
			return 10;
			break;
				
		default:		//Others are themselves
			return (cardnum%13+1);	 
	}
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	
	//print shape
	switch(cardnum/13)
	{
		case 0:
			printf("¢¼");
			break;
		case 1:
			printf("¡ß");
			break;
		case 2:
			printf("¢À");
			break;
		case 3:
			printf("¢¾");
			break;
	}
	
	//print number
	switch(cardnum%13+1)
	{
		case 1:
			printf("A");
			break;	
		case 11:
			printf("J");
			break;	
		case 12:
			printf("Q");
			break;	
		case 13:
			printf("K");
			break;
		default:
			printf("%d",cardnum%13+1);
			break;					 
	}
	
}
