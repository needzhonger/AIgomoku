/*
	���ߣ�����и�
	
	�����Ż���
	1��AI������
	2�������˳��̡��ؿ��̡��л����̡֡��浵�����̹���
	3���������̣�����������Ӻ�ץ����Ƶ��
	4������������
	5��ʤ����ʧ��ҳ�������̣�����ʤ����ʧ��ҳ�水����
	6����ʾ������
	7��AI����������
	8�����˵��̡�˫�˶�ս�̡�����ģʽ��
*/

#include <iostream>
#include "GameManager.h"

int main(void) {
	AI ai;
	Player player;
	Chess chess(15, 149, 910, 152, 910, 54.2143);
	GameManager game(&player, &ai, &chess);
	
	game.mainList();
	
	return 0;
}