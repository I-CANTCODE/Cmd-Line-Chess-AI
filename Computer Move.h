//
//  Computer Move.h
//  Cmd Line Chess AI
//
//  Created by Robert Lewis on 6/12/21.
//  Copyright © 2021 Robert Lewis. All rights reserved.
//

#include "Play Move.h"

int evaluateBoard(std::array<piece, 64> currentBoard, int colourEvaluatedFor) {
	int value = 0;

	for (int i = 0; i < 64; i ++) {
		value += currentBoard[i].value * 100;
	}

	value += generateAllMoves(currentBoard, 1).size();
	value -= generateAllMoves(currentBoard, -1).size();

	return value;
}

int incrementer = 0;
int maxSearchDepth = 3;
std::vector<int> computerMove(std::array<piece, 64> currentBoard, int colourToMove, int depth, int prevBest) {

	int boardHash = hashBoard(currentBoard);

	for (int i = 0; i < boardStore[boardHash].size(); i ++) {
		if (depthStore[boardHash][i] >= depth) {
			if (perspectiveStore[boardHash][i] == colourToMove) {
				bool boardsAreEqual = true;
				for (int j = 0; j < 64; j ++) {
					if (!boardStore[boardHash][i][j].isEqual(currentBoard[j])) {
						boardsAreEqual = false;
					}
				}
				if (boardsAreEqual) {
					return {moveStore[boardHash][i], evaluationStore[boardHash][i]};
				}
			}
		}
	}



	std::array<piece, 64> tempBoard;

	std::vector<int> moveList = generateAllMoves(currentBoard, colourToMove);

	int winValue = 10000000 * colourToMove;

	int bestMoveScore = -1 * winValue;

	std::vector<int> bestMoves = {moveList[0]};

	for (int i = 0; i < moveList.size(); i ++){

		tempBoard = makeMove(currentBoard, colourToMove, moveList[i]);

//		std::cout << depth << " " << colourToMove << std::endl;
//		printBoard(tempBoard);

		int newMoveScore;

		std::vector<int> opponentMoveList = generateAllMoves(tempBoard, -1 * colourToMove);

		if (opponentMoveList.size() == 0) {
			if (inCheck(findKing(tempBoard, -1 * colourToMove), tempBoard, -1 * colourToMove)) {
//				std::cout << "found Mate " << depth << std::endl;
				return {moveList[i], winValue};
			}
			else newMoveScore = 0;
//			std::cout << "Made It" << std::endl;
		}
		else if (depth == 1) {
			if (currentBoard[moveList[i] % 100].value != 0) {
//				std::cout << "extra move " << currentBoard[moveList[i] % 100].name << " " << extraDepth << std::endl;
				newMoveScore = computerMove(tempBoard, colourToMove * -1, 1, bestMoveScore)[1];
			}
			else {
				newMoveScore = evaluateBoard(tempBoard, colourToMove);
			}

		}
		else newMoveScore = computerMove(tempBoard, colourToMove * -1, depth - 1, bestMoveScore)[1];
//		std::cout << moveList[i] << " " << newMoveScore * colourToMove << " " << bestMove << " " << bestMoveScore << std::endl;

		if (newMoveScore * colourToMove > prevBest * colourToMove) {
			return {moveList[i], newMoveScore};
		}
		else if (newMoveScore * colourToMove > bestMoveScore * colourToMove) {
			bestMoves = {moveList[i]};
			bestMoveScore = newMoveScore;
		}
		else if (newMoveScore * colourToMove == bestMoveScore * colourToMove) {
			bestMoves.push_back(moveList[i]);
		}

	}



	int bestMove = bestMoves[rand() % bestMoves.size()];

//	std::cout << bestMove << ": ";
//	printVector(bestMoves);

	bool replaced = false;

	for (int i = 0; i < boardStore[boardHash].size(); i ++) {
		if (perspectiveStore[boardHash][i] == colourToMove) {
			bool boardsAreEqual = true;
			for (int j = 0; j < 64; j ++) {
				if (!boardStore[boardHash][i][j].isEqual(currentBoard[j])) {
					boardsAreEqual = false;
				}
			}

			if (boardsAreEqual) {
				evaluationStore[boardHash][i] = bestMoveScore;
				moveStore[boardHash][i] = bestMove;
				depthStore[boardHash][i] = depth;
				replaced = true;
				break;
			}
		}
	}

	if (!replaced) {
		boardStore[boardHash].push_back(currentBoard);
		perspectiveStore[boardHash].push_back(colourToMove);
		evaluationStore[boardHash].push_back(bestMoveScore);
		moveStore[boardHash].push_back(bestMove);
		depthStore[boardHash].push_back(depth);
	}

	if (depth == maxSearchDepth - 1) {
		std::cout << incrementer << " ";
		incrementer ++;
	}

	if (depth == maxSearchDepth) {
		incrementer = 0;
	}

	return {bestMove, bestMoveScore};

	}


 /* Computer_Move_h */
