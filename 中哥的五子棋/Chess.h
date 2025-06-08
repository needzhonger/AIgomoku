#pragma once
#include <graphics.h>
#include <vector>
using namespace std;


typedef enum {
	W = -1, 
	B = 1 
} chess_kind;

struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

class Chess {
public:

	Chess(int gradeSize, int margin_left, int matgin_right, int margin_up, int margin_down ,float chessSize);
	void init(bool playerFlag);
	void initquiz(bool playerFlag);

	bool clickBoard(int x, int y, ChessPos* pos);

	void chessDown(ChessPos* pos, chess_kind kind);
	bool checkPosition(ChessPos* pos, chess_kind kind);

	void goWrong();

	int getGradeSize();

	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	int checkOver(bool player);

	void changeChessMap(int row, int col, int side);

	void printMap();

	int margin_left;
	int margin_right;
	int margin_up;
	int margin_down;

	void reStart();
	void saveLoad();
	void readLoad();
	void changeSide();
	void toExit();
	int waitToChoose();
	void waitToChoose_inMode3();
	void readquiz(int n);
	

	bool playerFlag;
	int turn = 0;
	int playerFirst;
	int gameModeCode = 0;
private:

	vector<vector<int>> chessMap;

	int gradeSize;
	float chessSize;

	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	ChessPos lastPos;

	void updateGameMap(ChessPos* pos);
	bool checkWin();

};