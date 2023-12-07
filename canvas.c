#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	printf("                 intl  str  stm\n");
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s  %2d  %2d    %2d\n", p, &player[p] ? "alive" : "DEAD", player[p].intel, player[p].str, player[p].stamina);
	}
}



void dialog(char message[]) {
	int sec = DIALOG_DURATION_SEC;
	while (sec >= 0) {
		for (int i = 0; i < 12; i++) {
			gotoxy(6, 14 + i);
			printf("*");
			gotoxy(8, 14 + i);
			printf("*");
		}
		gotoxy(7, 14);
		printf("*");
		gotoxy(7, 25);
		printf("*");

		for (int i = 0; i <= sec; i++) {
			gotoxy(7, 15);
			printf("%d", sec);
			draw();
			sec--;
			gotoxy(7, 17);
			printf(message);
			draw();
			Sleep(1000);

			if (i == 0) {
				for (int i = 0; i < 12; i++) {
					gotoxy(6, 14 + i);
					printf(" ");
					gotoxy(7, 14 + i);
					printf(" ");
					gotoxy(8, 14 + i);
					printf(" ");
				}
			}
			draw();
		}
	}

}

