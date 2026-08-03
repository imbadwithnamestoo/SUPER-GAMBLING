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
#include <iomanip>

#define wait(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
    int _getch() {
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

// --- Shop Items ---
int oracleEyeOwned = 0;
int streakGuardOwned = 0;
int streakGuardUses = 0;
int goldenThreadOwned = 0;
int blindfoldOwned = 0;

// --- Tracking Stats ---
int totalPointsLost = 0;
int biggestSingleLoss = 0;
int totalGuessesMade = 0;

// --- Settings & Themes ---
int textDelayActive = 1;
int currentTheme = 0; 
int defaultDifficulty = 2; 

std::string T_TITLE = "\033[1;37m";
std::string T_USER = "\033[32m";
std::string T_PRICE = "\033[33m";
std::string T_INFO = "\033[36m";
std::string T_WIN = "\033[32m";
std::string T_LOSS = "\033[31m";
std::string T_ACCENT = "\033[33m";
std::string T_SPECIAL = "\033[35m"; 
std::string T_EXTRA = "\033[34m";   
std::string T_RESET = "\033[0m";

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
int badgeClutch = 0;
int badgeVeteran = 0;
int badgeUnstoppable = 0;
int badgeBigSpender = 0;

std::vector<std::string> unlockedBadges;

std::string playerName;

// --- Helper Functions ---

void updateThemeColors() {
    if (currentTheme == 0) {
        T_TITLE = "\033[1;37m";
        T_USER = "\033[32m";
        T_PRICE = "\033[33m";
        T_INFO = "\033[36m";
        T_WIN = "\033[32m";
        T_LOSS = "\033[31m";
        T_ACCENT = "\033[33m";
        T_SPECIAL = "\033[35m";
        T_EXTRA = "\033[34m";
    }
    else if (currentTheme == 1) {
        T_TITLE = "\033[1;36m";
        T_USER = "\033[35m";
        T_PRICE = "\033[33m";
        T_INFO = "\033[1;37m";
        T_WIN = "\033[36m";
        T_LOSS = "\033[35m";
        T_ACCENT = "\033[33m";
        T_SPECIAL = "\033[1;36m";
        T_EXTRA = "\033[35m";
    }
    else if (currentTheme == 2) {
        T_TITLE = "\033[1;37m";
        T_USER = "\033[1;37m";
        T_PRICE = "\033[1;37m";
        T_INFO = "\033[1;37m";
        T_WIN = "\033[1;37m";
        T_LOSS = "\033[1;37m";
        T_ACCENT = "\033[1;37m";
        T_SPECIAL = "\033[1;37m";
        T_EXTRA = "\033[1;37m";
    }
}

void smartWait(int ms) {
    if (textDelayActive == 1) {
        wait(ms);
    }
}

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
        std::cout << T_ACCENT << "BADGE UNLOCKED: " << T_RESET << badgeName << std::endl;
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

        outFile << oracleEyeOwned << std::endl;
        outFile << streakGuardOwned << std::endl;
        outFile << streakGuardUses << std::endl;
        outFile << goldenThreadOwned << std::endl;
        outFile << blindfoldOwned << std::endl;

        outFile << totalPointsLost << std::endl;
        outFile << biggestSingleLoss << std::endl;
        outFile << totalGuessesMade << std::endl;

        outFile << textDelayActive << std::endl;
        outFile << currentTheme << std::endl;
        outFile << defaultDifficulty << std::endl;

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
        outFile << badgeClutch << std::endl;
        outFile << badgeVeteran << std::endl;
        outFile << badgeUnstoppable << std::endl;
        outFile << badgeBigSpender << std::endl;

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
    if (roundsPlayed >= 50) {
        markBadgeAsUnlocked(badgeVeteran, "Veteran");
    }
    if (bestStreak >= 10) {
        markBadgeAsUnlocked(badgeUnstoppable, "Unstoppable");
    }
    if (highestSingleWager >= 5000) {
        markBadgeAsUnlocked(badgeBigSpender, "Big Spender");
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
        std::getline(inFile >> std::ws, playerName); 
        inFile >> totalPoints 
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

        inFile >> oracleEyeOwned
               >> streakGuardOwned
               >> streakGuardUses
               >> goldenThreadOwned
               >> blindfoldOwned;

        inFile >> totalPointsLost
               >> biggestSingleLoss
               >> totalGuessesMade;

        inFile >> textDelayActive;
        inFile >> currentTheme;
        inFile >> defaultDifficulty;

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
               >> badgeCollector
               >> badgeClutch
               >> badgeVeteran
               >> badgeUnstoppable
               >> badgeBigSpender;

        inFile.close();
        updateThemeColors();
    }
}

