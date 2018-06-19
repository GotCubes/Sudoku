#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sudoku.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char **argv)
{
	// Verify input arguments.
	assert(argc == 1);
	
	// Flags and variables.
	int puzzle[9][9] = {0};
	int selection = 0;
	int exitFlag = FALSE;

	while(!exitFlag)
	{
		// Generate main menu.
		printf("\n");
		printf("+-------------------+\n");
		printf("| 1. Load Puzzle    |\n");
		printf("| 2. Create Puzzle  |\n");
		printf("| 3. Solve Puzzle   |\n");
		printf("| 4. Exit           |\n");
		printf("+-------------------+\n");

		// Query for selection.
		printf("Make Selection: ");
		scanf("%d", &selection);
		
		// Process user input.
		switch(selection)
		{
			// Load puzzle.
			case 1:
				handleLoadScreen(puzzle);
				break;

			// Create Puzzle
			case 2:
				handleCreateScreen(puzzle);
				break;

			// Solve Puzzle.
			case 3:
				handleSolveScreen(puzzle);
				break;

			// Exit.
			case 4:
				handleExitScreen(&exitFlag);
				break;

			// Invalid option.
			default:
				handleInvalidOption();
				break;
		}
	}

	return EXIT_SUCCESS;
}

void handleLoadScreen(int puzzle[][9])
{
	// Pre-process loading screen.
	system("clear");

	// Generate load menu.
	printf("\n");
	printf("+-------------------+\n");
	printf("|    Load Puzzle    |\n");
	printf("+-------------------+\n");
	printf("\n");

	char filename[100];

	// Query for puzzle input file.
	printf("Please input a file name, including path.\n");
	printf("Path: ");
	scanf("%s", filename);

	// Load input file.
	printf("\nLoading file %s.\n\n", filename);
	if(loadPuzzle(puzzle, filename))	// Puzzle successfully loaded.
	{
		printPuzzle(puzzle);
		printf("File successfully read.\n");
	}
	else // Puzzle did not load.
	{
		printf("Error: Puzzle failed to load.\n");
		printf("Please specify a valid path.\n");
	}
}

void handleCreateScreen(int puzzle[][9])
{
	// Flags and variables.
	int doneFlag = FALSE;
	int selection = 0;
	int row, col, val;

	while(!doneFlag)
	{
		// Pre-process loading screen.
		system("clear");
		printPuzzle(puzzle);

		// Generate load menu.
		printf("+-------------------+\n");
		printf("|   Create Puzzle   |\n");
		printf("|                   |\n");
		printf("| 1. Add Value      |\n");
		printf("| 2. Delete Value   |\n");
		printf("| 3. Done           |\n");
		printf("+-------------------+\n");
		printf("\n");

		// Query for selection.
		printf("Make your selection followed\n");
		printf("by the specified arguments\n");
		printf("delimited by spaces.\n");
		printf("Selection: ");
		scanf("%d", &selection);

		switch(selection)
		{
			case 1:
				printf("\nAdd Value:\n");
				
				// Query input row and column.
				do
				{
					printf("\nEnter a Coordinate (Row Column): ");
					scanf("%d %d", &row, &col);

					if(row < 1 || row > 9)
						printf("Row must be between 1 and 9.\n");
					if(col < 1 || col > 9)
						printf("Column must be between 1 and 9.\n");
				}while((row < 1 || row > 9) || (col < 1 || col > 9));

				// Query input value.
				do
				{
					printf("\nEnter a value (1 - 9): ");
					scanf("%d", &val);
					
					if(val < 1 || val > 9)
						printf("Value just be between 1 and 9.\n");
				}while(val < 1 || val > 9);

				puzzle[row - 1][col - 1] = val;
				break;

			case 2:
				// Query input row and column.
				do
				{
					printf("\nEnter a Coordinate (Row Column): ");
					scanf("%d %d", &row, &col);

					if(row < 1 || row > 9)
						printf("Row must be between 1 and 9.\n");
					if(col < 1 || col > 9)
						printf("Column must be between 1 and 9.\n");
				}while((row < 1 || row > 9) || (col < 1 || col > 9));

				puzzle[row - 1][col - 1] = 0;
				break;

			case 3:
				system("clear");
				doneFlag = TRUE;
				break;

			default:
				break;
		}
	}
}

