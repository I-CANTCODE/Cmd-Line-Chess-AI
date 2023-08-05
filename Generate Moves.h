//
//  Moves.h
//  Cmd Line Chess AI
//
//  Created by Robert Lewis on 1/12/21.
//  Copyright © 2021 Robert Lewis. All rights reserved.
//

#include "Boards.h"

bool inCheck(int location, std::array<piece, 64> currentBoard, int kingColour);

std::array<piece, 64> makeMove(std::array<piece, 64> oldBoard, int colourToMove, int move);


std::vector<int> pawnMove(int tLocation, int tColour, std::array<piece, 64> currentBoard) {
	std::vector<int> moveList;

	//Forward
	int location = tLocation + 8 * tColour;

	if (currentBoard[location].colour == 0) {
		if(location >= 56 or location <= 7) moveList.push_back(50000 + 100 * tLocation + location);
		else moveList.push_back(100 * tLocation + location);
		
		location += 8 * tColour;
		//Forward x 2
		if (currentBoard[location].colour == 0 and currentBoard[tLocation].move2) {
			moveList.push_back(40000 + 100 * tLocation + location);
		}
	}


	//Capture
	location = tLocation + 1 + 8 * tColour;
	if (currentBoard[location].colour == -1 * tColour and location % 8 == tLocation % 8 + 1) {
		if(location >= 56 or location <= 7) moveList.push_back(50000 + 100 * tLocation + location);
		else moveList.push_back(100 * tLocation + location);
	}

	location = tLocation - 1 + 8 * tColour;
	if (currentBoard[location].colour == -1 * tColour and location % 8 == tLocation % 8 - 1) {
		if(location >= 56 or location <= 7) moveList.push_back(50000 + 100 * tLocation + location);
		else moveList.push_back(100 * tLocation + location);
	}


	//En Passant
	if (currentBoard[tLocation + 1].enPassant) moveList.push_back(30000 + tLocation * 100 + tLocation + 9);
	if (currentBoard[tLocation - 1].enPassant) moveList.push_back(30000 + tLocation * 100 + tLocation + 7);

	return moveList;
}




std::vector<int> rookMove(int tLocation, int tColour, std::array<piece, 64> currentBoard) {
	std::vector<int> moveList;

	//Left
	int location = tLocation % 8;
	int offset = -1;
	while (location + offset >= 0) {
		if (currentBoard[tLocation + offset].colour != tColour) {
			moveList.push_back(100 * tLocation + (tLocation + offset));
			if (currentBoard[tLocation + offset].colour == -1 * tColour) {
				break;
			}
		}
		else break;
		offset --;
	}

	//Right
	offset = 1;
	while (location + offset < 8) {
		if (currentBoard[tLocation + offset].colour != tColour) {
			moveList.push_back(100 * tLocation + (tLocation + offset));
			if (currentBoard[tLocation + offset].colour == -1 * tColour) {
				break;
			}
		}
		else break;
		offset ++;
	}

	//Down
	offset = -1;
	while (tLocation + offset * 8 >= 0) {
		if (currentBoard[tLocation + offset * 8].colour != tColour) {
			moveList.push_back(100 * tLocation + (tLocation + offset * 8));
			if (currentBoard[tLocation + offset * 8].colour == -1 * tColour) {
				break;
			}
		}
		else break;
		offset --;
	}

	//Up
	offset = 1;
	while (tLocation + offset * 8 < 64) {
		if (currentBoard[tLocation + offset * 8].colour != tColour) {
			moveList.push_back(100 * tLocation + (tLocation + offset * 8));
			if (currentBoard[tLocation + offset * 8].colour == -1 * tColour) {
				break;
			}
		}
		else break;
		offset ++;
	}


	return moveList;
}


std::vector<int> knightMove(int tLocation, int tColour, std::array<piece, 64> currentBoard) {
	std::vector<int> moveList;

	int file = tLocation % 8;

	if (file + 1 < 8){
		if(tLocation + 17 < 64 and currentBoard[tLocation + 17].colour != tColour) moveList.push_back(tLocation * 100 + tLocation + 17);
		if (tLocation - 15 >= 0 and currentBoard[tLocation - 15].colour != tColour) moveList.push_back(tLocation * 100 + tLocation - 15);

		if (file + 2 < 8) {
			if(tLocation + 10 < 64 and currentBoard[tLocation + 10].colour != tColour) moveList.push_back(tLocation * 100 + tLocation + 10);
			if (tLocation - 6 >= 0 and currentBoard[tLocation - 6].colour != tColour) moveList.push_back(tLocation * 100 + tLocation - 6);
		}
	}

	if (file - 1 >= 0){
		if(tLocation + 15 < 64 and currentBoard[tLocation + 15].colour != tColour) moveList.push_back(tLocation * 100 + tLocation + 15);
		if (tLocation - 17 >= 0 and currentBoard[tLocation - 17].colour != tColour) moveList.push_back(tLocation * 100 + tLocation - 17);

		if (file - 2 >= 0) {
			if(tLocation + 6 < 64 and currentBoard[tLocation + 6].colour != tColour) moveList.push_back(tLocation * 100 + tLocation + 6);
			if (tLocation - 10 >= 0 and currentBoard[tLocation - 10].colour != tColour) moveList.push_back(tLocation * 100 + tLocation - 10);
		}
	}

	return moveList;
}


