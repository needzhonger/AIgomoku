/*
	作者：你的中哥
	
	待做优化：
	1、AI升级√
	2、完善退出√、重开√、切换先手√、存档读档√功能
	3、背景音√，随机播放落子和抓子音频√
	4、棋子美化√
	5、胜利、失败页面美化√，完善胜利、失败页面按键√
	6、显示步数√
	7、AI二次升级√
	8、主菜单√、双人对战√、闯关模式√
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