#include "SudokuBoard.h"


void main() {
	SudokuSolver ss;

	ss.printBoard(board);
	std::cout << std::endl;

	if (ss.solveBoard(board))
		std::cout << "Solved Successfully!" << std::endl;
	else
		std::cout << "Unsolvable" << std::endl;

	ss.printBoard(board);
}