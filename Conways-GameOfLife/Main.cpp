#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

// Global Consts
const int BOARD_SIZE = 50;

// Functions Declarations
void DrawBoard(bool board[BOARD_SIZE][BOARD_SIZE]);
int CountNeig(bool board[BOARD_SIZE][BOARD_SIZE], int cell_row, int cell_col);
void Turn(bool board[BOARD_SIZE][BOARD_SIZE]);
bool InitBoard(bool board[BOARD_SIZE][BOARD_SIZE], string dataFileName);

int main(int argc, char* argv[])
{
	// Consts
	const int TURN_TIME_MS = 1500;
	const string INIT_LIVE_CELLS_FILE_NAME = "../Conways-GameOfLife/cells.txt";

	// Arrays
	bool board[BOARD_SIZE][BOARD_SIZE]{};

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
	int current_row;
	int currernt_col;
	
	// Clear before drawing
	system("CLS");

	// For ALL the board (include walls)
	// Print the correct cell sign.
	for (current_row = -1; current_row < BOARD_SIZE + 1; current_row++)
	{		
		for (currernt_col = -1; currernt_col < BOARD_SIZE + 1; currernt_col++)
		{			
			if (current_row < 0 || currernt_col < 0 || current_row == BOARD_SIZE || currernt_col == BOARD_SIZE )
			{
				cout << BORDER;
			}
			else
			{
				cout << (board[current_row][currernt_col] ? LIVE : DEAD);
			}
		}

		cout << endl;
	}
}

void Turn(bool board[BOARD_SIZE][BOARD_SIZE])
{
	// Arrays
	bool demoBoard[BOARD_SIZE][BOARD_SIZE]{};

	// Variables
	int neigCount;	
	int current_row;
	int current_col;
		
	// Check all the cells
	for (current_row = 0; current_row < BOARD_SIZE; current_row++)
	{
		for (current_col = 0; current_col < BOARD_SIZE; current_col++)
		{			
			neigCount = CountNeig(board, current_row, current_col);
			
			// Check if alive 
			if (board[current_row][current_col] && (neigCount < 2 || neigCount > 3))
			{
				// Cell is dead
				demoBoard[current_row][current_col] = false;
			}
			else if ((!board[current_row][current_col]) && neigCount == 3)
			{
				// Cell is becoming live
				demoBoard[current_row][current_col] = true;
			}
			else
			{
				// No chage needed.
				demoBoard[current_row][current_col] = board[current_row][current_col];
			}
		}
	}

	// Update board
	for (current_row = 0; current_row < BOARD_SIZE; current_row++)
	{
		for (current_col = 0; current_col < BOARD_SIZE; current_col++)
		{
			board[current_row][current_col] = demoBoard[current_row][current_col];
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
	int current_row;
	int current_col;

	for (current_row = MIN_ROW; current_row <= MAX_ROW; current_row++)
	{		
		for (current_col = MIN_COL; current_col <= MAX_COL; current_col++)
		{
			if (board[current_row][current_col] && !(current_row == cell_row && current_col == cell_col))
			{				
				liveNeigbhorsCounter++;
			}
		}
	}

	return liveNeigbhorsCounter;
}