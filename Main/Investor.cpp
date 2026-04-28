#include "Investor.h"
#include "Stock.h"
#include "MarketSimulator.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

Investor::Investor(const std::string& username_in, double initialFunds)
    : username(username_in), funds(initialFunds) {
    if (!fs::exists("saves")) {
        fs::create_directory("saves");
    }
}

Investor::Investor(const std::string& username_in)
    : username(username_in), funds(0.0) {
    if (!fs::exists("saves")) {
        fs::create_directory("saves");
    }
}

void Investor::displayFunds() const {
    std::cout << "Your funds: " << std::fixed << std::setprecision(2) << funds << " PLN\n";
}

void Investor::displayPortfolio(MarketSimulator& market) const {
    std::cout << "\n=== Your Portfolio ===\n";
    if (portfolio.isEmpty()) {
        std::cout << "Portfolio is empty.\n";
        return;
    }
    int i = 1;
    for (const auto& pair : portfolio.getOwnedStocks()) {
        std::string stockName = pair.first;
        int quantity = pair.second.quantity;
        double averageBuyPrice = pair.second.averageBuyPrice;

        std::shared_ptr<Stock> marketStock = market.getStockByName(stockName);
        double currentMarketPrice = marketStock ? marketStock->getPrice() : 0.0; 

        double totalBuyValue = quantity * averageBuyPrice;
        double currentMarketValue = quantity * currentMarketPrice;
        double profitLoss = currentMarketValue - totalBuyValue;

        std::cout << i++ << ". " << stockName
            << ": " << quantity << " shares "
            << "(Avg. Buy: " << std::fixed << std::setprecision(2) << averageBuyPrice << " PLN, "
            << "Current Market: " << std::fixed << std::setprecision(2) << currentMarketPrice << " PLN) "
            << "Profit/Loss: " << std::fixed << std::setprecision(2) << profitLoss << " PLN "
            << (profitLoss >= 0 ? "(+" : "(") << std::fixed << std::setprecision(2) << (totalBuyValue != 0 ? (profitLoss / totalBuyValue) * 100 : 0.0) << "%)\n"; 
    }
}


void Investor::displayHistory() const {
    history.displayTransactions();
}

bool Investor::buyStock(const std::shared_ptr<Stock>& stock, int quantity, MarketSimulator& market) {
    if (!stock || quantity <= 0) {
        std::cout << "Invalid stock or quantity.\n";
        return false;
    }

    double currentPrice = stock->getPrice();
    double totalCost = currentPrice * quantity;

    if (funds >= totalCost) {
        funds -= totalCost;
        portfolio.addStock(stock->getName(), quantity, currentPrice);
        history.addTransaction("BUY", stock->getName(), quantity, currentPrice);
        std::cout << "Successfully bought " << quantity << " shares of " << stock->getName() << ".\n";
        return true;
    }
    else {
        std::cout << "Insufficient funds to buy " << quantity << " shares of " << stock->getName() << ".\n";
        return false;
    }
}

bool Investor::sellStock(const std::shared_ptr<Stock>& stock, int quantity, MarketSimulator& market) {
    if (!stock || quantity <= 0) {
        std::cout << "Invalid stock or quantity.\n";
        return false;
    }

    if (portfolio.removeStock(stock->getName(), quantity)) {
        double currentPrice = stock->getPrice();
        double totalRevenue = currentPrice * quantity;
        funds += totalRevenue;
        history.addTransaction("SELL", stock->getName(), quantity, currentPrice);
        std::cout << "Successfully sold " << quantity << " shares of " << stock->getName() << ".\n";
        return true;
    }
    else {
        std::cout << "You don't own enough shares of " << stock->getName() << " to sell " << quantity << ".\n";
        return false;
    }
}

Portfolio& Investor::getPortfolio() {
    return portfolio;
}

const Portfolio& Investor::getPortfolio() const {
    return portfolio;
}

double Investor::getFunds() const {
    return funds;
}

void Investor::setFunds(double newFunds) {
    funds = newFunds;
}

