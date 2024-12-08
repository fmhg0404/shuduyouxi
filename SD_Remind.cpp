#include "SD_Remind.h"

/*	�������ֵ�Ƿ�������������
*	��飺	��⵱ǰ���뵥Ԫ�����ڵ�С�����С������Ƿ������������ֵ��ͬ��ֵ
*	������	gamei	:����λ�ö�Ӧ����ĺ�����
*			gamej	:����λ�ö�Ӧ�����������
*			n		:ѡ���������ֵ
*	����ֵ����ͻ����1������ͻ����0
*/
bool SD_detection(u_8 game_i, u_8 game_j, u_8 n)
{
	TCHAR remind_str[20];
	for (u_8 i = game_i / 3 * 3; i < game_i / 3 * 3 + 3; i++)
	{
		for (u_8 j = game_j / 3 * 3; j < game_j / 3 * 3 + 3; j++)
		{
			if (SD.game[i][j] == n) {	//�жϸ�С�������Ƿ����ظ�����
				swprintf_s(remind_str, _T("�þ����Ѵ������� %d !"), n);
				MessageBox(hwnd, remind_str, _T("���뾯��"), MB_OK);
				return 1;
			}
		}
	}
	for (int j = 0; j < 9; j++)
	{	//�жϸ����Ƿ����ظ�����
		if (SD.game[game_i][j] == n)
		{
			swprintf_s(remind_str, _T("�����Ѵ������� %d !"), n);
			MessageBox(hwnd, remind_str, _T("���뾯��"), MB_OK);
			return 1;
		}
	}
	for (int i = 0; i < 9; i++)
	{	//�жϸ����Ƿ����ظ�����
		if (SD.game[i][game_j] == n)
		{
			swprintf_s(remind_str, _T("�����Ѵ������� %d !"), n);
			MessageBox(hwnd, remind_str, _T("���뾯��"), MB_OK);
			return 1;
		}
	}
	return 0;
}

/*	����ʾ����ť����ʵ��
*	��飺	ÿִ��һ�ξ͸����û���ǰ����ֵ����һ�����Ž⣬���޽���ͨ����Ϣ�Ի�����
*	������	game_x	:��Ԫ�����Ͻ�ͼƬ���������
*			game_y	:��Ԫ�����Ͻ�ͼƬ���������
*			game_i	:��Ԫ���Ӧ���������
*			game_j	:��Ԫ���Ӧ����������
*	����ֵ����ʾ����Ϸʤ������1���޽����Ϸû��������0
*/
bool SD_hint(u_16 game_x, u_16 game_y, u_8 game_i, u_8 game_j)
{
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
			SD.solve[i][j] = SD.game[i][j];	//����Ŀǰ��Ϸ����ֵ
	if (SD_unlock(SD.solve) == 1)	//����unlock_sd()����������
	{
		SD.game[game_i][game_j] = SD.solve[game_i][game_j];		//������ʾֵ
		putimage(game_x, game_y, &numimg[SD.game[game_i][game_j]]);		//�����ӦͼƬ
		SD.Linputflag = 0;		//�������������
		for (u_8 n = 0; n < 10; n++)	//�һ�����������
			SD.right_data[game_i][game_j][n] = 0;
		if (SD_verify())		//�����ʾֵΪ���һ��ֵ����Ϸʤ����ֱ�ӷ��ص�������
			return 1;
	}
	else
	{	//���޽�����ʾ�û��޸�֮ǰ����ֵ
		MessageBox(hwnd, _T("�޽�!�뽫��һֵ�޸Ļ���������ԣ�"), _T("��ʾ����"), MB_OK);
		if (SD.right_data[game_i][game_j][9] != 0)	//������һ���־��ԭ
			right_mouse_sign(game_x, game_y, game_i, game_j);
	}
	return 0;		//��ʾֵ�������һ�����޽��򷵻�0
}

