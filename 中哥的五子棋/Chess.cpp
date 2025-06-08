#include "Chess.h"
#include <iostream>
#include <mmsystem.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <graphics.h>
#pragma comment(lib, "winmm.lib")



Chess::Chess(int gradeSize, int margin_left, int margin_right, int margin_up, int margin_down, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_left = margin_left;
	this->margin_right = margin_right;
	this->margin_up = margin_up;
	this->margin_down = margin_down;
	this->chessSize = chessSize;
	playerFirst = 1;
	playerFlag = true;
	
	for (int i = 0; i < gradeSize; i++) {
		vector<int>row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void Chess::init(bool playerFlag)
{
	turn = 0;
	loadimage(0, "����'.png");
	
	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	mciSendString("setaudio res/bg.mp3 volume to 100", 0, 0, 0);
	loadimage(&chessBlackImg, "����.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "white.png", chessSize, chessSize, true);

	for (int i = 0; i < chessMap.size(); i++)
		for (int j = 0; j < chessMap[i].size(); j++)
			chessMap[i][j] = 0;
	this->playerFlag = playerFlag;
}

void Chess::initquiz(bool playerFlag)
{
	turn = 0;
	loadimage(0, "��������.png");

	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	mciSendString("setaudio res/bg.mp3 volume to 100", 0, 0, 0);
	loadimage(&chessBlackImg, "����.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "white.png", chessSize, chessSize, true);

	for (int i = 0; i < chessMap.size(); i++)
		for (int j = 0; j < chessMap[i].size(); j++)
			chessMap[i][j] = 0;
	this->playerFlag = playerFlag;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int col = (x - margin_left) / chessSize;
	int row = (y - margin_up) / chessSize;

	//��ȡ����������Ͻǵĸ������
	int leftTopPosX = margin_left + chessSize * col;
	int leftTopPosY = margin_up + chessSize * row;
	int offset = 0.4 * chessSize;

	bool selectPos = false;
	
	int len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
	if (len < offset) {//���Ͻ�
		pos->row = row;
		pos->col = col;
		if (chessMap[pos->row][pos->col] == 0)
			selectPos = true;
	}
	else {
		len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {//���Ͻ�
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0)
				selectPos = true;
		}
		else {
			len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
			if (len < offset) {//���½�
				pos->row = row + 1;
				pos->col = col + 1;
				if (chessMap[pos->row][pos->col] == 0)
					selectPos = true;
			}
			else {
				len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
				if (len < offset) {//���½�
					pos->row = row + 1;
					pos->col = col;
					if (chessMap[pos->row][pos->col] == 0)
						selectPos = true;
				}
			}
		}
	}

	return selectPos;//��������ӽ��������Ч
}

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? 1 : -1;
	playerFlag = !playerFlag;
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;
	for (int i = 0; i < 5; i++)
	{
		if (col - i < 0 || col - i + 4 >= gradeSize)
			continue;
		else if (chessMap[row][col - i] == chessMap[row][col - i + 1] && chessMap[row][col - i] == chessMap[row][col - i + 2] && chessMap[row][col - i] == chessMap[row][col - i + 3] && chessMap[row][col - i] == chessMap[row][col - i + 4]) {
			return true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (row - i < 0 || row - i + 4 >= gradeSize)
			continue;
		else if (chessMap[row - i][col] == chessMap[row - i + 1][col] && chessMap[row - i][col] == chessMap[row - i + 2][col] && chessMap[row - i][col] == chessMap[row - i + 3][col] && chessMap[row - i][col] == chessMap[row - i + 4][col]) {
			return true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (col - i < 0 || col - i + 4 >= gradeSize || row - i < 0 || row - i + 4 >= gradeSize)
			continue;
		else if (chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] && chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] && chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] && chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]) {
			return true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (row + i >= gradeSize || row + i - 4 < 0 || col - i + 4 >= gradeSize || col - i < 0)
			continue;
		else if (chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] && chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] && chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] && chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]) {
			return true;
		}
	}
	return false;
}

void Chess::chessDown(ChessPos* pos, chess_kind kind)
{
	if (kind == W)
		playerFlag = false;
	else
		playerFlag = true;
	//���л����ֺ�֤chessMap��׼ȷ��

	TCHAR text[4];
	turn++;
	mciSendString("play res/down7.wav", 0, 0, 0);
	int x = margin_left + pos->col * chessSize - 0.5 * chessSize;
	int y = margin_up + pos->row * chessSize - 0.5 * chessSize;

	if (kind == W) {
		putimagePNG(x, y, &chessWhiteImg);
		settextcolor(BLACK);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
		settextcolor(WHITE);
	}
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "�����п�");
	sprintf_s(text, _T("%d"), turn);
	if (turn >= 100) {
		x -= 9;
		y -= 4;
	}//����ʾ���ֵ���������޲�
	else if (turn >= 10) {
		x -= 5;
		y -= 3;
	}
	outtextxy(x+20, y+15, text);
	updateGameMap(pos);

}