std::vector<int> bishopMove(int tLocation, int tColour, std::array<piece, 64> currentBoard) {
	std::vector<int> moveList;

	//Down Left
	int location = tLocation % 8;
	int offset = -1;
	while (location + offset >= 0 and tLocation + offset * 9 >= 0) {
		if (currentBoard[tLocation + offset * 9].colour != tColour) {
			moveList.push_back(tLocation * 100 + tLocation + 9 * offset);
			if (currentBoard[tLocation + offset * 9].colour == -1 * tColour) {
				break;
			}
		}
		else break;

		offset --;
	}

	//Down Right
	offset = -1;
	while (location - offset < 8 and tLocation + offset * 7 >= 0) {
		if (currentBoard[tLocation + offset * 7].colour != tColour) {
			moveList.push_back(tLocation * 100 + tLocation + 7 * offset);
			if (currentBoard[tLocation + offset * 7].colour == -1 * tColour) {
				break;
			}
		}
		else break;

		offset --;
	}

	//Up Right
	offset = 1;
	while (location + offset < 8 and tLocation + offset * 9 < 64) {
		if (currentBoard[tLocation + offset * 9].colour != tColour) {
			moveList.push_back(tLocation * 100 + tLocation + 9 * offset);
			if (currentBoard[tLocation + offset * 9].colour == -1 * tColour) {
				break;
			}
		}
		else break;

		offset ++;
	}

	//Up Left
	offset = 1;
	while (location - offset >= 0 and tLocation + offset * 7 < 64) {
		if (currentBoard[tLocation + offset * 7].colour != tColour) {
			moveList.push_back(tLocation * 100 + tLocation + 7 * offset);
			if (currentBoard[tLocation + offset * 7].colour == -1 * tColour) {
				break;
			}
		}
		else break;

		offset ++;
	}


	return moveList;
}


std::vector<int> queenMove(int tLocation, int tColour, std::array<piece, 64> currentBoard) {
	std::vector<int> moveList = bishopMove(tLocation, tColour, currentBoard);
	std::vector<int> rookMoveList = rookMove(tLocation, tColour, currentBoard);


	moveList.insert(std::end(moveList), std::begin(rookMoveList), std::end(rookMoveList));

	return moveList;
}


std::vector<int> kingMove(int tLocation, int tColour, std::array<piece, 64> currentBoard) {
	std::vector<int> moveList;

	int location = tLocation % 8;
	//Up
	int moveTo = tLocation + 8;
	if (currentBoard[moveTo].colour != tColour and moveTo < 64) {
		moveList.push_back(tLocation * 100 + moveTo);
	}

	//Up Right
	moveTo = tLocation + 9;
	if (currentBoard[moveTo].colour != tColour and moveTo < 64 and location + 1 < 8) {
		moveList.push_back(tLocation * 100 + moveTo);
	}

	//Right
	moveTo = tLocation + 1;
	if (currentBoard[moveTo].colour != tColour and location + 1 < 8) {
		moveList.push_back(tLocation * 100 + moveTo);
	}

	//Down Right
	moveTo = tLocation - 7;
	if (currentBoard[moveTo].colour != tColour and moveTo >= 0 and location + 1 < 8) {
		moveList.push_back(tLocation * 100 + moveTo);
	}

	//Down
	moveTo = tLocation - 8;
	if (currentBoard[moveTo].colour != tColour and moveTo >= 0) {
		moveList.push_back(tLocation * 100 + moveTo);
	}

	//Down Left
	moveTo = tLocation - 9;
	if (currentBoard[moveTo].colour != tColour and moveTo >= 0 and location - 1 >= 0) {
		moveList.push_back(tLocation * 100 + moveTo);
	}


	//Left
	moveTo = tLocation - 1;
	if (currentBoard[moveTo].colour != tColour and location - 1 >= 0) {
		moveList.push_back(tLocation * 100 + moveTo);
	}


	//Up Left
	moveTo = tLocation + 7;
	if (currentBoard[moveTo].colour != tColour and moveTo < 64 and location - 1 >= 0) {
		moveList.push_back(tLocation * 100 + moveTo);
	}

	//Castle Kingside
	if (currentBoard[tLocation].castle == true and currentBoard[tLocation + 1].colour == 0 and currentBoard[tLocation + 2].colour == 0 and currentBoard[tLocation + 3].castle == true and currentBoard[tLocation + 3].colour == tColour) {
		if (!inCheck(tLocation, currentBoard, tColour) and !inCheck(tLocation + 1, currentBoard, tColour)) {
			moveList.push_back(10000 + tLocation * 100 + tLocation + 2);
		}
	}

	//Castle Queenside
	if (currentBoard[tLocation].castle == true and currentBoard[tLocation - 1].colour == 0 and currentBoard[tLocation - 2].colour == 0 and currentBoard[tLocation - 3].colour == 0 and currentBoard[tLocation - 4].castle == true and currentBoard[tLocation - 4].colour == tColour) {
		if (!inCheck(tLocation, currentBoard, tColour) and !inCheck(tLocation - 1, currentBoard, tColour)) {
			moveList.push_back(20000 + tLocation * 100 + tLocation - 2);
		}
	}
	return moveList;
}


