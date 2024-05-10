/* Minesweeper in C 1.0.0 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define board_rows 5
#define board_cols 5
#define total_mines 3


// Author Vinícius Henrique Sponchiado 

// Array to store the position of mines
int mines[board_rows][board_cols];
// Array to store selected positions
int selected_position[board_rows][board_cols];

int score = 0;
int gameover;



void initializeMines(int mines[board_rows][board_cols]) {
	int i,j;
	
    srand(time(NULL)); 
    
    // Setting all positions of the board as 0 initially
    for(i = 0; i < board_rows; i++){
        for(j = 0; j < board_cols; j++){
            mines[i][j] = 0;
        }
    }

	// Setting 1 in 5 random positions on the board (mines)
    for(i = 0; i < total_mines ; i++){
        int row = rand() % board_rows;
        int col = rand() % board_cols;
        mines[row][col] = 1; 
    }
}


void printBoard(){
    int i, j;
    
	printf("\n----- Minesweeper -----\n");
	printf("\nScore: %i \n\n", score);
	
    for(i = 0; i < board_rows; i++){
        for(j = 0; j < board_cols; j++){
        	if(selected_position[i][j] == 3){
        		// Position that has been selected
        		printf("#  ");
			}
			else{
				// Hidden positions
				printf("*  ");		
			}
        }
        printf("\n");
    }
    
    choosePosition();
}	
void choosePosition(){
	int row, col;
	
	printf("\nTake a guess!\n");
	printf("\nChoose a row 0-4: ");
	scanf("%i", &row); 
	
	printf("Choose a column 0-4: ");
	scanf("%i",&col); 

	// Validating the entered positions
	validatePosition(row,col);
	
}

void validatePosition(int row, int col){
	
	int i, j;
	
	int valid_position = 0;
	
	for(i = 0; i< board_rows; i++){
		for(j = 0; j < board_cols; j++){
			if(i == row && j == col){
				valid_position = 1;
			}		
		}
	}
	
	if(!valid_position){
		// If an invalid position is chosen, nothing happens, just reprint the board
        system("cls");
        printBoard();
		return;
	}
	
    if(mines[row][col] == 1){
    	// If a mine is chosen, gameover is activated
        gameover = 1;
        return;
    } 
	else if(selected_position[row][col] == 3){
		// If the same position is chosen, nothing happens, just reprint the board
        system("cls");
        printBoard();
		return;
	}
	else {
		// Setting the chosen position
        selected_position[row][col] = 3;
        // Increasing the score
        score ++;
        // Clearing the screen
        system("cls");
        // Updating the board
        printBoard();
    }
}

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "English");

	// Initializing the mines (5)
	initializeMines(mines);
	
	do{
		// Displaying the board
		printBoard();
		
	} while(gameover == 0); // Repetition condition to continue the game
	
	if(gameover == 1){
			// Clearing the terminal
			system("cls");
			printf("\n----- GAME OVER -----\n");
			printf("You reached a score of: %i ", score);
			return;
	}

	return 0;
}

