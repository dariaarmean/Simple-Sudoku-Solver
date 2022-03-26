#pragma once
#include <iostream>

const int DIMENSION = 9;

int board[DIMENSION][DIMENSION] = {
	{0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 3, 0, 0, 0, 0, 0, 0, 0},
	{4, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 2, 0, 0, 0, 0, 0, 5, 0},
	{0, 0, 0, 7, 0, 0, 0, 0, 0},
	{1, 0, 0, 5, 0, 0, 0, 2, 7},
	{0, 0, 0, 0, 1, 0, 0, 0, 4},
	{0, 4, 0, 0, 0, 0, 0, 8, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};


class SudokuSolver {
public:
	/*
	/===============================================================\
	|	This method will check if a specific number					|
	|	is already in a specified row.								|
	|	If the number is in that row, it will return true.			|
	\===============================================================/
	*/
	static bool isNumberInRow(int board[DIMENSION][DIMENSION], int number, int row) {
		for (int col = 0; col < DIMENSION; col++)
			if (board[row][col] == number)
				return true;

		return false;
	}

	/*
	/===============================================================\
	|	This method will check if a specific number					|
	|	is already in a specified column.							|
	|	If the number is in already in that column, the method will |
	|	return true.												|
	\===============================================================/
	*/

	static bool isNumberInColumn(int board[DIMENSION][DIMENSION], int number, int col) {
		for (int row = 0; row < DIMENSION; row++)
			if (board[row][col] == number)
				return true;

		return false;
	}

	/*
	/===============================================================\
	|	A box is a 3x3 mini-board. All numbers from 1 to 9 must be  |
	|	inside the box.												|
	|	A board is made out of 9 boxes.								|
	|	This method will check if a specific number					|
	|	is already in a box. The box will be determined				|	
	|	by specifying the row and column.							|
	|	For row = 5, col = 3, box 5 is selected.					|
	\===============================================================/
	*/

	static bool isNumberInBox(int board[DIMENSION][DIMENSION], int number, int row, int col) {
		// assume you are on row 5 column 2
		// the box has its first cell on row 3 column 0
		// in order to obtain these coordinates, we have to mod
		// the received row and column by 3 ( 5 % 3 = 2; % 3 = 2)
		// and use this in a subtraction to get the actual desired values
		const int boxRow = row - row % 3;
		const int boxColumn = col - col % 3;

		for (int i = boxRow; i < boxRow + 3; i++)
			for (int j = boxColumn ; j < boxColumn + 3; j++)
				if (board[i][j] == number)
					return true;

		return false;
	}

	/*
	/===============================================================\
	|	This method calls the 3 functions implemented above			|
	|	in order to check if the number to be placed can be			|
	|	stored.														|
	\===============================================================/
	*/

	static bool isValidPlacement(int board[DIMENSION][DIMENSION], int number, int row, int col) {
		return !isNumberInRow(board, number, row) &&
			!isNumberInColumn(board, number, col) &&
			!isNumberInBox(board, number, row, col);
	}

	/*
	/===============================================================\
	|	This is the backtracking that occurs for each cell in order	|
	|	to solve the board.											|
	|	Say you want to find a number for cell found on row 0, col 1|
	|	The algorithm searches for the first number from 1 to 9		|
	|	which is not already placed on row 0. Once it finds that, it|
	|	will check if other previous criteria are all satisfied		|
	|	(same number can't be found inside the same col and box)	|
	|	It fills the cell and moves to a new one. Row 0, col 3		|
	|	The process starts all over again and does the same thing	|
	|	until it fills an entire board.								|
	|	If, at any point, the algorithm fails to store a new value	|
	|	inside a cell, it will go back to a previously stored number|
	|	and restart the process, excluding the number already stored|
	\===============================================================/
	*/
	static bool solveBoard(int board[DIMENSION][DIMENSION]) {
		for (int row = 0; row < DIMENSION; row++)
			for (int col = 0; col < DIMENSION; col++)
				// if the cell at position row, column is empty (or filled with 0)
				if (board[row][col] == 0) {
					// search for a number (which is not already on that row)
					// to store in the cell
					for (int numberToTry = 1; numberToTry <= DIMENSION; numberToTry++)
						if (isValidPlacement(board, numberToTry, row, col)) {
							board[row][col] = numberToTry;

							// if such a value was found and placed, return true
							// else refill the cell with a 0
							if (solveBoard(board))
								return true;
							else
								board[row][col] = 0;
						}

					// however, if there was no number which could fill in the gap
					// the board could not be solved by the algorithm
					return false;
				}

		return true;
	}

	static void printBoard(int board[DIMENSION][DIMENSION]) {
		for (int row = 0; row < DIMENSION; row++) {
			if (row % 3 == 0 && row != 0)
				std::cout << "-------------------" << std::endl;
			for (int col = 0; col < DIMENSION; col++) {
				if (col % 3 == 0 && col != 0)
					std::cout << "|";
				std::cout << board[row][col] << " ";
			}

			std::cout << std::endl;
		}
	}
};