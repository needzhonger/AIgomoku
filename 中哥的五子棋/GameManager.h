#pragma once
#include "Player.h"
#include "AI.h"
#include "Chess.h"

class GameManager
{
public:
	GameManager(Player*, AI*, Chess*);
	void playMode1();
	void playMode2();
	void playMode3(int n);

	void quizList();
	void mainList();

private:
	Player* player;
	AI* ai;
	Chess* chess;
};


