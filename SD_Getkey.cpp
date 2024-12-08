#include "SD_Getkey.h"
/*	按键检测函数
*	简介：	每当一个按键按下后，将该键值对应的key_state[256]数组中的数据写1，直到松开才归0，可防止重复检测
*	参数：	key_code	:要检测的虚拟键值
*	返回值：按键按下返回1，按键弹起返回0
*/
bool get_key(BYTE key_code)		//非阻塞式检测按键是否按下，
{
	static bool key_state[256] = { 0 };		//静态数组存储每个虚拟键的状态
	if (Key_Down(key_code)) {
		if (!key_state[key_code])			//上一次记录为松开状态，这次记录为按下状态
		{
			key_state[key_code] = 1;
			return 1;
		}
	}
	if (Key_Up(key_code))
		if (key_state[key_code])			//上一次记录为按下状态，这次记录为松开状态
			key_state[key_code] = 0;
	return 0;
}

/*	输入位置检测
*	简介：	检测按键输入或标记的第一个位置，每次初始化后按'Q''L''E''R'时，第一个显示位置
*	参数：	game_x	:单元格左上角图片输出横坐标
*			game_y	:单元格左上角图片输出纵坐标
*			game_i	:单元格对应数组横坐标
*			game_j	:单元格对应数组纵坐标
*	返回值：找到第一个位置返回1，没找到返回0
*/
bool Key_place(u_16* game_x, u_16* game_y, u_8* game_i, u_8* game_j)
{
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
			if (SD.Init[i][j] == 0)
			{
				*game_i = i;		//更新数组中的位置
				*game_j = j;
				*game_x = GAME_START_X + (j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL);		//更新图形界面数字输出位置
				*game_y = GAME_START_Y + (i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL);	//x因j改变，y因i改变
				return 1;
			}
	return 0;
}

/*	按键数字按键
*	简介：	检测数字按键是否按下，将接收到的按键值存入SD.number变量中，允许小键盘输入数字
*	参数：	无
*	返回值：有数字按键按下返回1，无数字按键按下返回0
*/
bool Key_number(void)		//扫描数字输入，数字存在SD.number中
{
	if (get_key('1') || get_key('1' + 48) && Num_LK) {
		SD.number = 1;
		return 1;				//检测完直接返回
	}	//数字按键 || (右侧按键Num LK解锁 && 按下按键)
	if (get_key('2') || get_key('2' + 48) && Num_LK) {
		SD.number = 2;
		return 1;
	}
	if (get_key('3') || get_key('3' + 48) && Num_LK) {
		SD.number = 3;
		return 1;
	}
	if (get_key('4') || get_key('4' + 48) && Num_LK) {
		SD.number = 4;
		return 1;
	}
	if (get_key('5') || get_key('5' + 48) && Num_LK) {
		SD.number = 5;
		return 1;
	}
	if (get_key('6') || get_key('6' + 48) && Num_LK) {
		SD.number = 6;
		return 1;
	}
	if (get_key('7') || get_key('7' + 48) && Num_LK) {
		SD.number = 7;
		return 1;
	}
	if (get_key('8') || get_key('8' + 48) && Num_LK) {
		SD.number = 8;
		return 1;
	}
	if (get_key('9') || get_key('9' + 48) && Num_LK) {
		SD.number = 9;
		return 1;
	}
	return 0;			//没检查到按键按下返回0
}

