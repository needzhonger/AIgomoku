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
    int personNum = 0;  //玩家连成子的个数
    int botNum = 0;     //AI连成子的个数
    int emptyNum = 0;   //各方向空白位的个数

    int size = chess->getGradeSize();
    int Count3 = 0;//形成活三的数目
    int Count4 = 0;//形成活四的数目
    bool tooLong = false;//判断是否长连禁手
    int total = 0;
    //对对手评分（正反两个方向）（代表本棋的防守价值）
    for (int y = -1; y <= 0; y++) {
        for (int x = -1; x <= 1; x++) {
            if (y == 0 && x != 1) continue;
            personNum = 0;
            emptyNum = 0;
            for (int i = 1; i <= 5; i++)//每个方向延伸5个子
            {
                int curRow = row + i * y;
                int curCol = col + i * x;
                if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -side) { // 真人玩家的子
                    personNum++;
                }
                else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) { // 空白位
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
                if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -side) { // 真人玩家的子
                    personNum++;
                }
                else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) { // 空白位
                    emptyNum++;
                    break;
                }
                else {
                    break;
                }
            }

            if (personNum == 1) {//杀二
                total += 10;
            }
            else if (personNum == 2){//杀三
                if (emptyNum == 1)
                    total += 30;
                else if (emptyNum == 2) {
                    total += 40;
                    Count3++;
                }
            }
            else if (personNum == 3){//杀四
                if (emptyNum == 1)
                    total += 60;
                else if (emptyNum == 2) {
                    total += 5000;
                    Count4++;
                }
            }
            else if (personNum >= 4) {//杀五
                if (personNum >= 5) {
                    tooLong = true;
                }
                total += 2000000;
            }
        }
    }

    if (-side == 1 && ((Count3 >= 2 || Count4 >= 2) || tooLong) ) {//禁手判断：如果本棋是对手的禁手点，则本棋没有防守价值
        total = 0;
    }

    emptyNum = 0;
    Count3 = 0;
    Count4 = 0;
    tooLong = false;
    //对自己评分（代表本棋的进攻价值）
    for (int y = -1; y <= 0; y++) {
         for (int x = -1; x <= 1; x++) {
            if (y == 0 && x != 1) continue;
            botNum = 0;
            emptyNum = 0;
            for (int i = 1; i <= 5; i++)//每个方向延伸5个子
            {
                int curRow = row + i * y;
                int curCol = col + i * x;
                if (curRow >= 0 && curRow < size &&curCol >= 0 && curCol < size &&chess->getChessData(curRow, curCol) == side){ // ai的子
                    botNum++;
                }
                else if (curRow >= 0 && curRow < size &&curCol >= 0 && curCol < size &&chess->getChessData(curRow, curCol) == 0){ // 空白位
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
                if (curRow >= 0 && curRow < size &&curCol >= 0 && curCol < size &&chess->getChessData(curRow, curCol) == side){ // ai的子
                    botNum++;
                }
                else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) { // 空白位
                    emptyNum++;
                    break;
                }
                else {
                    break;
                }
            }

            if (botNum == 0) {//普通下子
                total += 5;
            }
            else if (botNum == 1){//活二
                total += 10;
                
            }
            else if (botNum == 2){
                if (emptyNum == 1) {//死三
                    total += 25;
                }
                else if (emptyNum == 2) {//活三
                    Count3++;
                    total += 50;
                }
            }
            else if (botNum == 3)
            {
                if (emptyNum == 1) {//死四
                    total += 55;
                }
                else if (emptyNum == 2) {//活四
                    Count4++;
                    total += 10000; 
                }
            }
            else if (botNum >= 4) {
                total += 4000000;//成五，应该具有最高优先级
                if (botNum >= 5) {
                    tooLong = true;
                }
            }
        }
    }
    if ((Count3 >= 2 || Count4 >= 2) && side == 1) {//禁手判断：如果本棋是自己的禁手点，则除非成五，否则不能下
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