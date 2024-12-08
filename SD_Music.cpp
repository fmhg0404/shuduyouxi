#include "SD_Music.h"

//º¯Êý
void SD_Music_import(void)
{
	mciSendString(L"open ./music/background_bgm.mp3 alias BGM", NULL, 0, NULL);
	mciSendString(L"open ./music/input_number.mp3 alias IN_NUM", NULL, 0, NULL);
	mciSendString(L"open ./music/button_down.mp3 alias PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"open ./music/game_victory.mp3 alias VICTORY", NULL, 0, NULL);
	mciSendString(L"open ./music/game_lose.mp3 alias LOSE", NULL, 0, NULL);
	mciSendString(L"setaudio BGM volume to 500", NULL, 0, NULL);
	mciSendString(L"setaudio IN_NUM volume to 600", NULL, 0, NULL);
	mciSendString(L"setaudio PUT_DOWN volume to 600", NULL, 0, NULL);
	mciSendString(L"setaudio VICTORY volume to 700", NULL, 0, NULL);
	mciSendString(L"setaudio LOSE volume to 700", NULL, 0, NULL);
	mciSendString(L"play BGM repeat", NULL, 0, NULL);
}

void SD_music_innum(void)
{
	mciSendString(L"close IN_NUM", NULL, 0, NULL);
	mciSendString(L"open ./music/input_number.mp3 alias IN_NUM", NULL, 0, NULL);
	mciSendString(L"play IN_NUM", NULL, 0, NULL);
}

void SD_music_button(void)
{
	mciSendString(L"close PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"open ./music/button_down.mp3 alias PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"play PUT_DOWN", NULL, 0, NULL);
}

void SD_music_victory(void)
{
	mciSendString(L"close VICTORY", NULL, 0, NULL);
	mciSendString(L"open ./music/game_victory.mp3 alias VICTORY", NULL, 0, NULL);
	mciSendString(L"play VICTORY", NULL, 0, NULL);
}

void SD_music_lose(void)
{
	mciSendString(L"close LOSE", NULL, 0, NULL);
	mciSendString(L"open ./music/game_lose.mp3 alias LOSE", NULL, 0, NULL);
	mciSendString(L"play LOSE", NULL, 0, NULL);
}


void SD_Music_close(void)
	{
	mciSendString(L"close BGM", NULL, 0, NULL);
	mciSendString(L"close IN_NUM", NULL, 0, NULL);
	mciSendString(L"close PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"close VICTORY", NULL, 0, NULL);
	mciSendString(L"close LOSE", NULL, 0, NULL);

	}