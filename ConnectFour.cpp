/******************************************
*
* Name: Jennifer Colletta
*
* Compiler:  Visual Studio
*
*******************************************/
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
#define ROWS 8
#define COLS 8

typedef struct {
	char name[20];
	int win;
	int lose;
	int draw;
} winloss;

/*****Function Prototypes*****/
int getstar(char board [][COLS]);
void printBoard(char board[][COLS]);
int takeTurn(char board[][COLS], int col);
void clearbuffer(char board[][COLS]);
int computerturnrand(char board[][COLS]);
int diagonalcheckup(char board[][COLS],char p1[]);
int diagonalcheckdown(char board[][COLS], char p1[]);
int verticalcheck(char board[][COLS],char p1[]);
int horizontalcheck(char board[][COLS],char p1[]);
int diagonalchecktup(char board[][COLS]);
int diagonalchecktdown(char board[][COLS]);
int horizontalcheckt(char board[][COLS]);
int verticalcheckt(char board[][COLS]);
void won(char p1[]);
void lose(char p1[]);
void draw(char p1 []);
void select_sort(winloss list[],int numbitems);
int search(winloss list[], char target[30], int numItems);
void swap(winloss* itemone, winloss* itemtwo);
int get_max_range(winloss list[], int first, int last);
void printScores(winloss list[], int numb); //struct
int readScores(winloss list[], FILE *infile); //struct
int checkdraw(char board[][COLS], char p1[]);
void removeNewLine(char aLine[]);
void searchplayer(char board[][COLS], char p1[]);
int diagonalcheckupspanish(char board[][COLS], char p1[]);
int diagonalcheckdownspanish(char board[][COLS], char p1[]);
int verticalcheckspanish(char board[][COLS], char p1[]);
int horizontalcheckspanish(char board[][COLS], char p1[]);
int getstarspanish(char board[][COLS]);
void wonspanish(char p1[]);
void losespanish(char p1[]);
void drawspanish(char p1[]);
int checkdrawspanish(char board[][COLS], char p1[]);
void searchplayerspanish(char board[][COLS], char p1[]);
void gamespanish(char board[][COLS]);
void game(char board[][COLS]);

int main()
{
	//Declarations
	char language;
	char board[ROWS][COLS];
	
	//Seed the random number generator
	srand(time(0));									//SRAND

	//Introduction
	printf("Welcome to connect four!\n");
	printf("Select a language:\nA. English\nB.Spanish");
	scanf(" %c", &language);
	switch (language) {
	case 'a': case 'A':
		game(board);
		break;
	case 'b': case 'B':
		gamespanish(board);
		break;
	}

}
/*****FUNCTION DEFINITIONS*****/

/*Gets the column number for the player to put a chip in. Parameter is 
the game board. Return value is 1.*/
int getstar(char board[][COLS])
{
	int col;
	do
	{
		printf("Enter column from 1 to 7: ");
		scanf("%d", &col);
	} while (col<0 || col >= ROWS);
	col = col - 1;
	takeTurn(board,col);
	printBoard(board);
	return 1;
}
/*Asks the player what column number the player wants to put 
 a chip in in spanish. Parameter is the game board. 
 Return value is 1.*/
