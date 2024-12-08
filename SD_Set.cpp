#include "SD_Set.h"
/*	�Զ������ú���
*	��飺	���û����ж����ʼֵ���ý���ֻ��������������������ǲ��������๦�ܺ���Ϸ���庯������
*	������	��
*	����ֵ����
*/
void SD_Set_self(void)
{
	u_16 game_x = 801, game_y = 601;
	u_8 game_i = 0, game_j = 0;
	wchar_t input_num[10];			//����������Ϣ
	u_8 set_time = 20;				//ת��Ϊ�������ݣ���¼����ʱ��
	SD_Show_use();			//��ӡ����
	swprintf_s(str, _T("%.2d : %.2d : %.2d"), set_time, 0, 0);	//�޸�ʱ�����
	drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	SD.game_flag = EMPTY;				//����������ı�־
	SD.Linputflag = 0;					//�ر�����״̬
	SD.Rinputflag = 0;					//�رձ��״̬
	SD.Gameing = 0;						//���������Ϸ��־
	SD.New_state = 1;					//���ü������λ����״̬
	SD.Main_Interface = 1;				//��������������Զ������
	SD.Set_Self_Inerface = 1;			//�����û��Զ������
	SD.number = 0;						//���ѡ��ĸ�ֵ
	TIME.start = 0;				//�����ʼʱ��
	TIME.last = 0;				//�����ֹʱ��
	TIME.temp = 0;				//���ʱ��μ�¼
	TIME.total = 0;					//�����Ϸʱ��
	SD.Mouse_flag = 0;					//�������־�����ڼ�¼��������Ҽ�����
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
		{
			SD.Init[i][j] = SD.game[i][j] = SD.solve[i][j] = 0;		//�������
			for (u_8 k = 0; k < 10; k++)
				SD.right_data[i][j][k] = 0;			//����һ����
		}
	while (1)
	{
		//�����־
		SD.game_flag = EMPTY;
		//���������Ϣ
		if (peekmessage(&mouse_msg, EX_MOUSE))
			if (mouse_msg.message == WM_LBUTTONDOWN)
				SD_Count_x_y(&game_x, &game_y, &game_i, &game_j);	//�������������
		//���հ�����Ϣ
		Scan_Key(&game_x, &game_y, &game_i, &game_j);
		//��⵱ǰ��ִ��ʲô����
		switch (SD.game_flag)
		{
		case GAME_AREA:			//��Ϸ����
			if (SD.Linputflag == 1)		//�����������״̬����ʾ��ɫ�����롱ͼƬ
				putimage(game_x, game_y, &numimg[10]);
			else //����Ƿ�����״̬����ʾԭֵͼƬ
				putimage(game_x, game_y, &numimg[SD.game[game_i][game_j]]);
			break;
		case CHOOSE_AREA:			//ѡ������
			if (SD.Linputflag == 1)		//�����������״̬
			{
				SD_music_innum();		//����������Ч
				SD.game[game_i][game_j] = 0;	//����ǰ����λ�õ�ֵ���㣨�����޸�ʱ�ظ�����ͬһ��ֵ�����Ի���
				if (SD_detection(game_i, game_j, SD.number) == 0) {	//����ͻ
					SD.solve[game_i][game_j] = SD.game[game_i][game_j] = SD.number;	//���������鶼���и���
					putimage(game_x, game_y, &numimg[SD.number]);		//�����ӦͼƬ
					SD.Linputflag = 1;		//������󱣳�����״̬
				}
			}
			break;
		case GAME_CLEAR:			//�����ť
			if (SD.Linputflag == 1)
			{		//�������������״̬
				SD_music_button();		//���Ű�����Ч
				SD.solve[game_i][game_j] = SD.game[game_i][game_j] = 0;
				putimage(game_x, game_y, &numimg[0]);
				SD.Linputflag = 1;		//����󱣳�����״̬
			}
			break;
		case SET_TIME:				//����ʱ��
			SD_music_button();		//���Ű�����Ч
			InputBox(input_num, 10, L"�������趨ʱ�䣺\n��Χ��1 - 60 min��������\n���벻�Ϸ�Ĭ��Ϊ20", L"����ʱ��", L"20", true);
			set_time = _wtoi(input_num);
			if (set_time <= 0 || set_time >= 60)			//���볬����Χ
			{
				swprintf_s(str, _T("%.2d : %.2d : %.2d"), 20, 0, 0);
				drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
				SD.degree_time = 20;			//Ĭ��ʱ��Ϊ25����
			}
			else
			{
				swprintf_s(str, _T("%.2d : %.2d : %.2d"), set_time, 0, 0);
				drawtext(str, &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
				SD.degree_time = set_time;
			}
			break;
		case SET_SELF_YES:				//ȷ��
			SD_music_button();		//���Ű�����Ч
			if (SD_unlock(SD.solve) == 0) {		//�޽�
				MessageBox(hwnd, _T("�Զ�������޽�!����ת�����ý��棡"), _T("�Զ���"), MB_OK);
				SD_Set_game();
				return;		//����������ݹ飬ֱ�ӷ���
			}
			if (MessageBox(hwnd, _T("ȷ���Զ������"), _T("�Զ���"), MB_OKCANCEL) == 1)
			{
				for (u_8 i = 0; i < 9; i++)		//��SD.init�����ʼ��
					for (u_8 j = 0; j < 9; j++)
						SD.Init[i][j] = SD.game[i][j];
				SD_Show_main();
				SD.Set_Self_Inerface = 0;	//�������Զ������ý���
				SD.Linputflag = 0;				//�ر�����״̬
				return;		//ֱ������
			}
			break;
		}
	}
}

/*	�����á����ܺ���
*	��飺	�������ý��棬ʵ������ģʽ��Ӧ�Ĺ���
*	������	��
*	����ֵ����
*/
void SD_Set_game(void)
{
	u_16 game_x = 0, game_y = 0;
	u_8 game_i = 0, game_j = 0;
	SD.Main_Interface = 0;					//�������ý���
	SD_Show_set();				//�����ʾ���ý���
	while (1)
	{
		//�����־
		SD.game_flag = EMPTY;
		if (peekmessage(&mouse_msg, EX_MOUSE))
		{
			if (mouse_msg.message == WM_LBUTTONDOWN)
				//�������������
				SD_Count_x_y(&game_x, &game_y, &game_i, &game_j);
		}
		//���հ�����Ϣ
		Scan_Key(&game_x, &game_y, &game_i, &game_j);
		//��⵱ǰ��ִ��ʲô����
		switch (SD.game_flag)
		{
		case SET_EASY:				//��ģʽ
			SD_music_button();		//���Ű�����Ч
			SD.degree = 23;
			SD.degree_time = 20;
			SD_Game_Init();
			return;
		case SET_HARD:				//����ģʽ
			SD_music_button();		//���Ű�����Ч
			SD.degree = 18;
			SD.degree_time = 12;
			SD_Game_Init();
			return;
		case SET_HARDEST:			//����ģʽ
			SD_music_button();		//���Ű�����Ч
			SD.degree = 15;
			SD.degree_time = 8;
			SD_Game_Init();
			return;
		case SET_SELF:				//�Զ���ģʽ
			SD_music_button();		//���Ű�����Ч
			SD_Set_self();
			return;
		}
	}
}
