#include "GameManager.h"
#include <iostream>

GameManager::GameManager(Player* player, AI* ai, Chess* chess)
{
	this->player = player;
	this->ai = ai;
	this->chess = chess;

	ai->init(chess);
	player->init(chess);
}

void GameManager::playMode1()
{
	chess->gameModeCode = 1;
	chess->init(true);
	chess->playerFirst = 1;
	int tri;
	bool flag = true;
	while (true) {
		if (chess->playerFirst == 1) {
			int res = player->go(B);
			if (res == 1) {
				tri = chess->checkOver(true);
				if (tri == 0) {
					return;
				}
				else if ( tri == 1 ){
					continue;
				}
				ai->go(W);
				tri = chess->checkOver(false);
				if (tri == 0) {
					return;
				}
				else if ( tri == 1 ){
					continue;
				}
			}
			else if (res == 0) {
				flag = true;
				continue;
			}
			else if (res == -1) {
				flag = false;
				continue;
			}
			else if (res == -2) {
				return;
			}
		}
		else {
			if (flag) {
				ai->go(B);
				tri = chess->checkOver(true);
				if (tri == 0) {
					return;
				}
				else if ( tri == 1 ){
					continue;
				}
			}
			else {
				flag = true;
			}
			int res = player->go(W);
			if (res == 1) {
				tri = chess->checkOver(false);
				if (tri == 0) {
					return;
				}
				else if (tri == 1) {
					continue;
				}
			}
			else if (res == 0) {
				continue;
			}
			else if (res == -1) {
				flag = false;
				continue;
			}
			else if (res == -2) {
				return;
			}
		}
	}
}

void GameManager::playMode2()
{
	chess->gameModeCode = 2;
	chess->init(true);
	bool flag = true;
	int res;
	int tri;
	while (true) {
		if (flag) {
			
			res = player->go(B);
			if (res == 1) {
				tri = chess->checkOver(true);
				if ( tri == 0) {
					return;
				}
				else if (tri == 1) {
					continue;
				}
				else {
					chess->playerFirst = -1;
				}
			}
			else if (res == -2) {
				return;
			}
			else if (res == -1) {
				if (chess->playerFirst != 1) {
					flag = false;
				}
				continue;
			}
			else {
				continue;
			}
		}
		else {
			flag = true;
		}

		res = player->go(W);
		if (res == 1) {
			tri = chess->checkOver(true);
			if (tri == 0) {
				return;
			}
			else if (tri == 1) {
				continue;
			}
			else {
				chess->playerFirst = 1;
			}
		}
		else if (res == -2) {
			return;
		}
		else if (res == -1) {
			if (chess->playerFirst != 1) {
				flag = false;
			}
			continue;
		}
		else {
			continue;
		}
	}
}

void GameManager::playMode3(int n)
{
	chess->gameModeCode = 3;
	chess->readquiz(n);
	while (true) {
		if (chess->playerFirst == 1) {
			int res = player->goquiz(B);
			if (res == 1) {
				if (chess->checkOver(true) == 0) {
					return;
				}
				ai->go(W);
				if (chess->checkOver(false) == 0) {
					return;
				}
			}
			else if (res == 0) {
				chess->readquiz(n);
				continue;
			}
			else if (res == -2) {
				return;
			}
		}
		else {
			ai->go(B);
			if (chess->checkOver(true) == 0) {
				return;
			}
			int res = player->goquiz(W);
			if (res == 1) {
				if (chess->checkOver(false) == 0) {
					return;
				}
			}
			else if (res == 0) {
				chess->readquiz(n);
			}
			else if (res == -2) {
				return;
			}
		}
	}
}

void quitquiz() {
	cleardevice();
	mciSendString("close res/bg.mp3", 0, 0, 0);

	loadimage(0, "关卡选择.png");
	mciSendString("play res/gz'.mp3 repeat", 0, 0, 0);
	mciSendString("setaudio res/gz'.mp3 volume to 100", 0, 0, 0);
}

