#include "SD_Solve.h"

//����
static bool Is_answer(u_8 a[9][9], u_8 x, u_8 y, u_8 n)
{
	for (u_8 j = 0; j < 9; j++)	//�����
		if (a[x][j] == n)
			return 0;
	for (u_8 i = 0; i < 9; i++)	//�����
		if (a[i][y] == n)
			return 0;
	for (u_8 i = x / 3 * 3; i < x / 3 * 3 + 3; i++)	//��Ԫ�����
		for (u_8 j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
			if (a[i][j] == n)
				return 0;
	return 1;
}
static bool Solve_sudoku(u_8 a[9][9], u_8 x, u_8 y)
{
	if (y == 9)
	{
		y = 0;
		x++;
		if (x == 9)
			return 1;
	}
	if (a[x][y] != 0)
	{
		if (Solve_sudoku(a, x, y + 1))
			return 1;
	}
	else
	{
		for (u_8 i = 1; i <= 9; i++)
		{
			if (Is_answer(a, x, y, i))		//���С����С�3��3����Ԫ��
			{
				a[x][y] = i;
				if (Solve_sudoku(a, x, y + 1))
					return 1;
			}
		}
		a[x][y] = 0;
	}
	return 0;
}
bool SD_unlock(u_8 a[9][9])
{
	return Solve_sudoku(a, 0, 0);
}

/*	�ж���Ϸ�Ƿ�ʤ��
*	��飺	�����ҵ�����SD.game�����Ƿ�������������ʾ��Ϸʤ��
*	������	��
*	����ֵ��1��ʾ����������0��ʾ����û����
*/
bool SD_verify(void)
{
	for (u_8 i = 0; i < 9; i++)
	{
		for (u_8 j = 0; j < 9; j++)
		{
			if (SD.game[i][j] == 0)		//��λ��Ϊ0����������������
			{
				return 0;
			}
		}
	}
	return 1;
}