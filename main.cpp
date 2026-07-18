#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <limits>

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
int safeBetShieldOwned = 0;
int safeBetShieldUses = 0;
int highestSingleWager = 0;
int extremeWins = 0;
int totalShopPurchases = 0;
int firstTryWins = 0;
int currentStreak = 0;
int bestStreak = 0;
int jackpotsTriggered = 0;
int roundsPlayed = 0;
int totalRewardPaid = 0;
int luckyCharmOwned = 0;
int doubleDownOwned = 0;

// --- Badges ---
int badgeFirstWin = 0;
int badgeHighRoller = 0;
int badgeMillionaire = 0;
int badgeExtremeMaster = 0;
int badgeShopaholic = 0;
int badgeLuckyFirstTry = 0;
int badgeBillionaire = 0;
int badgeStreakMaster = 0;
int badgeJackpotHunter = 0;
int badgeLegend = 0;
int badgeCollector = 0;
std::vector<std::string> unlockedBadges;

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

bool hasBadge(std::string badgeName) {
    for (std::string badge : unlockedBadges) {
        if (badge == badgeName)
            return true;
    }
    return false;
}

void unlockBadge(std::string badgeName) {
    if (!hasBadge(badgeName)) {
        unlockedBadges.push_back(badgeName);
        std::cout << "\033[33mBADGE UNLOCKED: \033[0m" << badgeName << std::endl;
    }
}

void markBadgeAsUnlocked(int& badgeFlag, std::string badgeName) {
    if (!badgeFlag) {
        badgeFlag = 1;
        unlockBadge(badgeName);
    }
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

void waitForEnter() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl;
    int ch = _getch();
    while (ch != 13 && ch != 10) {
        ch = _getch();
    }
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
        outFile << highRewardOwned << std::endl;
        outFile << safeBetShieldOwned << std::endl;
        outFile << safeBetShieldUses << std::endl;
        outFile << highestSingleWager << std::endl;
        outFile << extremeWins << std::endl;
        outFile << totalShopPurchases << std::endl;
        outFile << firstTryWins << std::endl;
        outFile << currentStreak << std::endl;
        outFile << bestStreak << std::endl;
        outFile << jackpotsTriggered << std::endl;
        outFile << roundsPlayed << std::endl;
        outFile << totalRewardPaid << std::endl;
        outFile << luckyCharmOwned << std::endl;
        outFile << doubleDownOwned << std::endl;

        // --- Badges ---
        outFile << badgeFirstWin << std::endl;
        outFile << badgeHighRoller << std::endl;
        outFile << badgeMillionaire << std::endl;
        outFile << badgeExtremeMaster << std::endl;
        outFile << badgeShopaholic << std::endl;
        outFile << badgeLuckyFirstTry << std::endl;
        outFile << badgeBillionaire << std::endl;
        outFile << badgeStreakMaster << std::endl;
        outFile << badgeJackpotHunter << std::endl;
        outFile << badgeLegend << std::endl;
        outFile << badgeCollector << std::endl;

        outFile.close();
    }
}

void checkBadges() {
    if (totalWins >= 3) {
        markBadgeAsUnlocked(badgeFirstWin, "Winner");
    }
    if (highestSingleWager >= 1000) {
        markBadgeAsUnlocked(badgeHighRoller, "High Roller");
    }
    if (totalPoints >= 2500) {
        markBadgeAsUnlocked(badgeMillionaire, "Rich Player");
    }
    if (totalPoints >= 15000) {
        markBadgeAsUnlocked(badgeBillionaire, "Billionaire");
    }
    if (extremeWins >= 2) {
        markBadgeAsUnlocked(badgeExtremeMaster, "Extreme Master");
    }
    if (totalShopPurchases >= 3) {
        markBadgeAsUnlocked(badgeShopaholic, "Shopaholic");
    }
    if (firstTryWins >= 1) {
        markBadgeAsUnlocked(badgeLuckyFirstTry, "Lucky First Try");
    }
    if (bestStreak >= 5) {
        markBadgeAsUnlocked(badgeStreakMaster, "Streak Master");
    }
    if (jackpotsTriggered >= 3) {
        markBadgeAsUnlocked(badgeJackpotHunter, "Jackpot Hunter");
    }
    if (totalWins >= 15) {
        markBadgeAsUnlocked(badgeLegend, "Legend");
    }
    if (totalShopPurchases >= 8) {
        markBadgeAsUnlocked(badgeCollector, "Collector");
    }
    if (totalLoss >= 10) {
        unlockBadge("Bad Luck");
    }
    if (extraLifeOwned == 1 &&
        gamblingInsuranceOwned == 1 &&
        highRewardOwned == 1) {
        unlockBadge("Fully Equipped");
    }
}

