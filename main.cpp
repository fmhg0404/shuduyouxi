#include "SD_Resource.h"

/*	������
*	��飺	�������
*	������	��
*	����ֵ������������������0
*/
int main(void)
{
	TCHAR Show_vitory[50];			//�洢������Ϣ
	hwnd = initgraph(WINDOW_SIZE_L, WINDOW_SIZE_H);		//������ͼ����
	SD_music_import();			//���ű�������
	SD_import();			//������Դ�ļ�
	SD_Game_Init();			//��ʼ����Ϸ����
	while (1)
	{				//��ѭ������ҹرմ��ڲ��˳�
		if (SD_Play_Game())
		{		//����Ϸ���ж�
			SD_music_victory();		//����ʤ����Ч
			TIME.total = SD.degree_time * 60 * 1000 - TIME.total;		//��ʱTIME.totalΪ����Ϸʱ��
			swprintf_s(Show_vitory, _T("��ϲ������Ϸʤ��!\n��ʱ��%.2d : %.2d : %.2d"), TIME.total / 1000 / 60, TIME.total / 1000 % 60, TIME.total / 10 % 100);
			MessageBox(hwnd, Show_vitory, _T("ʤ������"), MB_OK);	//���������ʾ
			SD_Game_Init();		//��ʼ����Ϸ����
		}
		else
		{
			SD_music_lose();		//����ʧ����Ч
			swprintf_s(Show_vitory, _T("ʱ�䵽����û���ڹ涨ʱ���������Ϸ!\n"));
			MessageBox(hwnd, Show_vitory, _T("ʧ�ܽ���"), MB_OK);	//���������ʾ
			SD_Game_Init();		//��ʼ����Ϸ����
		}
	}
	SD_music_close();		//�ر�����
	closegraph();			//�رջ�ͼ����
	return 0;
}