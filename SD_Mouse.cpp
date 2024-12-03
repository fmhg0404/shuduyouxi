#include "SD_Mouse.h"

//函数
void SD_Count_x_y(u_16 *game_x, u_16 *game_y, u_8 *game_i,u_8 *game_j)
{
	SD.game_flag = EMPTY;
	if (SD.Int_face == MAIN ||SD.Int_face == SET_USE)
	{
		if (SD.Gameing || SD.Int_face == SET_USE)
		{
			if (mouse_msg.x >= GAME_START_X && mouse_msg.x <= GAME_START_X + GAME_BACKGROUND_SIZE - 21 && mouse_msg.y >= GAME_START_Y && mouse_msg.y <= GAME_START_Y + GAME_BACKGROUND_SIZE - 21)
			{//游戏区域

				SD.game_flag = GAME_AREA;
				return;
			}
			if (mouse_msg.x >= CHOOSE_START_X && mouse_msg.x <= CHOOSE_START_X + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y >= CHOOSE_START_Y && mouse_msg.y <= CHOOSE_START_Y + 3 * CHOOSE_PICTURE_SIZE + 2)
			{//选择区域
				SD.game_flag = CHOOSE_AREA;
				return;
			}
			if (mouse_msg.x >= CHOOSE_START_X && mouse_msg.x <= CHOOSE_START_X + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y >= CHOOSE_START_Y + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y <= CHOOSE_START_Y + 4 * CHOOSE_PICTURE_SIZE + 3)
			{//清除按钮
				SD.game_flag = GAME_CLEAR;
				return;
			}
		}
		if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y && mouse_msg.y <= BUTTON_MSTART_Y + BUTTON_MAIN_H)
		{//开始,停止按钮
			if (SD.Int_face == MAIN)
			{
				SD.Gameing = !SD.Gameing;
				if (SD.Gameing)
					SD.game_flag = GAME_START;
				else
					SD.game_flag = GAME_STOP;
			}
			else
				SD.game_flag = SET_TIME;
			return;
		}
		if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + BUTTON_MAIN_H + BUTTON_MINTERVAL && mouse_msg.y <= BUTTON_MSTART_Y + 2 * BUTTON_MAIN_H + BUTTON_MINTERVAL)
		{//再来一局
			SD.game_flag = PLAY_AGAIN;
			return;
		}
		if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + 2 * (BUTTON_MAIN_H + BUTTON_MINTERVAL) && mouse_msg.y <= BUTTON_MSTART_Y + 3 * BUTTON_MAIN_H + 2 * BUTTON_MINTERVAL)
		{//提示按钮,自定义界面确定按钮
			if (SD.Int_face == MAIN)
				SD.game_flag = GAME_HINT;
			else
				SD.game_flag = SET_SELF_YES;
			return;
		}
		if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + 3 * (BUTTON_MAIN_H + BUTTON_MINTERVAL) && mouse_msg.y <= BUTTON_MSTART_Y + 4 * BUTTON_MAIN_H + 3 * BUTTON_MINTERVAL)
		{//设置按钮
			SD.game_flag = GAME_SET;
			return;
		}
	}
	else
	{
		if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y && mouse_msg.y <= BUTTON_SSTART_Y + BUTTON_SET_H)
		{//简单模式
			SD.game_flag = SET_EASY;
			return;
		}
		if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + BUTTON_SET_H + BUTTON_SINTERVAL && mouse_msg.y <= BUTTON_SSTART_Y + 2 * BUTTON_SET_H + BUTTON_SINTERVAL)
		{//困难模式
			SD.game_flag = SET_HARD;
			return;
		}
		if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + 2 * (BUTTON_SET_H + BUTTON_SINTERVAL) && mouse_msg.y <= BUTTON_SSTART_Y + 3 * BUTTON_SET_H + 2 * BUTTON_SINTERVAL)
		{//炼狱模式
			SD.game_flag = SET_HARDEST;
			return;
		}
		if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + 3 * (BUTTON_SET_H + BUTTON_SINTERVAL) && mouse_msg.y <= BUTTON_SSTART_Y + 4 * BUTTON_SET_H + 3 * BUTTON_SINTERVAL)
		{//自定义模式
			SD.game_flag = SET_SELF;
			return;
		}
	}
}