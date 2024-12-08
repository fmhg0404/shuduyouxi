#include "SD_Play.h"

//函数
void delete_right_num(u_8 game_i, u_8 game_j, u_8 number)
{
	u_16 game_x = 0, game_y = 0;
	for (u_8 j = 0; j < 9; j++)		//将本行值为number的标记删除
	{
		if (SD.right_data[game_i][j][9] != 0 && SD.right_data[game_i][j][number - 1] == 1)
		{		//寻找需要删除标记的位置
			SD.right_data[game_i][j][number - 1] = 0;		//对应标记置0
			SD.right_data[game_i][j][9]--;			//标记计数-1
			game_x = GAME_START_X + (j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL);		//更新图形界面数字输出位置
			game_y = GAME_START_Y + (game_i * GAME_PICTURE_SIZE + game_i * GAME_INTERVAL + game_i / 3 * 2 * GAME_INTERVAL);	//x因j改变，y因i改变
			right_mouse_sign(game_x, game_y, game_i, j);		//更新整个右击区域
		}
	}
	for (u_8 i = 0; i < 9; i++)		//将本列值为number的标记删除
	{
		if (SD.right_data[i][game_j][9] != 0 && SD.right_data[i][game_j][number - 1] == 1)
		{
			SD.right_data[i][game_j][number - 1] = 0;
			SD.right_data[i][game_j][9]--;
			game_x = GAME_START_X + (game_j * GAME_PICTURE_SIZE + game_j * GAME_INTERVAL + game_j / 3 * 2 * GAME_INTERVAL);		//更新图形界面数字输出位置
			game_y = GAME_START_Y + (i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL);	//x因j改变，y因i改变
			right_mouse_sign(game_x, game_y, i, game_j);
		}
	}
	for (u_8 i = game_i / 3 * 3; i < game_i / 3 * 3 + 3; i++)		//将本列值为number的标记删除
		for (u_8 j = game_j / 3 * 3; j < game_j / 3 * 3 + 3; j++)
		{
			if (SD.right_data[i][j][9] != 0 && SD.right_data[i][j][number - 1] == 1)
			{
				SD.right_data[i][j][number - 1] = 0;
				SD.right_data[i][j][9]--;
				game_x = GAME_START_X + (j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL);		//更新图形界面数字输出位置
				game_y = GAME_START_Y + (i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL);	//x因j改变，y因i改变
				right_mouse_sign(game_x, game_y, i, j);
			}
		}
}


void SD_Game_Start(void)
{
	SD_Show_start();
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y, &button[4]);
	TIME.start = clock();
}

void SD_Game_Stop(void)
{
	SD.Linputflag = SD.Rinputflag = 0;
	SD_Show_mask();
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y, &button[0]);
	TIME.last = clock() - TIME.start;
	TIME.temp += TIME.last;
}


