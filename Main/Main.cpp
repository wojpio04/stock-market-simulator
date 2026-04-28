#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <filesystem> 
#include <regex>      
#include <future>     

namespace fs = std::filesystem;

#include "FunkPom.h" 
#include "MarketSimulator.h"
#include "Admin.h"
#include "Investor.h"
#include "Stock.h"
#include "TechStock.h"
#include "BankStock.h"
#include "EnergyStock.h"
#include "Portfolio.h"
#include "TransactionHistory.h"

// Menu Administratora
void adminMenu(Admin& admin, MarketSimulator& market) {
    int choice;
    do {
        clearScreen(); 
        std::cout << "\n==============================\n";
        std::cout << "Administrator\n";
        std::cout << "==============================\n";
        std::cout << "1. Add Company\n";
        std::cout << "2. Remove Company\n";
        std::cout << "3. Change Stock Price\n";
        std::cout << "4. Display All Companies\n";
        std::cout << "5. Back\n";
        std::cout << "Your choice: ";

        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            clearInputBuffer();
        }
        clearInputBuffer(); 

        switch (choice) {
        case 1:
            admin.addStock(market.getStocksRef());
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
        case 2:
            admin.removeStock(market.getStocksRef());
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
        case 3:
            admin.modifyPrice(market.getStocksRef());
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
        case 4:
            market.displayStocks();
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
        case 5:
            std::cout << "Returning to main menu.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::cout << "Press Enter to continue..."; std::cin.get();
        }
    } while (choice != 5);
}

// Menu Uzytkownika
void userMenu(Investor& investor, MarketSimulator& market) {
    int choice;
    int stockNumber;
    int quantity;
    std::shared_ptr<Stock> selectedStock;
    std::string stockNameFromPortfolio;

    do {
        clearScreen(); 
        std::cout << "\n==============================\n";
        std::cout << "User: " << investor.getUsername() << "\n";
        std::cout << "==============================\n";
        investor.displayFunds();
        std::cout << "1. Buy Stocks\n";
        std::cout << "2. Sell Stocks\n";
        std::cout << "3. Display Portfolio\n";
        std::cout << "4. Transaction History\n";
        std::cout << "5. Display Current Stock Prices\n";
        std::cout << "6. Back to User Selection\n";
        std::cout << "Your choice: ";

        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            clearInputBuffer();
        }
        clearInputBuffer();

        switch (choice) {
        case 1: // KUPNO
            market.displayStocks();
            std::cout << "Enter the number of the company whose shares you want to buy (0 to cancel): ";
            while (!(std::cin >> stockNumber) || stockNumber < 0 || stockNumber > market.getStocksRef().size()) {
                std::cout << "Invalid input. Please enter a number between 0 and " << market.getStocksRef().size() << ": ";
                std::cin.clear();
                clearInputBuffer();
            }
            clearInputBuffer();

            if (stockNumber == 0) {
                std::cout << "Stock purchase cancelled.\n";
            }
            else {
                std::cout << "Enter quantity: ";
                while (!(std::cin >> quantity) || quantity <= 0) {
                    std::cout << "Invalid quantity. Please enter a positive number: ";
                    std::cin.clear();
                    clearInputBuffer();
                }
                clearInputBuffer();

                selectedStock = market.getStockByIndex(stockNumber);
                if (selectedStock) {
                    investor.buyStock(selectedStock, quantity, market);
                }
                else {
                    std::cout << "Invalid stock number or stock not found. This should not happen with proper validation.\n";
                }
            }
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
		case 2: // SPRZEDA¯
            investor.displayPortfolio(market);
            if (investor.getPortfolio().isEmpty()) {
                std::cout << "You don't own any stocks to sell.\n";
            }
            else {
                size_t portfolioSize = investor.getPortfolio().getUniqueStockCount();

                std::cout << "Enter the number of the company whose shares you want to sell from your portfolio (0 to cancel): ";
                while (!(std::cin >> stockNumber) || stockNumber < 0 || stockNumber > portfolioSize) {
                    std::cout << "Invalid input. Please enter a number between 0 and " << portfolioSize << ": ";
                    std::cin.clear();
                    clearInputBuffer();
                }
                clearInputBuffer();

                if (stockNumber == 0) {
                    std::cout << "Stock sale cancelled.\n";
                }
                else {
                    std::cout << "Enter quantity: ";
                    while (!(std::cin >> quantity) || quantity <= 0) {
                        std::cout << "Invalid quantity. Please enter a number: ";
                        std::cin.clear();
                        clearInputBuffer();
                    }
                    clearInputBuffer();

                    stockNameFromPortfolio = investor.getPortfolio().getStockNameByIndex(stockNumber);

                    if (!stockNameFromPortfolio.empty()) {
                        selectedStock = market.getStockByName(stockNameFromPortfolio);
                        if (selectedStock) {
                            investor.sellStock(selectedStock, quantity, market);
                        }
                        else {
                            std::cout << "Error: Stock found in portfolio but not on the market.\n";
                        }
                    }
                    else {
                        std::cout << "Invalid stock number in your portfolio.\n";
                    }
                }
            }
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
        case 3: // POKAZ PORTFOLIO
            investor.displayPortfolio(market);
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
		case 4: // HISTORIA TRANSAKCJI
            investor.displayHistory();
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
		case 5: // AKTUALNE CENY AKCJI
            market.displayStocks();
            std::cout << "Press Enter to continue..."; std::cin.get();
            break;
		case 6: // COFNIÊCIE DO MENU 
        {
            std::cout << "Returning to user selection menu.\n";
            std::cout << "Saving game state in background...\n";
            std::future<void> save_future = std::async(std::launch::async, [&]() {
                investor.saveState();
                });
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::cout << "Press Enter to continue..."; std::cin.get();
        }
    } while (choice != 6);
}

