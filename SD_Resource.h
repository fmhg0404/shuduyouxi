#ifndef __SD_RESOURCE_H__
#define __SD_RESOURCE_H__

//类型重定义
typedef unsigned char	u_8;
typedef unsigned short	u_16;
typedef unsigned int	u_32;

//头文件引用
#include <graphics.h>		//Easyx库
#include <mmsystem.h>		//多媒体库
#include <time.h>			//时间库(含随机函数)
#include "SD_Getkey.h"
#include "SD_Init.h"
#include "SD_Mouse.h"
#include "SD_Music.h"
#include "SD_Play.h"
#include "SD_Remind.h"
#include "SD_Set.h"
#include "SD_Show.h"
#include "SD_Solve.h"

//关闭命令行窗口，将main函数设为起始窗口
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib,"winmm.lib")				//加载静态库

//宏定义
#define Key_Down(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0)		//按键按下
#define Key_Up(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0 : 1)		//按键弹起
//每次检测前需先将256 个虚拟密钥的状态复制到指定的缓冲区(LpKeyState_sd)，然后再检测Num LK的状态
#define Num_LK		(GetKeyboardState(LpKeyState_sd)?((LOBYTE(LpKeyState_sd[144])) ? 1 : 0):0)

#define WINDOW_SIZE_L			800		//绘制窗口长度
#define	WINDOW_SIZE_H			600		//绘制窗口宽度

#define	GAME_BAKROUD_X			290		//游戏区域背景起始位置x轴
#define	GAME_BAKROUD_Y			90		//游戏区域背景起始位置y轴
#define	GAME_BACKGROUND_SIZE	450		//游戏区域背景图片尺寸
#define	GAME_START_X			300		//游戏区域数字起始位置x轴
#define	GAME_START_Y			100		//游戏区域数字起始位置y轴
#define	GAME_PICTURE_SIZE		45		//游戏区域数字图片尺寸
#define	GAME_INTERVAL			2		//游戏区域数字图片间隔

#define	CHOOSE_START_X			180		//选择区域起始位置x轴
#define	CHOOSE_START_Y			100		//选择区域起始位置y轴
#define	CHOOSE_PICTURE_SIZE		30		//选择区域图片尺寸

#define	RIGHT_PICTURE_SIZE		15		//右击图片显示尺寸

#define	TIME_SHOW_X				590		//时间显示区域起始位置x轴
#define	TIME_SHOW_Y				55		//时间显示区域起始位置y轴
#define	TIME_SHOW_L				150		//时间显示区域长度
#define	TIME_SHOW_H				30		//时间显示区域宽度

#define	BUTTON_MSTART_X			80		//主界面按钮起始位置x轴
#define	BUTTON_MSTART_Y			250		//主界面按钮起始位置y轴
#define	BUTTON_MAIN_L			130		//主界面按钮尺寸长
#define	BUTTON_MAIN_H			50		//主界面按钮尺寸宽
#define	BUTTON_MINTERVAL		30		//主界面按钮间隔 

#define	BUTTON_SSTART_X			300		//设置界面按钮起始位置x轴
#define	BUTTON_SSTART_Y			150		//设置界面按钮起始位置y轴
#define	BUTTON_SET_L			200		//设置界面按钮尺寸长
#define	BUTTON_SET_H			70		//设置界面按钮尺寸宽
#define	BUTTON_SINTERVAL		30		//设置界面按钮间隔

//游戏功能
typedef enum gameflag
{
	EMPTY,				//无操作
	GAME_START,			//开始游戏
	GAME_STOP,			//停止游戏
	GAME_AREA,			//游戏区域
	CHOOSE_AREA,		//选择区域
	GAME_CLEAR,			//数字清零
	PLAY_AGAIN,			//再来一局
	GAME_HINT,			//提示
	GAME_SET, 			//设置
	SET_EASY,			//简单模式
	SET_HARD,			//困难模式
	SET_HARDEST,		//炼狱模式
	SET_SELF,			//自定义模式
	SET_BACK,			//设置界面返回
	SET_TIME,			//自定义设置时间
	SET_SELF_YES		//确定
}GAME_FLAG;

//输入位置的移动
typedef enum move
{
	NOT_MOVE,			//输入位置没改变
	LEFT,				//输入位置左移
	UP,					//输入位置上移
	RIGHT,				//输入位置右移
	DOWN,				//输入位置下移
}IN_MOVE;

//结构体定义
typedef struct sudoku
{
	u_8	Init[9][9] = { 0 };				//初始化数组
	u_8 solve[9][9] = { 0 };			//解数组
	u_8 game[9][9] = { 0 };				//游戏数组
	u_8 right_data[9][9][10] = { 0 };	//右击数组

	GAME_FLAG game_flag = EMPTY;		//功能区标志
	IN_MOVE game_insite_move = NOT_MOVE;//移动标志
	bool Linputflag = 0;				//输入状态
	bool Rinputflag = 0;				//标记状态
	bool Gameing = 0;					//正在游戏
	bool New_state = 1;					//是否是新状态
	//	Main_Interface	Set_Self_Inerface
	//		0					0		处于设置界面
	//		0					1		处于设置界面
	//		1					0		处于主界面
	//		1					1		处于用户自定义界面
	bool Main_Interface = 1;			//正处于主界面或自定义界面
	bool Set_Self_Inerface = 0;			//正处于用户自定义界面

	bool Mouse_flag = 0;				//0表示鼠标左击，1表示鼠标右击

	u_8 number = 0;						//记录选择区域输入的值
	u_8 degree = 23;					//调整游戏难度(显示已知数)
	u_8 degree_time = 20;				//调整游戏难度(限制游戏时间)
}SHUDU;

//游戏时间
typedef struct game_time
{
	u_32 start = 0;			//开始时间
	u_32 last = 0;			//结束时间
	u_32 temp = 0;			//记录时间段
	u_32 total = 0;			//总游戏时间

}GAME_TIME;

//变量声明
extern SHUDU SD;		//整体游戏控制变量
extern IMAGE numimg[11], rightimg[11], button[11], choose[10], background[2];		//存储各类图片
extern BYTE LpKeyState_sd[256];			//存储虚拟按键密钥 Key code
extern ExMessage mouse_msg;				//存储鼠标信息
extern HWND hwnd;						//窗口句柄
extern RECT r;							//时间显示的区域
extern TCHAR str[30];					//存储显示的字符串内容
extern GAME_TIME TIME;					//存储时间

//函数声明
void SD_import(void);


#endif

