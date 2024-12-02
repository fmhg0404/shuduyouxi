#include "SD_Show.h"

//����
//���Դ��
void SD_Show_mask(void)
{
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
			putimage(GAME_START_X + j * (GAME_PICTURE_SIZE + GAME_INTERVAL) + j / 3 * 4, GAME_START_Y + i * (GAME_PICTURE_SIZE + GAME_INTERVAL) + i / 3 * 4, &numimg[0]);
}

//�Զ������
void SD_Show_use(void)
{
	putimage(0, 0, &background[0]);
	putimage(GAME_BAKROUD_X, GAME_BAKROUD_Y, &background[1]);
	//ѡ������
	for (u_8 i = 0; i < 3; i++)
		for (u_8 j = 0; j < 3; j++)
			putimage(CHOOSE_START_X + j * (CHOOSE_PICTURE_SIZE + 1), CHOOSE_START_Y + i * (CHOOSE_PICTURE_SIZE +  1), &choose[j + 3 *i]);
	putimage(CHOOSE_START_X, CHOOSE_START_Y + 3 * (CHOOSE_PICTURE_SIZE + 1), &choose[9]);
	//��ť����
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y, &button[5]);
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y + 2 * (BUTTON_MAIN_H +BUTTON_MINTERVAL), &button[6]);
	SD_Show_mask();
	//ʱ����ʾ����
	
	setbkcolor(getpixel(690, 20));
	drawtext(_T("ʣ��ʱ��"), &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	swprintf_s(str, _T("%d : %d : %d"), 20, 12, 13);
	drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

}

//���ý���
void SD_Show_set(void)
{
	putimage(0, 0, &background[0]);
	for (u_8 i = 0; i < 4; i++)
	{
		putimage(BUTTON_SSTART_X, BUTTON_SSTART_Y + i * (BUTTON_SET_H + BUTTON_SINTERVAL), &button[7 + i]);
	}
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


