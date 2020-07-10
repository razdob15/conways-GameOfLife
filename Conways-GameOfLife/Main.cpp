#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <windows.graphics.h>
using namespace std;

// Global Consts
const int BOARD_SIZE = 50;

// Functions Declarations
void DrawBoard(bool board[BOARD_SIZE][BOARD_SIZE]);
int CountNeig(bool board[BOARD_SIZE][BOARD_SIZE], int cell_row, int cell_col);
void Turn(bool board[BOARD_SIZE][BOARD_SIZE]);
bool InitBoard(bool board[BOARD_SIZE][BOARD_SIZE], string dataFileName);
int CountLiveCells(bool board[BOARD_SIZE][BOARD_SIZE]);

int main(int argc, char* argv[])
 {
	const int TURN_TIME_MS = 50;
	const string INIT_LIVE_CELLS_FILE_NAME = "../../Conways-GameOfLife/boards/acron.txt";

	// Arrays
	bool board[BOARD_SIZE][BOARD_SIZE]{};

	// Variables
	int turnCount = 0;

	// Code section
	
	if (!InitBoard(board, INIT_LIVE_CELLS_FILE_NAME))
	{
		system("pause");
	}
	else
	{
		DrawBoard(board);

		// Always
		while (1)
		{
			Turn(board);
			Sleep(TURN_TIME_MS);
			DrawBoard(board);
			cout << endl << "Turn: " << turnCount << endl;
			cout << endl << "Live: " << CountLiveCells(board) << endl;
			turnCount++;
		}
	}
}


bool InitBoard(bool board[BOARD_SIZE][BOARD_SIZE], string liveCellsFileName)
{
	// Variables
	int row, col;
	ifstream liveCellsFile;
	bool isFileExists = false;
	
	// Code Section

	liveCellsFile.open(liveCellsFileName);
	
	// Check if file exist
	if (!liveCellsFile)
	{
		cout << "Unable to open file" << endl;
	}
	else
	{
		while (liveCellsFile >> row)
		{
			liveCellsFile >> col;
			board[row][col] = true;
		}

		isFileExists = true;
		liveCellsFile.close();
	}

	return isFileExists;
}

void DrawBoard(bool board[BOARD_SIZE][BOARD_SIZE])
{
	// Consts
	const char LIVE = '#';
	const char DEAD = '_';
	const char BORDER = '@';

	// Variables
	int currentRow;
	int currernt_col;
	string strToPrint = "";		

	// For ALL the board (include walls)
	// Print the correct cell sign.
	for (currentRow = -1; currentRow < BOARD_SIZE + 1; currentRow++)
	{		
		for (currernt_col = -1; currernt_col < BOARD_SIZE + 1; currernt_col++)
		{			
			if (currentRow < 0 || currernt_col < 0 || currentRow == BOARD_SIZE || currernt_col == BOARD_SIZE )
			{				
				strToPrint += BORDER;
			}
			else
			{				
				strToPrint += (board[currentRow][currernt_col] ? LIVE : DEAD);
			}
		}

		strToPrint += "\n";
	}

	// Clear before drawing
	system("CLS");

	// Draw the board
	cout << strToPrint;
}

void Turn(bool board[BOARD_SIZE][BOARD_SIZE])
{
	// Arrays
	bool demoBoard[BOARD_SIZE][BOARD_SIZE]{};

	// Variables
	int neigCount;	
	int currentRow;
	int currentCol;
		
	// Check all the cells
	for (currentRow = 0; currentRow < BOARD_SIZE; currentRow++)
	{
		for (currentCol = 0; currentCol < BOARD_SIZE; currentCol++)
		{			
			neigCount = CountNeig(board, currentRow, currentCol);
			
			// Check if alive 
			if (board[currentRow][currentCol] && (neigCount < 2 || neigCount > 3))
			{
				// Cell is dead
				demoBoard[currentRow][currentCol] = false;
			}
			else if ((!board[currentRow][currentCol]) && neigCount == 3)
			{
				// Cell is becoming live
				demoBoard[currentRow][currentCol] = true;
			}
			else
			{
				// No chage needed.
				demoBoard[currentRow][currentCol] = board[currentRow][currentCol];
			}
		}
	}

	// Update board
	for (currentRow = 0; currentRow < BOARD_SIZE; currentRow++)
	{
		for (currentCol = 0; currentCol < BOARD_SIZE; currentCol++)
		{
			board[currentRow][currentCol] = demoBoard[currentRow][currentCol];
		}
	}
}

int CountNeig(bool board[BOARD_SIZE][BOARD_SIZE], int cell_row, int cell_col)
{
	// Consts
	const int MIN_ROW = cell_row == 0 ? cell_row : cell_row - 1;
	const int MIN_COL = cell_col == 0 ? cell_col : cell_col - 1;
	const int MAX_ROW = cell_row + 1 == BOARD_SIZE ? cell_row : cell_row + 1;
	const int MAX_COL = cell_col + 1 == BOARD_SIZE ? cell_col : cell_col + 1;
	
	// Variables
	int liveNeigbhorsCounter = 0;
	int currentRow;
	int currentCol;

	for (currentRow = MIN_ROW; currentRow <= MAX_ROW; currentRow++)
	{		
		for (currentCol = MIN_COL; currentCol <= MAX_COL; currentCol++)
		{
			if (board[currentRow][currentCol] && !(currentRow == cell_row && currentCol == cell_col))
			{				
				liveNeigbhorsCounter++;
			}
		}
	}

	return liveNeigbhorsCounter;
}

int CountLiveCells(bool board[BOARD_SIZE][BOARD_SIZE])
{
	// Variables
	int liveCounter = 0;
	int currentRow;
	int currentCol;

	for (currentRow = 0; currentRow < BOARD_SIZE; currentRow++)
	{
		for (currentCol = 0; currentCol < BOARD_SIZE; currentCol++)
		{
			liveCounter += (int)board[currentRow][currentCol];
		}
	}
	return liveCounter;
	
}