//
//  Pieces.h
//  Cmd Line Chess AI
//
//  Created by Robert Lewis on 30/11/21.
//  Copyright © 2021 Robert Lewis. All rights reserved.
//
#include "Set Up.h"


class piece {
  public:
	int location;
	float value;
	int colour;
	char name;


	bool enPassant =false;
	bool move2 = false;

	bool castle = false;

	std::vector<int> generatePieceMove(int location, int colour, char name, std::array<piece, 64> currentBoard);

	bool isEqual(piece otherPiece) {
		return (otherPiece.value == value and otherPiece.enPassant == enPassant and otherPiece.move2 == move2 and otherPiece.castle == castle);
	}

	piece(char tName = ' ', int tLocation = 0) {
		char ID = std::tolower(tName);
		switch (ID) {
			case 'p':
				value = 1;
				move2 = true;
				break;
			case 'r':
				value = 5;
				castle = true;
				break;
			case 'n':
				value = 2.5;
				break;
			case 'b':
				value = 3;
				break;
			case 'q':
				value = 9;
				break;
			case 'k':
				value = 500;
				castle = true;
				break;
			case ' ':
				value = 0;
				break;
		}

		name = tName;

		if (value != 0) {
			value *= std::isupper(tName) ? 1 : -1;
			colour = std::isupper(tName) ? 1 : -1;
		}
		else {
			colour = 0;
		}

		location = tLocation;

	}
};

/* Pieces.h */