int getstarspanish(char board[][COLS])
{
	int col;
	do
	{
		printf("Introducir la columna 1 - 7 :");
		scanf("%d", &col);
	} while (col<0 || col >= ROWS);
	col = col - 1;
	takeTurn(board, col);
	printBoard(board);
	return 1;
}
//Prints the game board to the screen. Parameter is the game board*/
void printBoard(char board[][COLS])			//myown
{
	int row;
	printf("  1   2   3   4   5   6   7\n");
		for (row = 0; row < ROWS; row++) 
		{	
			printf("| %c | %c | %c | %c | %c | %c | %c |\n", board[row][0],board[row][1],board[row][2],board[row][3], board[row][4], board[row][5], board[row][6]);
			printf("-----------------------------\n");
		}
}
/*Puts the players chip on the game board Parameter is the game board 
and the number of the column they chose to put their chip in. Return 
is one*/
int takeTurn(char board[][COLS], int col)			//myown
{
	int i=ROWS-1;
	while (board[i][col] != ' ')
	{ 
		i--;
	}
	board[i][col] = 'R';
	return 1;
}
/*Clears the gameboard. Parameter is the game board.*/
void clearbuffer(char board[][COLS])
{
	int row, col;
	for (row = 0; row<COLS; row++)
	{
		for (col = 0; col<ROWS; col++)
			board[row][col] = ' ';
	}
}
/*Computers turn to put a chip on the board. Selects a random
number from 1 to 7. Parameter is the gameboard. Return value is one*/
int computerturnrand(char board[][COLS])	//myown
{
	int col, i = ROWS - 1;
	col = rand() % 7;						//RAND
	while (board[i][col] != ' ')
	{
		i--;
	}
	board[i][col] = 'Y';
	printBoard(board);
	return 1;
}
/*Checks if the player or computer won by placing four chips 
diagonally downwards. Parameter is the gameboard and the players name.
Returns 0 if there are four chips diagnally downwards and returns 1 if there isn't*/
int diagonalcheckdown(char board[][COLS], char p1[])		//myown
{
		{
			for (int row = 0;row <= 4;row++)
			{
				for (int col = ROWS - 1;col >= 5;col--)
				{
					if (board[row][col] == 'R' && board[row + 1][col - 1] == 'R' && board[row + 2][col - 2] == 'R' && board[row + 3][col - 3] == 'R')
					{
						won(p1);
						return 0;
					}
					if (board[row][col] == 'Y' && board[row + 1][col - 1] == 'Y' && board[row + 2][col - 2] == 'Y' && board[row + 3][col - 3] == 'Y')
					{
						lose(p1);
						return 0;
					}
				}
			}
		}
		return 1;
}
/*Checks if the player or computer won by placing four chips
 diagonally downwards. Calls won function in spanish if there are
 four R chips and lose function in spanish if
 there are four Y chips. Parameter is the gameboard and the players name.
Returns 0 if there are four chips diagnally downwards and returns 1 if there isn't*/
int diagonalcheckdownspanish(char board[][COLS], char p1[])		//myown
{
	{
		for (int row = 0;row <= 4;row++)
		{
			for (int col = ROWS - 1;col >= 5;col--)
			{
				if (board[row][col] == 'R' && board[row + 1][col - 1] == 'R' && board[row + 2][col - 2] == 'R' && board[row + 3][col - 3] == 'R')
				{
					wonspanish(p1);
					return 0;
				}
				if (board[row][col] == 'Y' && board[row + 1][col - 1] == 'Y' && board[row + 2][col - 2] == 'Y' && board[row + 3][col - 3] == 'Y')
				{
					losespanish(p1);
					return 0;
				}
			}
		}
	}
	return 1;
}
/*Checks if the player or computer won by placing four chips
diagonally upwards. Parameter is the gameboard and the players name.
Returns 0 if there are four chips diagnally upwards and returns 1 if there isn't*/
int diagonalcheckup(char board[][COLS], char p1[])		//myown
{
	{
		for (int row = ROWS - 1;row >= 3;row--)
		{
			for (int col = 0;col <= 4;col++)
			{
				if (board[row][col] == 'R' && board[row - 1][col + 1] == 'R' && board[row - 2][col + 2] == 'R' && board[row - 3][col + 3] == 'R')
				{
					won(p1);
					return 0;
				}
				if (board[row][col] == 'Y' && board[row - 1][col + 1] == 'Y' && board[row - 2][col + 2] == 'Y' && board[row - 3][col + 3] == 'Y')
				{
					lose(p1);
					return 0;
				}
			}
		}
	}
	return 1;
}
/*Checks if the player or computer won by placing four chips
 diagonally upwards.Calls won function in spanish if there are
 four R chips and lose function in spanish if
 there are four Y chips. Parameter is the gameboard and the players name.
Returns 0 if there are four chips diagnally upwards and returns 1 if there isn't*/
int diagonalcheckupspanish(char board[][COLS], char p1[])		//myown
{
	{
		for (int row = ROWS - 1;row >= 3;row--)
		{
			for (int col = 0;col <= 4;col++)
			{
				if (board[row][col] == 'R' && board[row - 1][col + 1] == 'R' && board[row - 2][col + 2] == 'R' && board[row - 3][col + 3] == 'R')
				{
					wonspanish(p1);
					return 0;
				}
				if (board[row][col] == 'Y' && board[row - 1][col + 1] == 'Y' && board[row - 2][col + 2] == 'Y' && board[row - 3][col + 3] == 'Y')
				{
					losespanish(p1);
					return 0;
				}
			}
		}
	}
	return 1;
}
/*Checks if the player or computer won by placing four chips
 in a column. Parameter is the gameboard and the players name.
Returns 0 if there are four chips in a column and returns 1 if there isn't*/
int verticalcheck(char board[][COLS],char p1[])		//myown
{
	int row,col, red, yellow;
	red = 0, yellow = 0;
	for (col = 0;col <= COLS - 1;col++)
	{
		for (row = ROWS - 1;row > 0;row--)
		{
			if (board[row][col] == 'R')
			{
				red++;
				yellow = 0;
			}
			if (board[row][col] == 'Y')
			{
				yellow++;
				red = 0;
			}
			if (board[row][col] == ' ')
			{
				red = 0;
				yellow = 0;
			}
			if (red == 4 )
			{
				won(p1);
				return 0;
			}
			if (yellow == 4)
			{
				lose(p1);
				return 0;
			}
		}
	}
	return 1;
}
/*Checks if the player or computer won by placing four chips
 in a column.Calls won function in spanish if there are
 four R chips and lose function in spanish if
 there are four Y chips. Parameter is the gameboard and the players name.
Returns 0 if there are four chips in a column and returns 1 if there isn't*/
int verticalcheckspanish(char board[][COLS], char p1[])		//myown
{
	int row, col, red, yellow;
	red = 0, yellow = 0;
	for (col = 0;col <= COLS - 1;col++)
	{
		for (row = ROWS - 1;row > 0;row--)
		{
			if (board[row][col] == 'R')
			{
				red++;
				yellow = 0;
			}
			if (board[row][col] == 'Y')
			{
				yellow++;
				red = 0;
			}
			if (board[row][col] == ' ')
			{
				red = 0;
				yellow = 0;
			}
			if (red == 4)
			{
				wonspanish(p1);
				return 0;
			}
			if (yellow == 4)
			{
				losespanish(p1);
				return 0;
			}
		}
	}
	return 1;
}
/*Checks if the player or computer won by placing four chips
 in a row. Parameter is the gameboard and the players name.
Returns 0 if there are four chips in a row and returns 1 if there isn't*/
int horizontalcheck(char board[][COLS],char p1[])			//myown
{
	int row, col, red, yellow;
	red = 0, yellow = 0;
	for (row = ROWS - 1;row >0;row--)
	{
		for (col = 0;col <= ROWS-1;col++)
		{
			if (board[row][col] == 'R')
			{
				red++;
				yellow = 0;
			}
			if (board[row][col] == 'Y')
			{
				yellow++;
				red = 0;
			}
			if (board[row][col] == ' ')
			{
				red = 0;
				yellow = 0;
			}
			if (red == 4)
			{
				won(p1);
				return 0;
			}
			if (yellow == 4)
			{
				lose(p1);
				return 0;
			}
		}
	}
	return 1;
}
/*Checks if the player or computer won by placing four chips
in a row. Calls won function in spanish if there are
four R chips and lose function in spanish if 
there are four Y chips. Parameter is the gameboard and the players name.
Returns 0 if there are four chips in a row and returns 1 if there isn't*/
int horizontalcheckspanish(char board[][COLS], char p1[])			//myown
{
	int row, col, red, yellow;
	red = 0, yellow = 0;
	for (row = ROWS - 1;row >0;row--)
	{
		for (col = 0;col <= ROWS - 1;col++)
		{
			if (board[row][col] == 'R')
			{
				red++;
				yellow = 0;
			}
			if (board[row][col] == 'Y')
			{
				yellow++;
				red = 0;
			}
			if (board[row][col] == ' ')
			{
				red = 0;
				yellow = 0;
			}
			if (red == 4)
			{
				wonspanish(p1);
				return 0;
			}
			if (yellow == 4)
			{
				losespanish(p1);
				return 0;
			}
		}
	}
	return 1;
}
/*Checks if the player has three chips together diagonally downward 
so the computer can block. Parameter is the gameboard. Returns 0 if there are
three of the players chips diagonally downwards and returns 1 if there aren't*/
int diagonalchecktdown(char board[][COLS])		//myown
{
	{
		for (int row = 0;row <= 4;row++)
		{
			for (int col=ROWS-1;col >= 5;col--)
			{
				if (board[row][col] == 'R' && board[row + 1][col - 1] == 'R' && board[row + 2][col - 2] == 'R' && board[row + 3][col - 3] == ' ')
				{
					board[row + 3][col - 3] = 'Y';
					return 1;
				}
			}
		}
	}
	return 0;
}
/*Checks if the player has three chips together diagonally upwards
so the computer can block. Parameter is the gameboard. Returns 0 if there are
three of the players chips diagonally upwards and returns 1 if there aren't*/
int diagonalchecktup(char board[][COLS])			//myown
{
	for (int row = ROWS - 1;row >= 3;row--)
	{
		for (int col = 0;col <= 4;col++)
		{
			if (board[row][col] == 'R' && board[row - 1][col + 1] == 'R' && board[row - 2][col + 2] == 'R' && board[row - 3][col + 3] == ' '&& board[row - 2][col + 2] != ' ')
			{
				board[row - 3][col + 3] = 'Y';
				return 1;
			}
		}
	}
	return 0;
}
/*Checks if the player has three chips together in a row so the computer can block. 
Parameter is the gameboard. Returns 0 if there are
three of the players chips in a row and returns 1 if there aren't*/
int horizontalcheckt(char board[][COLS])		//myown
{
	int red = 0; int yellow = 0;
	for (int row = ROWS - 1;row >0;row--)
	{
		for (int col = 0;col <= ROWS - 1;col++)
		{
			if (board[row][col] == 'R')
			{
				red++;
				yellow = 0;
			}
			if (board[row][col] == 'Y')
			{
				yellow++;
				red = 0;
			}
			if (board[row][col] == ' ')
			{
				red = 0;
				yellow = 0;
			}
			if (yellow == 3 && board[row][col-1] == ' ')
			{
				board[row - 1][col] = 'Y';
				return 1;
			}
			if (yellow == 3 && board[row][col+1] == ' ')
			{
				board[row][col+1] = 'Y';
				return 1;
			}
		}
	}
	return 0;
}
/*Checks if the player has three chips together in a column
so the computer can block. Parameter is the gameboard. Returns 0 if there are
three of the players chips in a column and returns 1 if there aren't*/
int verticalcheckt(char board[][COLS])			//myown
{
	int red = 0; int yellow = 0;
	for (int col = 0;col <= COLS - 1;col++)
	{
		for (int row = ROWS - 1;row > 0;row--)
		{
			if (board[row][col] == 'R')
			{
				red++;
				yellow = 0;
			}
			if (board[row][col] == 'Y')
			{
				yellow++;
				red = 0;
			}
			if (board[row][col] == ' ')
			{
				red = 0;
				yellow = 0;
			}
			if (red == 3 && board[row-1][col] == ' ')
			{
				board[row-1][col] = 'Y';
				return 1;
			}
			if (yellow == 3 && board[row-1][col] == ' ')
			{
				board[row-1][col] = 'Y';
				return 1;
			}
		}
	}
	return 0;
}
/*Displays message if player wins and displays the updated scores from file.
Parameter is players name.*/
void won(char p1[])										//myown
{
	char answer;
	winloss scores[100];
	int numbitems,a;
	FILE* myin;
	printf("Congratulations, %s you won!\n", p1);
	printf("Would you like to see a list of win/loss records? (y or n)");
	scanf(" %c", &answer);
	myin = fopen("winloss.txt", "r");
	numbitems = readScores(scores, myin);				//struct
	select_sort(scores, numbitems);						//sort
	a = search(scores, p1, numbitems);				//search
	if (a == -1)
		fprintf(myin, "%s     1     0     0", p1);
	if (answer == 'y')
	{
		printScores(scores, numbitems);					//struct
	}
	else
		printf("Thank you for playing Connect Four! Your score has been updated.\n");
		
	fclose(myin);
}
/*Displays message if player loses and displays the updated scores from file.
Parameter is players name.*/
void lose(char p1[])									//myown
{
	char answer; int numbitems, a;
	winloss scores[100];
	FILE* myin; 
	printf("Sorry, %s you lost.\n", p1);
	printf("Would you like to see a list of win/loss records? (y or n)");
	scanf(" %c", &answer);
	myin = fopen("winloss.txt", "r");
	numbitems = readScores(scores, myin);				//struct
	select_sort(scores, numbitems);					//sort
	a = search(scores, p1, numbitems);
	if (a == -1)
		fprintf(myin, "%s     0     1     0", p1);
	if (answer == 'y')
		printScores(scores, numbitems);					//struct
	else
		printf("Thank you for playing Connect Four!\n");

	fclose(myin);
}
/*Displays message if player wins and displays the updated scores from file.
Parameter is a players name*/
void draw(char p1[])												//myown
{
	winloss scores[100];
	char answer; int numbitems,a;
	FILE* myin; 
	printf("It's a tie!.\n");
	printf("Would you like to see a list of win/loss records? (y or n)");
	scanf(" %c", &answer);
	myin = fopen("winloss.txt", "r");
	numbitems = readScores(scores, myin);				//struct
	select_sort(scores, numbitems);						//sort
	a = search(scores, p1, numbitems);
	if (a == -1)
		fprintf(myin, "%s     1     0     0", p1);
	if (answer == 'y')
		printScores(scores,numbitems);					//struct
	else 
		printf("Thank you for playing Connect Four!\n");

	fclose(myin);
}
/*Displays message if player wins and displays the updated scores from file in spanish.
Parameter is players name.*/
void wonspanish(char p1[])										//myown
{
	char answer; 
	winloss scores[100];
	int numbitems,a;
	FILE* myin;
	printf("Felicitaciones, %s ganaste!\n", p1);
	printf("Le gustaria ver una lista de los registros de victorias / derrotas ? (y o n)");
	scanf(" %c", &answer);
	myin = fopen("winloss.txt", "r");
	numbitems = readScores(scores, myin);				//struct
	select_sort(scores, numbitems);						//sort

	if (answer == 'y')
	{
		printScores(scores, numbitems);					//struct
	}
	else
		printf("Gracias por jugar Conecta Cuatro !Su puntuaciun se ha actualizado .\n");

	a = search(scores, p1, numbitems);			//search
	if (a == -1)
		fprintf(myin, "%s     1     0     0", p1);
	//else

	fclose(myin);
}
/*Displays message if player loses and displays the updated scores from file in spanish.
Parameter is players name.*/
void losespanish(char p1[])									//myown
{
	char answer; int numbitems;
	winloss scores[100];
	FILE* myin; FILE* myout;
	printf("Lo sentimos , %s perdiste.\n", p1);
	printf("Le gustar�a ver una lista de los registros de victorias / derrotas ? (y o n)");
	scanf(" %c", &answer);
	myin = fopen("winloss.txt", "r");
	numbitems = readScores(scores, myin);				//struct
	select_sort(scores, numbitems);						//sort
	if (answer == 'y')
	{

		printScores(scores, numbitems);					//struct
	}
	else
		printf("Gracias por jugar Conecta Cuatro ! Su puntuaci�n se ha actualizado!\n");
	//myout = fopen("winloss.txt", "w");
	//a = search(scores, p1, numbitems);
	//if (a == -1)
	//	fprintf("%s     0     1     0", p1);
	fclose(myin);
	//fclose(myout);
}
/*Displays message if player wins and displays the updated scores from file in spanish.
Parameter is a players name*/
void drawspanish(char p1[])												//myown
{
	winloss scores[100];
	char answer; int numbitems, a;
	FILE* myin; FILE* myout;
	printf("Es un empate!\n");
	printf("Le gustar�a ver una lista de los registros de victorias / derrotas ? (y o n)");
	scanf(" %c", &answer);
	myin = fopen("winloss.txt", "r");
	numbitems = readScores(scores, myin);				//struct
	select_sort(scores, numbitems);						//sort


	if (answer == 'y')
	{
		printScores(scores, numbitems);					//struct
	}
	else
		printf("Gracias por jugar Conecta Cuatro ! Su puntuaciun se ha actualizado.\n");

	//myout = fopen("winloss.txt", "w");
	//a = search(scores, p1, numbitems);
	if (a == -1)
	//	fprintf("%s     1     0     0", p1);
	fclose(myin);
	//fclose(myout);b
    
}
/*Reads in scores from the file winloss.txt. Parameter
is an array to store the players name, number of wins,loses,draws and the file.
Returns the number of items in file*/
int readScores(winloss list[], FILE *infile)		//struct param  *param   myown
{
	int i = 0;	
	char junk;
	while (fgets(list[i].name, 40, infile)!= NULL)
	{
		removeNewLine(list[i].name);
		fscanf(infile, " %d %d %d%c", &list[i].win, &list[i].lose, &list[i].draw, &junk);	//I/O
		i++;									
	}
	return i;
}
/*Prints the scores from the file winloss.txt. Parameter
is an array that stored the players name, number of wins,loses,
draws and the number of items in file*/
void printScores(winloss list[], int numb)				//struct param *param  myown
{
	int i;
	for (i = 0;i < numb;i++)
		printf("%s    %d    %d     %d\n", list[i].name, list[i].win, list[i].lose, list[i].draw);		// I/O
}
/*Searches an array. Parameters are the array you wish to search,
what your looking to find in the array, and the number of 
items in the array. Returns 1 if target is found, returns
-1 if the target was not found*/
int search(winloss list[], char target[30], int numItems)			//struct param  *param
{
	int i;
	for (i = 0;i < numItems;i++)
	{
		if (strcmp(target, list[i].name)==0)
			return 1;
	}
	return -1;
}
/*********< get_max_range >************/
/*find and return the index of the greatest
value in the array list,
within the given range, index first to index last.*/
int get_max_range(
	winloss list[],  /* the array we are
				  looking in */
	int first,    /* the index of the
				  first element we will
				  look at */
	int last     /* the index of the
				 last element we will
				 look at */
	)
{
	int i;
	int index_of_max;
	index_of_max = first;
	/*for each value of i from first+1 to last*/
	for (i = first + 1; i <= last; i++)
		/*if list[i] is greater than list[index_of_max]*/
		if (list[i].win<list[index_of_max].win)
			/*update index_of_max to i*/
			index_of_max = i;

	return index_of_max;
}

