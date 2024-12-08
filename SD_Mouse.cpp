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
void SD_Count_x_y(u_16* game_x, u_16* game_y, u_8* game_i, u_8* game_j)
{
	if (SD.Main_Interface)			//在主界面或自定义界面的操作
	{
		if (SD.Gameing || SD.Set_Self_Inerface)		//正在游戏或在自定义模式时，才可对数字区域和选择区域进行操作
		{
			if (mouse_msg.x >= GAME_START_X && mouse_msg.x <= GAME_START_X + GAME_BACKGROUND_SIZE - 21 && mouse_msg.y >= GAME_START_Y && mouse_msg.y <= GAME_START_Y + GAME_BACKGROUND_SIZE - 21)
			{	//游戏区域
				u_8 i = 0, j = 0;							//坐标计算，i和j记录点击位置对应的数组下标
				int start_x = 0, start_y = 0, now_x = 0, now_y = 0;	//start_x, start_y：记录每个小方格的起始坐标； now_x, now_y：记录点击坐标在游戏区域的相对坐标
				now_x = mouse_msg.x - GAME_START_X;		//记录本次鼠标点击坐标在游戏区域的相对坐标（从游戏起始位置开始）
				now_y = mouse_msg.y - GAME_START_Y;
				while (!(now_x >= start_x && now_x <= start_x + GAME_PICTURE_SIZE && now_y >= start_y && now_y <= start_y + GAME_PICTURE_SIZE))
				{
					if (now_x - GAME_PICTURE_SIZE > start_x)
						j++;
					if (now_y - GAME_PICTURE_SIZE > start_y)
						i++;
					start_x = j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL;		//每次记录小方格左上角的起始坐标
					start_y = i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL;
					if (now_x < start_x || now_y < start_y)			//左击游戏区域的间隔上，操作无效
						return;
				}
				if (SD.Init[i][j] == 0)		//初始值不能被选中
				{
					if (GAME_START_X + start_x == *game_x && GAME_START_Y + start_y == *game_y)		//鼠标点击同一位置实现翻转
					{
						switch (mouse_msg.message)
						{
						case WM_LBUTTONDOWN:			//这次鼠标左击
							if (SD.Mouse_flag == 0)		//上次也是鼠标左击
								SD.Linputflag = !SD.Linputflag;		//鼠标左键点击同位置，左击标志翻转
							else
							{						//上次是鼠标右击
								SD.Linputflag = 1;		//设置左击标志
								SD.Rinputflag = 0;		//清除右击标志
							}
							SD.Mouse_flag = 0;
							break;
						case WM_RBUTTONDOWN:			//这次鼠标右击
							if (SD.Mouse_flag == 1)		//上次鼠标右击
								SD.Rinputflag = !SD.Rinputflag;		//鼠标右键点击同位置，右击标志翻转
							else
							{						//上次鼠标左击
								SD.Rinputflag = 1;		//设置右击标志
								SD.Linputflag = 0;		//清除左击标志
							}
							SD.Mouse_flag = 1;
							break;
						}
					}
					else
					{
						if (*game_x < WINDOW_SIZE_L)	//这次鼠标点击新区域，将上一位置恢复，第一次不用
						{
							if (SD.right_data[*game_i][*game_j][9] == 0)
							{
								putimage(*game_x, *game_y, &numimg[SD.game[*game_i][*game_j]]);	//上位置复原
							}
							if (SD.game[*game_i][*game_j] == 0 && SD.right_data[*game_i][*game_j][9] != 9)
							{	//判断鼠标右击的上一位置是否需要复原，上一位置若左键存值了或者已经标记满了则不需要复原
								SD.Rinputflag = 0;
								right_mouse_sign(*game_x, *game_y, *game_i, *game_j);	//鼠标右击区域输入状态关闭
							}
						}
						if (mouse_msg.message == WM_LBUTTONDOWN)		//本次鼠标左击
						{
							SD.Mouse_flag = 0;
							SD.Linputflag = 1;	//设置左击标志
							SD.Rinputflag = 0;	//清除右击标志
						}
						else if (mouse_msg.message == WM_RBUTTONDOWN)		//本次鼠标右击
						{
							SD.Mouse_flag = 1;
							SD.Rinputflag = 1;	//设置右击标志
							SD.Linputflag = 0;	//清除左击标志
						}
						*game_x = GAME_START_X + start_x;		//图片输出位置
						*game_y = GAME_START_Y + start_y;
						*game_i = i;			//与数组行列对应
						*game_j = j;
					}
					SD.game_flag = GAME_AREA;
					return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
				}
			}
			if (mouse_msg.message == WM_LBUTTONDOWN)
			{
				if (mouse_msg.x >= CHOOSE_START_X && mouse_msg.x <= CHOOSE_START_X + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y >= CHOOSE_START_Y && mouse_msg.y <= CHOOSE_START_Y + 3 * CHOOSE_PICTURE_SIZE + 2)
				{		//选择区域
					SD.number = (mouse_msg.y - CHOOSE_START_Y) / CHOOSE_PICTURE_SIZE * 3 + (mouse_msg.x - CHOOSE_START_X) / CHOOSE_PICTURE_SIZE + 1;	//记录对应值，用于游戏区域左键的赋值或右键的标记
					SD.game_flag = CHOOSE_AREA;
					return;
				}
				if (mouse_msg.x >= CHOOSE_START_X && mouse_msg.x <= CHOOSE_START_X + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y >= CHOOSE_START_Y + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y <= CHOOSE_START_Y + 4 * CHOOSE_PICTURE_SIZE + 3)
				{		//清除按钮
					SD.game_flag = GAME_CLEAR;
					return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
				}
			}
		}
		if (mouse_msg.message == WM_LBUTTONDOWN)
		{
			if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y && mouse_msg.y <= BUTTON_MSTART_Y + BUTTON_MAIN_H)
			{		//开始、停止按钮
				if (SD.Set_Self_Inerface == 0)		//主界面
				{
					SD.Gameing = !SD.Gameing;		//将  正在游戏状态  翻转
					if (SD.Gameing)
						SD.game_flag = GAME_START;
					else
						SD.game_flag = GAME_STOP;
				}
				else			//自定义界面
				{
					SD.game_flag = SET_TIME;
				}
				return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
			}
			if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + BUTTON_MAIN_H + BUTTON_MINTERVAL && mouse_msg.y <= BUTTON_MSTART_Y + 2 * BUTTON_MAIN_H + BUTTON_MINTERVAL)
			{		//再来一局
				SD.game_flag = PLAY_AGAIN;
				return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
			}
			if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + 2 * (BUTTON_MAIN_H + BUTTON_MINTERVAL) && mouse_msg.y <= BUTTON_MSTART_Y + 3 * BUTTON_MAIN_H + 2 * BUTTON_MINTERVAL)
			{		//提示按钮、自定义界面确定按钮
				if (SD.Set_Self_Inerface)
					SD.game_flag = SET_SELF_YES;
				else if (SD.Linputflag)
					SD.game_flag = GAME_HINT;
				return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
			}
			if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + 3 * (BUTTON_MAIN_H + BUTTON_MINTERVAL) && mouse_msg.y <= BUTTON_MSTART_Y + 4 * BUTTON_MAIN_H + 3 * BUTTON_MINTERVAL)
			{		//设置按钮
				SD.game_flag = GAME_SET;
				return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
			}
		}
	}
	else			//设置界面的操作
	{
		if (mouse_msg.message == WM_LBUTTONDOWN)
		{
			if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y && mouse_msg.y <= BUTTON_SSTART_Y + BUTTON_SET_H)
			{		//简单模式
				SD.game_flag = SET_EASY;
				return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
			}
			if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + BUTTON_SET_H + BUTTON_SINTERVAL && mouse_msg.y <= BUTTON_SSTART_Y + 2 * BUTTON_SET_H + BUTTON_SINTERVAL)
			{		//困难模式
				SD.game_flag = SET_HARD;
				return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
			}
			if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + 2 * (BUTTON_SET_H + BUTTON_SINTERVAL) && mouse_msg.y <= BUTTON_SSTART_Y + 3 * BUTTON_SET_H + 2 * BUTTON_SINTERVAL)
			{		//炼狱模式
				SD.game_flag = SET_HARDEST;
				return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
			}
			if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + 3 * (BUTTON_SET_H + BUTTON_SINTERVAL) && mouse_msg.y <= BUTTON_SSTART_Y + 4 * BUTTON_SET_H + 3 * BUTTON_SINTERVAL)
			{		//自定义模式
				SD.game_flag = SET_SELF;
				return;			//鼠标一次只可能点击一个区域，梅进入一个区域后就不需要检测下一个区域了
			}
		}
	}
}

