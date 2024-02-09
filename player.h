#pragma once
#include<string>


enum Stone {

	None = 0,
	Black = -1,
	White = 1,
	Sentinel = 2,
};

class Players {

	class Player {

	private:

		std::string name = "";
		Stone stn = Black;

	public:

		Player() {

		}

		Player(std::string _name, Stone _stn) :name(_name), stn(_stn) {

		}

		bool operator==(Player& x) {

			if (this->stn == x.stn) {

				return true;
			}

			return false;
		}

		std::string getName() { return name; }

		Stone getStone() { return stn; }
	};
private:

	Player* player;
	Player currentPlayer;

public:

	Players(std::string _name_player1, std::string _name_player2) {

		player = new Player[2];

		player[0] = Player(_name_player1, Black);
		player[1] = Player(_name_player2, White);

		currentPlayer = player[0];
	}

	void changePlayer() {

		if (currentPlayer == player[0]) {

			currentPlayer = player[1];
		}
		else {

			currentPlayer = player[0];
		}

		return;
	}

	Stone getConfStn() {

		if (currentPlayer.getStone() == Black) {

			return White;
		}
		
		return Black;
	}

	std::string getCurrentPlayerName() {

		return currentPlayer.getName();
	}
	
	Stone getCurrentPlayerStone() {

		return currentPlayer.getStone();
	}
};