bool SD_Play_Game(void)
{
	u_16 game_x = WINDOW_SIZE_L, game_y = WINDOW_SIZE_H;
	u_8 game_i = 0, game_j = 0;
	while(1)
	{
		//清除标志
		SD.game_flag = EMPTY;
	//时间输出
		if (SD.Gameing)
		{
			SD_Show_time();
		}	
	//鼠标扫描
		if (peekmessage(&mouse_msg, EX_MOUSE))
		{
			if (mouse_msg.message  == WM_LBUTTONDOWN || mouse_msg.message == WM_RBUTTONDOWN)
				SD_Count_x_y(&game_x, &game_y, &game_i, &game_j);
		}
	//键盘扫描
		Scan_Key(&game_x, &game_y, &game_i, &game_j);
	//游戏功能
	switch (SD.game_flag)
	{
	case GAME_START:
		SD_music_button();
		SD_Game_Start();
		break;
	case GAME_STOP:
		SD_music_button();
		SD_Game_Stop();
		break;
	case GAME_AREA:
		switch (SD.Mouse_flag)
		{
		case 0:		//当前鼠标左击
			if (SD.Linputflag == 1)		//如果处于输入状态，显示白色“输入”图片
				putimage(game_x, game_y, &numimg[10]);
			else if (SD.right_data[game_i][game_j][9] == 0)	//如果是非输入状态，且该位置没有标记，显示原值图片
				putimage(game_x, game_y, &numimg[SD.game[game_i][game_j]]);
			else 										//如果是非输入状态，但该位置有标记，显示标记图片
				right_mouse_sign(game_x, game_y, game_i, game_j);
			break;
		case 1:		//当前鼠标右击
			if (SD.Rinputflag == 1)
				right_mouse_sign(game_x, game_y, game_i, game_j);		//输出右击区域标记数值
			else if (SD.right_data[game_i][game_j][9] != 0)
				putimage(game_x + SD.right_data[game_i][game_j][9] % 3 * RIGHT_PICTURE_SIZE, game_y + SD.right_data[game_i][game_j][9] / 3 * RIGHT_PICTURE_SIZE, &rightimg[0]);	//鼠标右击区域输入状态关闭
			else
				putimage(game_x, game_y, &numimg[SD.game[game_i][game_j]]);	//上位置复原
			break;
		}
		break;
	case CHOOSE_AREA:			//选择区域
		if (SD.Linputflag == 1)		//处于左击输入状态
		{
			SD_music_innum();		//播放输入音效
			SD.game[game_i][game_j] = 0;			//输入前将该位置的值清零（避免修改时重复输入同一个值弹出对话框）
			if (SD_detection(game_i, game_j, SD.number) == 0)
			{	//不冲突
				if (SD.right_data[game_i][game_j][9] != 0)		//该位置被鼠标右击标记过，需要将该位置的右击标记清零
					for (u_8 n = 0; n < 10; n++)				//右击区域标记清零
						SD.right_data[game_i][game_j][n] = 0;
				SD.game[game_i][game_j] = SD.number;		//将选择区域对应存值入游戏数组
				delete_right_num(game_i, game_j, SD.number);		//赋值后删除本行、本列、本3*3小矩阵的该值的标记
				putimage(game_x, game_y, &numimg[SD.number]);		//输出对应图片
				if (SD_verify())		//每存入一个值就判断游戏结果，成立返回1
					return 1;			//return到主函数
				SD.Linputflag = 1;		//输入完后保持输入状态，方便键盘进行操作
			}
		}
		if (SD.Rinputflag == 1)		//处于右击标记状态
		{
			SD.game[game_i][game_j] = 0;
			SD.right_data[game_i][game_j][SD.number - 1] = 0x01 ^ SD.right_data[game_i][game_j][SD.number - 1];	//用异或^运算实现翻转，第一次显示第二次取消
			if (SD.right_data[game_i][game_j][SD.number - 1])
				SD.right_data[game_i][game_j][9]++;			//统计图片数量
			else
				SD.right_data[game_i][game_j][9]--;
			right_mouse_sign(game_x, game_y, game_i, game_j);		//输出右击区域标记数值
		}
		break;
	case GAME_CLEAR:			//清除按钮
		if (SD.Rinputflag == 1)
		{		//清除鼠标右键标记，进入输入状态
			SD_music_button();		//播放按键音效
			for (u_8 n = 0; n < 10; n++)
				SD.right_data[game_i][game_j][n] = 0;
			SD.Rinputflag = 1;		//保持输入状态
			right_mouse_sign(game_x, game_y, game_i, game_j);
		}			//左键输入状态下 && 不是初始值
		else if (SD.Linputflag == 1)
		{		//清除鼠标左键输入状态
			SD_music_button();		//播放按键音效
			SD.game[game_i][game_j] = 0;
			putimage(game_x, game_y, &numimg[0]);
			SD.Linputflag = 0;		//清零后清除输入状态
		}
		break;
	case PLAY_AGAIN:			//再来一局
		SD_music_button();		//播放按键音效
		if (SD.Gameing)			//如果正处于游戏状态
			SD_Game_Stop();			//隐藏游戏区域的数字
		if (MessageBox(hwnd, _T("是否重开一局？"), _T("数独"), MB_OKCANCEL) == IDOK)
		{
			SD_Game_Init();				//初始化游戏
		}
		else if (SD.Gameing)			//如果正处于游戏状态
			SD_Game_Start();		//继续游戏
		break;
	case GAME_HINT:				//提示
		if (SD.Init[game_i][game_j] == 0 && SD.Linputflag == 1)
		{
			SD_music_button();		//播放按键音效
			if (SD_hint(game_x, game_y, game_i, game_j))//左键输入状态才可调用“提示”函数
				return 1;
		}
		break;
	case GAME_SET:				//设置
		SD_music_button();		//播放按键音效
		if (SD.Gameing)			//如果正处于游戏状态
			SD_Game_Stop();			//隐藏游戏区域的数字
		if (MessageBox(hwnd, _T("是否进入设置界面？本局游戏进度不会保存！！！"), _T("数独"), MB_OKCANCEL) == IDOK)
		{
			SD_Set_game();
			if (SD_verify())
				return 1;
		}
		else if (SD.Gameing)			//如果正处于游戏状态
			SD_Game_Start();		//继续游戏
		break;
	}
	}
}
