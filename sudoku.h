#ifndef __sudoku_h_
#define __sudoku_h_

void handleLoadScreen(int puzzle[][9]);
void handleCreateScreen(int puzzle[][9]);
void handleSolveScreen(int puzzle[][9]);
void handleExitScreen(int *exitFlag);
void handleInvalidOption();
void printPuzzle(int puzzle[][9]);

int loadPuzzle(int puzzle[][9], char *filename);
int solvePuzzle(int puzzle[][9], char selection);
int emptyCells(int puzzle[][9], int *row, int *col);
int validNumber(int puzzle[][9], int row, int col, int num);

#endif