/*	检测主界面的指令按键
*	简介：	检测是否按下设定的命令按键，将按键对应命令赋值到SD.game_flag中
*	参数：	无
*	返回值：有指令按键按下返回1，无指令按键按下返回0
*/
bool Key_main_order(void)
{
	if (SD.Gameing || SD.Set_Self_Inerface)
	{
		if (get_key(8) || get_key(46)) {		//key code编码 Backspace=8	delete=46
			SD.game_flag = GAME_CLEAR;		//清除按钮
			return 1;
		}
		if (get_key('Q') || get_key('L')) {		//翻转输入状态
			if (SD.Mouse_flag == 0)
				SD.Linputflag = !SD.Linputflag;
			else
			{
				SD.Linputflag = 1;
				SD.Rinputflag = 0;
			}
			SD.Mouse_flag = 0;			//相当于鼠标左击
			SD.game_flag = GAME_AREA;			//相当于游戏区域左击
			return 1;
		}
		if (get_key('E') || get_key('R')) {		//翻转标记状态
			if (SD.Mouse_flag == 1)
				SD.Rinputflag = !SD.Rinputflag;
			else
			{
				SD.Rinputflag = 1;
				SD.Linputflag = 0;
			}
			SD.Mouse_flag = 1;			//相当于鼠标右击
			SD.game_flag = GAME_AREA;			//相当于游戏区域右击
			return 1;
		}
		if (get_key('H')) {		//提示按钮、自定义界面确定按钮
			if (SD.Set_Self_Inerface)
				SD.game_flag = SET_SELF_YES;
			else if (SD.Linputflag)
				SD.game_flag = GAME_HINT;
			return 1;
		}
		if (SD.Set_Self_Inerface)
			while (Key_Down(17) && Key_Down(13))		//自定义界面确定按钮，Contral: 17，回车键code : 13
			{
				SD.game_flag = SET_SELF_YES;		//封装的get_key函数无法保存上次按键状态，所有直接用Key_Down()
				return 1;
			}
		if (get_key('T')) {				//自定义界面设置时间
			if (SD.Set_Self_Inerface)
				SD.game_flag = SET_TIME;
			return 1;
		}
	}
	if (get_key('F')) {		//开始、停止按钮
		SD.Gameing = !SD.Gameing;		//将  正在游戏状态  翻转
		if (SD.Gameing)
			SD.game_flag = GAME_START;
		else
			SD.game_flag = GAME_STOP;
		return 1;
	}
	if (get_key('G')) {		//再来一局
		SD.game_flag = PLAY_AGAIN;
		return 1;
	}
	if (get_key('J')) {		//设置
		SD.game_flag = GAME_SET;
		return 1;
	}
	return 0;		//没检测到返回0
}

/*	检测设置界面的指令按键
*	简介：	在设置界面时输入1、2、3、4对应四种模式
*	参数：	无
*	返回值：有指令按键按下返回1，无指令按键按下返回0
*/
bool Key_set_order(void)
{
	if (get_key('1') || get_key('1' + 48) && Num_LK) {
		SD.game_flag = SET_EASY;		//简单模式
		return 1;				//检测完直接返回
	}	//数字按键 || (右侧按键Num LK解锁 && 按下按键)
	if (get_key('2') || get_key('2' + 48) && Num_LK) {
		SD.game_flag = SET_HARD;		//困难模式
		return 1;
	}
	if (get_key('3') || get_key('3' + 48) && Num_LK) {
		SD.game_flag = SET_HARDEST;		//炼狱模式
		return 1;
	}
	if (get_key('4') || get_key('4' + 48) && Num_LK) {
		SD.game_flag = SET_SELF;		//自定义模式
		return 1;
	}
	return 0;		//没检测到返回0
}

/*	检测方向指令按键
*	简介：	方向键对应输入或标记位置的移动，将信息存入SD.game_insite_move变量中
*	参数：	无
*	返回值：有指令按键按下返回1，无指令按键按下返回0
*/
bool Key_move(void)
{
	SD.game_insite_move = NOT_MOVE;			//恢复默认值
	if (get_key(37) || get_key('A')) {	//方向键控制
		SD.game_insite_move = LEFT;//key code编码 方向键 左：37	上：38	右：39	下：40
		return 1;
	}
	if (get_key(38) || get_key('W')) {
		SD.game_insite_move = UP;
		return 1;
	}
	if (get_key(39) || get_key('D')) {
		SD.game_insite_move = RIGHT;
		return 1;
	}
	if (get_key(40) || get_key('S')) {
		SD.game_insite_move = DOWN;
		return 1;
	}
	return 0;
}

