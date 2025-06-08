#pragma once
#include "Chess.h"

class AI
{
public:
	void init(Chess* chess);
	void go(chess_kind side);

private:
	Chess* chess;
	int Evaluate(int row, int col, int side);
	int Search(int depth, int row, int col, int side);
	ChessPos think(chess_kind kind);
	int Depth = 2;
	
};

