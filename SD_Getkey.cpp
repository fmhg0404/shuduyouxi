#include "SD_Getkey.h"
/*	������⺯��
*	��飺	ÿ��һ���������º󣬽��ü�ֵ��Ӧ��key_state[256]�����е�����д1��ֱ���ɿ��Ź�0���ɷ�ֹ�ظ����
*	������	key_code	:Ҫ���������ֵ
*	����ֵ���������·���1���������𷵻�0
*/
bool get_key(BYTE key_code)		//������ʽ��ⰴ���Ƿ��£�
{
	static bool key_state[256] = { 0 };		//��̬����洢ÿ���������״̬
	if (Key_Down(key_code)) {
		if (!key_state[key_code])			//��һ�μ�¼Ϊ�ɿ�״̬����μ�¼Ϊ����״̬
		{
			key_state[key_code] = 1;
			return 1;
		}
	}
	if (Key_Up(key_code))
		if (key_state[key_code])			//��һ�μ�¼Ϊ����״̬����μ�¼Ϊ�ɿ�״̬
			key_state[key_code] = 0;
	return 0;
}

/*	����λ�ü��
*	��飺	��ⰴ��������ǵĵ�һ��λ�ã�ÿ�γ�ʼ����'Q''L''E''R'ʱ����һ����ʾλ��
*	������	game_x	:��Ԫ�����Ͻ�ͼƬ���������
*			game_y	:��Ԫ�����Ͻ�ͼƬ���������
*			game_i	:��Ԫ���Ӧ���������
*			game_j	:��Ԫ���Ӧ����������
*	����ֵ���ҵ���һ��λ�÷���1��û�ҵ�����0
*/
bool Key_place(u_16* game_x, u_16* game_y, u_8* game_i, u_8* game_j)
{
	for (u_8 i = 0; i < 9; i++)
		for (u_8 j = 0; j < 9; j++)
			if (SD.Init[i][j] == 0)
			{
				*game_i = i;		//���������е�λ��
				*game_j = j;
				*game_x = GAME_START_X + (j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL);		//����ͼ�ν����������λ��
				*game_y = GAME_START_Y + (i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL);	//x��j�ı䣬y��i�ı�
				return 1;
			}
	return 0;
}

/*	�������ְ���
*	��飺	������ְ����Ƿ��£������յ��İ���ֵ����SD.number�����У�����С������������
*	������	��
*	����ֵ�������ְ������·���1�������ְ������·���0
*/
bool Key_number(void)		//ɨ���������룬���ִ���SD.number��
{
	if (get_key('1') || get_key('1' + 48) && Num_LK) {
		SD.number = 1;
		return 1;				//�����ֱ�ӷ���
	}	//���ְ��� || (�Ҳఴ��Num LK���� && ���°���)
	if (get_key('2') || get_key('2' + 48) && Num_LK) {
		SD.number = 2;
		return 1;
	}
	if (get_key('3') || get_key('3' + 48) && Num_LK) {
		SD.number = 3;
		return 1;
	}
	if (get_key('4') || get_key('4' + 48) && Num_LK) {
		SD.number = 4;
		return 1;
	}
	if (get_key('5') || get_key('5' + 48) && Num_LK) {
		SD.number = 5;
		return 1;
	}
	if (get_key('6') || get_key('6' + 48) && Num_LK) {
		SD.number = 6;
		return 1;
	}
	if (get_key('7') || get_key('7' + 48) && Num_LK) {
		SD.number = 7;
		return 1;
	}
	if (get_key('8') || get_key('8' + 48) && Num_LK) {
		SD.number = 8;
		return 1;
	}
	if (get_key('9') || get_key('9' + 48) && Num_LK) {
		SD.number = 9;
		return 1;
	}
	return 0;			//û��鵽�������·���0
}

