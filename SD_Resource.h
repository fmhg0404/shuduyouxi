#ifndef __SD_RESOURCE_H__
#define __SD_RESOURCE_H__

//头文件引用
#include <graphics.h>
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

#define BUTTON_START_X         300//设置界面按钮起始位置x轴
#define BUTTON_START_Y         150//设置界面按钮起始位置y轴
#define BUTTON_SET_L           200//设置界面按钮尺寸长
#define BUTTON_SET_H           70//设置界面按钮尺寸宽
#define BUTTON_SINTERVAL       30//设置界面按钮间隔
#endif