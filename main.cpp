//
//  main.cpp
//  Cmd Line Chess AI
//
//  Created by Robert Lewis on 30/11/21.
//  Copyright © 2021 Robert Lewis. All rights reserved.
//

#include "Computer Move.h"

int playGame(int firstColour) {
		int win = 0;
		int colourToMove = firstColour;
		std::vector<int> moveList;

		while (win == 0) {

	//		for (int i = 0; i < 63; i ++){
	//			if (tolower(board[i].name) == 'k'){
	//				if (board[i].colour == 1) kingLocation[2] = i;
	//				else kingLocation[0] = i;
	//			}
	//		}
			std::cout << std::endl << std::endl;

			if (colourToMove == 1) std::cout << "Whites Move" << std::endl;
			else std::cout<< "Blacks Move" << std::endl;
			printBoard(board, true);

			printVector(kingMove(0, 1, board));


			moveList = generateAllMoves(board, colourToMove);

			//Check Win
			if (moveList.size() == 0) {
				if (inCheck(findKing(board, colourToMove), board, colourToMove)) win = -1 * colourToMove;
				else win = 2;
				break;
			}
			int pieceNumber = 0;
			for (int i = 0; i < 64; i ++) {
				if (board[i].colour != 0) {
					pieceNumber ++;
				}
			}
			if (pieceNumber == 2) {
				win = 2;
				break;
			}

			//Choose Move
			int move;

			if ((colourToMove == 1 and computerPlaysWhite) or (colourToMove == -1 and computerPlaysBlack)) {
				move = computerMove(board, colourToMove, maxSearchDepth, 10000000 * colourToMove)[0];
				std::cout << "Computer plays: " << move << std::endl;
			}
			else move = playerMove(moveList);

			if (move == 0) {
				std::cout << "NOOOOOOOOOOOO" << std::endl;
			}
			//printVector(moveList);

			board = makeMove(board, colourToMove, move);

			colourToMove *= -1;

		}

		if (win == 1) std::cout << "White Wins";
		else if (win == -1) std::cout << "Black Wins";
		else if (win == 2) std::cout << "Draw";

	return 0;
}

int main(int argc, const char * argv[]) {

	playGame(1);

//	printBoard(board);

//	printVector(generateAllMoves(board, -1));

	return 0;
}