/*	����������ָ���
*	��飺	����Ƿ����趨�����������������Ӧ���ֵ��SD.game_flag��
*	������	��
*	����ֵ����ָ������·���1����ָ������·���0
*/
bool Key_main_order(void)
{
	if (SD.Gameing || SD.Set_Self_Inerface)
	{
		if (get_key(8) || get_key(46)) {		//key code���� Backspace=8	delete=46
			SD.game_flag = GAME_CLEAR;		//�����ť
			return 1;
		}
		if (get_key('Q') || get_key('L')) {		//��ת����״̬
			if (SD.Mouse_flag == 0)
				SD.Linputflag = !SD.Linputflag;
			else
			{
				SD.Linputflag = 1;
				SD.Rinputflag = 0;
			}
			SD.Mouse_flag = 0;			//�൱��������
			SD.game_flag = GAME_AREA;			//�൱����Ϸ�������
			return 1;
		}
		if (get_key('E') || get_key('R')) {		//��ת���״̬
			if (SD.Mouse_flag == 1)
				SD.Rinputflag = !SD.Rinputflag;
			else
			{
				SD.Rinputflag = 1;
				SD.Linputflag = 0;
			}
			SD.Mouse_flag = 1;			//�൱������һ�
			SD.game_flag = GAME_AREA;			//�൱����Ϸ�����һ�
			return 1;
		}
		if (get_key('H')) {		//��ʾ��ť���Զ������ȷ����ť
			if (SD.Set_Self_Inerface)
				SD.game_flag = SET_SELF_YES;
			else if (SD.Linputflag)
				SD.game_flag = GAME_HINT;
			return 1;
		}
		if (SD.Set_Self_Inerface)
			while (Key_Down(17) && Key_Down(13))		//�Զ������ȷ����ť��Contral: 17���س���code : 13
			{
				SD.game_flag = SET_SELF_YES;		//��װ��get_key�����޷������ϴΰ���״̬������ֱ����Key_Down()
				return 1;
			}
		if (get_key('T')) {				//�Զ����������ʱ��
			if (SD.Set_Self_Inerface)
				SD.game_flag = SET_TIME;
			return 1;
		}
	}
	if (get_key('F')) {		//��ʼ��ֹͣ��ť
		SD.Gameing = !SD.Gameing;		//��  ������Ϸ״̬  ��ת
		if (SD.Gameing)
			SD.game_flag = GAME_START;
		else
			SD.game_flag = GAME_STOP;
		return 1;
	}
	if (get_key('G')) {		//����һ��
		SD.game_flag = PLAY_AGAIN;
		return 1;
	}
	if (get_key('J')) {		//����
		SD.game_flag = GAME_SET;
		return 1;
	}
	return 0;		//û��⵽����0
}

/*	������ý����ָ���
*	��飺	�����ý���ʱ����1��2��3��4��Ӧ����ģʽ
*	������	��
*	����ֵ����ָ������·���1����ָ������·���0
*/
bool Key_set_order(void)
{
	if (get_key('1') || get_key('1' + 48) && Num_LK) {
		SD.game_flag = SET_EASY;		//��ģʽ
		return 1;				//�����ֱ�ӷ���
	}	//���ְ��� || (�Ҳఴ��Num LK���� && ���°���)
	if (get_key('2') || get_key('2' + 48) && Num_LK) {
		SD.game_flag = SET_HARD;		//����ģʽ
		return 1;
	}
	if (get_key('3') || get_key('3' + 48) && Num_LK) {
		SD.game_flag = SET_HARDEST;		//����ģʽ
		return 1;
	}
	if (get_key('4') || get_key('4' + 48) && Num_LK) {
		SD.game_flag = SET_SELF;		//�Զ���ģʽ
		return 1;
	}
	return 0;		//û��⵽����0
}

/*	��ⷽ��ָ���
*	��飺	�������Ӧ�������λ�õ��ƶ�������Ϣ����SD.game_insite_move������
*	������	��
*	����ֵ����ָ������·���1����ָ������·���0
*/
bool Key_move(void)
{
	SD.game_insite_move = NOT_MOVE;			//�ָ�Ĭ��ֵ
	if (get_key(37) || get_key('A')) {	//���������
		SD.game_insite_move = LEFT;//key code���� ����� ��37	�ϣ�38	�ң�39	�£�40
		return 1;
	}
	if (get_key(38) || get_key('W')) {
		SD.game_insite_move = UP;
		return 1;
	}
	if (get_key(39) || get_key('D')) {
		SD.game_insite_move = RIGHT;
		return 1;
	}
	if (get_key(40) || get_key('S')) {
		SD.game_insite_move = DOWN;
		return 1;
	}
	return 0;
}