void handleSolveScreen(int puzzle[][9])
{
	// Pre-process solve screen.
	system("clear");

	// Generate solve menu.
	printf("\n");
	printf("+-------------------+\n");
	printf("|   Solve  Puzzle   |\n");
	printf("+-------------------+\n");
	printf("\n");

	char selection;
	printf("Do you wish to have the\n");
	printf("algorithm's steps shown?\n");
	printf("Selection (Y / N): ");
	scanf(" %c", &selection);

	if(solvePuzzle(puzzle, selection)) // Puzzle has a solution.
	{
		printPuzzle(puzzle);
		printf("Puzzle successfully solved.\n");
	}
	else // Puzzle cannot be solved.
		printf("Puzzle does not have a legal solution.\n");
}

void handleExitScreen(int *exitFlag)
{
	// Generate exit menu.
	printf("\n");
	printf("+-------------------+\n");
	printf("|      Exiting      |\n");
	printf("+-------------------+\n");
	printf("\n");

	*exitFlag = TRUE;
}

void handleInvalidOption()
{
	// Generate invalid option menu.
	printf("\n");
	printf("+-------------------+\n");
	printf("|  Invalid  Option  |\n");
	printf("+-------------------+\n");
	printf("\n");
}

int loadPuzzle(int puzzle[][9], char *filename)
{
	// Open input file for reading.
	FILE *fptr = fopen(filename, "r");
	if(fptr == NULL)
		return FALSE;

	// Filter file stream into puzzle cells.
	int i,j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
			fscanf(fptr, "%d", &puzzle[i][j]);
	}
	
	// Close and return.
	fclose(fptr);
	return TRUE;
}

void printPuzzle(int puzzle[][9])
{
	// Pre-process puzzle printing.
	system("clear");
	
	// Print the puzzle if it can be solved.
	int row, col;
	for(row = 0; row < 9; row++)
	{
		for(col = 0; col < 9; col++)
		{
			if(puzzle[row][col] != 0)
				printf("%d ", puzzle[row][col]);
			else
				printf("  ");

			if(col == 2 || col == 5)
				printf("| ");
		}
		printf("\n");
		if(row == 2 || row == 5)
			printf("------+-------+------\n");
	}
	printf("\n");
	
}

int solvePuzzle(int puzzle[][9], char selection)
{
	// Base case, puzzle is full.
	int row, col;
	if(!emptyCells(puzzle, &row, &col))
		return TRUE;

	// Attempt each number.
	int num;
	for(num = 1; num <= 9; num++)
	{
		// Place the number in the cell if it is valid.
		if(validNumber(puzzle, row, col, num))
		{
			puzzle[row][col] = num;

			if(selection == 'Y' || selection == 'y')
				printPuzzle(puzzle);

			// Recursively branch to next available cell.
			if(solvePuzzle(puzzle, selection))
				return TRUE;
			else
				puzzle[row][col] = 0;
		}
	}

	// Return false if puzzle cannot be solved.
	return FALSE;
}

int emptyCells(int puzzle[][9], int *row, int *col)
{
	// Scan and return the first empty cell.
	for((*row) = 0; (*row) < 9; (*row)++)
	{
		for((*col) = 0; (*col) < 9; (*col)++)
		{
			if(puzzle[*row][*col] == 0)
				return TRUE;
		}
	}
	
	// Return false if no empty cell is found.
	return FALSE;
}

int validNumber(int puzzle[][9], int row, int col, int num)
{
	// Check the row and column of the cell for duplicates.
	int i,j;
	for(i = 0; i < 9; i++)
	{
		if(puzzle[row][i] == num || puzzle[i][col] == num)
			return FALSE;
	}

	// Check the box the cell is contained in.
	int rowS = row - (row % 3);
	int colS = col - (col % 3);
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if(puzzle[i + rowS][j + colS] == num)
				return FALSE;
		}
	}

	// Return true if it is a valid number.
	return TRUE;
}
