/**
* @file srcsl_timer.c
* @brief ʵ�ּ�ʱ���ͼ�ʱִ�ж�������
* @author Silonca
*/
#include "include/srcsl_timer.h"

#include <stdlib.h>

/// @var timer_cnt ȫ��ʱ�䣬��ʱ������ܵĻ�����32λ�޷��������Ժ���Ϊ��λ���Լ�ʱ49.7�죬�ڵ�Ƭ�������赣�����
static volatile uint32_t timer_cnt = 0;

/**
* @brief �����������������ݽ�����Ĭ�Ͻ������������ṩ����ӿڣ�
* @param ����������ģ��ָ��
* @return ����״̬
* @retval SRCSL_PLAYER_LIST_FRAME_OK		 �������б����֡������������
* @retval SRCSL_PLAYER_LIST_END				 �������б������ĩβ
* @retval SRCSL_PLAYER_LIST_FORMAT_ERROR	 �������б������ʽ����
*/
static uint8_t srcsl_player_list_analyse( SrcslActionPlayer *player);


//����ȫ��ʱ��
void srcsl_timer_updata(void)
{
    ++timer_cnt;
}

//��ʱ��ʼ
void srcsl_timer_set( SrcslTimer *timer)
{
    timer->time = timer_cnt;
}

//��ȡ�Կ�ʼ������ʱ��
uint32_t srcsl_timer_get( SrcslTimer *timer)
{
    return timer_cnt - timer->time;
}


//------------------------------------------------------------


//������������ʼ��
void srcsl_player_init( SrcslActionPlayer *player, const char *list, void ( *act_func)( int32_t action_code))
{
    player->list = list;

    player->player_state = SRCSL_PLAYER_PAUSE;
    player->timer_flag = SRCSL_RESET;
    player->processing_action = 0;
    player->processing_time = 0;
    

    player->analyse_func = srcsl_player_list_analyse;
    player->act_func = act_func;
}


//�������Ž����������ã������Զ������
void srcsl_player_set_analyse_func(SrcslActionPlayer *player, uint8_t (*analyse_func)(void *))
{
	player->analyse_func = analyse_func;
}


//������������ʼ���źͼ�������
void srcsl_player_start( SrcslActionPlayer *player)
{
	//��������״̬�޶���
	if (player->player_state == SRCSL_PLAYER_PLAYING)
		return;

    player->player_state = SRCSL_PLAYER_PLAYING;
    player->timer_flag = SRCSL_RESET;
}

//����������ͣ
void srcsl_player_pause( SrcslActionPlayer *player)
{
    player->player_state = SRCSL_PLAYER_PAUSE;
}

//����������ֹ
void srcsl_player_stop( SrcslActionPlayer *player)
{
    player->player_state = SRCSL_PLAYER_STOP;
	player->timer_flag = SRCSL_RESET;
	player->processing_action = 0;
	player->processing_time = 0;
	player->list_process = 0;
}

//�����������¿�ʼ
void srcsl_player_restart( SrcslActionPlayer *player)
{
	srcsl_player_stop(player);
	srcsl_player_start(player);
}


//��������������������Ҫ����������
uint8_t srcsl_player_server( SrcslActionPlayer *player)
{
	//�Ƿ���ͣ
	if (player->player_state == SRCSL_PLAYER_PAUSE || player->player_state == SRCSL_PLAYER_STOP)
	{
		return SRCSL_PLAYER_PAUSE;
	}

	//��ʱ�����ڲ�����״̬�������ȡ�״̬��ϣ�ʱ����ʼ��һ�ֽ����Ͷ���
	if (player->timer_flag == SRCSL_RESET)
    {
		//����
		do
		{ 
			player->analyse_state = player->analyse_func(player);
			switch(player->analyse_state)
			{
				//�����ʽ����
				case SRCSL_PLAYER_LIST_FORMAT_ERROR:
					srcsl_player_stop( player);
					break;
			}
			player->act_func( player->processing_action);                
        //����ȴ�ʱ��Ϊ0�����ٴν���
		} while (player->processing_time == 0);

		srcsl_timer_set( &( player->timer));
		player->timer_flag = SRCSL_SET;
    }
	//�ȴ�ʱ��-1����ȥ����ʱ��
	if (player->timer_flag == SRCSL_SET && srcsl_timer_get(&(player->timer)) == player->processing_time - 1) {
		player->timer_flag = SRCSL_RESET;
		//������ĩβ����ʱ��������Ϊ���Ž���
		if (player->analyse_state == SRCSL_PLAYER_LIST_END)
		{
			srcsl_player_stop(player);
			return SRCSL_PLAYER_STOP;
		}
	}
	
	return player->player_state;
}

//�����������������ݽ���
static uint8_t srcsl_player_list_analyse(SrcslActionPlayer *player)
{
	int32_t num_1 = 0, num_2 = 0;

	//��ȡ��һ������
	num_1 = atoi(player->list + player->list_process);

	//�ҡ�,��
	for (; player->list[player->list_process] != ','; ++player->list_process)
	{
		//��ǰ�����ַ�����β��˵����ʽ����
		if (player->list[player->list_process] == '\0')
		{
			return SRCSL_PLAYER_LIST_FORMAT_ERROR;
		}
	}
	++player->list_process;

	//��ȡ�ڶ�������
	num_2 = atoi(player->list + player->list_process);

	//Ѱ�ҡ�;��
	for (; player->list[player->list_process] != ';'; ++player->list_process)
	{
		//��ǰ�����ַ�����β��˵����ʽ����
		if (player->list[player->list_process] == '\0')
		{
			return SRCSL_PLAYER_LIST_FORMAT_ERROR;
		}
	}
	++player->list_process;

	//��ֵ����
	if (num_1 == -1 || num_2 == -1)
	{
		return SRCSL_PLAYER_LIST_FORMAT_ERROR;
	}

	//��ȡ����       
	player->processing_action = num_1;
	//��ȡ�ӳ�ʱ��
	player->processing_time = num_2;


	//����������list��β
	if (player->list[player->list_process + 1] == '\0')
	{
		return SRCSL_PLAYER_LIST_END;
	}

	//֡��������
	return SRCSL_PLAYER_LIST_FRAME_OK;
}

