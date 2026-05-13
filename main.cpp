#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>

#define wait(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
    int _getch() { // stole this code btw
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

// --- Global Stats ---
int totalWins = 0;
int totalLoss = 0;
int totalPoints = 100;
int extraLifeOwned = 0;
int gamblingInsuranceOwned = 0;
int highRewardOwned = 0;
std::string playerName;

// --- Helper Functions ---
int checkLives(int amount) {
	if (amount > 0) return true;
	else return false;
}

int newNum(int currentNum, int guess) {
	int newNum;
	if (currentNum - 3 == guess) newNum = currentNum + 3;
	else if (currentNum - 3 != guess) newNum = currentNum - 3;
	return newNum;
}

void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void resetCursor() {
    std::cout << "\033[H";
}

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
        inFile >> playerName >> totalPoints >> totalWins >> totalLoss >> extraLifeOwned >> gamblingInsuranceOwned >> highRewardOwned;
        inFile.close();
    }
}

int chooseShopItem() {
    clear();
    int selected = 1;
    bool choiceMade = false;

    while (!choiceMade) {
        resetCursor();
        std::cout << "\033[H";

        std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mITEMS\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "\033[32m[" << (selected == 1 ? "*" : "1") << "]\033[0m Extra Life             \033[33m$150\033[0m" << std::endl;
        std::cout << "\033[32m[" << (selected == 2 ? "*" : "2") << "]\033[0m Gambling Insurance    \033[33m$350\033[0m" << std::endl;
        std::cout << "\033[32m[" << (selected == 3 ? "*" : "3") << "]\033[0m High Reward           \033[33m$250\033[0m" << std::endl;
        std::cout << "\033[31m[" << (selected == 4 ? "*" : "4") << "]\033[0m Back to Menu" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Use Arrows to move, Enter to select" << std::endl;

        int input = _getch();
        if (input == 224 || input == 27) {
            int arrow = _getch();
            if (input == 27 && arrow == 91) arrow = _getch();

            if (arrow == 72 || arrow == 'A') {
                if (selected > 1) selected--;
                else selected = 4;
            } 
            else if (arrow == 80 || arrow == 'B') {
                if (selected < 4) selected++;
                else selected = 1;
            }
        } 
        else if (input == 13 || input == 10) {
            choiceMade = true;
        }
    }

    return selected; 
}

