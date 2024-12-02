#ifndef __SD_RESOURCE_H__
#define __SD_RESOURCE_H__

typedef unsigned char u_8;
typedef unsigned short u_16;
typedef unsigned int u_32;

//ͷ�ļ�����
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

//�ر������д���
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#pragma comment(lib,"winmm.lib")

//�궨��
#define WINDOW_SIZE_L          800//���ƴ��ڳ���
#define WINDOW_SIZE_H          600//���ƴ��ڿ��

#define GAME_BAKROUD_X         290//��Ϸ���򱳾���ʼλ��x��
#define GAME_BAKROUD_Y         90//��Ϸ���򱳾���ʼλ��Y��
#define GAME_BACKGROUND_SIZE   450//��Ϸ���򱳾�ͼƬ�ߴ�
#define GAME_START_X           300//��Ϸ����������ʼλ��x��
#define GAME_START_Y           100//��Ϸ����������ʼλ��y��
#define GAME_PICTURE_SIZE      45//��Ϸ��������ͼƬ�ߴ�
#define GAME_INTERVAL          2//��Ϸ��������ͼƬ���

#define CHOOSE_START_X         180//ѡ��������ʼλ��x��
#define CHOOSE_START_Y         100//ѡ��������ʼλ��y��
#define CHOOSE_PICTURE_SIZE    30//ѡ������ͼƬ�ߴ�

#define RIGHT_PICTURE_SIZE     15//�һ�ͼƬ��ʾ�ߴ�

#define TIME_SHOW_X            590//ʱ����ʾ������ʼλ��x��
#define TIME_SHOW_Y            55//ʱ����ʾ������ʼλ��y��
#define TIME_SHOW_L            150//ʱ����ʾ���򳤶�
#define TIME_SHOW_H            30//ʱ����ʾ������

#define BUTTON_MSTART_X        80//�����水ť��ʼλ��x��
#define BUTTON_MSTART_Y        250//�����水ť��ʼλ��y��
#define BUTTON_MAIN_L          130//�����水ť�ߴ糤
#define BUTTON_MAIN_H          50//�����水ť�ߴ��
#define BUTTON_MINTERVAL       30//�����水ť���

#define BUTTON_SSTART_X         300//���ý��水ť��ʼλ��x��
#define BUTTON_SSTART_Y         150//���ý��水ť��ʼλ��y��
#define BUTTON_SET_L           200//���ý��水ť�ߴ糤
#define BUTTON_SET_H           70//���ý��水ť�ߴ��
#define BUTTON_SINTERVAL       30//���ý��水ť���



//��Ϸ����
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

//����λ�õ��ƶ�
typedef enum move
{
	NOT_MOVE,
	LEFT,
	UP,
	RIGHT,
	DOWN,
}IN_MOVE;

//�����ĸ�����
typedef enum Interface {
	MAIN,
	SET,
	SET_USE
}INT_FACE;

//�ṹ�嶨��
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

//��Ϸʱ��
typedef struct game_time
{
	u_32 start = 0;
	u_32 last = 0;
	u_32 temp = 0;
	u_32 total = 0;
}GAME_TIME;

//��������
extern SHUDU SD;
extern IMAGE numimg[11], rightimg[11], button[11], choose[10], background[2];    //�洢����ͼƬ
extern BYTE LpKeyState_sd[256];
extern ExMessage mouse_msg;
extern HWND hwnd;
extern RECT r;
extern TCHAR str[30];
extern GAME_TIME TIME;


void SD_import(void);

#endif;