/*********< select_sort >************/
/* sort the array list into increasing order.
n is the number of items in the array. */
void select_sort(
	winloss list[],/* list to be sorted */
	int n)      /* number of elements */

{
	int to_fill; /* subscript of last
				 element of unsorted array*/
	int index_of_max; /*index of greatest
					  element in unsorted array */

					  /*for to_fill = n-1 (whole array unsorted) down to to_fill = 1
					  (remaining 2 elements need to be put in order) */
	for (to_fill = n - 1; to_fill >= 1; to_fill--)
	{
		/*Find position of greatest element in unsorted array.*/
		index_of_max = get_max_range(list, 0, to_fill);
		/*Swap it with the element at end of unsorted array.*/
		swap(&list[index_of_max], &list[to_fill]);
	}  /* end for to_fill */
}
/*********< swap >************/
/* swap the values pointed to by the parameters *itemone and *itemtwo*/
void swap(winloss* itemone, winloss* itemtwo)
{
	winloss z;
	z = *itemone;
	*itemone = *itemtwo;
	*itemtwo = z;
}
/*Checks if all the spaces on the board are full
If they are calls the draw function. Parameter is 
the game board and the players name*/
int checkdraw(char board[][COLS],char p1[])
{
	for (int row = ROWS - 1;row > 0;row--)
	{
		for (int col = 0;col <= ROWS - 1;col++)
		{
			if (board[row][col] == ' ')
				return 0;
		}
	}
	draw(p1);
	return 1;
}
/*Checks if all the spaces on the board are full
If they are calls the draw function in spanish. Parameter is
the game board and the players name*/
int checkdrawspanish(char board[][COLS], char p1[])
{
	for (int row = ROWS - 1;row > 0;row--)
	{
		for (int col = 0;col <= ROWS - 1;col++)
		{
			if (board[row][col] == ' ')
				return 0;
		}
	}
	drawspanish(p1);
	return 1;
}
/*Removes the newline character when reading in 
a file. Parameter aLine[] is the string you would
like to remove the newline from*/
void removeNewLine(char aLine[])
{
	int i;
	i = 0;
	while (aLine[i] != '\n')
	{
		i++;
	}
	aLine[i] = '\0'; /* get rid of the newline */
}
/*Searches for the player in the input file. Parameters
 are the gameboard and the players name*/
