/*
* Item Card
*/
#ifndef ITEM
#define ITEM

#include <iostream>
#include "card.hpp"
#include "player.hpp"

class ItemCard : public Card {
	/*
	* An item card can be picked up
	* by the player for a certain cost (gold).
	*/
	protected:
		unsigned int cost;

		std::vector<std::string> cardDesc() {
			std::vector <std::string> v;
			v.push_back(cardName);
			v.push_back(cardType);
			v.push_back("Cost: " + std::to_string(cost));
			return v;
		}

	public:
		ItemCard(
			std::string name,
			unsigned int c = 5
		) : Card("item", name) {
			cost = c;
		};
		virtual void giveTo(Player& player) = 0;
		bool interact(Player& player, std::deque<std::string>& gameLog) {
			if (player.getGold() >= cost) {
				// player pays `cost`, gets given the item
				gameLog.push_back("Paying " + std::to_string(cost) + " gold");
				player.subGold(cost);
				giveTo(player);
				gameLog.push_back("Acquired " + cardName + "!");
				active = false;
			}
			else {
				gameLog.push_back("Not enough gold!");
			}
			return checkActive();
		}
};


class Armor : public ItemCard {
	/*
	* Increases the player's defense.
	*/
	public:
		Armor() : ItemCard("armor", 1) {};
		const unsigned int def = 1;
		void giveTo(Player& player) {
			player.addDef(1);
		}
	private:
		std::vector <std::string> cardArt() {
			std::vector <std::string> v;
			v.push_back(R"(____________)");
			v.push_back(R"(|    ||    |)");
			v.push_back(R"(|___o()o___|)");
			v.push_back(R"(|__((<>))__|)");
			v.push_back(R"(\   o\/o   /)");
			v.push_back(R"( \   ||   / )");
			v.push_back(R"(  ' _||_ '  )");
			return v;
		}
};

class Sword : public ItemCard {
	/*
	* Increases the player's attack.
	*/
	public:
		Sword() : ItemCard("sword", 1) {};
		const unsigned int att = 1;
		void giveTo(Player& player) {
			player.addAtt(1);
		}
	private:
		std::vector <std::string> cardArt() {
			std::vector <std::string> v;
			v.push_back(R"(   ^  )");
			v.push_back(R"(  ||  )");
			v.push_back(R"(  ||  )");
			v.push_back(R"(  ||  )");
			v.push_back(R"(__||__)");
			v.push_back(R"(  II  )");
			v.push_back(R"(  II  )");
			return v;
		}

};

#endif