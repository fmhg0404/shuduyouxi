#include "SD_Init.h"

//º¯Êý
void SD_Game_Init(void)
{
	srand((int)time(NULL));
	u_8 x = 0, y = 0;
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
		if (SD.init[x][y] == 0)
		{
			SD.init[x][y] = SD.game[x][y] = SD.solve[x][y];
			SD.init[x][8 - y] = SD.game[x][8 - y] = SD.solve[x][8 - y];
			i++;
		}
	}
	SD_Show_main();

}