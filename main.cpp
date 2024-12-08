#include "SD_Resource.h"

/*	主函数
*	简介：	程序入口
*	参数：	无
*	返回值：程序正常结束返回0
*/
int main(void)
{
	TCHAR Show_vitory[50];			//存储交互信息
	hwnd = initgraph(WINDOW_SIZE_L, WINDOW_SIZE_H);		//创建绘图窗口
	SD_music_import();			//播放背景音乐
	SD_import();			//导入资源文件
	SD_Game_Init();			//初始化游戏参数
	while (1)
	{				//死循环，玩家关闭窗口才退出
		if (SD_Play_Game())
		{		//边游戏边判断
			SD_music_victory();		//播放胜利音效
			TIME.total = SD.degree_time * 60 * 1000 - TIME.total;		//此时TIME.total为总游戏时间
			swprintf_s(Show_vitory, _T("恭喜您！游戏胜利!\n用时：%.2d : %.2d : %.2d"), TIME.total / 1000 / 60, TIME.total / 1000 % 60, TIME.total / 10 % 100);
			MessageBox(hwnd, Show_vitory, _T("胜利界面"), MB_OK);	//输出窗口提示
			SD_Game_Init();		//初始化游戏参数
		}
		else
		{
			SD_music_lose();		//播放失败音效
			swprintf_s(Show_vitory, _T("时间到！您没能在规定时间内完成游戏!\n"));
			MessageBox(hwnd, Show_vitory, _T("失败界面"), MB_OK);	//输出窗口提示
			SD_Game_Init();		//初始化游戏参数
		}
	}
	SD_music_close();		//关闭音乐
	closegraph();			//关闭绘图窗口
	return 0;
}