//
//  Boards.h
//  Cmd Line Chess AI
//
//  Created by Robert Lewis on 1/12/21.
//  Copyright © 2021 Robert Lewis. All rights reserved.
//

#include "Hash.h"

void transferBoardState(piece keptBoard[64], piece updatedBoard[64]) {
	for (int i = 0; i < 64; i++) {
		updatedBoard[i] = keptBoard[i];
	}
}

//Default

std::array<piece, 64> board = {
piece('R', 0),  piece('N', 1),  piece('B', 2),  piece('Q', 3),  piece('K', 4),  piece('B', 5),  piece('N', 6),  piece('R', 7),
piece('P', 8),  piece('P', 9),  piece('P', 10), piece('P', 11), piece('P', 12), piece('P', 13), piece('P', 14), piece('P', 15),
piece(' ', 16), piece(' ', 17), piece(' ', 18), piece(' ', 19), piece(' ', 20), piece(' ', 21), piece(' ', 22), piece(' ', 23),
piece(' ', 24), piece(' ', 25), piece(' ', 26), piece(' ', 27), piece(' ', 28), piece(' ', 29), piece(' ', 30), piece(' ', 31),
piece(' ', 32), piece(' ', 33), piece(' ', 34), piece(' ', 35), piece(' ', 36), piece(' ', 37), piece(' ', 38), piece(' ', 39),
piece(' ', 40), piece(' ', 41), piece(' ', 42), piece(' ', 43), piece(' ', 44), piece(' ', 45), piece(' ', 46), piece(' ', 47),
piece('p', 48), piece('p', 49), piece('p', 50), piece('p', 51), piece('p', 52), piece('p', 53), piece('p', 54), piece('p', 55),
piece('r', 56), piece('n', 57), piece('b', 58), piece('q', 59), piece('k', 60), piece('b', 61), piece('n', 62), piece('r', 63)};

//None
/*
std::array<piece, 64> board = {
piece(' ', 0),  piece(' ', 1),  piece(' ', 2),  piece(' ', 3),  piece(' ', 4),  piece(' ', 5),  piece(' ', 6),  piece(' ', 7),
piece(' ', 8),  piece(' ', 9),  piece(' ', 10), piece(' ', 11), piece(' ', 12), piece(' ', 13), piece(' ', 14), piece(' ', 15),
piece(' ', 16), piece(' ', 17), piece(' ', 18), piece(' ', 19), piece(' ', 20), piece(' ', 21), piece(' ', 22), piece(' ', 23),
piece(' ', 24), piece(' ', 25), piece(' ', 26), piece(' ', 27), piece(' ', 28), piece(' ', 29), piece(' ', 30), piece(' ', 31),
piece(' ', 32), piece(' ', 33), piece(' ', 34), piece(' ', 35), piece(' ', 36), piece(' ', 37), piece(' ', 38), piece(' ', 39),
piece(' ', 40), piece(' ', 41), piece(' ', 42), piece(' ', 43), piece(' ', 44), piece(' ', 45), piece(' ', 46), piece(' ', 47),
piece(' ', 48), piece(' ', 49), piece(' ', 50), piece(' ', 51), piece(' ', 52), piece(' ', 53), piece(' ', 54), piece(' ', 55),
piece(' ', 56), piece(' ', 57), piece(' ', 58), piece(' ', 59), piece(' ', 60), piece(' ', 61), piece(' ', 62), piece(' ', 63)};
*/

//Custom
/*
std::array<piece, 64> board = {
piece('R', 0),  piece(' ', 1),  piece('B', 2),  piece(' ', 3),  piece('K', 4),  piece('B', 5),  piece('N', 6),  piece('R', 7),
piece('P', 8),  piece('P', 9),  piece('P', 10), piece('P', 11), piece(' ', 12), piece('P', 13), piece('P', 14), piece('P', 15),
piece(' ', 16), piece(' ', 17), piece('N', 18), piece(' ', 19), piece('P', 20), piece(' ', 21), piece(' ', 22), piece(' ', 23),
piece(' ', 24), piece(' ', 25), piece(' ', 26), piece(' ', 27), piece(' ', 28), piece(' ', 29), piece(' ', 30), piece(' ', 31),
piece(' ', 32), piece(' ', 33), piece(' ', 34), piece(' ', 35), piece(' ', 36), piece(' ', 37), piece(' ', 38), piece('Q', 39),
piece(' ', 40), piece(' ', 41), piece(' ', 42), piece(' ', 43), piece('p', 44), piece('q', 45), piece(' ', 46), piece(' ', 47),
piece('p', 48), piece('p', 49), piece('p', 50), piece('p', 51), piece(' ', 52), piece('p', 53), piece('p', 54), piece('p', 55),
piece('r', 56), piece('n', 57), piece('b', 58), piece(' ', 59), piece('k', 60), piece('b', 61), piece('n', 62), piece('r', 63)};
*/

void printBoard(std::array<piece, 64> board, bool debug = true) {
	int x = 56;
	if (!debug) {
		while (x >= 0) {
			if (board[x].name == ' ') std::cout << '-' << ' ';
			else std::cout << board[x].name << ' ';
			x ++;
			if (x % 8 == 0) {
				x -= 16;
				std::cout << std::endl;
			}
		}
	}
	else {
		while (x >= 0) {
			if (board[x].name == ' ') {
				std::cout << x << ' ';
				if (x < 10) std::cout << ' ';
			}
			else std::cout << board[x].name << "  ";
			x ++;
			if (x % 8 == 0) {
				x -= 16;
				std::cout << std::endl;
			}
		}
	}
	std::cout << "________________________" << std::endl;

}

void printVector(std::vector<int> vector) {
	for (int i = 0; i < vector.size(); i ++) {
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}
/* Boards_h */
