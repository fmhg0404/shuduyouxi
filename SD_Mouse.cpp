#include "SD_Mouse.h"

void right_mouse_sign(u_16 game_x, u_16 game_y, u_8 game_i, u_8 game_j)
{
	u_8 n = 1, k = 0;
	for (; k < SD.right_data[game_i][game_j][0]; k++)
	{
		while (SD.right_data[game_i][game_j][n++] == 0);
		putimage(game_x + k % 3 * RIGHT_PICTURE_SIZE, game_y + k / 3 * RIGHT_PICTURE_SIZE, &rightimg[n-  1]);
	}
	if (k < 9)
	{
		if (SD.Rinputflag == 1)
			putimage(game_x + k % 3 * RIGHT_PICTURE_SIZE, game_y + k / 3 * RIGHT_PICTURE_SIZE, &rightimg[10]);
		else
			putimage(game_x + k % 3 * RIGHT_PICTURE_SIZE, game_y + k / 3 * RIGHT_PICTURE_SIZE, &rightimg[0]);
		k++;
	}
	for (; k < 9; k++)
	{
		putimage(game_x + k % 3 * RIGHT_PICTURE_SIZE, game_y + k / 3 * RIGHT_PICTURE_SIZE, &rightimg[0]);
	}
}

//����
void SD_Count_x_y(u_16* game_x, u_16* game_y, u_8* game_i, u_8* game_j)
{
	if (SD.Main_Interface)			//����������Զ������Ĳ���
	{
		if (SD.Gameing || SD.Set_Self_Inerface)		//������Ϸ�����Զ���ģʽʱ���ſɶ����������ѡ��������в���
		{
			if (mouse_msg.x >= GAME_START_X && mouse_msg.x <= GAME_START_X + GAME_BACKGROUND_SIZE - 21 && mouse_msg.y >= GAME_START_Y && mouse_msg.y <= GAME_START_Y + GAME_BACKGROUND_SIZE - 21)
			{	//��Ϸ����
				u_8 i = 0, j = 0;							//������㣬i��j��¼���λ�ö�Ӧ�������±�
				int start_x = 0, start_y = 0, now_x = 0, now_y = 0;	//start_x, start_y����¼ÿ��С�������ʼ���ꣻ now_x, now_y����¼�����������Ϸ������������
				now_x = mouse_msg.x - GAME_START_X;		//��¼�����������������Ϸ�����������꣨����Ϸ��ʼλ�ÿ�ʼ��
				now_y = mouse_msg.y - GAME_START_Y;
				while (!(now_x >= start_x && now_x <= start_x + GAME_PICTURE_SIZE && now_y >= start_y && now_y <= start_y + GAME_PICTURE_SIZE))
				{
					if (now_x - GAME_PICTURE_SIZE > start_x)
						j++;
					if (now_y - GAME_PICTURE_SIZE > start_y)
						i++;
					start_x = j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL;		//ÿ�μ�¼С�������Ͻǵ���ʼ����
					start_y = i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL;
					if (now_x < start_x || now_y < start_y)			//�����Ϸ����ļ���ϣ�������Ч
						return;
				}
				if (SD.Init[i][j] == 0)		//��ʼֵ���ܱ�ѡ��
				{
					if (GAME_START_X + start_x == *game_x && GAME_START_Y + start_y == *game_y)		//�����ͬһλ��ʵ�ַ�ת
					{
						switch (mouse_msg.message)
						{
						case WM_LBUTTONDOWN:			//���������
							if (SD.Mouse_flag == 0)		//�ϴ�Ҳ��������
								SD.Linputflag = !SD.Linputflag;		//���������ͬλ�ã������־��ת
							else
							{						//�ϴ�������һ�
								SD.Linputflag = 1;		//���������־
								SD.Rinputflag = 0;		//����һ���־
							}
							SD.Mouse_flag = 0;
							break;
						case WM_RBUTTONDOWN:			//�������һ�
							if (SD.Mouse_flag == 1)		//�ϴ�����һ�
								SD.Rinputflag = !SD.Rinputflag;		//����Ҽ����ͬλ�ã��һ���־��ת
							else
							{						//�ϴ�������
								SD.Rinputflag = 1;		//�����һ���־
								SD.Linputflag = 0;		//��������־
							}
							SD.Mouse_flag = 1;
							break;
						}
					}
					else
					{
						if (*game_x < WINDOW_SIZE_L)	//�������������򣬽���һλ�ûָ�����һ�β���
						{
							if (SD.right_data[*game_i][*game_j][9] == 0)
							{
								putimage(*game_x, *game_y, &numimg[SD.game[*game_i][*game_j]]);	//��λ�ø�ԭ
							}
							if (SD.game[*game_i][*game_j] == 0 && SD.right_data[*game_i][*game_j][9] != 9)
							{	//�ж�����һ�����һλ���Ƿ���Ҫ��ԭ����һλ���������ֵ�˻����Ѿ������������Ҫ��ԭ
								SD.Rinputflag = 0;
								right_mouse_sign(*game_x, *game_y, *game_i, *game_j);	//����һ���������״̬�ر�
							}
						}
						if (mouse_msg.message == WM_LBUTTONDOWN)		//����������
						{
							SD.Mouse_flag = 0;
							SD.Linputflag = 1;	//���������־
							SD.Rinputflag = 0;	//����һ���־
						}
						else if (mouse_msg.message == WM_RBUTTONDOWN)		//��������һ�
						{
							SD.Mouse_flag = 1;
							SD.Rinputflag = 1;	//�����һ���־
							SD.Linputflag = 0;	//��������־
						}
						*game_x = GAME_START_X + start_x;		//ͼƬ���λ��
						*game_y = GAME_START_Y + start_y;
						*game_i = i;			//���������ж�Ӧ
						*game_j = j;
					}
					SD.game_flag = GAME_AREA;
					return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
				}
			}
			if (mouse_msg.message == WM_LBUTTONDOWN)
			{
				if (mouse_msg.x >= CHOOSE_START_X && mouse_msg.x <= CHOOSE_START_X + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y >= CHOOSE_START_Y && mouse_msg.y <= CHOOSE_START_Y + 3 * CHOOSE_PICTURE_SIZE + 2)
				{		//ѡ������
					SD.number = (mouse_msg.y - CHOOSE_START_Y) / CHOOSE_PICTURE_SIZE * 3 + (mouse_msg.x - CHOOSE_START_X) / CHOOSE_PICTURE_SIZE + 1;	//��¼��Ӧֵ��������Ϸ��������ĸ�ֵ���Ҽ��ı��
					SD.game_flag = CHOOSE_AREA;
					return;
				}
				if (mouse_msg.x >= CHOOSE_START_X && mouse_msg.x <= CHOOSE_START_X + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y >= CHOOSE_START_Y + 3 * CHOOSE_PICTURE_SIZE + 2 && mouse_msg.y <= CHOOSE_START_Y + 4 * CHOOSE_PICTURE_SIZE + 3)
				{		//�����ť
					SD.game_flag = GAME_CLEAR;
					return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
				}
			}
		}
		if (mouse_msg.message == WM_LBUTTONDOWN)
		{
			if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y && mouse_msg.y <= BUTTON_MSTART_Y + BUTTON_MAIN_H)
			{		//��ʼ��ֹͣ��ť
				if (SD.Set_Self_Inerface == 0)		//������
				{
					SD.Gameing = !SD.Gameing;		//��  ������Ϸ״̬  ��ת
					if (SD.Gameing)
						SD.game_flag = GAME_START;
					else
						SD.game_flag = GAME_STOP;
				}
				else			//�Զ������
				{
					SD.game_flag = SET_TIME;
				}
				return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
			}
			if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + BUTTON_MAIN_H + BUTTON_MINTERVAL && mouse_msg.y <= BUTTON_MSTART_Y + 2 * BUTTON_MAIN_H + BUTTON_MINTERVAL)
			{		//����һ��
				SD.game_flag = PLAY_AGAIN;
				return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
			}
			if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + 2 * (BUTTON_MAIN_H + BUTTON_MINTERVAL) && mouse_msg.y <= BUTTON_MSTART_Y + 3 * BUTTON_MAIN_H + 2 * BUTTON_MINTERVAL)
			{		//��ʾ��ť���Զ������ȷ����ť
				if (SD.Set_Self_Inerface)
					SD.game_flag = SET_SELF_YES;
				else if (SD.Linputflag)
					SD.game_flag = GAME_HINT;
				return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
			}
			if (mouse_msg.x >= BUTTON_MSTART_X && mouse_msg.x <= BUTTON_MSTART_X + BUTTON_MAIN_L && mouse_msg.y >= BUTTON_MSTART_Y + 3 * (BUTTON_MAIN_H + BUTTON_MINTERVAL) && mouse_msg.y <= BUTTON_MSTART_Y + 4 * BUTTON_MAIN_H + 3 * BUTTON_MINTERVAL)
			{		//���ð�ť
				SD.game_flag = GAME_SET;
				return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
			}
		}
	}
	else			//���ý���Ĳ���
	{
		if (mouse_msg.message == WM_LBUTTONDOWN)
		{
			if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y && mouse_msg.y <= BUTTON_SSTART_Y + BUTTON_SET_H)
			{		//��ģʽ
				SD.game_flag = SET_EASY;
				return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
			}
			if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + BUTTON_SET_H + BUTTON_SINTERVAL && mouse_msg.y <= BUTTON_SSTART_Y + 2 * BUTTON_SET_H + BUTTON_SINTERVAL)
			{		//����ģʽ
				SD.game_flag = SET_HARD;
				return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
			}
			if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + 2 * (BUTTON_SET_H + BUTTON_SINTERVAL) && mouse_msg.y <= BUTTON_SSTART_Y + 3 * BUTTON_SET_H + 2 * BUTTON_SINTERVAL)
			{		//����ģʽ
				SD.game_flag = SET_HARDEST;
				return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
			}
			if (mouse_msg.x >= BUTTON_SSTART_X && mouse_msg.x <= BUTTON_SSTART_X + BUTTON_SET_L && mouse_msg.y >= BUTTON_SSTART_Y + 3 * (BUTTON_SET_H + BUTTON_SINTERVAL) && mouse_msg.y <= BUTTON_SSTART_Y + 4 * BUTTON_SET_H + 3 * BUTTON_SINTERVAL)
			{		//�Զ���ģʽ
				SD.game_flag = SET_SELF;
				return;			//���һ��ֻ���ܵ��һ������÷����һ�������Ͳ���Ҫ�����һ��������
			}
		}
	}
}

