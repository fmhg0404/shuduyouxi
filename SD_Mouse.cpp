#include "SD_Mouse.h"

void right_mouse_sign(u_16 game_x, u_16 game_y, u_8 game_i, u_8 game_j)
{
	u_8 n = 1, k = 0;
	for (; k < SD.right_data[game_i][game_j][0]; k++)
	{
		while (SD.right_data[game_i][game_j][n++] == 0);
		putimage(game_x + k % 3 * RIGHT_PICTURE_SIZE, game_y + k / 3 * RIGHT_PICTURE_SIZE, &rightimg[n-  1]);
	}
	if (k < 9)
	{
		if (SD.Rinputflag == 1)
			putimage(game_x + k % 3 * RIGHT_PICTURE_SIZE, game_y + k / 3 * RIGHT_PICTURE_SIZE, &rightimg[10]);
		else
			putimage(game_x + k % 3 * RIGHT_PICTURE_SIZE, game_y + k / 3 * RIGHT_PICTURE_SIZE, &rightimg[0]);
		k++;
	}
	for (; k < 9; k++)
	{
		putimage(game_x + k % 3 * RIGHT_PICTURE_SIZE, game_y + k / 3 * RIGHT_PICTURE_SIZE, &rightimg[0]);
	}
}

//函数
void SD_Count_x_y(u_16 *game_x, u_16 *game_y, u_8 *game_i,u_8 *game_j)
{
	if (SD.Int_face == MAIN ||SD.Int_face == SET_USE)
	{
		if (SD.Gameing || SD.Int_face == SET_USE)
		{
			if (mouse_msg.x >= GAME_START_X && mouse_msg.x <= GAME_START_X + GAME_BACKGROUND_SIZE - 21 && mouse_msg.y >= GAME_START_Y && mouse_msg.y <= GAME_START_Y + GAME_BACKGROUND_SIZE - 21)
			{//游戏区域
				u_8 i = 0, j = 0;
				u_16 startx = 0, starty = 0, nowx = 0, nowy = 0;
				nowx = mouse_msg.x - GAME_START_X;
				nowy = mouse_msg.y - GAME_START_Y;
				while (!(nowx >= startx && nowx <= startx + GAME_PICTURE_SIZE && nowy >= starty && nowy <= starty + GAME_PICTURE_SIZE))
				{
					if (startx + GAME_PICTURE_SIZE < nowx)
						j++;
					if (starty + GAME_PICTURE_SIZE < nowy)
						i++;
					startx = j * (GAME_PICTURE_SIZE + GAME_INTERVAL) + j / 3 * 4;
					starty = i * (GAME_PICTURE_SIZE + GAME_INTERVAL) + i / 3 * 4;
					if (nowx < startx || nowy < starty)
						return;
				}
				if (SD.Init[i][j] == 0)
				{
					if (*game_i == i && *game_j == j)
					{
						switch (mouse_msg.message)
						{
						case WM_LBUTTONDOWN:
							if (SD.Mouse_flag == 0)
								SD.Linputflag = !SD.Linputflag;
							else
							{
								SD.Rinputflag = 0;
								SD.Linputflag = 1;
							}
							SD.Mouse_flag = 0;
							break;
						case WM_RBUTTONDOWN:
							if (SD.Mouse_flag == 1)
								SD.Rinputflag = !SD.Rinputflag;
							else
							{
								SD.Linputflag = 0;
								SD.Rinputflag = 1;
							}
							SD.Mouse_flag = 1;
							break;
						}
					}
					else
					{
						//关闭前一状态
						if (SD.right_data[*game_i][*game_j][0] == 0)
							putimage(*game_x, *game_y, &numimg[SD.game[*game_i][*game_j]]);
						else
						{
							SD.Rinputflag = 0;
							right_mouse_sign(*game_x, *game_y, *game_i, *game_j);
						}	
						if (mouse_msg.message == WM_LBUTTONDOWN)
						{
							SD.Mouse_flag = 0;
							SD.Rinputflag = 0;
							SD.Linputflag = 1;
						}
						else if (mouse_msg.message == WM_RBUTTONDOWN)
						{
							SD.Mouse_flag = 1;
							SD.Rinputflag = 1;
							SD.Linputflag = 0;
						}
						*game_x = startx + GAME_START_X;
						*game_y = starty + GAME_START_Y;
						*game_i = i;
						*game_j = j;
					}
				}

				SD.game_flag = GAME_AREA;
				return;
			}
			if (mouse_msg.message == WM_LBUTTONDOWN)
			{
				if (mouse_msg.x >= CHOOSE_START_X && mouse_msg.x <= CHOOSE_START_X + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y >= CHOOSE_START_Y && mouse_msg.y <= CHOOSE_START_Y + 3 * CHOOSE_PICTURE_SIZE + 2)
				{//选择区域
					SD.number = (mouse_msg.x - CHOOSE_START_X) / CHOOSE_PICTURE_SIZE + (mouse_msg.y - CHOOSE_START_Y) / CHOOSE_PICTURE_SIZE * 3 + 1;
					SD.game_flag = CHOOSE_AREA;
					return;
				}
				if (mouse_msg.x >= CHOOSE_START_X && mouse_msg.x <= CHOOSE_START_X + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y >= CHOOSE_START_Y + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y <= CHOOSE_START_Y + 4 * CHOOSE_PICTURE_SIZE + 3)
				{//清除按钮
					SD.game_flag = GAME_CLEAR;
					return;
				}
			}
		}
		if (mouse_msg.message == WM_LBUTTONDOWN)
		{
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
	}
	else
	{
		if (mouse_msg.message == WM_LBUTTONDOWN)
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
}