int findKing(std::array<piece, 64> currentBoard, int kingColour) {
	for (int i = 0; i < 64; i ++) {
		if (currentBoard[i].value == 500 * kingColour) return i;
	}

	printBoard(currentBoard);

	while (true) std::cout << "NO King!!!!!!!!!!!! " << kingColour << std::endl;
}



std::vector<int> piece::generatePieceMove(int location, int colour, char name, std::array<piece, 64> currentBoard) {
	char ID = std::tolower(name);
	std::vector<int> moveList;


	switch (ID) {
		case 'p':
			moveList = pawnMove(location, colour, currentBoard);
			break;
		case 'r':
			moveList = rookMove(location, colour, currentBoard);
			break;
		case 'n':
			moveList = knightMove(location, colour, currentBoard);
			break;
		case 'b':
			moveList = bishopMove(location, colour, currentBoard);
			break;
		case 'q':
			moveList = queenMove(location, colour, currentBoard);
			break;
		case 'k':
			moveList = kingMove(location, colour, currentBoard);
			break;
		case ' ':
			moveList = {};
			break;
	}

	return moveList;
}



std::vector<int> generateAllMoves(std::array<piece, 64> currentBoard, int colourToMove) {
	std::vector<int> moveList;

	for(int i = 0; i < 64; i ++) {
		std::vector<int> newMovesList;
		if (currentBoard[i].colour == colourToMove) {
			newMovesList = currentBoard[i].generatePieceMove(i, currentBoard[i].colour, currentBoard[i].name, currentBoard);

			moveList.insert(std::end(moveList), std::begin(newMovesList), std::end(newMovesList));

		}
	}
	int i = 0;
	std::array<piece, 64> tempBoard;
	while (i < moveList.size()) {
		tempBoard = makeMove(currentBoard, colourToMove, moveList[i]);

		if (inCheck(findKing(tempBoard, colourToMove), tempBoard, colourToMove)) {
			moveList.erase(moveList.begin() + i);
		}
		else i ++;
	}

//	for (int i = 0; i < rejectedMoves.size(); i ++) std::cout << rejectedMoves[i] << " ";
		   
	return moveList;
}