bool Chess::checkPosition(ChessPos* pos, chess_kind kind)
{
	if (kind == W) {//����û�н���
		return true;
	}
	int personNum = 0, emptyNum = 0;
	int row = pos->row;
	int col = pos->col;
	int Count3 = 0, Count4 = 0;
	for (int y = -1; y <= 0; y++) {
		for (int x = -1; x <= 1; x++) {
			if (y == 0 && x != 1) continue;
			personNum = 0;
			emptyNum = 0;
			for (int i = 1; i <= 5; i++)//ÿ����������5����
			{
				int curRow = row + i * y;
				int curCol = col + i * x;
				if (curRow >= 0 && curRow < gradeSize && curCol >= 0 && curCol < gradeSize && chessMap[curRow][curCol] == 1) { // ������ҵ���
					personNum++;
				}
				else if (curRow >= 0 && curRow < gradeSize && curCol >= 0 && curCol < gradeSize && chessMap[curRow][curCol] == 0) { // �հ�λ
					emptyNum++;
					break;
				}
				else {
					break;
				}
			}

			for (int i = 1; i <= 5; i++)
			{
				int curRow = row - i * y;
				int curCol = col - i * x;
				if (curRow >= 0 && curRow < gradeSize && curCol >= 0 && curCol < gradeSize && chessMap[curRow][curCol] == 1) { // ������ҵ���
					personNum++;
				}
				else if (curRow >= 0 && curRow < gradeSize && curCol >= 0 && curCol < gradeSize && chessMap[curRow][curCol] == 0) { // �հ�λ
					emptyNum++;
					break;
				}
				else {
					break;
				}
			}
			if (personNum == 4) {//���һ������������һ��ĺ������ĸ�����˴����ӿ���ֱ��Ӯ�����ӽ��֡�
				return true;
			}
			if (personNum >= 5) {//�жϳ�������
				return false;
			}
			if (personNum == 2 && emptyNum == 2) {//�Ƿ��л���
				Count3++;
			}
			else if (personNum == 3 && emptyNum == 2 ) {//�Ƿ��л���
				Count4++;
			}
		}
	}
	if (Count3 >= 2 || Count4 >= 2) {//�����жϣ���������Ƕ��ֵĽ��ֵ㣬����û�з��ؼ�ֵ
		return false;
	}
	else {
		return true;
	}
}

void Chess::goWrong()
{
	mciSendString("play res/����.mp3", 0, 0, 0);
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

int Chess::checkOver(bool player)
{
	if (checkWin()) {
		bool checkrole;
		if (playerFirst == 1)
			checkrole = true;
		else
			checkrole = false;
		if (checkrole == player) {
			Sleep(1000);
			mciSendString("close res/bg.mp3", 0, 0, 0);
			mciSendString("play ʤ��.mp3", 0, 0, 0);
			mciSendString("setaudio ʤ��.mp3 volume to 150", 0, 0, 0);
			if (gameModeCode == 3) {
				loadimage(0, "����ʤ��.png");
			}
			else {
				loadimage(0, "ʤ��.png");
			}

		}
		else {
			Sleep(1000);
			mciSendString("close res/bg.mp3", 0, 0, 0);
			mciSendString("play ʧ��.mp3", 0, 0, 0);
			mciSendString("setaudio ʧ��.mp3 volume to 150", 0, 0, 0);
			if (gameModeCode == 3) {
				loadimage(0, "����ʧ��.png");
			}
			else {
				loadimage(0, "ʧ��.png");
			}
		}
		if ( gameModeCode == 1 || gameModeCode == 2 ) {
			if (waitToChoose() == 1) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (gameModeCode == 3) {
			waitToChoose_inMode3();
			return 0;
		}
	}
	return -1;
}

void Chess::changeChessMap(int row, int col, int side)
{
	chessMap[row][col] = side;
	return;
}

void Chess::printMap()
{
	for (int i = 0; i < gradeSize; i++)
	{
		for (int j = 0; j < gradeSize; j++)
			cout << chessMap[i][j] << " ";
		cout << endl;
	}
}

void Chess::reStart()
{
	mciSendString("play res/click.mp3", 0, 0, 0);
	cleardevice();
	turn = 0;
	init(playerFirst);
}

void Chess::saveLoad()
{
	mciSendString("play res/click.mp3", 0, 0, 0);
	ofstream outfile("�浵.dat", ios::out);
	if (!outfile) {
		cerr << "open error!" << endl;
		exit(1);
	}
	cout << playerFirst << endl;
	outfile << playerFirst << endl;
	for (int i = 0; i < chessMap.size(); i++) {
		for (int j = 0; j < chessMap[i].size(); j++) {
			outfile << chessMap[i][j] << " ";
		}
		outfile << endl;
	}
	outfile.close();
}

void Chess::readLoad()
{
	mciSendString("play res/click.mp3", 0, 0, 0);
	cleardevice();
	turn = 0;
	ifstream infile("�浵.dat", ios::in);
	if (!infile) {
		cerr << "open error!" << endl;
		exit(1);
	}
	infile >> playerFirst;
	init(playerFirst);
	for (int i = 0;i < chessMap.size();i++) {
		for (int j = 0;j < chessMap[i].size();j++) {
			infile >> chessMap[i][j];
			if (chessMap[i][j] == 1) {
				int x = margin_left + j * chessSize - 0.5 * chessSize;
				int y = margin_up + i * chessSize - 0.5 * chessSize;
				putimagePNG(x, y, &chessBlackImg);
			}
			else if (chessMap[i][j] == -1) {
				int x = margin_left + j * chessSize - 0.5 * chessSize;
				int y = margin_up + i * chessSize - 0.5 * chessSize;
				putimagePNG(x, y, &chessWhiteImg);
			}
		}
	}
}

void Chess::changeSide()
{
	mciSendString("play res/click.mp3", 0, 0, 0);
	playerFirst = -playerFirst;
	reStart();
}

void Chess::toExit()
{
	mciSendString("play res/click.mp3", 0, 0, 0);
	exit(0);
}

int Chess::waitToChoose()
{
	MOUSEMSG msg;
	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x >= 248 && msg.x <= 615 && msg.y >= 652 && msg.y <= 745) {
				mciSendString("close ʤ��.mp3", 0, 0, 0);
				mciSendString("close ʧ��.mp3", 0, 0, 0);
				playerFlag = true;
				playerFirst = 1;
				reStart();
				return 1;
			}
			else if (msg.x >= 806 && msg.x < 1170 && msg.y >= 652 && msg.y <= 745) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				return 0;
			}
		}
	}
}

