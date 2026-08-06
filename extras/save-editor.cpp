#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

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

// --- Color Scheme ---
const std::string T_TITLE = "\033[1;37m";
const std::string T_USER = "\033[32m";
const std::string T_PRICE = "\033[33m";
const std::string T_INFO = "\033[36m";
const std::string T_WIN = "\033[32m";
const std::string T_LOSS = "\033[31m";
const std::string T_ACCENT = "\033[33m";
const std::string T_SPECIAL = "\033[35m"; 
const std::string T_RESET = "\033[0m";

struct GameData {
    std::string playerName;
    int totalPoints, totalWins, totalLoss, extraLifeOwned, gamblingInsuranceOwned, highRewardOwned;
    int safeBetShieldOwned, safeBetShieldUses, highestSingleWager, extremeWins, totalShopPurchases;
    int firstTryWins, currentStreak, bestStreak, jackpotsTriggered, roundsPlayed, totalRewardPaid;
    int luckyCharmOwned, doubleDownOwned, oracleEyeOwned, streakGuardOwned, streakGuardUses;
    int goldenThreadOwned, blindfoldOwned, totalPointsLost, biggestSingleLoss, totalGuessesMade;
    int textDelayActive, currentTheme, defaultDifficulty;
    int b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15; 
} data;

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool fileExists() {
    std::ifstream f("save.txt");
    return f.good();
}

void load() {
    std::ifstream inFile("save.txt");
    std::getline(inFile >> std::ws, data.playerName);
    inFile >> data.totalPoints >> data.totalWins >> data.totalLoss >> data.extraLifeOwned 
           >> data.gamblingInsuranceOwned >> data.highRewardOwned >> data.safeBetShieldOwned 
           >> data.safeBetShieldUses >> data.highestSingleWager >> data.extremeWins 
           >> data.totalShopPurchases >> data.firstTryWins >> data.currentStreak 
           >> data.bestStreak >> data.jackpotsTriggered >> data.roundsPlayed >> data.totalRewardPaid 
           >> data.luckyCharmOwned >> data.doubleDownOwned >> data.oracleEyeOwned 
           >> data.streakGuardOwned >> data.streakGuardUses >> data.goldenThreadOwned 
           >> data.blindfoldOwned >> data.totalPointsLost >> data.biggestSingleLoss 
           >> data.totalGuessesMade >> data.textDelayActive >> data.currentTheme 
           >> data.defaultDifficulty >> data.b1 >> data.b2 >> data.b3 >> data.b4 >> data.b5 
           >> data.b6 >> data.b7 >> data.b8 >> data.b9 >> data.b10 >> data.b11 >> data.b12 
           >> data.b13 >> data.b14 >> data.b15;
    inFile.close();
}

