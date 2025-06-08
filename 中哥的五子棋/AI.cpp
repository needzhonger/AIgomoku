#include "AI.h"
#include <iostream>

void AI::init(Chess* chess)
{
    this->chess = chess;

    int size = chess->getGradeSize();
}

void AI::go(chess_kind side)
{
    ChessPos pos = think(side);
    chess->chessDown(&pos, side);
}

int AI::Evaluate(int row, int col, int side)
{
    int personNum = 0;  //��������ӵĸ���
    int botNum = 0;     //AI�����ӵĸ���
    int emptyNum = 0;   //������հ�λ�ĸ���

    int size = chess->getGradeSize();
    int Count3 = 0;//�γɻ�������Ŀ
    int Count4 = 0;//�γɻ��ĵ���Ŀ
    bool tooLong = false;//�ж��Ƿ�������
    int total = 0;
    //�Զ������֣������������򣩣�������ķ��ؼ�ֵ��
    for (int y = -1; y <= 0; y++) {
        for (int x = -1; x <= 1; x++) {
            if (y == 0 && x != 1) continue;
            personNum = 0;
            emptyNum = 0;
            for (int i = 1; i <= 5; i++)//ÿ����������5����
            {
                int curRow = row + i * y;
                int curCol = col + i * x;
                if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -side) { // ������ҵ���
                    personNum++;
                }
                else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) { // �հ�λ
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
                if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -side) { // ������ҵ���
                    personNum++;
                }
                else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) { // �հ�λ
                    emptyNum++;
                    break;
                }
                else {
                    break;
                }
            }

            if (personNum == 1) {//ɱ��
                total += 10;
            }
            else if (personNum == 2){//ɱ��
                if (emptyNum == 1)
                    total += 30;
                else if (emptyNum == 2) {
                    total += 40;
                    Count3++;
                }
            }
            else if (personNum == 3){//ɱ��
                if (emptyNum == 1)
                    total += 60;
                else if (emptyNum == 2) {
                    total += 5000;
                    Count4++;
                }
            }
            else if (personNum >= 4) {//ɱ��
                if (personNum >= 5) {
                    tooLong = true;
                }
                total += 2000000;
            }
        }
    }

    if (-side == 1 && ((Count3 >= 2 || Count4 >= 2) || tooLong) ) {//�����жϣ���������Ƕ��ֵĽ��ֵ㣬����û�з��ؼ�ֵ
        total = 0;
    }

    emptyNum = 0;
    Count3 = 0;
    Count4 = 0;
    tooLong = false;
    //���Լ����֣�������Ľ�����ֵ��
    for (int y = -1; y <= 0; y++) {
         for (int x = -1; x <= 1; x++) {
            if (y == 0 && x != 1) continue;
            botNum = 0;
            emptyNum = 0;
            for (int i = 1; i <= 5; i++)//ÿ����������5����
            {
                int curRow = row + i * y;
                int curCol = col + i * x;
                if (curRow >= 0 && curRow < size &&curCol >= 0 && curCol < size &&chess->getChessData(curRow, curCol) == side){ // ai����
                    botNum++;
                }
                else if (curRow >= 0 && curRow < size &&curCol >= 0 && curCol < size &&chess->getChessData(curRow, curCol) == 0){ // �հ�λ
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
                if (curRow >= 0 && curRow < size &&curCol >= 0 && curCol < size &&chess->getChessData(curRow, curCol) == side){ // ai����
                    botNum++;
                }
                else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) { // �հ�λ
                    emptyNum++;
                    break;
                }
                else {
                    break;
                }
            }

            if (botNum == 0) {//��ͨ����
                total += 5;
            }
            else if (botNum == 1){//���
                total += 10;
                
            }
            else if (botNum == 2){
                if (emptyNum == 1) {//����
                    total += 25;
                }
                else if (emptyNum == 2) {//����
                    Count3++;
                    total += 50;
                }
            }
            else if (botNum == 3)
            {
                if (emptyNum == 1) {//����
                    total += 55;
                }
                else if (emptyNum == 2) {//����
                    Count4++;
                    total += 10000; 
                }
            }
            else if (botNum >= 4) {
                total += 4000000;//���壬Ӧ�þ���������ȼ�
                if (botNum >= 5) {
                    tooLong = true;
                }
            }
        }
    }
    if ((Count3 >= 2 || Count4 >= 2) && side == 1) {//�����жϣ�����������Լ��Ľ��ֵ㣬����ǳ��壬��������
        total -= 2500000;
    }
    if (side == 1 && tooLong) {
        total = 0;
    }
    return total;
}

int AI::Search(int depth, int row, int col, int side)
{
    
    int best = -99999999;
    int size = chess->getGradeSize();
    if (depth <= 0)
    {
        return Evaluate(row, col, -side);
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (chess->getChessData(i, j) == 0){
                chess->changeChessMap(i, j, side);
                int val = Search(depth - 1, i, j, -side);
                if (val > best)
                    best = val;
                chess->changeChessMap(i, j, 0);
            }
        }
    }
    return Evaluate(row, col, -side) - best;
}
ChessPos AI::think(chess_kind side)
{
    int kind;
    if (side == B)
        kind = 1;
    else
        kind = -1;
    vector<ChessPos> maxPoints;
    int maxScore = -99999999;
    int size = chess->getGradeSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (chess->getChessData(i, j) == 0) {
                chess->changeChessMap(i, j, kind);
                int score = Search(Depth, i, j, -kind);
                if (score > maxScore) {
                    maxScore = score;
                    maxPoints.clear();
                    maxPoints.push_back(ChessPos(i, j));
                }
                else if (score == maxScore) {
                    maxPoints.push_back(ChessPos(i, j));
                }
                chess->changeChessMap(i, j, 0);
            }
        }
    }
    //cout << maxScore << endl;
    int index = rand() % maxPoints.size();
    if (chess->turn == 0 && chess->getChessData(7, 7) == 0 )
        return ChessPos(7, 7);
    else
        return maxPoints[index];
}