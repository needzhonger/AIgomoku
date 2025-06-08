#pragma once
#include "Chess.h"
#include "AI.h"
class Player
{
public:
	void init(Chess* chess);
	int go(chess_kind side);
	int goquiz(chess_kind side);

private:
	Chess* chess;

	bool isInBoard(int x, int y);
	bool reStart(int x, int y);
	bool saveLoad(int x, int y);
	bool readLoad(int x, int y);
	bool toExit(int x, int y);
	bool changeSide(int x, int y);
};

