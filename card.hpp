/*
* Game card parent class.
*/

#ifndef CARD
#define CARD

#include <string>
#include <vector>
#include <queue>
#include "player.hpp"
#include "pictures.hpp"

class Card {
	/*
	* Parent card class. 
	* All cards inherit from this class.
	*/
	public:
		std::string cardType;
		std::string cardName;

		Card(std::string type, std::string name) {
			cardType = type;
			cardName = name;
		};
		// Method for player to interact with a card.
		virtual bool interact(Player& player, std::deque<std::string>& gameLog) = 0;

		std::vector <std::string> getCardRepr(int width, int height) {
			/*
			* Return a list of strings that represent the card
			* list will have length `height`
			* and each string will have length `width`
			*/

			std::vector <std::string> img;
			for (std::string s : cardArt()) {
				img.push_back('|' + padOrTruncate(s, width - 2) + '|');
			}
			std::vector <std::string> desc;
			for (std::string s : cardDesc()) {
				desc.push_back('|' + padOrTruncate(s, width - 2) + '|');
			}

			// padding: -2 for borders
			int vertical_padding = height - img.size() - desc.size() - 2;
			int top_padding = vertical_padding / 2;
			int bottom_padding = vertical_padding - top_padding;

			std::vector <std::string> cardRepr;
			cardRepr.push_back(std::string(width, '-')); // top border
			for (int i = 0; i < top_padding; i++) {
				cardRepr.push_back('|' + std::string(width - 2, ' ') + '|');
			}
			cardRepr.insert(cardRepr.end(), desc.begin(), desc.end());
			cardRepr.insert(cardRepr.end(), img.begin(), img.end());
			for (int i = 0; i < bottom_padding; i++) {
				cardRepr.push_back('|' + std::string(width - 2, ' ') + '|');
			}
			cardRepr.push_back(std::string(width, '-')); // bottom border

			return cardRepr;
		}

	protected:
		/* When not active, the card should be destroyed */
		bool active = true;
		bool checkActive() {
			/* returns a callback on whether the card is still active */
			if (!active) {
				return false;
			}
			return true;
		}

		virtual std::vector <std::string> cardArt() = 0;
		virtual std::vector <std::string> cardDesc() = 0;
};

#endif
