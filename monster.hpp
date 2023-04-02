/*
* Monster Card
*/
#ifndef MONSTER
#define MONSTER

#include <iostream>

#include "card.hpp"
#include "combatant.hpp"
#include "player.hpp"


class MonsterCard : public Card {
	/*
	* A monster card is a monster
	* that the player can combat.
	*/
	protected:
		Combatant combatant;
		unsigned int reward;

	public:
		MonsterCard(
			std::string name,
			unsigned int h = 3,
			unsigned int a = 3,
			unsigned int d = 3,
			unsigned int r = 5
		): Card("monster", name) {
			combatant = Combatant(cardName, h, a, d);
			reward = r;
		};
		
		bool interact(Player& player, std::deque<std::string>& gameLog) {
			// Player attacks first
			//TODO: mechanism to decide who attacks first
			gameLog.push_back("Player attacks");
			player.attack(combatant, gameLog);
			active = combatant.stillAlive();
			if (active) {
				combatant.attack(player, gameLog);
			}
			else {
				gameLog.push_back("Monster defeated! Gain " + std::to_string(reward) + " gold");
				player.addGold(reward);
			}
			return checkActive();
		}

		~MonsterCard() {}

	private:
		std::vector <std::string> cardArt() {
			std::vector <std::string> v;
			v.push_back(R"(    ___    )");
			v.push_back(R"( _ / @@\   )");
			v.push_back(R"(( \  O /__ )");
			v.push_back(R"(  /____|__))");
			v.push_back(R"( /      \  )");
			v.push_back(R"(/        \ )");
			v.push_back(R"(`"""""```` )");
			return v;
		}
		
		std::vector <std::string> cardDesc() {
			std::vector<std::string> v;
			v.push_back(cardName);
			v.push_back(cardType);
			v.push_back("Health: " + std::to_string(combatant.getHealth()));
			v.push_back("Attack: " + std::to_string(combatant.getAtt()));
			v.push_back("Defense: " + std::to_string(combatant.getDef()));
			v.push_back("Reward: " + std::to_string(reward));
			return v;
		}
};

#endif