void loadGame() {
    std::ifstream inFile("save.txt");

    if (inFile.is_open()) {
        inFile >> playerName 
               >> totalPoints 
               >> totalWins 
               >> totalLoss 
               >> extraLifeOwned 
               >> gamblingInsuranceOwned 
               >> highRewardOwned
               >> safeBetShieldOwned
               >> safeBetShieldUses
               >> highestSingleWager
               >> extremeWins
               >> totalShopPurchases
               >> firstTryWins
               >> currentStreak
               >> bestStreak
               >> jackpotsTriggered
               >> roundsPlayed
               >> totalRewardPaid
               >> luckyCharmOwned
               >> doubleDownOwned;

        inFile >> badgeFirstWin
               >> badgeHighRoller
               >> badgeMillionaire
               >> badgeExtremeMaster
               >> badgeShopaholic
               >> badgeLuckyFirstTry
               >> badgeBillionaire
               >> badgeStreakMaster
               >> badgeJackpotHunter
               >> badgeLegend
               >> badgeCollector;

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
        int shieldCost = 300 * (1 << safeBetShieldUses);
        std::cout << "\033[32m[" << (selected == 4 ? "*" : "4") << "]\033[0m Safe Bet Shield      \033[33m$" << shieldCost << "\033[0m" << std::endl;
        std::cout << "\033[33m[" << (selected == 5 ? "*" : "5") << "]\033[0m Lucky Charm           \033[33m$400\033[0m" << std::endl;
        std::cout << "\033[35m[" << (selected == 6 ? "*" : "6") << "]\033[0m Double Down          \033[33m$500\033[0m" << std::endl;
        std::cout << "\033[31m[" << (selected == 7 ? "*" : "7") << "]\033[0m Back to Menu" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Use Arrows to move, Enter to select" << std::endl;

        int input = _getch();
        if (input == 224 || input == 27) {
            int arrow = _getch();
            if (input == 27 && arrow == 91) arrow = _getch();

            if (arrow == 72 || arrow == 'A') {
                if (selected > 1) selected--;
                else selected = 7;
            } 
            else if (arrow == 80 || arrow == 'B') {
                if (selected < 7) selected++;
                else selected = 1;
            }
        } 
        else if (input == 13 || input == 10) {
            choiceMade = true;
        }
    }

    return selected; 
}