void openSettings() {
    int selected = 1;
    bool inSettings = true;
    clear(); 

    while (inSettings) {
        resetCursor();
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << T_TITLE << "SETTINGS" << T_RESET << " // " << T_USER << playerName << T_RESET << "\033[K" << std::endl;
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << T_WIN << "[" << (selected == 1 ? "*" : "1") << "]" << T_RESET << " Change Username\033[K" << std::endl;
        std::cout << T_INFO << "[" << (selected == 2 ? "*" : "2") << "]" << T_RESET << " Text Delays: " << (textDelayActive ? T_WIN + "ON" : T_LOSS + "OFF") << T_RESET << "\033[K" << std::endl;
        
        std::string themeName = "Classic";
        if (currentTheme == 1) themeName = "Cyber";
        if (currentTheme == 2) themeName = "Monochrome";
        std::cout << T_PRICE << "[" << (selected == 3 ? "*" : "3") << "]" << T_RESET << " Color Theme: " << T_INFO << themeName << T_RESET << "\033[K" << std::endl;

        std::string diffName = "Normal";
        if (defaultDifficulty == 1) diffName = "Easy";
        if (defaultDifficulty == 3) diffName = "Hard";
        if (defaultDifficulty == 4) diffName = "EXTREME";
        std::cout << T_SPECIAL << "[" << (selected == 4 ? "*" : "4") << "]" << T_RESET << " Default Difficulty: " << T_INFO << diffName << T_RESET << "\033[K" << std::endl;
        
        std::cout << T_LOSS << "[" << (selected == 5 ? "*" : "5") << "]" << T_RESET << " Wipe All Data\033[K" << std::endl;
        std::cout << T_TITLE << "[" << (selected == 6 ? "*" : "6") << "]" << T_RESET << " Back to Menu\033[K" << std::endl;
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << T_INFO << "Patch Version: V1.5.1\033[K" << std::endl;

        int input = _getch();
        if (input == 224 || input == 27) {
            int arrow = _getch();
            if (input == 27 && arrow == 91) arrow = _getch();

            if (arrow == 72 || arrow == 'A') {
                if (selected > 1) selected--;
                else selected = 6;
            } 
            else if (arrow == 80 || arrow == 'B') {
                if (selected < 6) selected++;
                else selected = 1;
            }
        } 
        else if (input == 13 || input == 10) {
            if (selected == 1) {
                clear();
                std::cout << "Enter new username: ";
                std::getline(std::cin >> std::ws, playerName);
                saveGame();
                std::cout << "Username updated!" << std::endl;
                smartWait(1000);
                clear();
            }
            else if (selected == 2) {
                textDelayActive = !textDelayActive;
                saveGame();
            }
            else if (selected == 3) {
                currentTheme++;
                if (currentTheme > 2) currentTheme = 0;
                updateThemeColors();
                saveGame();
            }
            else if (selected == 4) {
                defaultDifficulty++;
                if (defaultDifficulty > 4) defaultDifficulty = 1;
                saveGame();
            }
            else if (selected == 5) {
                std::cout << T_LOSS << "ARE YOU SURE? (Y/N): " << T_RESET;
                char confirm;
                if (!(std::cin >> confirm)) {
                    std::cin.clear();
                }
                std::cin.ignore(1000, '\n');
                if (confirm == 'y' || confirm == 'Y') {
                    remove("save.txt");
                    std::cout << "Data wiped. Exiting game..." << std::endl;
                    exit(0);
                }
                clear();
            }
            else if (selected == 6) {
                inSettings = false;
            }
        }
    }
}

