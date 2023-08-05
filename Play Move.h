//
//  Make Move.h
//  Cmd Line Chess AI
//
//  Created by Robert Lewis on 6/12/21.
//  Copyright © 2021 Robert Lewis. All rights reserved.
//

#include "Generate Moves.h"

std::array<piece, 64> makeMove(std::array<piece, 64> oldBoard, int colourToMove, int move) {

	std::array<piece, 64> newBoard;

	int origin = floor((move % 10000) / 100);
	int destination = move % 100;
	int special = floor(move / 10000);

	
	piece movedPiece = oldBoard[origin];
	movedPiece.location = destination;
	movedPiece.move2 = false;
	movedPiece.castle = false;


	for (int i = 0; i < 64; i ++) {
		piece blankPiece(' ', i);

		if (i == origin) {
			newBoard[i] = blankPiece;
		}
		else if (i == destination) {
			newBoard[i] = movedPiece;
		}
		else {
			newBoard[i] = oldBoard[i];
		}
	}


	if (special != 0) {
		if (special == 1) {
			//Castle Kingside
			newBoard[destination + 1].castle = false;

			newBoard[destination - 1] = newBoard[destination + 1];

			piece blankPiece(' ', destination + 1);
			newBoard[destination + 1] = blankPiece;
		}
		else if (special == 2) {
			//Castle Queenside
			newBoard[destination - 2].castle = false;

			newBoard[destination + 1] = newBoard[destination - 2];

			piece blankPiece(' ', destination - 2);
			newBoard[destination - 2] = blankPiece;
		}
		else if (special == 3) {
			//En Passant
			piece blankPiece(' ', destination - 8 * colourToMove);

			newBoard[destination - 8 * colourToMove] = blankPiece;
		}
		else if (special == 4) {
			//Move 2
			newBoard[destination].move2 = false;
			newBoard[destination].enPassant = true;
		}
		else if (special == 5) {
			//Promote To Queen
			if (colourToMove == 1) {
				piece queen('Q', destination);
				newBoard[destination] = queen;
			}
			else {
				piece queen('q', destination);
				newBoard[destination] = queen;
			}
		}
	}

	//Disable EnPassant
	int begin = 28 + 4 * colourToMove;
	for (int i = 0; i < 8; i ++) {
		newBoard[begin + i].enPassant = false;
	}

	return newBoard;
}

int playerMove(std::vector<int> moveList) {
	bool allowedMove = false;
	int move = 0;
	while (!allowedMove) {
		std::cout << "You play: ";
		std::cin >> move;
		if (move == 0) {
			for (int i = 0; i < moveList.size(); i ++){
				std::cout << moveList[i] << std::endl;
			}
		}
		else {
			for (int i = 0; i < moveList.size(); i ++){
				if (moveList[i] == move) {
					allowedMove = true;
					break;
				}
			}
		if (!allowedMove) std::cout << "Move not in Move List" << std::endl;
		}
	}
	return move;
}


/* Make_Move_h */
