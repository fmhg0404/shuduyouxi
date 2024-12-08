#include "SD_Remind.h"

/*	检测输入值是否满足数独规则
*	简介：	检测当前输入单元格所在的小矩阵、行、列中是否存在与输入数值相同的值
*	参数：	gamei	:输入位置对应数组的横坐标
*			gamej	:输入位置对应数组的纵坐标
*			n		:选择区输入的值
*	返回值：冲突返回1，不冲突返回0
*/
bool SD_detection(u_8 game_i, u_8 game_j, u_8 n)
{
	TCHAR remind_str[20];
	for (u_8 i = game_i / 3 * 3; i < game_i / 3 * 3 + 3; i++)
	{
		for (u_8 j = game_j / 3 * 3; j < game_j / 3 * 3 + 3; j++)
		{
			if (SD.game[i][j] == n) {	//判断该小矩阵内是否有重复的数
				swprintf_s(remind_str, _T("该矩阵已存在数字 %d !"), n);
				MessageBox(hwnd, remind_str, _T("输入警告"), MB_OK);
				return 1;
			}
		}
	}
	for (int j = 0; j < 9; j++)
	{	//判断该行是否有重复的数
		if (SD.game[game_i][j] == n)
		{
			swprintf_s(remind_str, _T("该行已存在数字 %d !"), n);
			MessageBox(hwnd, remind_str, _T("输入警告"), MB_OK);
			return 1;
		}
	}
	for (int i = 0; i < 9; i++)
	{	//判断该列是否有重复的数
		if (SD.game[i][game_j] == n)
		{
			swprintf_s(remind_str, _T("该列已存在数字 %d !"), n);
			MessageBox(hwnd, remind_str, _T("输入警告"), MB_OK);
			return 1;
		}
	}
	return 0;
}

/*	“提示”按钮功能实现
*	简介：	每执行一次就根据用户当前数组值更新一次最优解，若无解则通过消息对话框反馈
*	参数：	game_x	:单元格左上角图片输出横坐标
*			game_y	:单元格左上角图片输出纵坐标
*			game_i	:单元格对应数组横坐标
*			game_j	:单元格对应数组纵坐标
*	返回值：提示后游戏胜利返回1，无解或游戏没结束返回0
*/
bool SD_hint(u_16 game_x, u_16 game_y, u_8 game_i, u_8 game_j)
{
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
			SD.solve[i][j] = SD.game[i][j];	//更新目前游戏数组值
	if (SD_unlock(SD.solve) == 1)	//调用unlock_sd()函数将其解出
	{
		SD.game[game_i][game_j] = SD.solve[game_i][game_j];		//给出提示值
		putimage(game_x, game_y, &numimg[SD.game[game_i][game_j]]);		//输出对应图片
		SD.Linputflag = 0;		//左键输入标记清零
		for (u_8 n = 0; n < 10; n++)	//右击区域标记清零
			SD.right_data[game_i][game_j][n] = 0;
		if (SD_verify())		//如果提示值为最后一个值则游戏胜利，直接返回到主函数
			return 1;
	}
	else
	{	//若无解则提示用户修改之前输入值
		MessageBox(hwnd, _T("无解!请将上一值修改或清除后重试！"), _T("提示警告"), MB_OK);
		if (SD.right_data[game_i][game_j][9] != 0)	//如果有右击标志则复原
			right_mouse_sign(game_x, game_y, game_i, game_j);
	}
	return 0;		//提示值不是最后一个或无解则返回0
}

