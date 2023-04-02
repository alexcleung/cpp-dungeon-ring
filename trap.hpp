/*
* Mystery card.
*/
#ifndef TRAP
#define TRAP

#include <iostream>

#include "card.hpp"
#include "player.hpp"

class TrapCard : public Card {
	/*
	* A trap card invokes some negative effect on the player.
	*/
	public:
		// put "???" to not reveal to the player that it is a trapcard.
		TrapCard(std::string name) : Card("trap", name) {};

	protected:
		std::vector<std::string> cardDesc() {
			std::vector <std::string> v;
			v.push_back("???"); // trap card - hide name
			v.push_back("???"); // trap card - hide type
			return v;
		}

		// trap card image is hidden
		std::vector <std::string> cardArt() {
			std::vector <std::string> v;
			v.push_back(R"(________ )");
			v.push_back(R"(| ____  |)");
			v.push_back(R"(|_|  |  |)");
			v.push_back(R"( ____|  |)");
			v.push_back(R"( | _____|)");
			v.push_back(R"( |_|     )");
			v.push_back(R"( |_|     )");
			return v;
		}
};

class GoldSteal : public TrapCard {
	/*
	* Steals gold from the player
	* Based on difficulty 
	*/
	public:
		GoldSteal() : TrapCard("goldSteal") {};

		bool interact(Player& player, std::deque<std::string>& gameLog) {
			//TODO: based on difficulty
			player.subGold(1);
			gameLog.push_back("Stepped on gold trap, lost 1 gold!");
			active = false;
			return checkActive();
		}
};

class HealthSteal : public TrapCard {
	/*
	* Steals gold from the player
	* Based on difficulty
	*/
	public:
		HealthSteal() : TrapCard("healthSteal") {};

		bool interact(Player& player, std::deque<std::string>& gameLog) {
			//TODO: based on difficulty
			player.subHealth(1);
			gameLog.push_back("Stepped on health trap, lost 1 health!");
			active = false;
			return checkActive();
		}
};

#endif
