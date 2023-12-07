#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
/*
* �ؾ�����: 1. Ż�� �˰��� �ϼ�( dialog �� ���)
*           2. ���� �������� ���
*           3. q ��� ������
*           4. �Ѹ� ������ ��� ����
*/
#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void camera(int x);
void observe(int see);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�
int px_log[PLAYER_MAX], py_log[PLAYER_MAX], player_rand[PLAYER_MAX];//������ ������ �α�, �÷��̾� �̵�Ȯ��
int loop;


int random_move;
int random_x, random_y;



void camera(int x) {//���� ����
	if (x == 1) {
		for (int i = 4; i < 8; i++) {
			back_buf[i][2] = '#';
		}
	}
	else if (x == 0) {
		for (int i = 4; i < 8; i++) {
			back_buf[i][2] = '@';
		}
	}
}


void move(int player) {//������ ���� Ȯ��

	random_move = randint(1, 10);

	if (random_move <= 1) {//������ ����Ȯ�� 10%
		random_x = 0;
		random_y = 0;
	}
	else if (random_move <= 2) {// �Ʒ��� ������ Ȯ��10%
		random_x = 0;
		random_y = 1;
	}
	else if (random_move <= 3) {// ���� �ö� Ȯ��10%
		random_x = 0;
		random_y = -1;
	}
	else {//�������� �̵��� Ȯ�� 70%
		random_x = -1;
		random_y = 0;
	}
}


void observe(int see) {
	bool gameover[PLAYER_MAX];
	if (see == 1) {//���� ������ ������ �Լ�

		for (int i = 1; i < n_alive; i++) {//���� ������ ai������
			if (gameover[i] == true && tick % period[i] == 0) {
				move(i);
			}
		}
	}
	else if (see == 0) {//���� ���� ai������
		for (int i = 1; i < n_alive; i++) {
			if (gameover[i] == true && player_rand[i] == 1) {
				move(i);
			}
		}
	}
}


int save[PLAYER_MAX];//
void stop(void) {
	for (int i = 0; i < n_player; i++) {
		px_log[i] = px[i];
		py_log[i] = py[i];
	}
}

void stop_chack(void) {//���� ���� �����ϰ�� ��Ƴ��� ����
	for (int i = 0; i < n_player; i++) {
		for (int j = i + 1; j < n_player; j++) {
			if (py_log[i] == py_log[j] && px_log[i] > px_log[j]) {
				save[i] = 0;//���� ���ɼ� ����
				break;
			}
			else {
				save[i] = 1;//���ɼ� ����
			}
		}
	}
	for (int i = 7; i >= 0; i--) {
		if (py_log[8] == py_log[i] && px_log[8] > px_log[i]) {
			save[8] = 0;//���� ���ɼ� ����
			break;
		}
		else {
			save[8] = 1;//���ɼ� ����
		}

	}
}

int dead_player[PLAYER_MAX];

void kill_player(void) {
	bool gameover[PLAYER_MAX];
	for (int i = 0; i < n_player; i++) {
		if (save[i] == 1) {
			if (px[i] != px_log[i] || py[i] != py_log[i]) {
				gameover[i] = false;
				player[i].is_alive = false;
				dead_player[i] = i;
				n_alive--;
			}
		}
	}
}



void win(void) {
	for (int i = 0; i < n_player; i++) {
		if (px[i] > 4 && px[i] < 8) {
			if (py[i] == 3) {
				char message[50];
				snprintf(message, sizeof(message), "player%d win", i);
				dialog(message, 5);
				winer[i] = 1;
				break;
			}
		}

		else if (px[i] == 3 || px[i] == 8) {
			if (py[i] == 2) {
				char message[50];
				snprintf(message, sizeof(message), "player%d win", i);
				dialog(message, 5);
				winer[i] = 1;
				break;
			}
		}
	}
}



void mugung(void) {
	if (tick == 10) {
		gotoxy(N_ROW + 1, 0);
		printf("��");

	}
	else if (tick == 100) {
		gotoxy(N_ROW + 1, 0);
		printf("����");
	}
	else if (tick == 300) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ");
	}
	else if (tick == 600) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ��");
	}
	else if (tick == 1000) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ����");
	}
	else if (tick == 1700) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� ��");
	}
	else if (tick == 2000) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� �Ǿ�");
	}
	else if (tick == 2200) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� �Ǿ���");
	}
	else if (tick == 2300) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� �Ǿ�����");
	}
	else if (tick == 2380) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� �Ǿ����ϴ�");
		camera(0);
		for (int i = 0; i < n_player; i++) {
			player_rand[i] = randint(1, 10);
		}
	}
	else if (tick == 5380) {
		for (int i = 0; i < n_player; i++) {
			if (!player[i].is_alive) {
				char message[50];
				snprintf(message, sizeof(message), "player%d dead", i);
				dialog(message, 5);
			}
		}
		for (int i = 0; i < 20; i++) {
			gotoxy(N_ROW + 1, i);
			printf(" ");
			tick = 0;
			camera(1);
		}
	}

}

void mugunghwa_map(void) {
	map_init(15, 40);
	
	for (int i = 0; i < n_alive; i++) {
		px[i] = 3 + i;
		py[i] = 38;

		back_buf[px[i]][py[i]] = '0' + i;
	}
}

void mugunghwa(void) {
	mugunghwa_map();
	camera(1);

	system("cls");
	display();
	while (1) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (tick % 20 == 0 && player[0].is_alive) {
			if (key == K_QUIT) {
				break;
			}
			else if (key != K_UNDEFINED) {
				move_manual(key);
			}
		}
		

		mugung();

		if (tick <= 3480) {
				observe(1);
		}
		else if (tick > 3480) {
				observe(0);
			stop_chack();
			kill_player();

		}

		stop();

		if (n_alive == 1) {
			for (int i = 1; i < n_player; i++) {
				if (player[i].is_alive) {
					char message[50];
					snprintf(message, sizeof(message), "player %d win", i);
					dialog(message, 4);
					winer[i] = 1;
					break;
				}
			}
		}

		win();
		display();
		Sleep(10);
		tick += 10;
	}
}