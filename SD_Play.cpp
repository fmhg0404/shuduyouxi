#include "SD_Play.h"

//函数

void SD_Game_Start(void)
{
	SD_Show_start();
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y, &button[4]);
	TIME.start = clock();
}

void SD_Game_Stop(void)
{
	SD_Show_mask();
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y, &button[0]);
	TIME.last = clock() - TIME.start;
	TIME.temp += TIME.last;
}


bool SD_Play_game(void)
{
	while(1)
	{
	//时间输出
		SD_Show_Time();
	//鼠标扫描

	//键盘扫描

	//游戏功能
	switch (SD.game_flag)
	{
	case GAME_START:
		SD_music_button();
		SD_Game_Start();
	case GAME_STOP:
		SD_music_button();
		SD_Game_Stop();
	case GAME_AREA:

		break;
	case CHOOSE_AREA:

		break;
	case GAME_CLEAR:

		break;
	case PLAY_AGAIN:

		break;
	case GAME_HINT:

		break;
	case GAME_SET:

		break;
	}
}
}