#include "SD_Init.h"

//º¯Êý
void SD_Game_Init(void)
{
	srand((int)time(NULL));
	u_8 x = 0, y = 0;
	SD.game_flag = EMPTY;
	SD.game_insite_move = NOT_MOVE;
	SD.Linputflag = 0;
	SD.Rinputflag = 0;
	SD.Gameing = 0;
	SD.New_state = 1;
	SD.Int_face = MAIN;
	SD.number = 0;
	TIME.start = 0;
	TIME.last = 0;
	TIME.temp = 0;
	TIME.total = 0;
	SD.Mouse_flag = 0;
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
		{
			SD.Init[i][j] = SD.game[i][j] = SD.solve[i][j] = 0;
			for (u_8 k = 0; k < 10; k++)
				SD.right_data[i][j][k] = 0;
		}
	for (u_8 i = 0; i < 3; i++)
	{
		for (u_8 n = 1; n <= 9;)
		{
			x = rand() % 3 + i * 3;
			y = rand() % 3 + i * 3;
			if (SD.solve[x][y] == 0)
			{
				SD.solve[x][y] = n;
				n++;
			}
		}
	}
	SD_unlock(SD.solve);
	for (u_8 i = 0; i < SD.degree;)
	{
		x = rand() % 9;
		y = rand() % 9;
		if (SD.Init[x][y] == 0)
		{
			SD.Init[x][y] = SD.game[x][y] = SD.solve[x][y];
			SD.Init[x][8 - y] = SD.game[x][8 - y] = SD.solve[x][8 - y];
			i++;
		}
	}
	SD_Show_main();

}