void viewBadges() {
    checkBadges();
    clear();

    int totalBadges = 11;
    int unlockedCount = badgeFirstWin + badgeHighRoller + badgeMillionaire + badgeExtremeMaster + badgeShopaholic + badgeLuckyFirstTry + badgeBillionaire + badgeStreakMaster + badgeJackpotHunter + badgeLegend + badgeCollector;

    std::cout << "\033[1;37mBADGES\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    std::cout << (badgeFirstWin ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Winner" << std::endl;
    std::cout << "     Win 3 rounds total." << std::endl << std::endl;

    std::cout << (badgeHighRoller ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "High Roller" << std::endl;
    std::cout << "     Wager 1000 points in one game." << std::endl << std::endl;

    std::cout << (badgeMillionaire ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Millionaire" << std::endl;
    std::cout << "     Reach 2500 points." << std::endl << std::endl;

    std::cout << (badgeExtremeMaster ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Extreme Master" << std::endl;
    std::cout << "     Beat Extreme difficulty 2 times." << std::endl << std::endl;

    std::cout << (badgeShopaholic ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Shopaholic" << std::endl;
    std::cout << "     Buy 3 shop items." << std::endl << std::endl;

    std::cout << (badgeLuckyFirstTry ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Lucky First Try" << std::endl;
    std::cout << "     Guess correctly on your first try." << std::endl << std::endl;

    std::cout << (badgeBillionaire ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Billionaire" << std::endl;
    std::cout << "     Reach 15,000 points." << std::endl << std::endl;

    std::cout << (badgeStreakMaster ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Streak Master" << std::endl;
    std::cout << "     Reach a streak of 5 wins." << std::endl << std::endl;

    std::cout << (badgeJackpotHunter ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Jackpot Hunter" << std::endl;
    std::cout << "     Trigger 3 jackpots." << std::endl << std::endl;

    std::cout << (badgeLegend ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Legend" << std::endl;
    std::cout << "     Win 15 rounds total." << std::endl << std::endl;

    std::cout << (badgeCollector ? "\033[32m[✓]\033[0m " : "\033[31m[ ]\033[0m ")
              << "Collector" << std::endl;
    std::cout << "     Purchase 8 shop items." << std::endl << std::endl;

    std::cout << "------------------------------------" << std::endl;
    std::cout << "Unlocked: \033[33m" << unlockedCount << "/" << totalBadges << "\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Press ENTER to return ";

    _getch();
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
                    totalShopPurchases++;
                    checkBadges();
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
            std::cout << " Reduces all wager losses by \033[32m10%\033[0m." << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
            std::cin >> buyChoice;
            std::cin.ignore(1000, '\n');
            if (buyChoice == 'y' || buyChoice == 'Y') {
                if (gamblingInsuranceOwned == 1) std::cout << "Already owned!" << std::endl;
                else if (totalPoints >= 350) { 
                    totalPoints -= 350; 
                    gamblingInsuranceOwned = 1; 
                    totalShopPurchases++;
                    checkBadges();
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
                    totalShopPurchases++;
                    checkBadges();
                    saveGame(); 
                    std::cout << "Purchased!" << std::endl; 
                } else std::cout << "Not enough points!" << std::endl;
                wait(1000);
            }
        } 
        else if (choice == 4) {
            clear();
            std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            int shieldCost = 300 * (1 << safeBetShieldUses);
            std::cout << "\033[1;37mITEM:\033[0m \033[35mSafe Bet Shield\033[0m" << std::endl; 
            std::cout << "\033[1;37mCOST:\033[0m \033[33m$" << shieldCost << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << " Reduces the penalty of your next loss by \033[32m50%\033[0m." << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
            std::cin >> buyChoice;
            std::cin.ignore(1000, '\n');
            if (buyChoice == 'y' || buyChoice == 'Y') {
                int shieldCost = 300 * (1 << safeBetShieldUses);
                if (safeBetShieldOwned == 1) std::cout << "Already owned!" << std::endl;
                else if (totalPoints >= shieldCost) { 
                    totalPoints -= shieldCost; 
                    safeBetShieldOwned = 1; 
                    totalShopPurchases++;
                    checkBadges();
                    saveGame(); 
                    std::cout << "Purchased!" << std::endl; 
                } else std::cout << "Not enough points!" << std::endl;
                wait(1000);
            }
        }
        else if (choice == 5) {
            clear();
            std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "\033[1;37mITEM:\033[0m \033[35mLucky Charm\033[0m" << std::endl; 
            std::cout << "\033[1;37mCOST:\033[0m \033[33m$400\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << " Gives your next win a \033[32m10% bonus\033[0m and a \033[32msmall extra jackpot chance\033[0m." << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
            std::cin >> buyChoice;
            std::cin.ignore(1000, '\n');
            if (buyChoice == 'y' || buyChoice == 'Y') {
                if (luckyCharmOwned == 1) std::cout << "Already owned!" << std::endl;
                else if (totalPoints >= 400) { 
                    totalPoints -= 400; 
                    luckyCharmOwned = 1; 
                    totalShopPurchases++;
                    checkBadges();
                    saveGame(); 
                    std::cout << "Purchased!" << std::endl; 
                } else std::cout << "Not enough points!" << std::endl;
                wait(1000);
            }
            continue;
        }
        else if (choice == 6) {
            clear();
            std::cout << "\033[1;37mSHOP\033[0m \033[33m//\033[0m \033[36mDESCRIPTION\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "\033[1;37mITEM:\033[0m \033[35mDouble Down\033[0m" << std::endl; 
            std::cout << "\033[1;37mCOST:\033[0m \033[33m$500\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << " Doubles your next win reward and makes the next loss more forgiving." << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Purchase? [\033[32mY\033[0m/\033[31mN\033[0m]: ";
            std::cin >> buyChoice;
            std::cin.ignore(1000, '\n');
            if (buyChoice == 'y' || buyChoice == 'Y') {
                if (doubleDownOwned == 1) std::cout << "Already owned!" << std::endl;
                else if (totalPoints >= 500) { 
                    totalPoints -= 500; 
                    doubleDownOwned = 1; 
                    totalShopPurchases++;
                    checkBadges();
                    saveGame(); 
                    std::cout << "Purchased!" << std::endl; 
                } else std::cout << "Not enough points!" << std::endl;
                wait(1000);
            }
            continue;
        }
        else if (choice == 7) {
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
    std::cout << "Rounds: \033[36m" << roundsPlayed << "\033[0m" << std::endl;
    std::cout << "Current Streak: \033[35m" << currentStreak << "\033[0m" << std::endl;
    std::cout << "Best Streak: \033[35m" << bestStreak << "\033[0m" << std::endl;
    std::cout << "Jackpots: \033[33m" << jackpotsTriggered << "\033[0m" << std::endl;
    std::cout << "Reward Paid: \033[32m" << totalRewardPaid << "\033[0m" << std::endl;
    std::cout << "Highest Wager: \033[31m" << highestSingleWager << "\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Inventory: ";
    bool hasAnyItem = false;
    if (extraLifeOwned) {
        std::cout << "Extra Life";
        hasAnyItem = true;
    }
    if (gamblingInsuranceOwned) {
        if (hasAnyItem) std::cout << ", ";
        std::cout << "Insurance";
        hasAnyItem = true;
    }
    if (highRewardOwned) {
        if (hasAnyItem) std::cout << ", ";
        std::cout << "High Reward";
        hasAnyItem = true;
    }
    if (safeBetShieldOwned) {
        if (hasAnyItem) std::cout << ", ";
        std::cout << "Shield";
        hasAnyItem = true;
    }
    if (luckyCharmOwned) {
        if (hasAnyItem) std::cout << ", ";
        std::cout << "Lucky Charm";
        hasAnyItem = true;
    }
    if (doubleDownOwned) {
        if (hasAnyItem) std::cout << ", ";
        std::cout << "Double Down";
        hasAnyItem = true;
    }
    if (!hasAnyItem) std::cout << "Empty";
    std::cout << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Press ENTER to return ";
    _getch();
}

// --- Gameplay ---
void playGame() {
    std::srand(std::time(0));
    int range = 10;
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

    if (wager > 0) {
        highestSingleWager = std::max(highestSingleWager, wager);
    }

    roundsPlayed++;
    std::string status = "I'm thinking of a number between 1 and 10.";
    int attemptCount = 1;
    while (lives > 0) {
        clear();
        std::cout << "\033[1;37mGAMEPLAY\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m | Lives: \033[1;31m" << lives << "\033[0m" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Status: " << status << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Enter your guess \033[32m>\033[0m ";
        std::cin >> guess;

        bool guessedCorrectly = (guess == secretNum);
        if (attemptCount == 1 && guessedCorrectly) {
            firstTryWins++;
            checkBadges();
        }

        if (guessedCorrectly) {
            totalWins++;
            currentStreak++;
            bestStreak = std::max(bestStreak, currentStreak);
            clear();
            double rewardMult = (difficulty == 3) ? 0.55 : 0.20;
            int winAmt = std::round(wager * rewardMult);
            if (highRewardOwned == 1) {
                winAmt = std::round(winAmt * 1.35);
                highRewardOwned = 0;
                std::cout << "Bonus applied! ";
            }
            bool usedLuckyCharm = false;
            if (luckyCharmOwned == 1) {
                winAmt = std::round(winAmt * 1.10);
                luckyCharmOwned = 0;
                usedLuckyCharm = true;
                std::cout << "Lucky Charm activated! ";
            }
            if (doubleDownOwned == 1) {
                winAmt *= 2;
                doubleDownOwned = 0;
                std::cout << "Double Down triggered! ";
            }
            bool jackpot = (std::rand() % 10 == 0);
            if (usedLuckyCharm && !jackpot) {
                jackpot = (std::rand() % 20 == 0);
            }
            if (jackpot) {
                winAmt *= 2;
                jackpotsTriggered++;
            }
            totalPoints += winAmt;
            totalRewardPaid += winAmt;
            if (difficulty == 4) {
                extremeWins++;
            }
            checkBadges();
            clear();
            std::cout << "\033[1;37mROUND RESULT\033[0m \033[33m//\033[0m \033[32mWIN\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Reward: \033[32m+" << winAmt << " points\033[0m" << std::endl;
            std::cout << "Lives left: \033[35m" << lives << "\033[0m" << std::endl;
            std::cout << "Streak: \033[36m" << currentStreak << "\033[0m" << std::endl;
            if (jackpot) {
                std::cout << "\033[33mJACKPOT! Double reward!\033[0m" << std::endl;
            }
            std::cout << "Total points: \033[33m" << totalPoints << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Progress is saved." << std::endl;
            std::cout << "Press ENTER to continue";
            saveGame();
            waitForEnter();
            return;
        } else {
            attemptCount++;
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
    currentStreak = 0;
    int lostAmt = wager;
    if (gamblingInsuranceOwned == 1) {
        lostAmt = std::round(wager * 0.90);
        gamblingInsuranceOwned = 0;
        std::cout << "Insurance saved you 10%!" << std::endl;
    }
    if (safeBetShieldOwned == 1) {
        lostAmt = std::round(lostAmt * 0.5);
        safeBetShieldOwned = 0;
        safeBetShieldUses++;
        std::cout << "Safe Bet Shield reduced the loss!" << std::endl;
    }
    totalPoints -= lostAmt;
    checkBadges();
    clear();
    std::cout << "\033[1;37mROUND RESULT\033[0m \033[33m//\033[0m \033[31mLOSS\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Penalty: \033[31m-" << lostAmt << " points\033[0m" << std::endl;
    std::cout << "Streak ended: \033[35m0\033[0m" << std::endl;
    std::cout << "The number was: \033[36m" << secretNum << "\033[0m" << std::endl;
    std::cout << "Total points: \033[33m" << totalPoints << "\033[0m" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Press ENTER to continue";
    saveGame();
    waitForEnter();
    if (totalPoints <= 0) {
        std::cout << "Bankrupt! Save deleted." << std::endl;
        remove("save.txt");
        exit(0);
    }
    wait(3000);
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
            std::cout << "\033[1;37mSUPER GAMBLING\033[0m \033[33m//\033[0m \033[36mV1.4\033[0m \033[33m//\033[0m \033[32m" << playerName << "\033[0m" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "\033[32m[" << (selected == 1 ? "*" : "1") << "]\033[0m Start Game" << std::endl;
            std::cout << "\033[36m[" << (selected == 2 ? "*" : "2") << "]\033[0m Open Store" << std::endl;
            std::cout << "\033[33m[" << (selected == 3 ? "*" : "3") << "]\033[0m View Stats" << std::endl;
            std::cout << "\033[35m[" << (selected == 4 ? "*" : "4") << "]\033[0m Badges" << std::endl;
            std::cout << "\033[31m[" << (selected == 5 ? "*" : "5") << "]\033[0m Exit" << std::endl;

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

        if (selected == 1) playGame();
        else if (selected == 2) openStore();
        else if (selected == 3) viewStats();
        else if (selected == 4) viewBadges();
        else if (selected == 5) break;
    }

    return 0;
}