/*	�����ƶ����λ��
*	��飺	ͨ�����SD.game_insite_move�м�¼���ƶ�������������ƶ����ͼƬ���λ�ã��Ͷ�Ӧ����λ��
*	������	game_x	:��Ԫ�����Ͻ�ͼƬ���������
*			game_y	:��Ԫ�����Ͻ�ͼƬ���������
*			game_i	:��Ԫ���Ӧ���������
*			game_j	:��Ԫ���Ӧ����������
*	����ֵ����ָ������·���1����ָ������·���0
*/
void Inputflag_Move(u_16* game_x, u_16* game_y, u_8* game_i, u_8* game_j)
{
	u_8 i = *game_i;
	u_8 j = *game_j;
	switch (SD.game_insite_move) {
	case LEFT:		//��������
		while (1) {
			j--;		//����
			if (j > 8) {		//����ʹ�õ�u_8���ͣ���j=0ʱ��ִ��j--��j��ֵ�ͻ��Ϊ255
				j = 8;
				i--;	//���Ƶ��߽������һ��
				if (i > 8)
					i = 8;
			}
			if (SD.Init[i][j] == 0)
				break;
		}
		break;
	case UP:		//��������
		while (1) {
			i--;		//����
			if (i > 8) {
				i = 8;
				j--;	//���Ƶ��߽������һ��
				if (j > 8)
					j = 8;
			}
			if (SD.Init[i][j] == 0)
				break;
		}
		break;
	case RIGHT:		//��������
		while (1) {
			j++;		//����
			if (j > 8) {
				j = 0;
				i = (i + 1) % 9;	//���Ƶ��߽������һ��
			}
			if (SD.Init[i][j] == 0)
				break;
		}
		break;
	case DOWN:		//��������
		while (1) {
			i++;		//����
			if (i > 8) {
				i = 0;
				j = (j + 1) % 9;		//���Ƶ��߽������һ��
			}
			if (SD.Init[i][j] == 0)
				break;
		}
		break;
	}
	if (SD.Linputflag)			//��ǰΪ����״̬�ƶ�
		if (SD.right_data[*game_i][*game_j][9] == 0) {		//���һ����
			putimage(*game_x, *game_y, &numimg[SD.game[*game_i][*game_j]]);	//��λ�ø�ԭ
		}
		else
			right_mouse_sign(*game_x, *game_y, *game_i, *game_j);				//�Ҽ��������״̬
	if (SD.Rinputflag)			//��ǰΪ���״̬�ƶ�
		if (SD.game[*game_i][*game_j] != 0)				//�Ҽ�״̬��ֻ�����һ���ı��״̬ȡ������
			putimage(*game_x, *game_y, &numimg[SD.game[*game_i][*game_j]]);	//��λ�ø�ԭ
		else
			putimage(*game_x + SD.right_data[*game_i][*game_j][9] % 3 * RIGHT_PICTURE_SIZE, *game_y + SD.right_data[*game_i][*game_j][9] / 3 * RIGHT_PICTURE_SIZE, &rightimg[0]);	//����һ���������״̬�ر�

	*game_x = GAME_START_X + (j * GAME_PICTURE_SIZE + j * GAME_INTERVAL + j / 3 * 2 * GAME_INTERVAL);		//����ͼ�ν����������λ��
	*game_y = GAME_START_Y + (i * GAME_PICTURE_SIZE + i * GAME_INTERVAL + i / 3 * 2 * GAME_INTERVAL);	//x��j�ı䣬y��i�ı�
	*game_i = i;		//���������е�λ��
	*game_j = j;
}

/*	�������
*	��飺	����ʵ�����������Ӧ��װ�İ�������������Ϸ���庯��SD_Play_Game()����
*	������	game_x	:��Ԫ�����Ͻ�ͼƬ���������
*			game_y	:��Ԫ�����Ͻ�ͼƬ���������
*			game_i	:��Ԫ���Ӧ���������
*			game_j	:��Ԫ���Ӧ����������
*	����ֵ���а������·���1���ް������·���0
*/
void Scan_Key(u_16* game_x, u_16* game_y, u_8* game_i, u_8* game_j)
{
	if (SD.Main_Interface)		//��������Զ������
	{
		if (Key_main_order() && SD.game_flag == GAME_AREA && SD.New_state == 1)	//������������
		{
			Key_place(game_x, game_y, game_i, game_j);		//ȷ����һ�������λ��ÿ�γ�ʼ����ִֻ��һ��
			SD.New_state = 0;			//��״̬���㣬�´γ�ʼ��֮ǰ����Ҫ��Ѱ�ҵ�һ������λ��
		}
		if (SD.Gameing || SD.Set_Self_Inerface)
			if (SD.Linputflag || SD.Rinputflag)		//�������״̬
			{
				if (Key_move())			//����λ�øı���
				{
					Inputflag_Move(game_x, game_y, game_i, game_j);
					SD.game_flag = GAME_AREA;		//����Ϸ�������
				}
				if (Key_number())
				{
					SD.game_flag = CHOOSE_AREA;
				}
			}
	}
	else		//���ý���
	{
		Key_set_order();
	}
}