/*	计算移动后的位置
*	简介：	通过检测SD.game_insite_move中记录的移动操作，计算出移动后的图片输出位置，和对应数组位置
*	参数：	game_x	:单元格左上角图片输出横坐标
*			game_y	:单元格左上角图片输出纵坐标
*			game_i	:单元格对应数组横坐标
*			game_j	:单元格对应数组纵坐标
*	返回值：有指令按键按下返回1，无指令按键按下返回0
*/
void Inputflag_Move(u_16* game_x, u_16* game_y, u_8* game_i, u_8* game_j)
{
	u_8 i = *game_i;
	u_8 j = *game_j;
	switch (SD.game_insite_move) {
	case LEFT:		//向左搜索
		while (1) {
			j--;		//左移
			if (j > 8) {		//由于使用的u_8类型，当j=0时再执行j--，j的值就会变为255
				j = 8;
				i--;	//左移到边界后上移一行
				if (i > 8)
					i = 8;
			}
			if (SD.Init[i][j] == 0)
				break;
		}
		break;
	case UP:		//向上搜索
		while (1) {
			i--;		//上移
			if (i > 8) {
				i = 8;
				j--;	//上移到边界后左移一列
				if (j > 8)
					j = 8;
			}
			if (SD.Init[i][j] == 0)
				break;
		}
		break;
	case RIGHT:		//向右搜索
		while (1) {
			j++;		//右移
			if (j > 8) {
				j = 0;
				i = (i + 1) % 9;	//右移到边界后下移一行
			}
			if (SD.Init[i][j] == 0)
				break;
		}
		break;
	case DOWN:		//向下搜索
		while (1) {
			i++;		//下移
			if (i > 8) {
				i = 0;
				j = (j + 1) % 9;		//下移到边界后右移一列
			}
			if (SD.Init[i][j] == 0)
				break;
		}
		break;
	}
	if (SD.Linputflag)			//当前为输入状态移动
		if (SD.right_data[*game_i][*game_j][9] == 0) {		//无右击标记
			putimage(*game_x, *game_y, &numimg[SD.game[*game_i][*game_j]]);	//上位置复原
		}
		else
			right_mouse_sign(*game_x, *game_y, *game_i, *game_j);				//右键标记输入状态
	if (SD.Rinputflag)			//当前为标记状态移动
		if (SD.game[*game_i][*game_j] != 0)				//右键状态下只需把上一处的标记状态取消即可
			putimage(*game_x, *game_y, &numimg[SD.game[*game_i][*game_j]]);	//上位置复原
		else
			putimage(*game_x + SD.right_data[*game_i][*game_j][9] % 3 * RIGHT_PICTURE_SIZE, *game_y + SD.right_data[*game_i][*game_j][9] / 3 * RIGHT_PICTURE_SIZE, &rightimg[0]);	//鼠标右击区域输入状态关闭

	*game_x = GAME_START_X + (j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL);		//更新图形界面数字输出位置
	*game_y = GAME_START_Y + (i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL);	//x因j改变，y因i改变
	*game_i = i;		//更新数组中的位置
	*game_j = j;
}

/*	按键检测
*	简介：	根据实际情况调用相应封装的按键函数，由游戏主体函数SD_Play_Game()调用
*	参数：	game_x	:单元格左上角图片输出横坐标
*			game_y	:单元格左上角图片输出纵坐标
*			game_i	:单元格对应数组横坐标
*			game_j	:单元格对应数组纵坐标
*	返回值：有按键按下返回1，无按键按下返回0
*/
void Scan_Key(u_16* game_x, u_16* game_y, u_8* game_i, u_8* game_j)
{
	if (SD.Main_Interface)		//主界面或自定义界面
	{
		if (Key_main_order() && SD.game_flag == GAME_AREA && SD.New_state == 1)	//主界面命令检测
		{
			Key_place(game_x, game_y, game_i, game_j);		//确定第一个输入的位置每次初始化后只执行一次
			SD.New_state = 0;			//新状态置零，下次初始化之前不需要再寻找第一个输入位置
		}
		if (SD.Gameing || SD.Set_Self_Inerface)
			if (SD.Linputflag || SD.Rinputflag)		//输入或标记状态
			{
				if (Key_move())			//输入位置改变了
				{
					Inputflag_Move(game_x, game_y, game_i, game_j);
					SD.game_flag = GAME_AREA;		//在游戏区域操作
				}
				if (Key_number())
				{
					SD.game_flag = CHOOSE_AREA;
				}
			}
	}
	else		//设置界面
	{
		Key_set_order();
	}
}