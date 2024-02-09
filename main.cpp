#include<iostream>


//#define boradSize 10 //盤の一辺
//#define squaresSize boradSize + 2 //処理対象のマス目の数

#define squaresSize 20

int board[squaresSize][squaresSize] = { };
int player = 1;

enum Stone {

	None = 0,
	Black = -1,
	White = 1,
	Sentinel = 2,
};

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

		putStone( row, line);

		player *= -1;
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

	//番兵
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

	//プレイヤーを交代して試行
	player *= -1;
	for (int i = 1; i < squaresSize - 1; i++) {
		for (int j = 1; j < squaresSize - 1; j++) {

			if (isPlaceable(i, j)) {

				std::cout << "置ける場所がないため、プレーヤーを交代します." << std::endl;
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
				std::cout << "〇";
				break;

			case White :
				std::cout << "●";
				break;

			case None:
				std::cout << "ー";
				break;

			default:
				std::cout << "0";
				break;
			}
		}
		std::cout << std::endl;
	}
}

void printPlayer() {

	switch (player) {

	case Black:
		std::cout << "先手(黒)の番" << std::endl;
		break;

	case White:
		std::cout << "後手(白)の番" << std::endl;
		break;
	}
}
bool isPlaceable(int _row, int _line) {

	if (board[_row][_line] == None) {
		//空であれば処理

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
	while (board[_row + dir_row * num][_line + dir_line * num] == player * -1) {
		//自分の石または番兵であれば終了

		num++;
	}

	if (board[_row + dir_row * num][_line + dir_line * num] == player) {
		//番兵でなければ自分の石であり、挟めるので、相手の石の数を返す

		return num - 1;
	}

	return 0;
}


void putStone(int _row, int _line) {

	//配置箇所の石の置き換え
	board[_row][_line] = player;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2;j++) {

			int numChange = checkDir(_row, _line, i, j);

			for (int k = 1; k < numChange; k++) {
				//挟める箇所の石の置き換え
				
				board[_row + i * k][_line + j * k] = player;
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


}