int chooseDifficulty() {
    clear();
    int selected = 1;
    bool choiceMade = false;

    while (!choiceMade) {
        resetCursor();
        std::cout << "\033[H";
        std::cout << "\033[1;37mDIFFICULTY\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "\033[32m[" << (selected == 1 ? "*" : "1") << "]\033[0m Easy   (7 lives)" << std::endl;
        std::cout << "\033[33m[" << (selected == 2 ? "*" : "2") << "]\033[0m Normal (4 lives)" << std::endl;
        std::cout << "\033[31m[" << (selected == 3 ? "*" : "3") << "]\033[0m Hard   (3 lives)" << std::endl;
        std::cout << "\033[35m[" << (selected == 4 ? "*" : "4") << "]\033[0m EXTREME\033[0m" << std::endl;
        std::cout << "\033[37m[" << (selected == 5 ? "*" : "5") << "]\033[0m Exit to menu" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Use Arrows to move, Enter to select" << std::endl;

        int input = _getch();
        if (input == 224 || input == 27) {
            int arrow = _getch();
            if (input == 27 && arrow == 91) arrow = _getch();

            if (arrow == 72 || arrow == 'A') {
                if (selected > 1) selected--;
                else selected = 5;
            } 
            else if (arrow == 80 || arrow == 'B') { // DOWN
                if (selected < 5) selected++;
                else selected = 1;
            }
        } 
        else if (input == 13 || input == 10) {
            choiceMade = true;
        }
    }

    return selected; 
}

// --- Store ---
void openStore() {
    while (true) {
        int choice = chooseShopItem();
        char buyChoice;

        if (choice == 1) {
            clear();
            std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "\033[1;37mITEM:\033[0m \033[35mExtra Life\033[0m" << std::endl; 
            std::cout << "\033[1;37mCOST:\033[0m \033[33m$150\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << " Provides \033[32m+1 Extra Life\033[0m for your next" << std::endl;
            std::cout << " round. This is a \033[33msingle-use\033[0m item." << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
            std::cin >> buyChoice;
            std::cin.ignore(1000, '\n');
            if (buyChoice == 'y' || buyChoice == 'Y') {
                if (extraLifeOwned == 1) std::cout << "Already owned!" << std::endl;
                else if (totalPoints >= 150) { 
                    totalPoints -= 150; 
                    extraLifeOwned = 1; 
                    saveGame(); 
                    std::cout << "Purchased!" << std::endl; 
                } else std::cout << "Not enough points!" << std::endl;
                wait(1000);
            }
        } 
        else if (choice == 2) {
            clear();
            std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "\033[1;37mITEM:\033[0m \033[35mGambling Insurance\033[0m" << std::endl; 
            std::cout << "\033[1;37mCOST:\033[0m \033[33m$350\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << " Reduces all wager losses by \033[32m35%\033[0m." << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
            std::cin >> buyChoice;
            std::cin.ignore(1000, '\n');
            if (buyChoice == 'y' || buyChoice == 'Y') {
                if (gamblingInsuranceOwned == 1) std::cout << "Already owned!" << std::endl;
                else if (totalPoints >= 350) { 
                    totalPoints -= 350; 
                    gamblingInsuranceOwned = 1; 
                    saveGame(); 
                    std::cout << "Purchased!" << std::endl; 
                } else std::cout << "Not enough points!" << std::endl;
                wait(1000);
            }
        } 
        else if (choice == 3) {
            clear();
            std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "\033[1;37mITEM:\033[0m \033[35mHigh Reward\033[0m" << std::endl; 
            std::cout << "\033[1;37mCOST:\033[0m \033[33m$250\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << " Increases your next win by \033[32m35%\033[0m." << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
            std::cin >> buyChoice;
            std::cin.ignore(1000, '\n');
            if (buyChoice == 'y' || buyChoice == 'Y') {
                if (highRewardOwned == 1) std::cout << "Already owned!" << std::endl;
                else if (totalPoints >= 250) { 
                    totalPoints -= 250; 
                    highRewardOwned = 1; 
                    saveGame(); 
                    std::cout << "Purchased!" << std::endl; 
                } else std::cout << "Not enough points!" << std::endl;
                wait(1000);
            }
        } 
        else if (choice == 4) {
            return; 
        }
    }
}

void viewStats() {
    clear();
    std::cout << "\033[1;37mPLAYER STATS\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Points: \033[33m" << totalPoints << "\033[0m" << std::endl;
    std::cout << "Wins:   \033[1;32m" << totalWins << "\033[0m" << std::endl;
    std::cout << "Losses: \033[1;31m" << totalLoss << "\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Press ENTER to return ";
    _getch();
}

// --- Gameplay ---
void playGame() {
    std::srand(std::time(0));
    int range = 10; // not in use yet hehehehaw
    int secretNum = std::rand() % range + 1;
    int guess = 0;
    int lives = 5;
    int difficulty = chooseDifficulty();
    int wager = 0;
    int minWager = totalPoints * 0.15;
    if (minWager <= 0) minWager = totalPoints;
    if (difficulty == 1) lives = 7;
    else if (difficulty == 2) lives = 4;
    else if (difficulty == 3) lives = 3;
    else if (difficulty == 4) lives = 5;
    else if (difficulty == 5) return;
    if (difficulty > 1 && extraLifeOwned == 1) {
        lives++;
        extraLifeOwned = 0;
        saveGame();
        std::cout << "\033[35mExtra life applied!\033[0m" << std::endl;
    }

    if (difficulty == 1) {
        wager = 0;
        std::cout << "Easy mode: No wagering." << std::endl;
        wait(1000);
    } else {
        std::cout << "\033[1;37mPoints: \033[33m$" << totalPoints << "\033[0m (Min: $" << minWager << ")" << std::endl;
        std::cout << "Wager: $";
        std::cin >> wager;

        if (wager > totalPoints || wager < minWager) {
            wager = totalPoints;
            std::cout << "Invalid! Going all-in: \033[31m$" << wager << "\033[0m" << std::endl;
            wait(1500);
        }
    }

    std::string status = "I'm thinking of a number between 1 and 10.";
    while (lives > 0) {
        clear();
        std::cout << "\033[1;37mGAMEPLAY\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m | Lives: \033[1;31m" << lives << "\033[0m" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Status: " << status << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Enter your guess \033[32m>\033[0m ";
        std::cin >> guess;

        if (guess == secretNum) {
            totalWins++;
            clear();
            double rewardMult = (difficulty == 3) ? 0.55 : 0.20;
            int winAmt = std::round(wager * rewardMult);
            if (highRewardOwned == 1) {
                winAmt = std::round(winAmt * 1.35);
                highRewardOwned = 0;
                std::cout << "Bonus applied! ";
            }
            totalPoints += winAmt;
            std::cout << "Awarded " << winAmt << " points!" << std::endl;
            std::cout << "\033[32mYou won with " << lives << " lives!\033[0m" << std::endl;
            saveGame();
            wait(2000);
            return;
        } else {
            lives--;
            if (difficulty == 4) {
                status = "Number shifted 3 and range removed.";
                secretNum = newNum(secretNum, guess);
            } else {
                status = (guess > secretNum) ? "\033[31mLower!\033[0m" : "\033[31mHigher!\033[0m";
            }
        }
    }

    totalLoss++;
    int lostAmt = wager;
    if (gamblingInsuranceOwned == 1) {
        lostAmt = std::round(wager * 0.65);
        gamblingInsuranceOwned = 0;
        std::cout << "Insurance saved you 35%!" << std::endl;
    }
    totalPoints -= lostAmt;
    saveGame();
    std::cout << "You lost " << lostAmt << " points! The number was " << secretNum << std::endl;
    if (totalPoints <= 0) {
        std::cout << "Bankrupt! Save deleted." << std::endl;
        remove("save.txt");
        exit(0);
    }
    wait(2000);
}

// --- Main Menu ---
int main() {
    clear();
    std::ifstream checkFile("save.txt");
    if (!checkFile.is_open()) {
        std::cout << "Please choose a username: ";
        std::cin >> playerName;
        std::cin.ignore(1000, '\n');
        saveGame();
    } else {
        checkFile.close();
        loadGame();
    }

    int selected = 1;

    while (true) {
        clear();
        bool choiceMade = false;
        while (!choiceMade) {
            resetCursor();
            std::cout << "\033[1;37mSUPER GAMBLING\033[0m \033[33m//\033[0m \033[36mV1.3\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "\033[32m[" << (selected == 1 ? "*" : "1") << "]\033[0m Start Game" << std::endl;
            std::cout << "\033[36m[" << (selected == 2 ? "*" : "2") << "]\033[0m Open Store" << std::endl;
            std::cout << "\033[33m[" << (selected == 3 ? "*" : "3") << "]\033[0m View Stats" << std::endl;
            std::cout << "\033[31m[" << (selected == 4 ? "*" : "4") << "]\033[0m Exit" << std::endl;
            
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Use Arrows to move, Enter to select" << std::endl;

            int input = _getch();

            if (input == 224 || input == 27) {
                int arrow = _getch();
                if (input == 27 && arrow == 91) arrow = _getch(); 

                if (arrow == 72 || arrow == 'A') {
                    if (selected > 1) selected--;
                    else selected = 4;
                } 
                else if (arrow == 80 || arrow == 'B') { // DOWN
                    if (selected < 4) selected++;
                    else selected = 1;
                }
            }
            else if (input == 13 || input == 10) {
                choiceMade = true;
            }
        }
        if (selected == 1) playGame();
        else if (selected == 2) openStore();
        else if (selected == 3) viewStats();
        else if (selected == 4) break;
        
    }
    return 0;
}