void save() {
    std::ofstream outFile("save.txt");
    outFile << data.playerName << "\n" << data.totalPoints << "\n" << data.totalWins << "\n" 
            << data.totalLoss << "\n" << data.extraLifeOwned << "\n" << data.gamblingInsuranceOwned << "\n" 
            << data.highRewardOwned << "\n" << data.safeBetShieldOwned << "\n" << data.safeBetShieldUses << "\n" 
            << data.highestSingleWager << "\n" << data.extremeWins << "\n" << data.totalShopPurchases << "\n" 
            << data.firstTryWins << "\n" << data.currentStreak << "\n" << data.bestStreak << "\n" 
            << data.jackpotsTriggered << "\n" << data.roundsPlayed << "\n" << data.totalRewardPaid << "\n" 
            << data.luckyCharmOwned << "\n" << data.doubleDownOwned << "\n" << data.oracleEyeOwned << "\n" 
            << data.streakGuardOwned << "\n" << data.streakGuardUses << "\n" << data.goldenThreadOwned << "\n" 
            << data.blindfoldOwned << "\n" << data.totalPointsLost << "\n" << data.biggestSingleLoss << "\n" 
            << data.totalGuessesMade << "\n" << data.textDelayActive << "\n" << data.currentTheme << "\n" 
            << data.defaultDifficulty << "\n" << data.b1 << "\n" << data.b2 << "\n" << data.b3 << "\n" 
            << data.b4 << "\n" << data.b5 << "\n" << data.b6 << "\n" << data.b7 << "\n" << data.b8 << "\n" 
            << data.b9 << "\n" << data.b10 << "\n" << data.b11 << "\n" << data.b12 << "\n" << data.b13 << "\n" 
            << data.b14 << "\n" << data.b15;
    outFile.close();
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void editInt(std::string label, int& val) {
    clear();
    std::cout << "------------------------------------\n";
    std::cout << T_TITLE << "EDITING: " << T_INFO << label << T_RESET << std::endl;
    std::cout << "Current Value: " << val << std::endl;
    std::cout << "------------------------------------\n";
    std::cout << "Enter New Value: ";
    if (!(std::cin >> val)) {
        clearInput();
    } else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void itemManager() {
    int subSelected = 1;
    struct ItemLink { std::string name; int* val; };
    std::vector<ItemLink> items = {
        {"Extra Life", &data.extraLifeOwned},
        {"Insurance", &data.gamblingInsuranceOwned},
        {"High Reward", &data.highRewardOwned},
        {"Safe Shield", &data.safeBetShieldOwned},
        {"Lucky Charm", &data.luckyCharmOwned},
        {"Double Down", &data.doubleDownOwned},
        {"Oracle Eye", &data.oracleEyeOwned},
        {"Streak Guard", &data.streakGuardOwned},
        {"Golden Thread", &data.goldenThreadOwned},
        {"The Blindfold", &data.blindfoldOwned}
    };

    while (true) {
        clear();
        std::cout << "------------------------------------\n";
        std::cout << T_TITLE << "INVENTORY MANAGER" << T_RESET << "\n";
        std::cout << "------------------------------------\n";
        for (int i = 0; i < items.size(); i++) {
            std::cout << (subSelected == i + 1 ? T_WIN + "[*] " : "[-] ") << T_RESET 
                      << items[i].name << ": " 
                      << (*items[i].val ? T_WIN + "OWNED" : T_LOSS + "EMPTY") << T_RESET << "\n";
        }
        std::cout << (subSelected == 11 ? T_WIN + "[*] " : "[-] ") << T_RESET << "Back to Main Menu\n";
        
        int input = _getch();
        if (input == 224 || input == 27) {
            int arrow = _getch();
            if (input == 27 && arrow == 91) arrow = _getch();
            if (arrow == 72 || arrow == 'A') subSelected = (subSelected > 1) ? subSelected - 1 : 11;
            else if (arrow == 80 || arrow == 'B') subSelected = (subSelected < 11) ? subSelected + 1 : 1;
        } else if (input == 13 || input == 10) {
            if (subSelected <= 10) *items[subSelected - 1].val = !(*items[subSelected - 1].val);
            else return;
        }
    }
}

int main() {
    if (!fileExists()) {
        clear();
        std::cout << T_LOSS << "FATAL ERROR: 'save.txt' not found!" << T_RESET << "\n";
        std::cout << "Make sure this editor is in the same folder as your game.\n";
        std::cout << "Press any key to exit...";
        _getch();
        return 1;
    }

    load();
    int selected = 1;
    while (true) {
        clear();
        std::cout << "------------------------------------\n";
        std::cout << T_TITLE << "SUPER GAMBLING " << T_LOSS << "SAVE EDITOR" << T_RESET << "\n";
        std::cout << "User: " << T_USER << data.playerName << T_RESET << " | Points: " << T_PRICE << "$" << data.totalPoints << T_RESET << "\n";
        std::cout << "------------------------------------\n";
        
        std::vector<std::string> options = {
            "Change Name", 
            "Set Points", 
            "Set Wins", 
            "Set Losses",
            "Set Best Streak", 
            "Manage Inventory (Items)", 
            "Unlock All Badges", 
            "Save & Exit", 
            "Exit without Saving"
        };

        for (int i = 0; i < options.size(); i++) {
            if (selected == i + 1) std::cout << T_WIN << "[*] " << T_RESET;
            else std::cout << "[-] ";
            std::cout << options[i] << "\n";
        }

        int input = _getch();
        if (input == 224 || input == 27) {
            int arrow = _getch();
            if (input == 27 && arrow == 91) arrow = _getch();
            if (arrow == 72 || arrow == 'A') selected = (selected > 1) ? selected - 1 : options.size();
            else if (arrow == 80 || arrow == 'B') selected = (selected < options.size()) ? selected + 1 : 1;
        } else if (input == 13 || input == 10) {
            if (selected == 1) {
                clear(); std::cout << "Enter New Name: "; 
                std::getline(std::cin >> std::ws, data.playerName);
            }
            else if (selected == 2) editInt("Total Points", data.totalPoints);
            else if (selected == 3) editInt("Total Wins", data.totalWins);
            else if (selected == 4) editInt("Total Losses", data.totalLoss);
            else if (selected == 5) editInt("Best Streak", data.bestStreak);
            else if (selected == 6) itemManager();
            else if (selected == 7) {
                data.b1=data.b2=data.b3=data.b4=data.b5=data.b6=data.b7=data.b8=data.b9=data.b10=data.b11=data.b12=data.b13=data.b14=data.b15=1;
                clear(); std::cout << T_WIN << "All badges unlocked! Press any key to continue." << T_RESET << "\n"; _getch();
            }
            else if (selected == 8) { save(); break; }
            else if (selected == 9) break;
        }
    }
    return 0;
}
