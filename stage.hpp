/*
* Tracks the state of a stage (level) of the game.
*/
#ifndef STAGE
#define STAGE

#include <list>
#include <queue>

#include "player.hpp"
#include "card.hpp"
#include "item.hpp"
#include "monster.hpp"
#include "pictures.hpp"
#include "trap.hpp"
#include "rng.hpp"

class Stage {
	private:
		unsigned int stageNum;

		//for managing cards
		std::list<std::unique_ptr<Card>> stageCards;

		/* 
		player position:
			the player's position is indicated
			by the index of the card to the player's left. 
		*/
		int playerPosition = 0;

		int getRightPosition() {
			/* index of card to the player's right */
			return (playerPosition + 1) % (int)stageCards.size();
		}

	public:
		Stage(
			unsigned int diff,
			unsigned int s
			) {
			stageNum = s;

			//TODO: these elements dynamic based on difficulty
			// generate the cards
			int nCards = 5;
			for (int i = 0; i < nCards; i++) {
				std::unique_ptr<Card> newCard;
				switch ((int)std::floor(runif(0, 5))) {
					case 0:
						newCard.reset(new Armor());
						break;
					case 1:
						newCard.reset(new Sword());
						break;
					case 2:
						newCard.reset(new GoldSteal());
						break;
					case 3:
						newCard.reset(new HealthSteal());
						break;
					case 4:
						newCard.reset(new MonsterCard("ghost"));
						break;
				};
				stageCards.push_back(std::move(newCard));
			}
		}

		void interact(Player& player, bool left, std::deque < std::string>& gameLog) {
			/*
			player interacts with a card, either to left or right
			*/
			size_t pos;
			if (left) {
				pos = playerPosition;
			}
			else {
				pos = getRightPosition();
			}

			auto cardPtr = stageCards.begin();
			std::advance(cardPtr, pos);
			bool cardActive = (**cardPtr).interact(player, gameLog);

			// conditionally delete the card and adjust player position
			if (!cardActive) {
				stageCards.erase(cardPtr);
				if (!isActive()) {
					return; // exit right away if no cards left
				}
				if (pos <= playerPosition) {
					// shift player position to the left
					// if the card index removed is lower than player index
					move(true, gameLog);
				}
			}
		}

		void move(bool left, std::deque<std::string>& gameLog) {
			if (left) {
				gameLog.push_back("Moving left");
				int p = (playerPosition - 1) % ((int)stageCards.size());
				playerPosition = p < 0 ? p + stageCards.size() : p;
			}
			else {
				gameLog.push_back("Moving right");
				playerPosition = getRightPosition();
			}
		}

		bool isActive() {
			return (int)stageCards.size() > 0;
		}

		int getnCards() {
			return (int)stageCards.size();
		}

		int getPlayerPosition() {
			return playerPosition;
		}

		void drawStage(int screenWidth, int screenHeight) {
			/*
			* Draw the cards to the left and right of the player
			*/
			int cardWidth = (screenWidth - 20) / 2; //TODO: dynamic?

			std::vector<std::vector<std::string>> cardReprs;
			auto leftCardPtr = stageCards.begin();
			std::advance(leftCardPtr, playerPosition);
			cardReprs.push_back((**leftCardPtr).getCardRepr(cardWidth, screenHeight));

			if (playerPosition != getRightPosition()) {
				auto rightCardPtr = stageCards.begin();
				std::advance(rightCardPtr, getRightPosition());
				cardReprs.push_back((**rightCardPtr).getCardRepr(cardWidth, screenHeight));
			}

			std::string out;
			for (int i = 0; i < screenHeight; i++) {
				std::string line = "";
				for (int j = 0; j < cardReprs.size(); j++) {
					line += cardReprs[j][i];
				}
				line = padOrTruncate(line, screenWidth);
				out += line + "\n";
			}

			system("cls");
			std::cout << padOrTruncate("### STAGE " + std::to_string(stageNum) + " ###", screenWidth) << "\n";
			std::cout << out;
		}

};

#endif
