// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init() {
	srand((unsigned int)time(NULL));
	FILE* fp;
	fopen_s(&fp, DATA_FILE, "r");
	if (fp == NULL) {
		return -1; // -1 �����ϸ� �����Լ����� ó���ϰ� ����
	}
	// �÷��̾� ������ load

	fscanf_s(fp, "%d", &n_player);
	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		// ���� �� ��� ����(����ü ������, ��������������)
		PLAYER* p = &player[i];
		// ���Ͽ��� �� ���� �ִ� �б�
		fscanf_s(fp, "%s%d%d", p->name, (unsigned int)sizeof(p->name),
			&(p->intel), &(p->str));
		p->stamina = 100; // 100%
		// ���� ����
		p->is_alive = true;
		p->hasitem = false;
	}
	// ������ ������ load
	                                                                                 int n_item;
	fscanf_s(fp, "%d", &n_item);
	for (int i = 0; i < n_item; i++) {
		fscanf_s(fp, "%s%d%d%d",
			item[i].name, (unsigned int)sizeof(item[i].name),
			&(item[i].intel_buf),
			&(item[i].str_buf),
			&(item[i].stamina_buf));
	}
	fclose(fp);
	return 0;
}
int intro() {
	printf(
		"    _         _           _    _                                               _  \n"
		"   (_)       (_)         | |  | |                                             | | \n"
		"    _   ___   _  _ __    | |_ | |__    ___       _ __   __ _  _ __ ___  ___   | | \n"
		"   | | / _ \\  | || '_ \\    | __|| '_ \\   /          |/ _` || '_ ` _\\ / _          | | \n"
		"   | || (_) || || | | |  |   |_ | | | ||__/      |(_| || (_| || | | | |||__/  |_|\n"
		"   | |  \\___/ |_||_| |_|    \\__||_| |_|  \\___|       \\__,||\\__,_||_| |_| |_|  \\__|  (_)\n"
		"  _/ |                                            __/ |                           \n"
		"  |__/                                           |___/                            \n"
	);
	Sleep(700);
	return 0;
}


void ending(void) {
	for (int i = 0; i < n_player; i++) {
		if (winer[i] == 1)
		{
			system("cls");
			printf("����ڴ� player%d �Դϴ�", i);

		}
	}

}

int main(void) {
	jjuggumi_init();
	//sample();
	//mugunghwa();
	//nightgame();
	//juldarigi();
	jebi();
	return 0;
}
