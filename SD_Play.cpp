#include "SD_Play.h"

//����
void delete_right_num(u_8 game_i, u_8 game_j, u_8 number)
{
	u_16 game_x = 0, game_y = 0;
	for (u_8 j = 0; j < 9; j++)		//������ֵΪnumber�ı��ɾ��
	{
		if (SD.right_data[game_i][j][9] != 0 && SD.right_data[game_i][j][number - 1] == 1)
		{		//Ѱ����Ҫɾ����ǵ�λ��
			SD.right_data[game_i][j][number - 1] = 0;		//��Ӧ�����0
			SD.right_data[game_i][j][9]--;			//��Ǽ���-1
			game_x = GAME_START_X + (j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL);		//����ͼ�ν����������λ��
			game_y = GAME_START_Y + (game_i * GAME_PICTURE_SIZE + game_i * GAME_INTERVAL + game_i / 3 * 2 * GAME_INTERVAL);	//x��j�ı䣬y��i�ı�
			right_mouse_sign(game_x, game_y, game_i, j);		//���������һ�����
		}
	}
	for (u_8 i = 0; i < 9; i++)		//������ֵΪnumber�ı��ɾ��
	{
		if (SD.right_data[i][game_j][9] != 0 && SD.right_data[i][game_j][number - 1] == 1)
		{
			SD.right_data[i][game_j][number - 1] = 0;
			SD.right_data[i][game_j][9]--;
			game_x = GAME_START_X + (game_j * GAME_PICTURE_SIZE + game_j * GAME_INTERVAL + game_j / 3 * 2 * GAME_INTERVAL);		//����ͼ�ν����������λ��
			game_y = GAME_START_Y + (i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL);	//x��j�ı䣬y��i�ı�
			right_mouse_sign(game_x, game_y, i, game_j);
		}
	}
	for (u_8 i = game_i / 3 * 3; i < game_i / 3 * 3 + 3; i++)		//������ֵΪnumber�ı��ɾ��
		for (u_8 j = game_j / 3 * 3; j < game_j / 3 * 3 + 3; j++)
		{
			if (SD.right_data[i][j][9] != 0 && SD.right_data[i][j][number - 1] == 1)
			{
				SD.right_data[i][j][number - 1] = 0;
				SD.right_data[i][j][9]--;
				game_x = GAME_START_X + (j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL);		//����ͼ�ν����������λ��
				game_y = GAME_START_Y + (i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL);	//x��j�ı䣬y��i�ı�
				right_mouse_sign(game_x, game_y, i, j);
			}
		}
}


void SD_Game_Start(void)
{
	SD_Show_start();
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y, &button[4]);
	TIME.start = clock();
}

void SD_Game_Stop(void)
{
	SD.Linputflag = SD.Rinputflag = 0;
	SD_Show_mask();
	putimage(BUTTON_MSTART_X, BUTTON_MSTART_Y, &button[0]);
	TIME.last = clock() - TIME.start;
	TIME.temp += TIME.last;
}


