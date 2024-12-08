#ifndef __SD_RESOURCE_H__
#define __SD_RESOURCE_H__

//�����ض���
typedef unsigned char	u_8;
typedef unsigned short	u_16;
typedef unsigned int	u_32;

//ͷ�ļ�����
#include <graphics.h>		//Easyx��
#include <mmsystem.h>		//��ý���
#include <time.h>			//ʱ���(���������)
#include "SD_Getkey.h"
#include "SD_Init.h"
#include "SD_Mouse.h"
#include "SD_Music.h"
#include "SD_Play.h"
#include "SD_Remind.h"
#include "SD_Set.h"
#include "SD_Show.h"
#include "SD_Solve.h"

//�ر������д��ڣ���main������Ϊ��ʼ����
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib,"winmm.lib")				//���ؾ�̬��

//�궨��
#define Key_Down(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0)		//��������
#define Key_Up(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0 : 1)		//��������
//ÿ�μ��ǰ���Ƚ�256 ��������Կ��״̬���Ƶ�ָ���Ļ�����(LpKeyState_sd)��Ȼ���ټ��Num LK��״̬
#define Num_LK		(GetKeyboardState(LpKeyState_sd)?((LOBYTE(LpKeyState_sd[144])) ? 1 : 0):0)

#define WINDOW_SIZE_L			800		//���ƴ��ڳ���
#define	WINDOW_SIZE_H			600		//���ƴ��ڿ��

#define	GAME_BAKROUD_X			290		//��Ϸ���򱳾���ʼλ��x��
#define	GAME_BAKROUD_Y			90		//��Ϸ���򱳾���ʼλ��y��
#define	GAME_BACKGROUND_SIZE	450		//��Ϸ���򱳾�ͼƬ�ߴ�
#define	GAME_START_X			300		//��Ϸ����������ʼλ��x��
#define	GAME_START_Y			100		//��Ϸ����������ʼλ��y��
#define	GAME_PICTURE_SIZE		45		//��Ϸ��������ͼƬ�ߴ�
#define	GAME_INTERVAL			2		//��Ϸ��������ͼƬ���

#define	CHOOSE_START_X			180		//ѡ��������ʼλ��x��
#define	CHOOSE_START_Y			100		//ѡ��������ʼλ��y��
#define	CHOOSE_PICTURE_SIZE		30		//ѡ������ͼƬ�ߴ�

#define	RIGHT_PICTURE_SIZE		15		//�һ�ͼƬ��ʾ�ߴ�

#define	TIME_SHOW_X				590		//ʱ����ʾ������ʼλ��x��
#define	TIME_SHOW_Y				55		//ʱ����ʾ������ʼλ��y��
#define	TIME_SHOW_L				150		//ʱ����ʾ���򳤶�
#define	TIME_SHOW_H				30		//ʱ����ʾ������

#define	BUTTON_MSTART_X			80		//�����水ť��ʼλ��x��
#define	BUTTON_MSTART_Y			250		//�����水ť��ʼλ��y��
#define	BUTTON_MAIN_L			130		//�����水ť�ߴ糤
#define	BUTTON_MAIN_H			50		//�����水ť�ߴ��
#define	BUTTON_MINTERVAL		30		//�����水ť��� 

#define	BUTTON_SSTART_X			300		//���ý��水ť��ʼλ��x��
#define	BUTTON_SSTART_Y			150		//���ý��水ť��ʼλ��y��
#define	BUTTON_SET_L			200		//���ý��水ť�ߴ糤
#define	BUTTON_SET_H			70		//���ý��水ť�ߴ��
#define	BUTTON_SINTERVAL		30		//���ý��水ť���

//��Ϸ����
typedef enum gameflag
{
	EMPTY,				//�޲���
	GAME_START,			//��ʼ��Ϸ
	GAME_STOP,			//ֹͣ��Ϸ
	GAME_AREA,			//��Ϸ����
	CHOOSE_AREA,		//ѡ������
	GAME_CLEAR,			//��������
	PLAY_AGAIN,			//����һ��
	GAME_HINT,			//��ʾ
	GAME_SET, 			//����
	SET_EASY,			//��ģʽ
	SET_HARD,			//����ģʽ
	SET_HARDEST,		//����ģʽ
	SET_SELF,			//�Զ���ģʽ
	SET_BACK,			//���ý��淵��
	SET_TIME,			//�Զ�������ʱ��
	SET_SELF_YES		//ȷ��
}GAME_FLAG;

//����λ�õ��ƶ�
typedef enum move
{
	NOT_MOVE,			//����λ��û�ı�
	LEFT,				//����λ������
	UP,					//����λ������
	RIGHT,				//����λ������
	DOWN,				//����λ������
}IN_MOVE;

//�ṹ�嶨��
typedef struct sudoku
{
	u_8	Init[9][9] = { 0 };				//��ʼ������
	u_8 solve[9][9] = { 0 };			//������
	u_8 game[9][9] = { 0 };				//��Ϸ����
	u_8 right_data[9][9][10] = { 0 };	//�һ�����

	GAME_FLAG game_flag = EMPTY;		//��������־
	IN_MOVE game_insite_move = NOT_MOVE;//�ƶ���־
	bool Linputflag = 0;				//����״̬
	bool Rinputflag = 0;				//���״̬
	bool Gameing = 0;					//������Ϸ
	bool New_state = 1;					//�Ƿ�����״̬
	//	Main_Interface	Set_Self_Inerface
	//		0					0		�������ý���
	//		0					1		�������ý���
	//		1					0		����������
	//		1					1		�����û��Զ������
	bool Main_Interface = 1;			//��������������Զ������
	bool Set_Self_Inerface = 0;			//�������û��Զ������

	bool Mouse_flag = 0;				//0��ʾ��������1��ʾ����һ�

	u_8 number = 0;						//��¼ѡ�����������ֵ
	u_8 degree = 23;					//������Ϸ�Ѷ�(��ʾ��֪��)
	u_8 degree_time = 20;				//������Ϸ�Ѷ�(������Ϸʱ��)
}SHUDU;

//��Ϸʱ��
typedef struct game_time
{
	u_32 start = 0;			//��ʼʱ��
	u_32 last = 0;			//����ʱ��
	u_32 temp = 0;			//��¼ʱ���
	u_32 total = 0;			//����Ϸʱ��

}GAME_TIME;

//��������
extern SHUDU SD;		//������Ϸ���Ʊ���
extern IMAGE numimg[11], rightimg[11], button[11], choose[10], background[2];		//�洢����ͼƬ
extern BYTE LpKeyState_sd[256];			//�洢���ⰴ����Կ Key code
extern ExMessage mouse_msg;				//�洢�����Ϣ
extern HWND hwnd;						//���ھ��
extern RECT r;							//ʱ����ʾ������
extern TCHAR str[30];					//�洢��ʾ���ַ�������
extern GAME_TIME TIME;					//�洢ʱ��

//��������
void SD_import(void);


#endif

