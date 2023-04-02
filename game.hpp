/*
* Tracks the state of the game.
*/
#ifndef GAME
#define GAME

# include <iostream>
# include <cctype>
# include <conio.h>
# include <queue>

# include "stage.hpp"
# include "player.hpp"
# include "pictures.hpp"

class Game {
	private:
		Player player = Player();

		std::unique_ptr<Stage> stage;

		// TODO: how many?
		int nStages = 2;
		// TODO: scale diff
		int stageDifficulty = 1;
		// TODO: how to make this dynamic?
		int screenWidth = 100;
		int screenHeight = 20;

		// number of lines to have in game console.
		int logSize = 5;
		std::deque<std::string> gameLog;

		void printGameLog() {
			while (gameLog.size() > logSize) {
				gameLog.pop_front();
			}

			for (std::string logString : gameLog) {
				std::cout << logString << "\n";
			}
		}

		void spawnStage(int diff, int s){
			stage.reset(new Stage(diff, (unsigned int) s));
		}

		void titleScreen() {
			std::vector<std::string> title;
			title.push_back(R"( _____                                       _____  _             )");
			title.push_back(R"(|  __ \                                     |  __ \(_)            )");
			title.push_back(R"(| |  | |_   _ _ __   __ _  ___  ___  _ __   | |__) |_ _ __   __ _ )");
			title.push_back(R"(| |  | | | | | '_ \ / _` |/ _ \/ _ \| '_ \  |  _  /| | '_ \ / _` |)");
			title.push_back(R"(| |__| | |_| | | | | (_| |  __/ (_) | | | | | | \ \| | | | | (_| |)");
			title.push_back(R"(|_____/ \__,_|_| |_|\__, |\___|\___/|_| |_| |_|  \_\_|_| |_|\__, |)");
			title.push_back(R"(                     __/ |                                   __/ |)");
			title.push_back(R"(                    |___/                                   |___/ )");
			title.push_back(R"(Press any key to continue...)");

			for (std::string line : title) {
				std::cout << padOrTruncate(line, screenWidth) << "\n";
			}
			_getch();
			system("cls");
		}

		void rulesScreen() {
			std::cout << padOrTruncate("### RULES ###", screenWidth) << "\n";
			std::cout << "*  The goal is to make it through each stage of the dungeon." << "\n";
			std::cout << "*  Each stage is made up of a set of cards, all of which must be cleared to progress." << "\n";
			std::cout << "*  The player can move left or right, as well as interact with the card on their left or right." << "\n";
			std::cout << "\n";
			std::cout << "Press any key to continue..." << "\n";

			_getch();
			system("cls");
		}

		void winScreen() {
			std::vector<std::string> v;
			v.push_back(R"(__     ______  _    _  __          _______ _   _ )");
			v.push_back(R"(\ \   / / __ \| |  | | \ \        / /_   _| \ | |)");
			v.push_back(R"( \ \_/ / |  | | |  | |  \ \  /\  / /  | | |  \| |)");
			v.push_back(R"(  \   /| |  | | |  | |   \ \/  \/ /   | | | . ` |)");
			v.push_back(R"(   | | | |__| | |__| |    \  /\  /   _| |_| |\  |)");
			v.push_back(R"(   |_|  \____/ \____/      \/  \/   |_____|_| \_|)");
			v.push_back(R"(                      ,                          )");
			v.push_back(R"(                   \  :  /                       )");
			v.push_back(R"(                `. __/ \__ .'                    )");
			v.push_back(R"(                _ _\     /_ _                    )");
			v.push_back(R"(                   /_   _\                       )");
			v.push_back(R"(                 .'  \ /  `.                     )");
			v.push_back(R"(                   /  :  \                       )");
			v.push_back(R"(                      '                          )");
			v.push_back(R"(Press any key to exit...)");

			for (std::string line : v) {
				std::cout << padOrTruncate(line, screenWidth) << "\n";
			}
			_getch();
			system("cls");
		}

		void loseScreen() {
			std::vector<std::string> v;
			v.push_back(R"(__     ______  _    _   _      ____   _____ ______ )");
			v.push_back(R"(\ \   / / __ \| |  | | | |    / __ \ / ____|  ____|)");
			v.push_back(R"( \ \_/ / |  | | |  | | | |   | |  | | (___ | |__   )");
			v.push_back(R"(  \   /| |  | | |  | | | |   | |  | |\___ \|  __|  )");
			v.push_back(R"(   | | | |__| | |__| | | |___| |__| |____) | |____ )");
			v.push_back(R"(   |_|  \____/ \____/  |______\____/|_____/|______|)");
			v.push_back(R"(                 {}         {}                    )");
			v.push_back(R"(                  \  _---_  /                     )");
			v.push_back(R"(                   \/     \/                      )");
			v.push_back(R"(                    |() ()|                       )");
			v.push_back(R"(                     \ + /                        )");
			v.push_back(R"(                    / HHH \                       )");
			v.push_back(R"(                   /  \_/  \                      )");
			v.push_back(R"(                 {}         {}                    )");
			v.push_back(R"(Press any key to exit...)");

			for (std::string line : v) {
				std::cout << padOrTruncate(line, screenWidth) << "\n";
			}
			_getch();
			system("cls");
		}

	public:
		int playGame() {
			titleScreen();
			rulesScreen();
			for (int s = 0; s < nStages; s++) {
				std::cout << "Entering stage " << s+1 << "\n";
				std::cout << "Press any key to continue..." << "\n";
				_getch();
				system("cls");
				spawnStage(stageDifficulty, s+1);
				int stageExit = playStage();
				switch (stageExit) {
					case 0:
						system("cls");
						if ((s + 1) < nStages) {
							std::cout << "Stage " << s + 1 << " Cleared!\n";
							std::cout << "Press any key to continue..." << "\n";
							_getch();
							system("cls");
							continue;
						}
						else {
							winScreen();
							return 0;
						}
					case 1:
						system("cls");
						loseScreen();
						return 1;
					case 2:
						system("cls");
						std::cout << "You quit\n";
						return 2;
				}
			}
			return 0;
		}

		int playStage() {
			/* 
			returns 0 if the stage completed
			returns 1 if the player died
			returns 2 if the stage was quit
			*/
			while ((*stage).isActive()) {
				system("cls");
				(*stage).drawStage(screenWidth, screenHeight);
				std::cout << "**************************************\n";
				logGameState();
				std::cout << "--------------------------------------\n";
				printGameLog();
				std::cout << "\n";
				std::string cmd = "A - Move Left   D - Move Right   J - Interact Left   L - Interact Right   Q - Quit\n";
				char user_input;
				std::cout << cmd;
				user_input = _getch();

				switch (toupper(user_input)) {
					case (65): // "A"
						(*stage).move(true, gameLog);
						break;
					case(68): // "D"
						(*stage).move(false, gameLog);
						break;
					case(74): // "J"
						(*stage).interact(player, true, gameLog);
						break;
					case(76): // "L"
						(*stage).interact(player, false, gameLog);
						break;
					case(81): //"Q"
						return 2;
					default:
						std::cout << "Invalid input!\n";
						continue;
				}
				if (!player.stillAlive()) {
					return 1;
				}
			}
			return 0;
		}

		void logGameState() {
			std::cout << "Gold: " << player.getGold() << "   ";
			std::cout << "Health: " << player.getHealth() << "   ";
			std::cout << "Attack: " << player.getAtt() << "   ";
			std::cout << "Defense: " << player.getDef() << "   ";
			std::cout << "Cards remaining " << (*stage).getnCards() << "   ";
			std::cout << "\n";
		}
};

#endif
