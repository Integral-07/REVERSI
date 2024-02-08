#include <iostream>

//�Ֆ� ��(0) ��(-1) ��(1) �ԕ�(2)
int board[10][10] = {};
//���
int player = -1;

//�Ֆʂ̐���
void make_board() {
	//�ԕ�
	for (int i = 0; i < 10; i++) {
		board[0][i] = 2;
		board[9][i] = 2;
		board[i][0] = 2;
		board[i][9] = 2;
	}
	//��{�ʒu
	board[4][4] = 1;
	board[5][5] = 1;
	board[4][5] = -1;
	board[5][4] = -1;
}

//�Ֆʂ̕\��
void show_board() {
	//�ԕ����܂߂ĕ\��
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (board[i][j]) {
			case -1:
				std::cout << "��";
				break;
			case 1:
				std::cout << "��";
				break;
			case 0:
				std::cout << "-";
				break;
			case 2:
				//std::cout << "~";
				break;
			default:
				break;
			}
		}
		std::cout << std::endl;
	}
}

//��Ԃ̕\��
void show_player() {
	switch (player) {
	case -1:
		std::cout << "���(��)�̎�Ԃł�" << std::endl;
		break;
	case 1:
		std::cout << "���(��)�̎�Ԃł�" << std::endl;
		break;
	default:
		//std::cout << "error" << std::endl;
		break;
	}
}

//����̍��W�������̕����ɋ��߂邩����
int check_dir(int i, int j, int dir_i, int dir_j) {
	//�w������ɑ���̐΂�����ꍇ�͎��̃}�X��T������
	int times = 1;
	while (board[i + dir_i * times][j + dir_j * times] == player * -1) {
		times++;
	}
	//�w������̍Ō�Ɏ����̐΂�����ꍇ
	if (board[i + dir_i * times][j + dir_j * times] == player) {
		//�w������ɑ���̐΂������邩��Ԃ�
		return times - 1;
	}
	//�w������̍Ō�Ɏ����̐΂��Ȃ����0��Ԃ�
	return 0;
}

//����̏ꏊ�ɒu�����Ƃ��ł��邩����
bool check_plc(int i, int j) {
	//�ꏊ����ł��邩�ǂ���
	if (board[i][j] == 0) {
		//�S������T��
		for (int dir_i = -1; dir_i < 2; dir_i++) {
			for (int dir_j = -1; dir_j < 2; dir_j++) {
				if (check_dir(i, j, dir_i, dir_j)) {
					//�z�u�\�ł����true��Ԃ�
					return true;
				}
			}
		}
	}
	return false;
}

//�I������
bool flag_fin() {
	//�u����ꏊ�����邩����
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_plc(i, j)) {
				return true;
			}
		}
	}

	//�v���C���[��ς��Ēu����ꏊ�����邩����
	player *= -1;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_plc(i, j)) {
				std::cout << "�u���ꏊ���Ȃ�����Player��ύX���܂���" << std::endl;
				return true;
			}
		}
	}

	return false;
}

//�΂�z�u����
void place_stn(int i, int j) {
	//�������ɑ���
	for (int dir_i = -1; dir_i < 2; dir_i++) {
		for (int dir_j = -1; dir_j < 2; dir_j++) {
			//���񂾐΂̐�
			int change_num = check_dir(i, j, dir_i, dir_j);
			//���񂾐΂̐������u��������
			for (int k = 1; k < change_num + 1; k++) {
				board[i + dir_i * k][j + dir_j * k] = player;
			}
		}
	}
	//�z�u�ӏ���u��������
	board[i][j] = player;
}

//���s����
void judge_board() {
	int count_b = 0; //���΂̐�
	int count_w = 0; //���΂̐�
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (board[i][j] == -1) {
				count_b++;
			}
			else if (board[i][j] == 1) {
				count_w++;
			}
		}
	}
	//���ʕ\��
	std::cout << "���" << count_b << ":���" << count_w << std::endl;
	//���s����
	if (count_b > count_w) {
		std::cout << "���̏���" << std::endl;
	}
	else if (count_w > count_b) {
		std::cout << "���̏���" << std::endl;
	}
	else {
		std::cout << "��������" << std::endl;
	}
}

int main() {
	//�Ֆʂ̐���
	make_board();
	//�I���܂Ń��[�v
	while (flag_fin()) {
		//�Ֆʂ̕\��
		show_board();
		//��Ԃ̕\��
		show_player();
		//���͎�t
		int i, j;
		do {
			std::cout << "�z�u�ꏊ����͂��Ă�������" << std::endl;
			std::cin >> i >> j;
		} while (!check_plc(i, j));
		//�΂�z�u����
		place_stn(i, j);
		//��Ԃ����ւ���
		player *= -1;
	}
	//�Ֆʂ̕\��
	show_board();
	//��������
	judge_board();
	return 0;
}