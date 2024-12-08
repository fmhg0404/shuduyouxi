#include "SD_Show.h"

//����
//�������
void SD_Show_mask(void)
{
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
			putimage(GAME_START_X + j * (GAME_PICTURE_SIZE + GAME_INTERVAL) + j / 3 * 4, GAME_START_Y + i * (GAME_PICTURE_SIZE + GAME_INTERVAL) + i / 3 * 4, &numimg[0]);
}

void SD_Show_use(void)
{
	putimage(0, 0, &background[0]);				//���汳��
	putimage(GAME_BAKROUD_X, GAME_BAKROUD_Y, &background[1]);		//��Ϸ����
	for (u_8 i = 0; i < 3; i++)
		for (u_8 j = 0; j < 3; j++)
		{
			putimage(CHOOSE_START_X + j * CHOOSE_PICTURE_SIZE + j, CHOOSE_START_Y + i * CHOOSE_PICTURE_SIZE + i, &choose[3 * i + j]);
		}
	putimage(CHOOSE_START_X, CHOOSE_START_Y + 3 * (CHOOSE_PICTURE_SIZE + 1), &choose[9]);
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y, &button[5]);
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y + 2 * (BUTTON_MAIN_H + BUTTON_MINTERVAL), &button[6]);
	//��ʾʱ��
	setbkcolor(getpixel(690, 70));		//��ȡʱ�䱳��ɫ
	drawtext(_T("ʣ��ʱ��: "), &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	TIME.total = SD.degree_time * 60 * 1000;
	swprintf_s(str, _T("%.2d : %.2d : %.2d"), TIME.total / 1000 / 60, TIME.total / 1000 % 60, TIME.total / 10 % 100);
	drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	SD_Show_mask();		//��ʾ����
}


void SD_Show_start(void)
{
	for(u_8 i =0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
		{
			putimage(GAME_START_X + j * (GAME_PICTURE_SIZE + GAME_INTERVAL) + j / 3 * 4, GAME_START_Y + i * (GAME_PICTURE_SIZE + GAME_INTERVAL) + i / 3 * 4, &numimg[SD.game[i][j]]);
			if (SD.Init[i][j] != 0)
				fillcircle(GAME_START_X + j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 4 + 7, GAME_START_Y + i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 4 + 7, 3);	//����Ϊ��Բ�ĵĺ����꣬�����꣬�뾶
			if (SD.right_data[i][j][9] != 0)
				right_mouse_sign(GAME_START_X + j * (GAME_PICTURE_SIZE + GAME_INTERVAL) + j / 3 * 4, GAME_START_Y + i * (GAME_PICTURE_SIZE + GAME_INTERVAL) + i / 3 * 4, i, j);		//����һ����
		}
}

bool SD_Show_time(void)
{
	TIME.last = clock() - TIME.start;
	TIME.total = SD.degree_time * 60 * 1000 - TIME.temp - TIME.last;
	swprintf_s(str, _T("%.2d : %.2d : %.2d"), TIME.total / 1000 / 60, TIME.total /1000 & 60, TIME.total / 10 % 100);
	drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	if (TIME.total == 0)
		return 0;			//������Ϸ�����趨ʱ���Զ��������ж�Ϊ��Ϸʧ��
	return 1;
}



//���ý���
void SD_Show_set(void)
{
	putimage(0, 0, &background[0]);
	for (u_8 i = 0; i < 4; i++)
	{
		putimage(BUTTON_SSTART_X, BUTTON_SSTART_Y + i * (BUTTON_SET_H + BUTTON_SINTERVAL), &button[7 + i]);
	}
	SD.Main_Interface = 0;
}


//������
void SD_Show_main(void)
{
	SD_Show_use();
	for (u_8 i = 0; i < 4; i++)
	{
		putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y + i * (BUTTON_MAIN_H + BUTTON_MINTERVAL), &button[i]);
	}
	
}