void Investor::saveState() const {
    std::string filename = "saves/" + username + ".txt";
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to save game state to " << filename << "\n";
        return;
    }

    outFile << "USERNAME:" << username << "\n";
    outFile << "FUNDS:" << funds << "\n";

    outFile << "PORTFOLIO:\n";
    for (const auto& pair : portfolio.getOwnedStocks()) {
        outFile << pair.first << ":" << pair.second.quantity << ":" << pair.second.averageBuyPrice << "\n";
    }
    outFile << "END_PORTFOLIO\n";

    outFile << "TRANSACTIONS:\n";
    for (const auto& t : history.getTransactions()) {
        outFile << t.type << ";" << t.stockName << ";" << t.quantity << ";" << t.price << ";"
            << std::chrono::duration_cast<std::chrono::seconds>(t.timestamp.time_since_epoch()).count() << "\n";
    }
    outFile << "END_TRANSACTIONS\n";

    outFile.close();
    std::cout << "Game state saved to " << filename << "\n";
}

bool Investor::loadState() {
    std::string filename = "saves/" + username + ".txt";
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false;
    }

    std::string line;

    if (std::getline(inFile, line) && line.rfind("USERNAME:", 0) == 0) {
        // username = line.substr(9); 
    }
    else {
        std::cerr << "Error loading USERNAME from " << filename << "\n";
        inFile.close();
        return false;
    }

    if (std::getline(inFile, line) && line.rfind("FUNDS:", 0) == 0) {
        try {
            funds = std::stod(line.substr(6));
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error parsing funds in " << filename << ": " << e.what() << "\n";
            inFile.close();
            return false;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Funds value out of range in " << filename << ": " << e.what() << "\n";
            inFile.close();
            return false;
        }
    }
    else {
        std::cerr << "Error loading FUNDS from " << filename << "\n";
        inFile.close();
        return false;
    }

    portfolio = Portfolio(); 

    if (std::getline(inFile, line) && line == "PORTFOLIO:") {
        while (std::getline(inFile, line) && line != "END_PORTFOLIO") {
            size_t firstColonPos = line.find(':');
            size_t secondColonPos = line.find(':', firstColonPos + 1);
            if (firstColonPos != std::string::npos && secondColonPos != std::string::npos) {
                try {
                    std::string stockName = line.substr(0, firstColonPos);
                    int quantity = std::stoi(line.substr(firstColonPos + 1, secondColonPos - (firstColonPos + 1)));
                    double avgBuyPrice = std::stod(line.substr(secondColonPos + 1));
                    if (!stockName.empty() && quantity > 0) {
                        portfolio.addStock(stockName, quantity, avgBuyPrice); 
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error parsing portfolio stock/quantity/price in " << filename << ": " << e.what() << "\n";
                    inFile.close();
                    return false;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Portfolio data out of range in " << filename << ": " << e.what() << "\n";
                    inFile.close();
                    return false;
                }
            }
        }
    }
    else {
        std::cerr << "Error loading PORTFOLIO from " << filename << "\n";
        inFile.close();
        return false;
    }

    history = TransactionHistory(); 

    if (std::getline(inFile, line) && line == "TRANSACTIONS:") {
        while (std::getline(inFile, line) && line != "END_TRANSACTIONS") {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while (std::getline(ss, segment, ';')) {
                parts.push_back(segment);
            }

            if (parts.size() == 5) {
                try {
                    std::string type = parts[0];
                    std::string stockName = parts[1];
                    int quantity = std::stoi(parts[2]);
                    double price = std::stod(parts[3]);
                    long long timestamp_sec = std::stoll(parts[4]);

                    std::chrono::system_clock::time_point ts = std::chrono::system_clock::from_time_t(timestamp_sec);
                    history.addTransaction(Transaction(type, stockName, quantity, price, ts));
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error parsing transaction data in " << filename << ": " << e.what() << "\n";
                    inFile.close();
                    return false;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Transaction data out of range in " << filename << ": " << e.what() << "\n";
                    inFile.close();
                    return false;
                }
            }
            else {
                std::cerr << "Warning: Malformed transaction line in " << filename << ": " << line << "\n";
            }
        }
    }
    else {
        std::cerr << "Error loading TRANSACTIONS from " << filename << "\n";
        inFile.close();
        return false;
    }

    inFile.close();
    std::cout << "Game state loaded from " << filename << "\n";
    return true;
}