bool SD_Play_Game(void)
{
	u_16 game_x = WINDOW_SIZE_L, game_y = WINDOW_SIZE_H;
	u_8 game_i = 0, game_j = 0;
	while(1)
	{
		//�����־
		SD.game_flag = EMPTY;
	//ʱ�����
		if (SD.Gameing)
		{
			SD_Show_time();
		}	
	//���ɨ��
		if (peekmessage(&mouse_msg, EX_MOUSE))
		{
			if (mouse_msg.message  == WM_LBUTTONDOWN || mouse_msg.message == WM_RBUTTONDOWN)
				SD_Count_x_y(&game_x, &game_y, &game_i, &game_j);
		}
	//����ɨ��
		Scan_Key(&game_x, &game_y, &game_i, &game_j);
	//��Ϸ����
	switch (SD.game_flag)
	{
	case GAME_START:
		SD_music_button();
		SD_Game_Start();
		break;
	case GAME_STOP:
		SD_music_button();
		SD_Game_Stop();
		break;
	case GAME_AREA:
		switch (SD.Mouse_flag)
		{
		case 0:		//��ǰ������
			if (SD.Linputflag == 1)		//�����������״̬����ʾ��ɫ�����롱ͼƬ
				putimage(game_x, game_y, &numimg[10]);
			else if (SD.right_data[game_i][game_j][9] == 0)	//����Ƿ�����״̬���Ҹ�λ��û�б�ǣ���ʾԭֵͼƬ
				putimage(game_x, game_y, &numimg[SD.game[game_i][game_j]]);
			else 										//����Ƿ�����״̬������λ���б�ǣ���ʾ���ͼƬ
				right_mouse_sign(game_x, game_y, game_i, game_j);
			break;
		case 1:		//��ǰ����һ�
			if (SD.Rinputflag == 1)
				right_mouse_sign(game_x, game_y, game_i, game_j);		//����һ���������ֵ
			else if (SD.right_data[game_i][game_j][9] != 0)
				putimage(game_x + SD.right_data[game_i][game_j][9] % 3 * RIGHT_PICTURE_SIZE, game_y + SD.right_data[game_i][game_j][9] / 3 * RIGHT_PICTURE_SIZE, &rightimg[0]);	//����һ���������״̬�ر�
			else
				putimage(game_x, game_y, &numimg[SD.game[game_i][game_j]]);	//��λ�ø�ԭ
			break;
		}
		break;
	case CHOOSE_AREA:			//ѡ������
		if (SD.Linputflag == 1)		//�����������״̬
		{
			SD_music_innum();		//����������Ч
			SD.game[game_i][game_j] = 0;			//����ǰ����λ�õ�ֵ���㣨�����޸�ʱ�ظ�����ͬһ��ֵ�����Ի���
			if (SD_detection(game_i, game_j, SD.number) == 0)
			{	//����ͻ
				if (SD.right_data[game_i][game_j][9] != 0)		//��λ�ñ�����һ���ǹ�����Ҫ����λ�õ��һ��������
					for (u_8 n = 0; n < 10; n++)				//�һ�����������
						SD.right_data[game_i][game_j][n] = 0;
				SD.game[game_i][game_j] = SD.number;		//��ѡ�������Ӧ��ֵ����Ϸ����
				delete_right_num(game_i, game_j, SD.number);		//��ֵ��ɾ�����С����С���3*3С����ĸ�ֵ�ı��
				putimage(game_x, game_y, &numimg[SD.number]);		//�����ӦͼƬ
				if (SD_verify())		//ÿ����һ��ֵ���ж���Ϸ�������������1
					return 1;			//return��������
				SD.Linputflag = 1;		//������󱣳�����״̬��������̽��в���
			}
		}
		if (SD.Rinputflag == 1)		//�����һ����״̬
		{
			SD.game[game_i][game_j] = 0;
			SD.right_data[game_i][game_j][SD.number - 1] = 0x01 ^ SD.right_data[game_i][game_j][SD.number - 1];	//�����^����ʵ�ַ�ת����һ����ʾ�ڶ���ȡ��
			if (SD.right_data[game_i][game_j][SD.number - 1])
				SD.right_data[game_i][game_j][9]++;			//ͳ��ͼƬ����
			else
				SD.right_data[game_i][game_j][9]--;
			right_mouse_sign(game_x, game_y, game_i, game_j);		//����һ���������ֵ
		}
		break;
	case GAME_CLEAR:			//�����ť
		if (SD.Rinputflag == 1)
		{		//�������Ҽ���ǣ���������״̬
			SD_music_button();		//���Ű�����Ч
			for (u_8 n = 0; n < 10; n++)
				SD.right_data[game_i][game_j][n] = 0;
			SD.Rinputflag = 1;		//��������״̬
			right_mouse_sign(game_x, game_y, game_i, game_j);
		}			//�������״̬�� && ���ǳ�ʼֵ
		else if (SD.Linputflag == 1)
		{		//�������������״̬
			SD_music_button();		//���Ű�����Ч
			SD.game[game_i][game_j] = 0;
			putimage(game_x, game_y, &numimg[0]);
			SD.Linputflag = 0;		//������������״̬
		}
		break;
	case PLAY_AGAIN:			//����һ��
		SD_music_button();		//���Ű�����Ч
		if (SD.Gameing)			//�����������Ϸ״̬
			SD_Game_Stop();			//������Ϸ���������
		if (MessageBox(hwnd, _T("�Ƿ��ؿ�һ�֣�"), _T("����"), MB_OKCANCEL) == IDOK)
		{
			SD_Game_Init();				//��ʼ����Ϸ
		}
		else if (SD.Gameing)			//�����������Ϸ״̬
			SD_Game_Start();		//������Ϸ
		break;
	case GAME_HINT:				//��ʾ
		if (SD.Init[game_i][game_j] == 0 && SD.Linputflag == 1)
		{
			SD_music_button();		//���Ű�����Ч
			if (SD_hint(game_x, game_y, game_i, game_j))//�������״̬�ſɵ��á���ʾ������
				return 1;
		}
		break;
	case GAME_SET:				//����
		SD_music_button();		//���Ű�����Ч
		if (SD.Gameing)			//�����������Ϸ״̬
			SD_Game_Stop();			//������Ϸ���������
		if (MessageBox(hwnd, _T("�Ƿ�������ý��棿������Ϸ���Ȳ��ᱣ�棡����"), _T("����"), MB_OKCANCEL) == IDOK)
		{
			SD_Set_game();
			if (SD_verify())
				return 1;
		}
		else if (SD.Gameing)			//�����������Ϸ״̬
			SD_Game_Start();		//������Ϸ
		break;
	}
	}
}