void searchplayer(char board[][COLS],char p1[])
{
	FILE* myin;
	int numbitems,j;
	winloss scores[100];
	myin = fopen("winloss.txt", "r");
	numbitems = readScores(scores, myin);			//struct
	j = search(scores, p1, numbitems);				//search
if (j == -1)
{
	printf("%s, I see this is your first time playing\n", p1);
	printf("%s,You will be R and the computer will be Y.\n", p1);
	printf("The player to get four chips in a row wins.\n Lets begin!\n");
}
else
printf("%s, I see you already know how to play. Lets begin!\n", p1);
fclose(myin);
clearbuffer(board);printBoard(board);
}
/*Searches for the player in the input file in spanish. Parameters
 are the gameboard and the players name*/
void searchplayerspanish(char board[][COLS], char p1[])
{
	FILE* myin;
	int numbitems, j;
	winloss scores[100];
	myin = fopen("winloss.txt", "r");
	numbitems = readScores(scores, myin);			//struct
	j = search(scores, p1, numbitems);				//search
	if (j == -1)
	{
		printf("%s, Veo esta es la primera vez que juegas\n", p1);
		printf("%s,Usted ser. R y el equipo va a ser Y.\n", p1);
		printf("El jugador que consigue cuatro fichas en una fila gana.\n Comencemos!\n");
	}
	else
		printf("%s, Veo que ya sabe cumo jugar. Vamos a empezar!\n", p1);
	fclose(myin);
	clearbuffer(board);printBoard(board);
}
void game(char board[][COLS])
{
	char p1[30], level;
	int a, b, c, d, e, f, g,h;
	printf("Player 1 please enter your name:");
	scanf("%s", p1);
	searchplayer(board, p1);
	printf("%s, please select a level:\n", p1);
	printf("A. Hard\nB. Easy\n");
	scanf(" %c", &level);
	a = 1;b = 1;c = 1, g = 1;
	switch (level)
	{
	case 'A':case 'a':
		while (a == 1 && b == 1 && c == 1 && g == 1)
		{
			getstar(board);
			f = diagonalchecktup(board);
			h = diagonalchecktdown(board);
			e = verticalcheckt(board);
			d = horizontalcheckt(board);
			//if (e != 0 && f != 0 && d != 0 && h != 0)
				printBoard(board);
			if (e == 1 && f == 1 && d == 1 && h == 1)
				computerturnrand(board);
			a = diagonalcheckup(board, p1);
			g = diagonalcheckdown(board, p1);
			b = verticalcheck(board, p1);
			c = horizontalcheck(board, p1);
			checkdraw(board, p1);
		}
		break;
	case 'B':case 'b':
		while (a == 1 && b == 1 && c == 1 && g == 1)
		{
			getstar(board);computerturnrand(board);
			a = diagonalcheckup(board, p1);
			g = diagonalcheckdown(board, p1);
			b = verticalcheck(board, p1);
			c = horizontalcheck(board, p1);
			checkdraw(board, p1);
		}
		break;
	default:printf("Invalid choice. Try again later.\n");
	}
}
void gamespanish(char board[][COLS])
{
	char level;
	char p1[30];
	int a, b, c, d, e, f, g,h;
	printf("El jugador uno por favor, introduzca su nombre:");
	scanf("%s", p1);
	searchplayerspanish(board, p1);
	printf("%s, por favor, seleccione un nivel :\n", p1);
	printf("A.dificil \nB.facil\n");
	scanf(" %c", &level);
	a = 1;b = 1;c = 1, g = 1;
	switch (level)
	{
	case 'A':case 'a':
		while (a == 1 && b == 1 && c == 1 && g == 1)
		{
			getstarspanish(board);
			f = diagonalchecktup(board);
			h = diagonalchecktdown(board);
			e = verticalcheckt(board);
			d = horizontalcheckt(board);
			//if (e == 0 && f == 0 && d == 0 && h == 0)
				printBoard(board);
			if (e == 1 && f == 1 && d == 1 && h == 1)
				computerturnrand(board);
			a = diagonalcheckupspanish(board, p1);
			g = diagonalcheckdownspanish(board, p1);
			b = verticalcheckspanish(board, p1);
			c = horizontalcheckspanish(board, p1);
			checkdrawspanish(board, p1);
		}
		break;
	case 'B':case 'b':
		while (a == 1 && b == 1 && c == 1 && g == 1)
		{
			getstarspanish(board);computerturnrand(board);
			a = diagonalcheckupspanish(board, p1);
			g = diagonalcheckdownspanish(board, p1);
			b = verticalcheckspanish(board, p1);
			c = horizontalcheckspanish(board, p1);
			checkdrawspanish(board, p1);
		}
		break;
	default:printf("Invalid choice. Try again later.\n");
	}
}

