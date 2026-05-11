#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
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

int totalWins = 0;
int totalLoss = 0;
int totalPoints = 100;

int extraLifeOwned = 0;
int gamblingInsuranceOwned = 0;
int highRewardOwned = 0;

std::string playerName;

void saveGame() {
    std::ofstream outFile("save.txt");
    if (outFile.is_open()) {
        outFile << playerName << std::endl;
        outFile << totalPoints << std::endl;
        outFile << totalWins << std::endl;
        outFile << totalLoss << std::endl;
        outFile << extraLifeOwned << std::endl;
		outFile << gamblingInsuranceOwned << std::endl;
		outFile << highRewardOwned;
        outFile.close();
    }
}
void loadGame() {
    std::ifstream inFile("save.txt");
    if (inFile.is_open()) {
        inFile >> playerName;
        inFile >> totalPoints;
        inFile >> totalWins;
        inFile >> totalLoss;
        inFile >> extraLifeOwned;
		inFile >> gamblingInsuranceOwned;
		inFile >> highRewardOwned;
        inFile.close();
    }
}

int main() {
	bool gameRun = true;

	while (gameRun) {
	clear();
	char choice;
	std::string exitChoice;
	int menuChoice;

	std::ifstream checkFile("save.txt");
	if (!checkFile.is_open()) {
        std::cout << "Please choose a username: ";
        std::cin >> playerName;
        saveGame();
    } 
    else {
        checkFile.close();
        loadGame();
        std::cout << "Welcome back, " << playerName << "!" << std::endl;
        wait(350);
    }

	std::cout << "\033[1;37mSUPER GAMBLING\033[0m \033[33m//\033[0m \033[36mV1.2\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    
    std::cout << "\033[32m[1]\033[0m Start Game" << std::endl;
	std::cout << "\033[36m[2]\033[0m Open Store" << std::endl;
    std::cout << "\033[33m[3]\033[0m View Stats" << std::endl;
    std::cout << "\033[31m[4]\033[0m Exit" << std::endl;
    
    std::cout << "------------------------------------" << std::endl;
    std::cout << "\033[1;37mAction:\033[0m ";
	std::cin >> menuChoice;

	switch (menuChoice) {
    case 2:
		int shopChoice;
		char buyChoice;
        clear();
		std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mITEMS\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
    	std::cout << "------------------------------------" << std::endl;

    	std::cout << "\033[32m[1]\033[0m Extra Life      \033[33m       $150\033[0m" << std::endl;
    	std::cout << "\033[32m[2]\033[0m Gambling Insurance \033[33m    $350\033[0m" << std::endl;
    	std::cout << "\033[32m[3]\033[0m High Reward       \033[33m     $250\033[0m" << std::endl;
    	std::cout << "\033[31m[5]\033[0m Back to Menu" << std::endl;

    	std::cout << "------------------------------------" << std::endl;
    	std::cout << "\033[1;37mAction:\033[0m ";
    	std::cin >> shopChoice;
		switch (shopChoice) {
			case 1:
				clear();
				std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
				std::cout << "------------------------------------" << std::endl;

				std::cout << "\033[1;37mITEM:\033[0m \033[35mExtra Life\033[0m" << std::endl; 
				std::cout << "\033[1;37mCOST:\033[0m \033[33m$150\033[0m" << std::endl;
				std::cout << "------------------------------------" << std::endl;

				std::cout << " Provides \033[32m+1 Extra Life\033[0m for your next" << std::endl;
				std::cout << " round. This is a \033[33msingle-use\033[0m item" << std::endl;
				std::cout << " and will be consumed after use." << std::endl;

				std::cout << "------------------------------------" << std::endl;

				std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
				std::cin >> buyChoice;
				if (buyChoice == 'y' || buyChoice == 'Y') {
					if (extraLifeOwned == 1) {
						std::cout << "You already own this. Returning to menu." << std::endl;
						wait(1000);
						main();
						break;
					} else if (extraLifeOwned == 0 && totalPoints >= 150) {
						totalPoints = totalPoints - 150;
						extraLifeOwned = 1;
						std::cout << "Item purchased! Returning to menu." << std::endl;
						saveGame();
						wait(1250);
						main();
						break;
					} else {
						std::cout << "Something went wrong. Can you afford this? Returning to menu." << std::endl;
						wait(1000);
						main();
						break;
					}
					break;
				} else if (buyChoice == 'n' || buyChoice == 'N') {
					main();
					break;
				}
			case 2:
				clear();
				std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
				std::cout << "------------------------------------" << std::endl;

				std::cout << "\033[1;37mITEM:\033[0m \033[35mGambling Insurance\033[0m" << std::endl; 
				std::cout << "\033[1;37mCOST:\033[0m \033[33m$350\033[0m" << std::endl;
				std::cout << "------------------------------------" << std::endl;

				std::cout << " A safety net for the gamblers. This" << std::endl;
				std::cout << " item reduces all wager losses by \033[32m35%\033[0m." << std::endl;
				std::cout << " " << std::endl;
				std::cout << " \033[31m* EFFECT:\033[0m If you lose $100, you" << std::endl;
				std::cout << "   only actually lose $65." << std::endl;

				std::cout << "------------------------------------" << std::endl;
				std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
				std::cin >> buyChoice;
				if (buyChoice == 'y' || buyChoice == 'Y') {
					if (gamblingInsuranceOwned == 1) {
						std::cout << "You already own this. Returning to menu." << std::endl;
						wait(1000);
						main();
						break;
					} else if (gamblingInsuranceOwned == 0 && totalPoints >= 150) {
						totalPoints = totalPoints - 150;
						gamblingInsuranceOwned = 1;
						std::cout << "Item purchased! Returning to menu." << std::endl;
						saveGame();
						wait(1250);
						main();
						break;
					} else {
						std::cout << "Something went wrong. Can you afford this? Returning to menu." << std::endl;
						wait(1000);
						main();
						break;
					}
					break;
				} else if (buyChoice == 'n' || buyChoice == 'N') {
					main();
					break;
				}
			case 3:
				std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
				std::cout << "------------------------------------" << std::endl;

				std::cout << "\033[1;37mITEM:\033[0m \033[35mHigh Reward\033[0m" << std::endl; 
				std::cout << "\033[1;37mCOST:\033[0m \033[33m$250\033[0m" << std::endl;
				std::cout << "------------------------------------" << std::endl;

				std::cout << " High stakes, higher returns. This" << std::endl;
				std::cout << " item increases your next win by \033[32m35%\033[0m." << std::endl;
				std::cout << " " << std::endl;
				std::cout << " \033[36m* EFFECT:\033[0m If you win $100, you" << std::endl;
				std::cout << "   actually receive $135." << std::endl;

				std::cout << "------------------------------------" << std::endl;
				std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
				std::cin >> buyChoice;
				if (buyChoice == 'y' || buyChoice == 'Y') {
					if (highRewardOwned == 1) {
						std::cout << "You already own this. Returning to menu." << std::endl;
						wait(1000);
						main();
						break;
					} else if (highRewardOwned == 0 && totalPoints >= 150) {
						totalPoints = totalPoints - 150;
						highRewardOwned = 1;
						std::cout << "Item purchased! Returning to menu." << std::endl;
						saveGame();
						wait(1250);
						main();
						break;
					} else {
						std::cout << "Something went wrong. Can you afford this? Returning to menu." << std::endl;
						wait(1000);
						main();
						break;
					}
				} else if (buyChoice == 'n' || buyChoice == 'N') {
					main();
					break;
				}
			case 5:
				main();
				break;
		}
		
    case 3:
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
        break;
	case 4:
		clear();
        std::cout << "Exiting..." << std::endl;
        exit(0);
        break;
}
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
		std::cout << "\033[33m2.\033[0m Normal (4 lives)" << std::endl;
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
			std::cout << "Easy mode selected! No wagering in this mode. Extra Lives cannot be used either." << std::endl;
			wait(1700);
			break;
		case 2:
			if (extraLifeOwned == 1) {
				lives = 5;
				std::cout << "Extra life being used!" << std::endl;
				extraLifeOwned = 0;
				saveGame();
			} else {lives = 4;}
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
			if (extraLifeOwned == 1) {
				lives = 4;
				std::cout << "Extra life being used!" << std::endl;
				extraLifeOwned = 0;
				saveGame();
			} else {lives = 3;}
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
			if (extraLifeOwned == 1) {
				std::cout << "Extra lives cannnot be used in this mode.";
			}
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

					saveGame();
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
						if (highRewardOwned == 1) {
							std::cout << "Awarded " << std::round((wager * 0.2) * 1.35) << " points! (35% multiplier)" << std::endl;
							totalPoints += std::round((wager * 0.2) * 1.35);
							highRewardOwned = 0;
						} else {
							std::cout << "Awarded " << std::round(wager * 0.2) << " points!" << std::endl;
							totalPoints += std::round(wager * 0.2);
						}
						break;
					case 3:
						if (highRewardOwned == 1) {
							std::cout << "Awarded " << std::round((wager * 0.55) * 1.35) << " points! (35% multiplier)" << std::endl;
							totalPoints += std::round((wager * 0.55) * 1.35);
							highRewardOwned = 0;
						} else {
							std::cout << "Awarded " << std::round(wager * 0.55) << " points!" << std::endl;
							totalPoints += std::round(wager * 0.55);
						}
						break;
					case 4:
						if (highRewardOwned == 1) {
							std::cout << "Awarded " << std::round((wager * 2) * 1.35) << " points! (35% multiplier)" << std::endl;
							totalPoints += std::round((wager * 2) * 1.35);
							highRewardOwned = 0;
						} else {
							std::cout << "Awarded " << std::round(wager * 2) << " points!" << std::endl;
							totalPoints += std::round(wager * 2);
						}
						break;
				}
				saveGame();

				std::cout << "\033[32mYou won the game with " << lives << " lives!\033[0m" << std::endl;
				
				std::cout << "Play again? (y/n): " << std::endl;
				std::cin >> choice;
			}
		}
	
	}

	return 0;
}
