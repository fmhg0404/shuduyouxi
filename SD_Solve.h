#ifndef __SD_SOLVE_H__
#define __SD_SOLVE_H__

//ͷ�ļ�����
#include "SD_Resource.h"

//��������
bool Is_answer(u_8 a[9][9], u_8 x, u_8 y, u_8 n);
bool Solve_sudoku(u_8 a[9][9], u_8 x, u_8 y);
bool SD_unlock(u_8 a[9][9]);
bool SD_verify(void);

#endif
