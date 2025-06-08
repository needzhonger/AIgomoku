#include "Player.h"
#include <iostream>
void Player::init(Chess* chess)
{
	this->chess = chess;
}

bool Player::isInBoard(int x, int y) {
	if (x >= chess->margin_left && x <= chess->margin_right && y >= chess->margin_up && y <= chess->margin_down)
		return true;
	else
		return false;
}

bool Player::reStart(int x, int y)
{
	if (x >= 997 && x <= 1351 && y >= 222 && y <= 311)
		return true;
	else
		return false;
}
bool Player::saveLoad(int x, int y) {
	if (x >= 992 && x <= 1356 && y >= 402 && y <= 490)
		return true;
	else
		return false;
}
bool Player::readLoad(int x, int y) {
	if (x >= 997 && x <= 1351 && y >= 587 && y <= 675)
		return true;
	else
		return false;
}

bool Player::toExit(int x, int y) {
	if (x >= 992 && x <= 1356 && y >= 766 && y <= 854)
		return true;
	else
		return false;
}
bool Player::changeSide(int x, int y){
	if (x >= 46 && x <= 396 && y >= 9 && y <= 87)
		return true;
	else
		return false;
}

int Player::go(chess_kind side)
{
	MOUSEMSG msg;
	ChessPos pos;
	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (isInBoard(msg.x, msg.y) && chess->clickBoard(msg.x, msg.y, &pos)) {
				if (chess->checkPosition(&pos, side)) {
					chess->chessDown(&pos, side);
					return 1;
				}
				else {
					chess->goWrong();
				}
			}
			else if (reStart(msg.x, msg.y)){ 
				chess->reStart();
				return 0;
			}
			else if (saveLoad(msg.x, msg.y)) {
				chess->saveLoad();
			}
			else if (readLoad(msg.x, msg.y)) {
				chess->readLoad();
				cout << "read:" << chess->playerFirst << endl;
				return -1;
			}
			else if (changeSide(msg.x, msg.y)) {
				chess->changeSide();
				return 0;
			}
			else if (toExit(msg.x, msg.y)) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				return -2;
			}
			//通过返回不同结果指示gamemanager进行不同操作
			else {
				chess->goWrong();
			}
		}
	}
	return 0;
}

int Player::goquiz(chess_kind side)
{
	MOUSEMSG msg;
	ChessPos pos;
	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (isInBoard(msg.x, msg.y) && chess->clickBoard(msg.x, msg.y, &pos)) {
				chess->chessDown(&pos, side);
				return 1;
			}
			else if (msg.x >= 1021 && msg.x <= 1387 && msg.y >= 403 && msg.y <= 491) {
				return 0;
			}
			else if (msg.x >= 1021 && msg.x <= 1387 && msg.y >= 623 && msg.y <= 712) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				return -2;
			}
			//通过返回不同结果指示gamemanager进行不同操作
			else {
				chess->goWrong();
			}
		}
	}
	return 0;
}
