include<iostream>
#include"player.h"

#define boardSize 10 //�Ղ̈��
#define squaresSize ( boardSize + 2 ) //�����Ώۂ̃}�X�ڂ̐�


int board[squaresSize][squaresSize] = { };

Players player("player1", "player2");

void initBoard();
bool isEnd();
void showBoard();
void printPlayer();
bool isPlaceable( int, int );
int checkDir(int, int, int, int);
void putStone(int, int);
void totalingStone( int* );
void printResult( int* );

int main() {

	int resultArray[2] = {};

	initBoard();

	while (isEnd()) {
	
		showBoard();

		printPlayer();

		int row, line;
		do {

			std::cout << "Input where you wanna put. \nex) >> [row] [line]" << std::endl << ">> ";
			std::cin >> row >> line;

		} while ( !isPlaceable( row, line ) );

		putStone( row, line );

		player.changePlayer();
	}

	showBoard();

	totalingStone( resultArray );
	printResult( resultArray );

	return 0;
}

void initBoard() {

	int initBasePosition = squaresSize / 2;

	board[initBasePosition][initBasePosition] = White;
	board[initBasePosition - 1][initBasePosition - 1] = White;
	board[initBasePosition][initBasePosition - 1] = Black;
	board[initBasePosition - 1][initBasePosition] = Black;

	//�ԕ�
	for (int i = 0; i < squaresSize; i++) {

		board[0][i] = Sentinel;
		board[i][0] = Sentinel;
		board[squaresSize - 1][i] = Sentinel;
		board[i][squaresSize - 1] = Sentinel;
	}

	return;
}


bool isEnd() {

	for (int i = 1; i < squaresSize - 1;i++) {
		for (int j = 1;j < squaresSize - 1;j++) {

			if (isPlaceable(i, j)) {

				return true;
			}
		}
	}

	//�v���C���[����サ�Ď��s
	player.changePlayer();
	for (int i = 1; i < squaresSize - 1; i++) {
		for (int j = 1; j < squaresSize - 1; j++) {

			if (isPlaceable(i, j)) {

				std::cout << "�u����ꏊ���Ȃ����߁A�v���[���[����サ�܂�." << std::endl;
				return true;
			}
		}
	}

	return false;
}

void showBoard() {

	for (int i = 0; i < squaresSize ; i++) {

		for (int j = 0; j < squaresSize ; j++) {

			switch (board[i][j]) {

			case Black:
				std::cout << "�Z";
				break;

			case White :
				std::cout << " ��";
				break;

			case None:
				std::cout << "�[";
				break;

			default:
				std::cout << "��";
				break;
			}
		}
		std::cout << std::endl;
	}
}

void printPlayer() {

	switch (player.getCurrentPlayerStone()) {

	case Black:
		std::cout << player.getCurrentPlayerName() << "(��)�̔�" << std::endl;
		break;

	case White:
		std::cout << player.getCurrentPlayerName() << "���(��)�̔�" << std::endl;
		break;
	}
}
bool isPlaceable(int _row, int _line) {

	if (board[_row][_line] == None) {
		//��ł���Ώ���

		for (int dir_row = -1; dir_row < 2; dir_row++) {
			for (int dir_line = -1; dir_line < 2; dir_line++) {

				if ( checkDir(_row, _line, dir_row, dir_line) ) {

					return true;
				}

			}
		}
	}

	return false;
}

int checkDir(int _row, int _line, int dir_row, int dir_line) {

	int num = 1;
	while (board[_row + dir_row * num][_line + dir_line * num] == player.getConfStn()) {
		//�����̐΂܂��͔ԕ��ł���ΏI��

		num++;
	}

	if (board[_row + dir_row * num][_line + dir_line * num] == player.getCurrentPlayerStone()) {
		//�ԕ��łȂ���Ύ����̐΂ł���A���߂�̂ŁA����̐΂̐���Ԃ�

		return num - 1;
	}

	return 0;
}


void putStone(int _row, int _line) {

	//�z�u�ӏ��̐΂̒u������
	board[_row][_line] = player.getCurrentPlayerStone();

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			int numChange = checkDir(_row, _line, i, j);

			for (int k = 1; k < numChange + 1; k++) {
				//���߂�ӏ��̐΂̒u������
				
				board[_row + i * k][_line + j * k] = player.getCurrentPlayerStone();
			}
		}
	}

	return;
}

void  totalingStone( int* result ) {

	int countBlackStone = 0;
	int countWhiteStone = 0;

	for (int i = 1; i < squaresSize - 1; i++) {
		for (int j = 1; j < squaresSize - 1; j++) {

			if (board[i][j] == Black) {

				countBlackStone++;
			}
			else if (board[i][j] == White) {

				countWhiteStone++;
			}
		}
	}

	result[0] = countBlackStone;
	result[1] = countWhiteStone;

	return;
}


void printResult(int* result) {

	for (int i = 0; i < boardSize; i++) {

		std::cout << "--";
	}
	std::cout << std::endl;

	std::cout << "���ʔ��\�I�I\n" << "���(��): " << result[0] << "��\n" << "���(��):" << result[1] << "��\n" << std::endl;

	if (result[0] < result[1]) {

		std::cout << "���(��)�̏���" << std::endl;
	}
	else if( result[0] > result[1] ){
	
		std::cout << "���(��)�̏���" << std::endl;
	}
	else {

		std::cout << "��������" << std::endl;
	}

	return;
}