int chooseShopItem() {
    int selected = 1;
    bool choiceMade = false;
    clear(); 

    while (!choiceMade) {
        resetCursor();
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << T_TITLE << "SHOP" << T_RESET << " // " << T_INFO << "ITEMS" << T_RESET << " // " << T_USER << playerName << T_RESET << "\033[K" << std::endl;
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << T_WIN << "[" << (selected == 1 ? "*" : "1") << "]" << T_RESET << " Extra Life             " << T_PRICE << "$150" << T_RESET << "\033[K" << std::endl;
        std::cout << T_WIN << "[" << (selected == 2 ? "*" : "2") << "]" << T_RESET << " Gambling Insurance    " << T_PRICE << "$350" << T_RESET << "\033[K" << std::endl;
        std::cout << T_WIN << "[" << (selected == 3 ? "*" : "3") << "]" << T_RESET << " High Reward           " << T_PRICE << "$250" << T_RESET << "\033[K" << std::endl;
        int shieldCost = 300 * (1 << safeBetShieldUses);
        std::cout << T_WIN << "[" << (selected == 4 ? "*" : "4") << "]" << T_RESET << " Safe Bet Shield      " << T_PRICE << "$" << shieldCost << T_RESET << "\033[K" << std::endl;
        std::cout << T_ACCENT << "[" << (selected == 5 ? "*" : "5") << "]" << T_RESET << " Lucky Charm           " << T_PRICE << "$400" << T_RESET << "\033[K" << std::endl;
        std::cout << T_SPECIAL << "[" << (selected == 6 ? "*" : "6") << "]" << T_RESET << " Double Down          " << T_PRICE << "$500" << T_RESET << "\033[K" << std::endl;
        std::cout << T_INFO << "[" << (selected == 7 ? "*" : "7") << "]" << T_RESET << " Oracle's Eye         " << T_PRICE << "$200" << T_RESET << "\033[K" << std::endl;
        int streakCost = 600 * (1 << streakGuardUses);
        std::cout << T_EXTRA << "[" << (selected == 8 ? "*" : "8") << "]" << T_RESET << " Streak Guard         " << T_PRICE << "$" << streakCost << T_RESET << "\033[K" << std::endl;
        std::cout << T_ACCENT << "[" << (selected == 9 ? "*" : "9") << "]" << T_RESET << " Golden Thread         " << T_PRICE << "$5000" << T_RESET << "\033[K" << std::endl;
        std::cout << T_LOSS << "[" << (selected == 10? "*" : "10") << "]" << T_RESET << " The Blindfold        " << T_PRICE << " $300" << T_RESET << "\033[K" << std::endl;
        std::cout << T_TITLE << "[" << (selected == 11? "*" : "11") << "]" << T_RESET << " Back to Menu\033[K" << std::endl;
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << "Use Arrows to move, Enter to select\033[K" << std::endl;

        int input = _getch();
        if (input == 224 || input == 27) {
            int arrow = _getch();
            if (input == 27 && arrow == 91) arrow = _getch();

            if (arrow == 72 || arrow == 'A') {
                if (selected > 1) selected--;
                else selected = 11;
            } 
            else if (arrow == 80 || arrow == 'B') {
                if (selected < 11) selected++;
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

    int totalBadges = 15;
    int unlockedCount = badgeFirstWin + badgeHighRoller + badgeMillionaire + badgeExtremeMaster + badgeShopaholic + badgeLuckyFirstTry + badgeBillionaire + badgeStreakMaster + badgeJackpotHunter + badgeLegend + badgeCollector + badgeClutch + badgeVeteran + badgeUnstoppable + badgeBigSpender;

    std::cout << "------------------------------------" << std::endl;
    std::cout << T_TITLE << "BADGES" << T_RESET << " // " << T_USER << playerName << T_RESET << std::endl;
    std::cout << "------------------------------------" << std::endl;

    auto displayBadge = [&](int flag, std::string name, std::string desc) {
        std::cout << (flag ? T_WIN + "[x]" + T_RESET + " " : T_LOSS + "[ ]" + T_RESET + " ") << name << "\n     " << desc << "\n\n";
    };

    displayBadge(badgeFirstWin, "Winner", "Win 3 rounds total.");
    displayBadge(badgeLuckyFirstTry, "Lucky First Try", "Guess correctly on your first try.");
    displayBadge(badgeClutch, "Clutch", "Win a round on your very last life.");
    displayBadge(badgeStreakMaster, "Streak Master", "Reach a streak of 5 wins.");
    displayBadge(badgeUnstoppable, "Unstoppable", "Reach a streak of 10 wins.");
    displayBadge(badgeHighRoller, "High Roller", "Wager 1000 points in one game.");
    displayBadge(badgeBigSpender, "Big Spender", "Wager 5000 points in one game.");
    displayBadge(badgeMillionaire, "Rich Player", "Reach 2500 points.");
    displayBadge(badgeBillionaire, "Billionaire", "Reach 15,000 points.");
    displayBadge(badgeExtremeMaster, "Extreme Master", "Beat Extreme difficulty 2 times.");
    displayBadge(badgeJackpotHunter, "Jackpot Hunter", "Trigger 3 jackpots.");
    displayBadge(badgeShopaholic, "Shopaholic", "Buy 3 shop items.");
    displayBadge(badgeCollector, "Collector", "Purchase 8 shop items.");
    displayBadge(badgeLegend, "Legend", "Win 15 rounds total.");
    displayBadge(badgeVeteran, "Veteran", "Play 50 rounds total.");

    std::cout << "------------------------------------" << std::endl;
    std::cout << "Unlocked: " << T_ACCENT << unlockedCount << "/" << totalBadges << T_RESET << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Press ENTER to return ";

    _getch();
}

int chooseDifficulty() {
    clear();
    int selected = defaultDifficulty;
    bool choiceMade = false;

    while (!choiceMade) {
        resetCursor();
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << T_TITLE << "DIFFICULTY" << T_RESET << " // " << T_USER << playerName << T_RESET << "\033[K" << std::endl;
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << T_WIN << "[" << (selected == 1 ? "*" : "1") << "]" << T_RESET << " Easy   (7 lives)\033[K" << std::endl;
        std::cout << T_ACCENT << "[" << (selected == 2 ? "*" : "2") << "]" << T_RESET << " Normal (4 lives)\033[K" << std::endl;
        std::cout << T_LOSS << "[" << (selected == 3 ? "*" : "3") << "]" << T_RESET << " Hard   (3 lives)\033[K" << std::endl;
        std::cout << T_SPECIAL << "[" << (selected == 4 ? "*" : "4") << "]" << T_RESET << " EXTREME\033[K" << std::endl;
        std::cout << T_TITLE << "[" << (selected == 5 ? "*" : "5") << "]" << T_RESET << " Exit to menu\033[K" << std::endl;
        std::cout << "------------------------------------\033[K" << std::endl;
        std::cout << "Use Arrows to move, Enter to select\033[K" << std::endl;

        int input = _getch();
        if (input == 224 || input == 27) {
            int arrow = _getch();
            if (input == 27 && arrow == 91) arrow = _getch();

            if (arrow == 72 || arrow == 'A') {
                if (selected > 1) selected--;
                else selected = 5;
            } 
            else if (arrow == 80 || arrow == 'B') {
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

void openStore() {
    while (true) {
        int choice = chooseShopItem();
        char buyChoice = 'n';

        if (choice == 11) {
            return;
        }

        clear();
        std::cout << "------------------------------------" << std::endl;
        std::cout << T_TITLE << "SHOP" << T_RESET << " // " << T_INFO << "DESCRIPTION" << T_RESET << " // " << T_USER << playerName << T_RESET << std::endl;
        std::cout << "Current Points: " << T_PRICE << "$" << totalPoints << T_RESET << std::endl; 
        std::cout << "------------------------------------" << std::endl;

        auto handlePurchase = [&](int& owned, int cost, bool isTiered = false, int* uses = nullptr) {
            std::cout << "Purchase? [" << T_WIN << "Y" << T_RESET << "/" << T_LOSS << "N" << T_RESET << "]: ";
            if (!(std::cin >> buyChoice)) {
                std::cin.clear();
            }
            std::cin.ignore(1000, '\n');
            if (buyChoice == 'y' || buyChoice == 'Y') {
                if (owned == 1 && !isTiered) {
                    std::cout << "Already owned!" << std::endl;
                } else if (totalPoints >= cost) { 
                    totalPoints -= cost; 
                    owned = 1; 
                    if (uses) (*uses)++;
                    totalShopPurchases++;
                    checkBadges();
                    saveGame(); 
                    std::cout << "Purchased!" << std::endl; 
                } else {
                    std::cout << "Not enough points!" << std::endl;
                }
                smartWait(1000);
            }
        };

        if (choice == 1) {
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "Extra Life" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$150" << T_RESET << std::endl;
            std::cout << " Provides " << T_WIN << "+1 Extra Life" << T_RESET << " for your next" << std::endl;
            std::cout << " round. This is a " << T_ACCENT << "single-use" << T_RESET << " item." << std::endl;
            handlePurchase(extraLifeOwned, 150);
        } 
        else if (choice == 2) {
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "Gambling Insurance" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$350" << T_RESET << std::endl;
            std::cout << " Reduces all wager losses by " << T_WIN << "10%" << T_RESET << "." << std::endl;
            handlePurchase(gamblingInsuranceOwned, 350);
        } 
        else if (choice == 3) {
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "High Reward" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$250" << T_RESET << std::endl;
            std::cout << " Increases your next win by " << T_WIN << "35%" << T_RESET << "." << std::endl;
            handlePurchase(highRewardOwned, 250);
        } 
        else if (choice == 4) {
            int shieldCost = 300 * (1 << safeBetShieldUses);
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "Safe Bet Shield" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$" << shieldCost << T_RESET << std::endl;
            std::cout << " Reduces the penalty of your next loss by " << T_WIN << "50%" << T_RESET << "." << std::endl;
            handlePurchase(safeBetShieldOwned, shieldCost);
        }
        else if (choice == 5) {
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "Lucky Charm" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$400" << T_RESET << std::endl;
            std::cout << " Gives your next win a " << T_WIN << "10% bonus" << T_RESET << " and a " << T_WIN << "small extra jackpot chance" << T_RESET << "." << std::endl;
            handlePurchase(luckyCharmOwned, 400);
        }
        else if (choice == 6) {
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "Double Down" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$500" << T_RESET << std::endl;
            std::cout << " Doubles your next win reward." << std::endl;
            handlePurchase(doubleDownOwned, 500);
        }
        else if (choice == 7) {
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "Oracle's Eye" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$200" << T_RESET << std::endl;
            std::cout << " Tells you if the secret number is EVEN or ODD at start." << std::endl;
            handlePurchase(oracleEyeOwned, 200);
        }
        else if (choice == 8) {
            int streakCost = 600 * (1 << streakGuardUses);
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "Streak Guard" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$" << streakCost << T_RESET << std::endl;
            std::cout << " If you lose, your win streak will not reset to zero." << std::endl;
            handlePurchase(streakGuardOwned, streakCost, true, &streakGuardUses);
        }
        else if (choice == 9) {
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "Golden Thread" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$5000" << T_RESET << std::endl;
            std::cout << " Prevents save deletion if points hit $0. Resets to $100." << std::endl;
            handlePurchase(goldenThreadOwned, 5000);
        }
        else if (choice == 10) {
            std::cout << T_TITLE << "ITEM:" << T_RESET << " " << T_SPECIAL << "The Blindfold" << T_RESET << std::endl; 
            std::cout << T_TITLE << "COST:" << T_RESET << " " << T_ACCENT << "$300" << T_RESET << std::endl;
            std::cout << " Removes Higher/Lower hints. Reward is Quadrupled (4x)." << std::endl;
            handlePurchase(blindfoldOwned, 300);
        }
    }
}

void viewStats() {
    clear();
    std::cout << "------------------------------------" << std::endl;
    std::cout << T_TITLE << "PLAYER STATS" << T_RESET << " // " << T_USER << playerName << T_RESET << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Points: " << T_PRICE << totalPoints << T_RESET << std::endl;
    std::cout << "Wins:   " << T_WIN << totalWins << T_RESET << std::endl;
    std::cout << "Losses: " << T_LOSS << totalLoss << T_RESET << std::endl;
    std::cout << "Rounds Played: " << T_INFO << roundsPlayed << T_RESET << std::endl;
    std::cout << "Current Streak: " << T_SPECIAL << currentStreak << T_RESET << std::endl;
    std::cout << "Best Streak: " << T_SPECIAL << bestStreak << T_RESET << std::endl;
    std::cout << "Jackpots: " << T_PRICE << jackpotsTriggered << T_RESET << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Total Reward Paid: " << T_WIN << "$" << totalRewardPaid << T_RESET << std::endl;
    std::cout << "Total Points Lost: " << T_LOSS << "$" << totalPointsLost << T_RESET << std::endl;
    std::cout << "Highest Wager: " << T_LOSS << "$" << highestSingleWager << T_RESET << std::endl;
    std::cout << "Biggest Single Loss: " << T_LOSS << "$" << biggestSingleLoss << T_RESET << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Total Guesses: " << T_INFO << totalGuessesMade << T_RESET << std::endl;
    double avg = 0;
    if (totalWins > 0) {
        avg = (double)totalGuessesMade / totalWins;
    }
    std::cout << "Avg Guesses/Win: " << T_INFO << std::fixed << std::setprecision(2) << avg << T_RESET << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Inventory: ";
    bool hasAnyItem = false;
    if (extraLifeOwned) { std::cout << T_SPECIAL << "Life" << T_RESET; hasAnyItem = true; }
    if (gamblingInsuranceOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "Insurance" << T_RESET; hasAnyItem = true; }
    if (highRewardOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "High Reward" << T_RESET; hasAnyItem = true; }
    if (safeBetShieldOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "Shield" << T_RESET; hasAnyItem = true; }
    if (luckyCharmOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "Charm" << T_RESET; hasAnyItem = true; }
    if (doubleDownOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "Double" << T_RESET; hasAnyItem = true; }
    if (oracleEyeOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "Oracle" << T_RESET; hasAnyItem = true; }
    if (streakGuardOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "Streak Guard" << T_RESET; hasAnyItem = true; }
    if (goldenThreadOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "Thread" << T_RESET; hasAnyItem = true; }
    if (blindfoldOwned) { std::cout << (hasAnyItem ? ", " : "") << T_SPECIAL << "Blindfold" << T_RESET; hasAnyItem = true; }
    if (!hasAnyItem) std::cout << "Empty";
    std::cout << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Press ENTER to return ";
    _getch();
}

void playGame() {
    std::srand(std::time(0));
    int range = 10;
    int secretNum = std::rand() % range + 1;
    int guess = 0;
    int lives = 5;
    int difficulty = chooseDifficulty();
    if (difficulty == 5) {
        return;
    }

    if (difficulty == 1) {
        lives = 7;
    } else if (difficulty == 2) {
        lives = 4;
    } else if (difficulty == 3) {
        lives = 3;
    } else if (difficulty == 4) {
        lives = 5;
    }

    if (difficulty > 1 && extraLifeOwned == 1) {
        lives++;
        extraLifeOwned = 0;
        std::cout << T_SPECIAL << "Extra life applied!" << T_RESET << std::endl;
    }

    int wager = 0;
    int minWager = totalPoints * 0.15;
    if (minWager > 1000) minWager = 1000; 
    if (minWager <= 0) {
        minWager = totalPoints;
    }

    if (difficulty == 1) {
        wager = 0;
        std::cout << "Easy mode: No wagering." << std::endl;
        smartWait(1000);
    } else {
        std::cout << T_TITLE << "Points: " << T_PRICE << "$" << totalPoints << T_RESET << " (Min: $" << minWager << ")" << std::endl;
        std::cout << "Wager: $";
        
        if (!(std::cin >> wager)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            wager = totalPoints;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (wager > totalPoints || wager < minWager) {
            wager = totalPoints;
            std::cout << T_LOSS << "Invalid! Going all-in: $" << wager << T_RESET << std::endl;
            smartWait(1500);
        }
    }

    highestSingleWager = std::max(highestSingleWager, wager);
    roundsPlayed++;

    std::string status = "I'm thinking of a number between 1 and 10.";

    if (oracleEyeOwned == 1) {
        if (secretNum % 2 == 0) {
            status = "The Oracle senses an " + T_INFO + "EVEN" + T_RESET + " number.";
        } else {
            status = "The Oracle senses an " + T_INFO + "ODD" + T_RESET + " number.";
        }
        oracleEyeOwned = 0;
    }

    bool blindfoldActive = false;
    if (blindfoldOwned == 1) {
        if (difficulty == 1) {
            std::cout << "Blindfold cannot be used on Easy!" << std::endl;
            smartWait(1000);
        } else {
            blindfoldActive = true;
            blindfoldOwned = 0;
            std::cout << T_LOSS << "Blindfold active: No hints, 4x Reward!" << T_RESET << std::endl;
            smartWait(1500);
        }
    }

    int attemptCount = 1;
    while (lives > 0) {
        clear();
        std::cout << "------------------------------------" << std::endl;
        std::cout << T_TITLE << "GAMEPLAY" << T_RESET << " // " << T_USER << playerName << T_RESET << " | Lives: " << T_LOSS << lives << T_RESET << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Status: " << status << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Enter your guess " << T_WIN << "> " << T_RESET;
        
        if (!(std::cin >> guess)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        totalGuessesMade++;

        if (guess == secretNum) {
            if (attemptCount == 1) {
                firstTryWins++;
            }
            if (lives == 1) {
                markBadgeAsUnlocked(badgeClutch, "Clutch");
            }
            
            totalWins++;
            currentStreak++;
            bestStreak = std::max(bestStreak, currentStreak);
            
            double rewardMult = (difficulty == 3) ? 0.55 : 0.20;
            int winAmt = std::round(wager * rewardMult);
            
            if (highRewardOwned == 1) {
                winAmt = std::round(winAmt * 1.35);
                highRewardOwned = 0;
                std::cout << "Bonus applied! ";
            }
            if (luckyCharmOwned == 1) {
                winAmt = std::round(winAmt * 1.10);
                luckyCharmOwned = 0;
                std::cout << "Lucky Charm activated! ";
            }
            if (doubleDownOwned == 1) {
                winAmt *= 2;
                doubleDownOwned = 0;
                std::cout << "Double Down triggered! ";
            }
            if (blindfoldActive) {
                winAmt *= 4;
            }
            if (std::rand() % 10 == 0) {
                winAmt *= 2;
                jackpotsTriggered++;
            }
            
            totalPoints += winAmt;
            totalRewardPaid += winAmt;
            if (difficulty == 4) {
                extremeWins++;
            }
            
            checkBadges();
            saveGame();
            clear();
            std::cout << "------------------------------------" << std::endl;
            std::cout << T_WIN << "WIN! +" << winAmt << " points" << T_RESET << std::endl;
            std::cout << "Total points: " << T_PRICE << totalPoints << T_RESET << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Press ENTER to continue";
            waitForEnter();
            return;
        } else {
            attemptCount++;
            lives--;
            if (difficulty == 4) {
                secretNum = newNum(secretNum, guess);
                status = "The number shifted!";
            } else {
                if (blindfoldActive) {
                    status = T_LOSS + "Wrong!" + T_RESET;
                } else {
                    status = (guess > secretNum) ? T_LOSS + "Lower!" + T_RESET : T_LOSS + "Higher!" + T_RESET;
                }
            }
        }
    }

    totalLoss++;
    if (streakGuardOwned == 1) {
        std::cout << T_EXTRA << "Streak Guard used: Streak saved!" << T_RESET << std::endl;
        streakGuardOwned = 0;
    } else {
        currentStreak = 0;
    }

    int lostAmt = wager;
    if (gamblingInsuranceOwned == 1) {
        lostAmt = std::round(wager * 0.90);
        gamblingInsuranceOwned = 0;
    }
    if (safeBetShieldOwned == 1) {
        lostAmt = std::round(lostAmt * 0.5);
        safeBetShieldOwned = 0;
        safeBetShieldUses++;
    }
    
    totalPoints -= lostAmt;
    totalPointsLost += lostAmt;
    biggestSingleLoss = std::max(biggestSingleLoss, lostAmt);

    if (totalPoints <= 0 && goldenThreadOwned == 1) {
        totalPoints = 100;
        goldenThreadOwned = 0;
        std::cout << T_ACCENT << "Golden Thread snapped! You revived with $100." << T_RESET << std::endl;
    }

    checkBadges();
    saveGame();
    clear();
    std::cout << "------------------------------------" << std::endl;
    std::cout << T_LOSS << "LOSS! -" << lostAmt << " points" << T_RESET << std::endl;
    std::cout << "The number was: " << T_INFO << secretNum << T_RESET << std::endl;
    std::cout << "Total points: " << T_PRICE << totalPoints << T_RESET << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Press ENTER to continue";
    waitForEnter();

    if (totalPoints <= 0) {
        std::cout << "Bankrupt! Save deleted." << std::endl;
        remove("save.txt");
        exit(0);
    }
}

int main() {
    clear();
    std::srand(std::time(0));
    std::ifstream checkFile("save.txt");
    if (!checkFile.is_open()) {
        std::cout << "Please choose a username: ";
        std::getline(std::cin >> std::ws, playerName);
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
            std::cout << "------------------------------------\033[K" << std::endl;
            std::cout << T_TITLE << "SUPER GAMBLING" << T_RESET << " // " << T_INFO << "V1.5" << T_RESET << " // " << T_USER << playerName << T_RESET << "\033[K" << std::endl;
            std::cout << "------------------------------------\033[K" << std::endl;
            std::cout << T_WIN << "[" << (selected == 1 ? "*" : "1") << "]" << T_RESET << " Start Game\033[K" << std::endl;
            std::cout << T_INFO << "[" << (selected == 2 ? "*" : "2") << "]" << T_RESET << " Open Store\033[K" << std::endl;
            std::cout << T_PRICE << "[" << (selected == 3 ? "*" : "3") << "]" << T_RESET << " View Stats\033[K" << std::endl;
            std::cout << T_SPECIAL << "[" << (selected == 4 ? "*" : "4") << "]" << T_RESET << " Badges\033[K" << std::endl;
            std::cout << T_EXTRA << "[" << (selected == 5 ? "*" : "5") << "]" << T_RESET << " Settings\033[K" << std::endl;
            std::cout << T_LOSS << "[" << (selected == 6 ? "*" : "6") << "]" << T_RESET << " Exit\033[K" << std::endl;
            std::cout << "------------------------------------\033[K" << std::endl;

            int input = _getch();
            if (input == 224 || input == 27) {
                int arrow = _getch();
                if (input == 27 && arrow == 91) {
                    arrow = _getch();
                }
                if (arrow == 72 || arrow == 'A') { 
                    if (selected > 1) {
                        selected--;
                    } else {
                        selected = 6;
                    }
                }
                else if (arrow == 80 || arrow == 'B') { 
                    if (selected < 6) {
                        selected++;
                    } else {
                        selected = 1;
                    }
                }
            } else if (input == 13 || input == 10) {
                choiceMade = true;
            }
        }

        if (selected == 1) {
            playGame();
        } else if (selected == 2) {
            openStore();
        } else if (selected == 3) {
            viewStats();
        } else if (selected == 4) {
            viewBadges();
        } else if (selected == 5) {
            openSettings();
        } else if (selected == 6) {
            break;
        }
    }
    return 0;
}
