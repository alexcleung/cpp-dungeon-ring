/*
Player object.
*/
#ifndef PLAYER
#define PLAYER

#include <iostream>

#include "combatant.hpp"

class Player : public Combatant{
	/*
	* This object tracks the player state through the game.
	*/
    private:
        unsigned int gold;

    public:
        Player(
            unsigned int h = 10,
            unsigned int a = 5,
            unsigned int d = 5,
            unsigned int g = 5
        ) : Combatant("player", h, a, d) {
            gold = g;
        };

        // public functions to interact with protected member `gold`
        void setGold(unsigned int g) {
            gold = g;
        }
        void addGold(unsigned int g) {
            gold = (gold >= (UINT_MAX - g)) ? UINT_MAX : gold + g;
        }
        void subGold(unsigned int g) {
            gold = (gold <= g) ? 0 : gold - g;
        }
        unsigned int getGold() {
            return gold;
        }
};

#endif
