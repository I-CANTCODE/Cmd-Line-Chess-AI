//
//  Hash.h
//  Cmd Line Chess AI
//
//  Created by Robert Lewis on 2/1/22.
//  Copyright © 2022 Robert Lewis. All rights reserved.
//

#include "Piece.h"

std::array<std::vector<std::array<piece, 64>>, 68000> boardStore;
std::array<std::vector<int>, 68000> depthStore;
std::array<std::vector<int>, 68000> evaluationStore;
std::array<std::vector<int>, 68000> perspectiveStore;
std::array<std::vector<int>, 68000> moveStore;


unsigned int hashBoard(std::array<piece, 64> currentBoard) {
	int hashed = 0;
	for (int i = 0; i < 64; i ++) {
		hashed += currentBoard[i].value * (i + 1);
	}

	return hashed + 34000;
}
