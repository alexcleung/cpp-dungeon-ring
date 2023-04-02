/*
* Combatants are classes that have health, att, def attributes
* i.e., Players or Monsters
*/
#ifndef COMBATANT
#define COMBATANT

#include <string>

class Combatant {
    protected:
        unsigned int health;
        unsigned int att;
        unsigned int def;

    public:
        std::string name;

        Combatant(
            std::string n = "combatant",
            unsigned int h = 20,
            unsigned int a = 5,
            unsigned int d = 5
        ) {
            name = n;
            health = h;
            att = a;
            def = d;
        }
        // public functions to interact with private member `health`
        void setHealth(unsigned int h) {
            health = h;
        }
        void addHealth(unsigned int h) {
            health = (health >= (UINT_MAX - h)) ? UINT_MAX : health + h;
        }
        void subHealth(unsigned int h) {
            health = (health <= h) ? 0 : health - h;
        }
        unsigned int getHealth() {
            return health;
        }

        // public functions to interact with private member `att`
        void setAtt(unsigned int a) {
            att = a;
        }
        void addAtt(unsigned int a) {
            att = (att >= (UINT_MAX - a)) ? UINT_MAX : att + a;
        }
        void subAtt(unsigned int a) {
            att = (att <= a) ? 0 : att - a;
        }
        unsigned int getAtt() {
            return att;
        }

        // public functions to interact with private member `def`
        void setDef(unsigned int d) {
            def = d;
        }
        void addDef(unsigned int d) {
            def = (def >= (UINT_MAX - d)) ? UINT_MAX : def + d;
        }
        void subDef(unsigned int d) {
            def = (def <= d) ? 0 : def - d;
        }
        unsigned int getDef() {
            return def;
        }

        // attack another enemy
        void attack(Combatant& enemy, std::deque<std::string>& gameLog) {
            unsigned int dmg = (att > enemy.getDef()) ? att - enemy.getDef() : 0;
            gameLog.push_back(name + " attacked " + enemy.name + " for " + std::to_string(dmg) + " damage!");
            enemy.subHealth(dmg);
        }

        // callback to return still alive
        bool stillAlive() {
            return (health <= 0) ? false : true;
        }
};

#endif
