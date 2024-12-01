#ifndef __SD_RESOURCE_H__
#define __SD_RESOURCE_H__

//ͷ�ļ�����
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

//�ر������д���
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


//�궨��
#define WINDOW_SIZE_L          800//���ƴ��ڳ���
#define WINDOW_SIZE_H          600//���ƴ��ڿ���

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
#define TIME_SHOW_H            30//ʱ����ʾ�������

#define BUTTON_MSTART_X        80//�����水ť��ʼλ��x��
#define BUTTON_MSTART_Y        250//�����水ť��ʼλ��y��
#define BUTTON_MAIN_L          130//�����水ť�ߴ糤
#define BUTTON_MAIN_H          50//�����水ť�ߴ��
#define BUTTON_MINTERVAL       30//�����水ť���

#define BUTTON_START_X         300//���ý��水ť��ʼλ��x��
#define BUTTON_START_Y         150//���ý��水ť��ʼλ��y��
#define BUTTON_SET_L           200//���ý��水ť�ߴ糤
#define BUTTON_SET_H           70//���ý��水ť�ߴ��
#define BUTTON_SINTERVAL       30//���ý��水ť���
#endif