std::vector<std::string> getSavedUsernames() {
    std::vector<std::string> usernames;
    const std::string savesDir = "saves/";

    if (!fs::exists(savesDir)) {
        fs::create_directory(savesDir);
    }

    for (const auto& entry : fs::directory_iterator(savesDir)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".txt") {
                usernames.push_back(filename.substr(0, filename.length() - 4));
            }
        }
    }
    std::sort(usernames.begin(), usernames.end());
    return usernames;
}

void deleteUser() {
    clearScreen();
    std::cout << "\n==============================\n";
    std::cout << "Delete User\n";
    std::cout << "==============================\n";

    std::vector<std::string> savedUsers = getSavedUsernames();
    if (savedUsers.empty()) {
        std::cout << "No saved users to delete.\n";
        std::cout << "Press Enter to continue..."; std::cin.get();
        return;
    }

    std::cout << "\n=== Saved Users ===\n";
    for (size_t i = 0; i < savedUsers.size(); ++i) {
        std::cout << (i + 1) << ". " << savedUsers[i] << "\n";
    }
    std::cout << "Enter the number of the user to delete (or 0 to cancel): ";

    int userIdx;
    while (!(std::cin >> userIdx) || userIdx < 0 || userIdx > savedUsers.size()) {
        std::cout << "Invalid input. Please enter a valid number from the list (or 0 to cancel): ";
        std::cin.clear();
        clearInputBuffer();
    }
    clearInputBuffer();

    if (userIdx > 0 && userIdx <= savedUsers.size()) {
        std::string usernameToDelete = savedUsers[userIdx - 1];
        std::string filenameToDelete = "saves/" + usernameToDelete + ".txt";

        std::cout << "Are you sure you want to delete user '" << usernameToDelete << "'? (yes/no): ";
        std::string confirmation;
        std::getline(std::cin, confirmation);

        if (toLower(confirmation) == "yes") {
            if (fs::remove(filenameToDelete)) {
                std::cout << "User '" << usernameToDelete << "' deleted successfully.\n";
            }
            else {
                std::cout << "Error: Could not delete user '" << usernameToDelete << "'. File might be in use or protected.\n";
            }
        }
        else {
            std::cout << "User deletion cancelled.\n";
        }
    }
    else if (userIdx != 0) {
        std::cout << "Invalid choice.\n";
    }
    else {
        std::cout << "User deletion cancelled.\n";
    }
    std::cout << "Press Enter to continue..."; std::cin.get();
}

