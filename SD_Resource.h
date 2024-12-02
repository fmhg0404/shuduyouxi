#ifndef __SD_RESOURCE_H__
#define __SD_RESOURCE_H__

typedef unsigned char u_8;
typedef unsigned short u_16;
typedef unsigned int u_32;

//头文件引用
#include <graphics.h>
#include <mmsystem.h>
#include <time.h>
#include "SD_Getkey.h"
#include "SD_Init.h"
#include "SD_Mouse.h"
#include "SD_Music.h"
#include "SD_Play.h"
#include "SD_Remind.h"
#include "SD_Set.h"
#include "SD_Show.h"
#include "SD_Solve.h"

//关闭命令行窗口
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#pragma comment(lib,"winmm.lib")

//宏定义
#define WINDOW_SIZE_L          800//绘制窗口长度
#define WINDOW_SIZE_H          600//绘制窗口宽度

#define GAME_BAKROUD_X         290//游戏区域背景起始位置x轴
#define GAME_BAKROUD_Y         90//游戏区域背景起始位置Y轴
#define GAME_BACKGROUND_SIZE   450//游戏区域背景图片尺寸
#define GAME_START_X           300//游戏区域数字起始位置x轴
#define GAME_START_Y           100//游戏区域数字起始位置y轴
#define GAME_PICTURE_SIZE      45//游戏区域数字图片尺寸
#define GAME_INTERVAL          2//游戏区域数字图片间隔

#define CHOOSE_START_X         180//选择区域起始位置x轴
#define CHOOSE_START_Y         100//选择区域起始位置y轴
#define CHOOSE_PICTURE_SIZE    30//选择区域图片尺寸

#define RIGHT_PICTURE_SIZE     15//右击图片显示尺寸

#define TIME_SHOW_X            590//时间显示区域起始位置x轴
#define TIME_SHOW_Y            55//时间显示区域起始位置y轴
#define TIME_SHOW_L            150//时间显示区域长度
#define TIME_SHOW_H            30//时间显示区域宽度

#define BUTTON_MSTART_X        80//主界面按钮起始位置x轴
#define BUTTON_MSTART_Y        250//主界面按钮起始位置y轴
#define BUTTON_MAIN_L          130//主界面按钮尺寸长
#define BUTTON_MAIN_H          50//主界面按钮尺寸宽
#define BUTTON_MINTERVAL       30//主界面按钮间隔

#define BUTTON_SSTART_X         300//设置界面按钮起始位置x轴
#define BUTTON_SSTART_Y         150//设置界面按钮起始位置y轴
#define BUTTON_SET_L           200//设置界面按钮尺寸长
#define BUTTON_SET_H           70//设置界面按钮尺寸宽
#define BUTTON_SINTERVAL       30//设置界面按钮间隔



//游戏功能
typedef enum gameflag
{
	EMPTY,
	GAME_START,
	GAME_STOP,
	GAME_AREA,
	CHOOSE_AREA,
	GAME_CLEAR,
	PLAY_AGAIN,
	GAME_HINT,
	GAME_SET,
	SET_EASY,
	SET_HAND,
	SET_HARDEST,
	SET_SELF,
	SET_BACK,
	SET_TIME,
	SET_SELF_YES
}GAME_FLAG;

//输入位置的移动
typedef enum move
{
	NOT_MOVE,
	LEFT,
	UP,
	RIGHT,
	DOWN,
}IN_MOVE;

//处于哪个界面
typedef enum Interface {
	MAIN,
	SET,
	SET_USE
}INT_FACE;

//结构体定义
typedef struct sudoku
{
	u_8 init[9][9] = { 0 };
	u_8 solve[9][9] = { 0 };
	u_8 game[9][9] = { 0 };
	u_8 right_date[9][9][10] = { 0 };

	GAME_FLAG game_flag = EMPTY;
	IN_MOVE game_insite_move = NOT_MOVE;
	bool Linputflag = 0;
	bool Rinputflag = 0;
	bool Gameing = 0;
	bool New_state = 1;
	INT_FACE INT_face = MAIN;

	bool Mouse_flag = 0;

	u_8 number = 0;
	u_8 degree = 23;
	u_8 degree_time = 20;
}SHUDU;

//游戏时间
typedef struct game_time
{
	u_32 start = 0;
	u_32 last = 0;
	u_32 temp = 0;
	u_32 total = 0;
}GAME_TIME;

//变量声明
extern SHUDU SD;
extern IMAGE numimg[11], rightimg[11], button[11], choose[10], background[2];    //存储各类图片
extern BYTE LpKeyState_sd[256];
extern ExMessage mouse_msg;
extern HWND hwnd;
extern RECT r;
extern TCHAR str[30];
extern GAME_TIME TIME;


void SD_import(void);

#endif;