void GameManager::quizList()
{
	cleardevice();

	loadimage(0, "关卡选择.png");

	MOUSEMSG msg;
	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x >= 1021 && msg.x <= 1381 && msg.y >= 873 && msg.y <= 963) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				return;
			}
			else if (msg.x >= 114 && msg.x <= 265 && msg.y >= 94 && msg.y <= 211) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(1);
				quitquiz();
			}
			else if (msg.x >= 321 && msg.x <= 470 && msg.y >= 94 && msg.y <= 211) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(2);
				quitquiz();
			}
			else if (msg.x >= 527 && msg.x <= 678 && msg.y >= 94 && msg.y <= 211) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(3);
				quitquiz();
			}
			else if (msg.x >= 734 && msg.x <= 883 && msg.y >= 94 && msg.y <= 211) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(4);
				quitquiz();
			}
			else if (msg.x >= 939 && msg.x <= 1090 && msg.y >= 94 && msg.y <= 211) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(5);
				quitquiz();
			}
			else if (msg.x >= 1146 && msg.x <= 1295 && msg.y >= 94 && msg.y <= 211) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(6);
				quitquiz();
			}
			else if (msg.x >= 114 && msg.x <= 265 && msg.y >= 248 && msg.y <= 363) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(7);
				quitquiz();
			}
			else if (msg.x >= 321 && msg.x <= 470 && msg.y >= 248 && msg.y <= 363) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(8);
				quitquiz();
			}
			else if (msg.x >= 527 && msg.x <= 678 && msg.y >= 248 && msg.y <= 363) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(9);
				quitquiz();
			}
			else if (msg.x >= 734 && msg.x <= 883 && msg.y >= 248 && msg.y <= 363) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(10);
				quitquiz();
			}
			else if (msg.x >= 939 && msg.x <= 1090 && msg.y >= 248 && msg.y <= 363) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(11);
				quitquiz();
			}
			else if (msg.x >= 1146 && msg.x <= 1295 && msg.y >= 248 && msg.y <= 363) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(12);
				quitquiz();
			}
			else if (msg.x >= 114 && msg.x <= 265 && msg.y >= 401 && msg.y <= 516) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(13);
				quitquiz();
			}
			else if (msg.x >= 321 && msg.x <= 470 && msg.y >= 401 && msg.y <= 516) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(14);
				quitquiz();
			}
			else if (msg.x >= 527 && msg.x <= 678 && msg.y >= 401 && msg.y <= 516) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(15);
				quitquiz();
			}
			else if (msg.x >= 734 && msg.x <= 883 && msg.y >= 401 && msg.y <= 516) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(16);
				quitquiz();
			}
			else if (msg.x >= 939 && msg.x <= 1090 && msg.y >= 401 && msg.y <= 516) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(17);
				quitquiz();
			}
			else if (msg.x >= 1146 && msg.x <= 1295 && msg.y >= 401 && msg.y <= 516) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(18);
				quitquiz();
			}
			else if (msg.x >= 114 && msg.x <= 265 && msg.y >= 557 && msg.y <= 675) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(19);
				quitquiz();
			}
			else if (msg.x >= 321 && msg.x <= 470 && msg.y >= 557 && msg.y <= 675) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(20);
				quitquiz();
			}
			else if (msg.x >= 527 && msg.x <= 678 && msg.y >= 557 && msg.y <= 675) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(21);
				quitquiz();
			}
			else if (msg.x >= 734 && msg.x <= 883 && msg.y >= 557 && msg.y <= 675) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(22);
				quitquiz();
			}
			else if (msg.x >= 939 && msg.x <= 1090 && msg.y >= 557 && msg.y <= 675) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(23);
				quitquiz();
			}
			else if (msg.x >= 1146 && msg.x <= 1295 && msg.y >= 557 && msg.y <= 675) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(24);
				quitquiz();
			}
			else if (msg.x >= 114 && msg.x <= 265 && msg.y >= 711 && msg.y <= 827) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(25);
				quitquiz();
			}
			else if (msg.x >= 321 && msg.x <= 470 && msg.y >= 711 && msg.y <= 827) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(26);
				quitquiz();
			}
			else if (msg.x >= 527 && msg.x <= 678 && msg.y >= 711 && msg.y <= 827) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(27);
				quitquiz();
			}
			else if (msg.x >= 734 && msg.x <= 883 && msg.y >= 711 && msg.y <= 827) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(28);
				quitquiz();
			}
			else if (msg.x >= 939 && msg.x <= 1090 && msg.y >= 711 && msg.y <= 827) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(29);
				quitquiz();
			}
			else if (msg.x >= 1146 && msg.x <= 1295 && msg.y >= 711 && msg.y <= 827) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode3(30);
				quitquiz();
			}
		}
	}

}

void show()
{
	mciSendString("close res/bg.mp3", 0, 0, 0);
	cleardevice();

	loadimage(0, "主界面.png");
	mciSendString("play res/gz'.mp3 repeat", 0, 0, 0);
	mciSendString("setaudio res/gz'.mp3 volume to 100", 0, 0, 0);
}

void GameManager::mainList()
{
	initgraph(1417, 1063, SW_MAXIMIZE);
	show();
	MOUSEMSG msg;
	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x >= 521 && msg.x <= 886 && msg.y >= 255 && msg.y <= 355) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode1();

				show();
			}
			else if (msg.x >= 521 && msg.x <= 886 && msg.y >= 426 && msg.y <= 514) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				mciSendString("close res/gz'.mp3", 0, 0, 0);
				playMode2();

				show();
			}
			else if (msg.x >= 521 && msg.x <= 886 && msg.y >= 597 && msg.y <= 686) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				quizList();

				show();
			}
			else if (msg.x >= 521 && msg.x <= 886 && msg.y >= 769 && msg.y <= 856) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				chess->toExit();
			}
		}
	}
}


