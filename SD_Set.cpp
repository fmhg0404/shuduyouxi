#include "SD_Set.h"
/*	自定义设置函数
*	简介：	供用户自行定义初始值，该界面只允许输入操作，不允许标记操作，其余功能和游戏主体函数类似
*	参数：	无
*	返回值：无
*/
void SD_Set_self(void)
{
	u_16 game_x = 801, game_y = 601;
	u_8 game_i = 0, game_j = 0;
	wchar_t input_num[10];			//接收输入信息
	u_8 set_time = 20;				//转换为整型数据，记录设置时间
	SD_Show_use();			//打印界面
	swprintf_s(str, _T("%.2d : %.2d : %.2d"), set_time, 0, 0);	//修改时间界面
	drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	SD.game_flag = EMPTY;				//清除功能区的标志
	SD.Linputflag = 0;					//关闭输入状态
	SD.Rinputflag = 0;					//关闭标记状态
	SD.Gameing = 0;						//清除正在游戏标志
	SD.New_state = 1;					//重置检测输入位置新状态
	SD.Main_Interface = 1;				//正处于主界面或自定义界面
	SD.Set_Self_Inerface = 1;			//处于用户自定义界面
	SD.number = 0;						//清除选择的赋值
	TIME.start = 0;				//清除开始时间
	TIME.last = 0;				//清除终止时间
	TIME.temp = 0;				//清除时间段记录
	TIME.total = 0;					//清除游戏时间
	SD.Mouse_flag = 0;					//清除鼠标标志，用于记录左键还是右键按下
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
		{
			SD.Init[i][j] = SD.game[i][j] = SD.solve[i][j] = 0;		//数组清空
			for (u_8 k = 0; k < 10; k++)
				SD.right_data[i][j][k] = 0;			//清空右击标记
		}
	while (1)
	{
		//清除标志
		SD.game_flag = EMPTY;
		//接收鼠标信息
		if (peekmessage(&mouse_msg, EX_MOUSE))
			if (mouse_msg.message == WM_LBUTTONDOWN)
				SD_Count_x_y(&game_x, &game_y, &game_i, &game_j);	//计算鼠标点击坐标
		//接收按键信息
		Scan_Key(&game_x, &game_y, &game_i, &game_j);
		//检测当前该执行什么功能
		switch (SD.game_flag)
		{
		case GAME_AREA:			//游戏区域
			if (SD.Linputflag == 1)		//如果处于输入状态，显示白色“输入”图片
				putimage(game_x, game_y, &numimg[10]);
			else //如果是非输入状态，显示原值图片
				putimage(game_x, game_y, &numimg[SD.game[game_i][game_j]]);
			break;
		case CHOOSE_AREA:			//选择区域
			if (SD.Linputflag == 1)		//处于左击输入状态
			{
				SD_music_innum();		//播放输入音效
				SD.game[game_i][game_j] = 0;	//输入前将该位置的值清零（避免修改时重复输入同一个值弹出对话框）
				if (SD_detection(game_i, game_j, SD.number) == 0) {	//不冲突
					SD.solve[game_i][game_j] = SD.game[game_i][game_j] = SD.number;	//将三个数组都进行复制
					putimage(game_x, game_y, &numimg[SD.number]);		//输出对应图片
					SD.Linputflag = 1;		//输入完后保持输入状态
				}
			}
			break;
		case GAME_CLEAR:			//清除按钮
			if (SD.Linputflag == 1)
			{		//清除鼠标左键输入状态
				SD_music_button();		//播放按键音效
				SD.solve[game_i][game_j] = SD.game[game_i][game_j] = 0;
				putimage(game_x, game_y, &numimg[0]);
				SD.Linputflag = 1;		//清零后保持输入状态
			}
			break;
		case SET_TIME:				//设置时间
			SD_music_button();		//播放按键音效
			InputBox(input_num, 10, L"请输入设定时间：\n范围：1 - 60 min（整数）\n输入不合法默认为20", L"设置时间", L"20", true);
			set_time = _wtoi(input_num);
			if (set_time <= 0 || set_time >= 60)			//输入超出范围
			{
				swprintf_s(str, _T("%.2d : %.2d : %.2d"), 20, 0, 0);
				drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
				SD.degree_time = 20;			//默认时间为25分钟
			}
			else
			{
				swprintf_s(str, _T("%.2d : %.2d : %.2d"), set_time, 0, 0);
				drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
				SD.degree_time = set_time;
			}
			break;
		case SET_SELF_YES:				//确定
			SD_music_button();		//播放按键音效
			if (SD_unlock(SD.solve) == 0) {		//无解
				MessageBox(hwnd, _T("自定义矩阵无解!将跳转到设置界面！"), _T("自定义"), MB_OK);
				SD_Set_game();
				return;		//避免无意义递归，直接返回
			}
			if (MessageBox(hwnd, _T("确认自定义完成"), _T("自定义"), MB_OKCANCEL) == 1)
			{
				for (u_8 i = 0; i < 9; i++)		//将SD.init数组初始化
					for (u_8 j = 0; j < 9; j++)
						SD.Init[i][j] = SD.game[i][j];
				SD_Show_main();
				SD.Set_Self_Inerface = 0;	//不处于自定义设置界面
				SD.Linputflag = 0;				//关闭输入状态
				return;		//直接跳出
			}
			break;
		}
	}
}

/*	“设置”功能函数
*	简介：	进入设置界面，实现四种模式对应的功能
*	参数：	无
*	返回值：无
*/
void SD_Set_game(void)
{
	u_16 game_x = 0, game_y = 0;
	u_8 game_i = 0, game_j = 0;
	SD.Main_Interface = 0;					//进入设置界面
	SD_Show_set();				//输出显示设置界面
	while (1)
	{
		//清除标志
		SD.game_flag = EMPTY;
		if (peekmessage(&mouse_msg, EX_MOUSE))
		{
			if (mouse_msg.message == WM_LBUTTONDOWN)
				//计算鼠标点击坐标
				SD_Count_x_y(&game_x, &game_y, &game_i, &game_j);
		}
		//接收按键信息
		Scan_Key(&game_x, &game_y, &game_i, &game_j);
		//检测当前该执行什么功能
		switch (SD.game_flag)
		{
		case SET_EASY:				//简单模式
			SD_music_button();		//播放按键音效
			SD.degree = 23;
			SD.degree_time = 20;
			SD_Game_Init();
			return;
		case SET_HARD:				//困难模式
			SD_music_button();		//播放按键音效
			SD.degree = 18;
			SD.degree_time = 12;
			SD_Game_Init();
			return;
		case SET_HARDEST:			//炼狱模式
			SD_music_button();		//播放按键音效
			SD.degree = 15;
			SD.degree_time = 8;
			SD_Game_Init();
			return;
		case SET_SELF:				//自定义模式
			SD_music_button();		//播放按键音效
			SD_Set_self();
			return;
		}
	}
}