int main() {
    MarketSimulator market;
    Admin admin;

    market.addStock(std::make_shared<TechStock>("TechCorp", 100.0));
    market.addStock(std::make_shared<TechStock>("InnovateX", 120.5));
    market.addStock(std::make_shared<TechStock>("CyberNet", 85.25));

    market.addStock(std::make_shared<BankStock>("GlobalBank", 50.0));
    market.addStock(std::make_shared<BankStock>("FinancierInc", 62.80));
    market.addStock(std::make_shared<BankStock>("SecureFunds", 45.10));

    market.addStock(std::make_shared<EnergyStock>("GreenEnergy", 75.0));
    market.addStock(std::make_shared<EnergyStock>("PowerGrid", 90.70));
    market.addStock(std::make_shared<EnergyStock>("SolarFuture", 68.30));

    market.start(); 

    int mainChoice;
    do {
        clearScreen();
        std::cout << "\n=====================================\n";
        std::cout << "Welcome to Stock Market Simulator!\n";
        std::cout << "=====================================\n";
        std::cout << "Select mode:\n";
        std::cout << "1. Administrator\n";
        std::cout << "2. User\n";
        std::cout << "3. Exit\n";
        std::cout << "Your choice: ";

        while (!(std::cin >> mainChoice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            clearInputBuffer();
        }
        clearInputBuffer();

        switch (mainChoice) {
        case 1:
            adminMenu(admin, market);
            break;
        case 2: {
            int userModeChoice;
            std::unique_ptr<Investor> currentInvestor;
            std::regex username_pattern("^[a-zA-Z0-9_]{3,16}$"); 

            do {
                clearScreen();
                std::cout << "\n==============================\n";
                std::cout << "User Mode\n";
                std::cout << "==============================\n";
                std::cout << "1. New Game\n";
                std::cout << "2. Load Game\n";
                std::cout << "3. Delete User\n";
                std::cout << "4. Back to Main Menu\n";
                std::cout << "Your choice: ";

                while (!(std::cin >> userModeChoice)) {
                    std::cout << "Invalid input. Please enter a number: ";
                    std::cin.clear();
                    clearInputBuffer();
                }
                clearInputBuffer();

                switch (userModeChoice) {
                case 1: { // Nowa Gra
                    std::string newUsername;
                    bool usernameExists;
                    do {
                        std::cout << "Enter a new username: ";
                        std::getline(std::cin, newUsername);
                        usernameExists = false;
                        for (const auto& existingUser : getSavedUsernames()) {
                            if (toLower(existingUser) == toLower(newUsername)) {
                                usernameExists = true;
                                std::cout << "Username '" << newUsername << "' already exists. Choose another name.\n";
                                break;
                            }
                        }
                        if (newUsername.empty()) {
                            usernameExists = true;
                            std::cout << "Username cannot be empty.\n";
                        }
                        if (!usernameExists && !std::regex_match(newUsername, username_pattern)) {
                            usernameExists = true; 
                            std::cout << "Invalid username. It must be 3-16 characters long and contain only letters, numbers, or underscores.\n";
                        }

                    } while (usernameExists);

                    currentInvestor = std::make_unique<Investor>(newUsername, 10000.0);
                    std::cout << "Starting new game for user: " << newUsername << "\n";
                    std::cout << "Press Enter to continue..."; std::cin.get();
                    userMenu(*currentInvestor, market);
                    currentInvestor.reset(); 
                    break;
                }
                case 2: { // Wczytaj Grê
                    std::vector<std::string> savedUsers = getSavedUsernames();
                    if (savedUsers.empty()) {
                        std::cout << "No saved games found. Please start a new game first.\n";
                        std::cout << "Press Enter to continue..."; std::cin.get();
                        break;
                    }

                    std::cout << "\n=== Saved Users ===\n";
                    for (size_t i = 0; i < savedUsers.size(); ++i) {
                        std::cout << (i + 1) << ". " << savedUsers[i] << "\n";
                    }
                    std::cout << "Enter the number of the user to load (or 0 to cancel): ";
                    int userIdx;
                    while (!(std::cin >> userIdx) || userIdx < 0 || userIdx > savedUsers.size()) {
                        std::cout << "Invalid input. Please enter a valid number from the list (or 0 to cancel): ";
                        std::cin.clear();
                        clearInputBuffer();
                    }
                    clearInputBuffer();

                    if (userIdx > 0 && userIdx <= savedUsers.size()) {
                        std::string selectedUsername = savedUsers[userIdx - 1];
                        currentInvestor = std::make_unique<Investor>(selectedUsername);
                        if (currentInvestor->loadState()) {
                            std::cout << "Game loaded successfully for " << selectedUsername << ".\n";
                            std::cout << "Press Enter to continue..."; std::cin.get();
                            userMenu(*currentInvestor, market);
                        }
                        else {
                            std::cout << "Failed to load game for " << selectedUsername << ". File might be corrupted or inaccessible.\n";
                            std::cout << "Press Enter to continue..."; std::cin.get();
                        }
                        currentInvestor.reset(); 
                    }
                    else if (userIdx != 0) { 
                        std::cout << "Invalid choice.\n";
                        std::cout << "Press Enter to continue..."; std::cin.get();
                    }
                    else { 
                        std::cout << "User selection cancelled.\n";
                        std::cout << "Press Enter to continue..."; std::cin.get();
                    }
                    break;
                }
				case 3: { // Usuwanie U¿ytkownika
                    deleteUser();
                    break;
                }
				case 4: // Powrót do Menu G³ównego
                    std::cout << "Returning to main menu.\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    std::cout << "Press Enter to continue..."; std::cin.get();
                    break;
                }
            } while (userModeChoice != 4);
            break;
        }
        case 3:
            std::cout << "Thank you for using the simulator!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    } while (mainChoice != 3);

    market.stop(); 

    return 0;
}