#include "SD_Resource.h"


SHUDU SD;
IMAGE numimg[11], rightimg[11], button[11], choose[10], background[2];    //´æ´¢¸÷ÀàÍ¼Æ¬
BYTE LpKeyState_sd[256];
ExMessage mouse_msg;
HWND hwnd;
RECT r = { TIME_SHOW_X, TIME_SHOW_Y, TIME_SHOW_X + TIME_SHOW_L, TIME_SHOW_Y + TIME_SHOW_H };
TCHAR str[30];
GAME_TIME TIME;


void SD_import(void)
{
	//Êý×ÖÇøÓòÍ¼Æ¬
	loadimage(&numimg[0], _T("./Image/0.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[1], _T("./Image/1.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[2], _T("./Image/2.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[3], _T("./Image/3.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[4], _T("./Image/4.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[5], _T("./Image/5.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[6], _T("./Image/6.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[7], _T("./Image/7.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[8], _T("./Image/8.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[9], _T("./Image/9.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);
	loadimage(&numimg[10], _T("./Image/10.jpg"), GAME_PICTURE_SIZE, GAME_PICTURE_SIZE);

	//ÓÒ»÷ÇøÓòÍ¼Æ¬
	loadimage(&rightimg[0], _T("./Image/0.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[1], _T("./Image/1.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[2], _T("./Image/2.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[3], _T("./Image/3.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[4], _T("./Image/4.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[5], _T("./Image/5.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[6], _T("./Image/6.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[7], _T("./Image/7.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[8], _T("./Image/8.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[9], _T("./Image/9.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);
	loadimage(&rightimg[10], _T("./Image/10.jpg"), RIGHT_PICTURE_SIZE, RIGHT_PICTURE_SIZE);

	//°´Å¥ÇøÓò
	loadimage(&button[0], _T("./Image/button1.jpg"), BUTTON_MAIN_L, BUTTON_MAIN_H);
	loadimage(&button[1], _T("./Image/button3.jpg"), BUTTON_MAIN_L, BUTTON_MAIN_H);
	loadimage(&button[2], _T("./Image/button4.jpg"), BUTTON_MAIN_L, BUTTON_MAIN_H);
	loadimage(&button[3], _T("./Image/button5.jpg"), BUTTON_MAIN_L, BUTTON_MAIN_H);
	loadimage(&button[4], _T("./Image/button2.jpg"), BUTTON_MAIN_L, BUTTON_MAIN_H);
	loadimage(&button[5], _T("./Image/button6.jpg"), BUTTON_MAIN_L, BUTTON_MAIN_H);
	loadimage(&button[6], _T("./Image/button7.jpg"), BUTTON_MAIN_L, BUTTON_MAIN_H);
	loadimage(&button[7], _T("./Image/mode1.jpg"), BUTTON_SET_L, BUTTON_SET_H);
	loadimage(&button[8], _T("./Image/mode2.jpg"), BUTTON_SET_L, BUTTON_SET_H);
	loadimage(&button[9], _T("./Image/mode3.jpg"), BUTTON_SET_L, BUTTON_SET_H);
	loadimage(&button[10], _T("./Image/mode4.jpg"), BUTTON_SET_L, BUTTON_SET_H);
	
	//Ñ¡ÔñÇøÓòÍ¼Æ¬
	loadimage(&choose[0], _T("./Image/1.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[1], _T("./Image/2.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[2], _T("./Image/3.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[3], _T("./Image/4.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[4], _T("./Image/5.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[5], _T("./Image/6.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[6], _T("./Image/7.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[7], _T("./Image/8.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[8], _T("./Image/9.jpg"), CHOOSE_PICTURE_SIZE, CHOOSE_PICTURE_SIZE);
	loadimage(&choose[9], _T("./Image/11.jpg"), 3 * CHOOSE_PICTURE_SIZE + 2, CHOOSE_PICTURE_SIZE);

	//±³¾°Í¼Æ¬
	loadimage(&background[0], _T("./Image/background.jpg"), WINDOW_SIZE_L, WINDOW_SIZE_H);
	loadimage(&background[1], _T("./Image/gamebackground.jpg"), GAME_BACKGROUND_SIZE, GAME_BACKGROUND_SIZE);


}