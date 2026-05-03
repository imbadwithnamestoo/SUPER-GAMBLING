#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <cmath>

#define wait(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

int checkLives(int amount) {
	if (amount > 0) {
		return true;
	} else {
		return false;
	}
}
int newNum(int currentNum, int guess) {
	int newNum;
	if (currentNum - 3 == guess) {
		newNum = currentNum + 3;
	} else if (currentNum - 3 != guess) {
		newNum = currentNum - 3;
	}
	return newNum;
}

void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int main() {
	clear();
	char choice;
	std::string exitChoice;
	int menuChoice;

	int totalWins = 0;
	int totalLoss = 0;
	int totalPoints = 100;

	std::string playerName;

	std::ifstream checkFile("save.txt");

	if (!checkFile.is_open()) {
		std::cout << "Please choose a username: ";
		std::cin >> playerName;

		std::ofstream outFile("save.txt");
		if (outFile.is_open()) {
			outFile << playerName << std::endl; // username
			outFile << 100 << std::endl; // points
			outFile << 0 << std::endl; // wins
			outFile << 0; // losses
			outFile.close();
		}
	} else {
		checkFile >> playerName;
		checkFile >> totalPoints;
		checkFile >> totalWins;
		checkFile >> totalLoss;
		checkFile.close();
		std::cout << "Welcome back, " << playerName << "!" << std::endl;
		wait(350);
	}

	std::cout << "\033[1;37mSUPER GAMBLING\033[0m \033[33m//\033[0m \033[36mV1.1\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    
    std::cout << "\033[32m[1]\033[0m Start Game" << std::endl;
    std::cout << "\033[33m[2]\033[0m View Stats" << std::endl;
    std::cout << "\033[31m[3]\033[0m Exit" << std::endl;
    
    std::cout << "------------------------------------" << std::endl;
    std::cout << "\033[1;37mAction:\033[0m ";
	std::cin >> menuChoice;

	switch (menuChoice) {
    case 2:
        clear();
        std::cout << "\033[1;37mPLAYER STATS\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
        std::cout << "------------------------------------" << std::endl;

		std::cout << "Points: \033[33m" << totalPoints << "\033[0m" << std::endl;
        std::cout << "Wins:   \033[1;32m" << totalWins << "\033[0m" << std::endl;
        std::cout << "Losses: \033[1;31m" << totalLoss << "\033[0m" << std::endl;
		std::cout << "W/L:    \033[1;36m" << (totalLoss == 0 ? (float)totalWins : (float)totalWins / totalLoss) << "\033[0m" << std::endl;
        std::cout << "------------------------------------" << std::endl;

        std::cout << "Press \033[1;37mENTER\033[0m to return ";
        
        std::cin.ignore(1000, '\n');
        std::cin.get();
		main();
        break; 

    case 3:
        clear();
        std::cout << "Exiting..." << std::endl;
        exit(0);
        break;
}
	do {
		std::srand(std::time(0));
		int secretNum = std::rand() % 10 + 1;
		int guess = 0;
		int lives = 5;
		int difficulty = 0;
		int wager;
		int minWager = totalPoints * 0.15;

		if (minWager <= 0) {
			minWager = totalPoints;
		}

		std::string status = "I'm thinking of a number between 1 and 10.";

		clear();
		std::cout << "\033[1;37mDIFFICULTY\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
		std::cout << "------------------------------------" << std::endl;

		std::cout << "\033[32m1.\033[0m Easy   (7 lives)" << std::endl;
		std::cout << "\033[33m2.\033[0m Normal (5 lives)" << std::endl;
		std::cout << "\033[31m3.\033[0m Hard   (3 lives)" << std::endl;
		std::cout << "\033[1;37m-1.\033[0m Exit to menu" << std::endl;

		std::cout << "------------------------------------" << std::endl;
		std::cout << "\033[1;37mSelect:\033[0m ";
		std::cin >> difficulty;


		switch (difficulty) {
		case 1:
			lives = 7;
			wager = 0;
			status = "Difficulty: \033[32mEasy\033[0m";
			std::cout << "Easy mode selected! No wagering in this mode." << std::endl;
			wait(1500);
			break;
		case 2:
			lives = 5;
			status = "Difficulty: \033[33mNormal\033[0m";
			std::cout << "\033[1;37mMinimum: \033[0m" << minWager << "\033[1;37m. Maximum: \033[0m" << totalPoints << std::endl;
 			std::cout << "\033[1;37mWager:\033[0m ";
			std::cin >> wager;
			if (wager > totalPoints || wager < minWager) {
				std::cout << "Invalid wager amount, going all-in!" << std::endl;
				wait(1500);
				wager = totalPoints;
			}
			break;
		case 3:
			std::cout << "\033[1;37mMinimum: \033[0m" << minWager << "\033[1;37m. Maximum: \033[0m" << totalPoints << std::endl;
 			std::cout << "\033[1;37mWager:\033[0m ";
			std::cin >> wager;
			if (wager > totalPoints || wager < minWager) {
				std::cout << "Invalid wager amount, going all-in!" << std::endl;
				wait(1500);
				wager = totalPoints;
			}
			status = "Difficulty: \033[31mHard\033[0m";
			lives = 3;
			break;
		case 4:
			status = "Difficulty: \033[33mExtreme\033[0m";
			lives = 5;
			std::cout << "wow you found the secret difficulty!" << std::endl;
			std::cout << "\033[1;37mMinimum: \033[0m" << minWager << "\033[1;37m. Maximum: \033[0m" << totalPoints << std::endl;
 			std::cout << "\033[1;37mWager:\033[0m ";
			std::cin >> wager;
			if (wager > totalPoints || wager < minWager) {
				std::cout << "Invalid wager amount, going all-in!" << std::endl;
				wait(1500);
				wager = totalPoints;
			}
			break;
		case -1:
			main();
			break;
		default:
			status = "Difficulty: Normal";
			lives = 5;
			break;
		}

		while (guess != secretNum && lives > 0) {
		clear();
		std::cout << "\033[1;37mGAMEPLAY\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m | Lives: \033[1;31m" << lives << "\033[0m" << std::endl;
		std::cout << "------------------------------------" << std::endl;

		std::cout << "Status: " << status << std::endl;
		std::cout << "------------------------------------" << std::endl;

		std::cout << "Enter your guess \033[32m>\033[0m ";
		std::cin >> guess;


			if (guess != secretNum) {
				lives--;
				if (checkLives(lives)) {
					if (guess > secretNum) {
						if (difficulty == 4) {
							status = "Lower! Range removed and number shifted 3";
							secretNum = newNum(secretNum, guess);
						} else {
							status = "\033[31mLower!\033[0m";
						}
					}
					if (guess < secretNum) {
						if (difficulty == 4) {
							status = "Higher! Range removed and number shifted 3";
							secretNum = newNum(secretNum, guess);
						} else {
							status = "\033[31mHigher!\033[0m";
						}
					}
				} else {
					totalLoss++;
					clear();

					totalPoints -= wager;

					if (totalPoints <= 0) {
						std::cout << "You've gone bankrupt! Your save file has been deleted." << std::endl;
						remove("save.txt");
						wait(1000);
						exit(0);
					}

					std::ofstream outFile3("save.txt");
					if (outFile3.is_open()) {
						std::cout << "Saving changes..." << std::endl;
						outFile3 << playerName << std::endl;
						outFile3 << totalPoints << std::endl;
						outFile3 << totalWins << std::endl;
						outFile3 << totalLoss;
						wait(400);
						outFile3.close();
					}
					std::cout << "You lost " << wager << " points!" << std::endl;
					std::cout << "\033[31mGame over!\033[0m The number was " << secretNum << "." << std::endl;

					std::cout << "Play again? (y/n): " << std::endl;
					std::cin >> choice;
				}
			}

			if (guess == secretNum) {
				totalWins++;
				clear();
				switch (difficulty) {
					case 1: 
						std::cout << "Easy mode. No points awarded." << std::endl;
						break;
					case 2:
						std::cout << "Awarded " << std::round(wager * 1.2) << " points!" << std::endl;
						totalPoints += std::round(wager * 0.2);
						break;
					case 3:
						std::cout << "Awarded " << std::round(wager * 1.55) << " points!" << std::endl;
						totalPoints += std::round(wager * 0.55);
						break;
					case 4:
						std::cout << "Awarded " << std::round(wager * 2) << " points!" << std::endl;
						totalPoints += std::round(wager * 2);
						break;
				}
				std::ofstream outFile2("save.txt");
				if (outFile2.is_open()) {
					std::cout << "Saving changes..." << std::endl;
					outFile2 << playerName << std::endl;
					outFile2 << totalPoints << std::endl;
					outFile2 << totalWins << std::endl;
					outFile2 << totalLoss;
					wait(400);
					outFile2.close();
				}

				std::cout << "\033[32mYou won the game with " << lives << " lives!\033[0m" << std::endl;
				
				std::cout << "Play again? (y/n): " << std::endl;
				std::cin >> choice;
			}
		}
	} while (choice == 'y');

	return 0;
}