bool inCheck(int kingLocation, std::array<piece, 64> currentBoard, int kingColour) {
	std::vector<int> moveList;
	std::vector<int> newMovesList;

	int kingFile = kingLocation % 8;

	//pawn
	int destination = kingLocation + 1 + 8 * kingColour;
	if ((kingLocation + 1) % 8 == kingFile + 1 and destination % 64 == destination) {
		moveList.push_back(destination);
		if (currentBoard[destination].value == -1 * kingColour) return true;
	}

	destination = kingLocation - 1 + 8 * kingColour;
	if ((kingLocation - 1) % 8 == kingFile - 1 and destination % 64 == destination){
		moveList.push_back(destination);
		if (currentBoard[destination].value == -1 * kingColour) return true;
	}

	//right
	int offset = 1;
	destination = kingLocation + offset;
	if (abs(destination) % 8 == kingLocation % 8 + offset){
		if (currentBoard[destination].value == -500 * kingColour) return true;
		while (abs(destination) % 8 == kingLocation % 8 + offset) {
			if (currentBoard[destination].value == -5 * kingColour or currentBoard[destination].value == -9 * kingColour) return true;
			else if (currentBoard[destination].colour == kingColour) break;
			offset ++;
			destination = kingLocation + offset;

		}
	}

	//left
	offset = -1;
	destination = kingLocation + offset;
	if (abs(destination) % 8 == kingLocation % 8 + offset){
		if (currentBoard[destination].value == -500 * kingColour) return true;
		while (abs(destination) % 8 == kingLocation % 8 + offset) {
			if (currentBoard[destination].value == -5 * kingColour or currentBoard[destination].value == -9 * kingColour) return true;
			else if (currentBoard[destination].colour == kingColour) break;
			offset --;
			destination = kingLocation + offset;

		}
	}
	//up
	offset = 1;
	destination = kingLocation + offset * 8;
	if (abs(destination) % 64 == destination){
		if (currentBoard[destination].value == -500 * kingColour) return true;
		while (abs(destination) % 64 == destination) {
			if (currentBoard[destination].value == -5 * kingColour or currentBoard[destination].value == -9 * kingColour) return true;
			else if (currentBoard[destination].colour == kingColour) break;
			offset ++;
			destination = kingLocation + offset * 8;

		}
	}
	//down
	offset = -1;
	destination = kingLocation + offset * 8;
	if (abs(destination) % 64 == destination){
		if (currentBoard[destination].value == -500 * kingColour) return true;
		while (abs(destination) % 64 == destination) {
			if (currentBoard[destination].value == -5 * kingColour or currentBoard[destination].value == -9 * kingColour) return true;
			else if (currentBoard[destination].colour == kingColour) break;
			offset --;
			destination = kingLocation + offset * 8;

		}
	}


	//Up Right
	offset = 1;
	destination = kingLocation + offset * 9;
	if (abs(destination) % 64 == destination and abs(destination) % 8 == kingLocation % 8 + offset){
		if (currentBoard[destination].value == -500 * kingColour) return true;
		while (abs(destination) % 64 == destination and abs(destination) % 8 == kingLocation % 8 + offset) {
			if (currentBoard[destination].value == -3 * kingColour or currentBoard[destination].value == -9 * kingColour) return true;
			else if (currentBoard[destination].colour == kingColour) break;
			offset ++;
			destination = kingLocation + offset * 9;

		}
	}

	//Up Left
	offset = 1;
	destination = kingLocation + offset * 7;
	if (abs(destination) % 64 == destination and abs(destination) % 8 == kingLocation % 8 - offset){
		if (currentBoard[destination].value == -500 * kingColour) return true;
		while (abs(destination) % 64 == destination and abs(destination) % 8 == kingLocation % 8 - offset) {
			if (currentBoard[destination].value == -3 * kingColour or currentBoard[destination].value == -9 * kingColour) return true;
			else if (currentBoard[destination].colour == kingColour) break;
			offset ++;
			destination = kingLocation + offset * 7;

		}
	}

	//Down Left
	offset = -1;
	destination = kingLocation + offset * 7;
	if (abs(destination) % 64 == destination and abs(destination) % 8 == kingLocation % 8 - offset){
		if (currentBoard[destination].value == -500 * kingColour) return true;
		while (abs(destination) % 64 == destination and abs(destination) % 8 == kingLocation % 8 - offset) {
			if (currentBoard[destination].value == -3 * kingColour or currentBoard[destination].value == -9 * kingColour) return true;
			else if (currentBoard[destination].colour == kingColour) break;
			offset --;
			destination = kingLocation + offset * 7;

		}
	}

	//Down Right
	offset = -1;
	destination = kingLocation + offset * 9;
	if (abs(destination) % 64 == destination and abs(destination) % 8 == kingLocation % 8 + offset){
		if (currentBoard[destination].value == -500 * kingColour) return true;
		while (abs(destination) % 64 == destination and abs(destination) % 8 == kingLocation % 8 + offset) {
			if (currentBoard[destination].value == -3 * kingColour or currentBoard[destination].value == -9 * kingColour) return true;
			else if (currentBoard[destination].colour == kingColour) break;
			offset --;
			destination = kingLocation + offset * 9;

		}
	}

	//Knight
	moveList = knightMove(kingLocation, kingColour, currentBoard);
	for (int i = 0; i < moveList.size(); i ++) {
		if (currentBoard[moveList[i] % 100].value == -2.5 * kingColour) return true;;
	}


	return false;
}
/* Moves_h */
