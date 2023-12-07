#define _CRT_SECURE_NO_WARNINGS
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3
#define DIR_SPACE   4
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];

int a;
void jebi_init(void);
void jebi_status(void);
bool jebi_placable(int row, int col);
void jebi_move_tail(int player, int nx, int ny);

void jebi_init(void) {
	map_init(15, 40);
	for (int i = 0; i < n_alive; i++) {
		back_buf[7][7 + 2 * i] = '?';
	}
	px[0] = 7;
	py[0] = 7;
	back_buf[px[0]][py[0]] = '@';
}


void jebi_status(void) {
	gotoxy(N_ROW, 0);
	int round = 1;
	printf("round %2d, turn: player %2d\n", round, 1);
}

void jebi_move_manual(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	case K_SPACE: dir = DIR_SPACE; break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0];
	ny = py[0] + dy[dir] * 2;

	if (!jebi_placable(nx, ny)) {
		return;
	}

	jebi_move_tail(0, nx, ny);
}


bool jebi_placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != '?') {
		return false;
	}
	return true;
}

void jebi_move_tail(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = '?';
	px[p] = nx;
	py[p] = ny;
}

void jebi_cho(void) {
	player[a].is_alive = false;
	n_alive--;
	char kill_name[50];
	sprintf(kill_name, "%d %s", a, "kill!");
	dialog(kill_name);
	jebi_init();
}

void jebi(void) {
	int round = 1;
	jebi_init();
	system("cls");
	display();
	jebi_status();
	a = randint(0, n_alive - 1);
	while(1){
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key == K_SPACE) {
			jebi_cho();
		}
		else if (key != K_UNDEFINED) {
			jebi_move_manual(key);
		}

		display();
		jebi_status();
		Sleep(10);
		tick += 10;
	}
}