void Chess::waitToChoose_inMode3()
{
	MOUSEMSG msg;
	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x >= 492 && msg.x <= 913 && msg.y >= 617 && msg.y <= 722) {
				mciSendString("play res/click.mp3", 0, 0, 0);
				return;
			}
		}
	}
}

void Chess::readquiz(int n)
{
	cleardevice();
	turn = 0;
	ifstream infile;
	switch (n) {
	case 1:
		infile.open("�ؿ�1.dat", ios::in);
		break;
	case 2:
		infile.open("�ؿ�2.dat", ios::in);
		break;
	case 3:
		infile.open("�ؿ�3.dat", ios::in);
		break;
	case 4:
		infile.open("�ؿ�4.dat", ios::in);
		break;
	case 5:
		infile.open("�ؿ�5.dat", ios::in);
		break;
	case 6:
		infile.open("�ؿ�6.dat", ios::in);
		break;
	case 7:
		infile.open("�ؿ�7.dat", ios::in);
		break;
	case 8:
		infile.open("�ؿ�8.dat", ios::in);
		break;
	case 9:
		infile.open("�ؿ�9.dat", ios::in);
		break;
	case 10:
		infile.open("�ؿ�10.dat", ios::in);
		break;
	case 11:
		infile.open("�ؿ�11.dat", ios::in);
		break;
	case 12:
		infile.open("�ؿ�12.dat", ios::in);
		break;
	case 13:
		infile.open("�ؿ�13.dat", ios::in);
		break;
	case 14:
		infile.open("�ؿ�14.dat", ios::in);
		break;
	case 15:
		infile.open("�ؿ�15.dat", ios::in);
		break;
	case 16:
		infile.open("�ؿ�16.dat", ios::in);
		break;
	case 17:
		infile.open("�ؿ�17.dat", ios::in);
		break;
	case 18:
		infile.open("�ؿ�18.dat", ios::in);
		break;
	case 19:
		infile.open("�ؿ�19.dat", ios::in);
		break;
	case 20:
		infile.open("�ؿ�20.dat", ios::in);
		break;
	case 21:
		infile.open("�ؿ�21.dat", ios::in);
		break;
	case 22:
		infile.open("�ؿ�22.dat", ios::in);
		break;
	case 23:
		infile.open("�ؿ�23.dat", ios::in);
		break;
	case 24:
		infile.open("�ؿ�24.dat", ios::in);
		break;
	case 25:
		infile.open("�ؿ�25.dat", ios::in);
		break;
	case 26:
		infile.open("�ؿ�26.dat", ios::in);
		break;
	case 27:
		infile.open("�ؿ�27.dat", ios::in);
		break;
	case 28:
		infile.open("�ؿ�28.dat", ios::in);
		break;
	case 29:
		infile.open("�ؿ�29.dat", ios::in);
		break;
	case 30:
		infile.open("�ؿ�30.dat", ios::in);
		break;
	}
	if (!infile) {
		cerr << "open error!" << endl;
		exit(1);
	}
	infile >> playerFirst;
	cout << playerFirst << endl;
	initquiz(playerFirst);
	for (int i = 0;i < chessMap.size();i++) {
		for (int j = 0;j < chessMap[i].size();j++) {
			infile >> chessMap[i][j];
			if (chessMap[i][j] == 1) {
				int x = margin_left + j * chessSize - 0.5 * chessSize;
				int y = margin_up + i * chessSize - 0.5 * chessSize;
				putimagePNG(x, y, &chessBlackImg);
			}
			else if (chessMap[i][j] == -1) {
				int x = margin_left + j * chessSize - 0.5 * chessSize;
				int y = margin_up + i * chessSize - 0.5 * chessSize;
				putimagePNG(x, y, &chessWhiteImg);
			}
		}
	}
}


