#define _CRT_SECURE_NO_WARNINGS // Wy³¹cza ostrzezenie o std::localtime 

#include "TransactionHistory.h"
#include <iostream>
#include <iomanip>
#include <ctime> 

void TransactionHistory::addTransaction(const std::string& type, const std::string& stockName, int quantity, double price) {
    transactions.push_back(Transaction(type, stockName, quantity, price));
}

void TransactionHistory::addTransaction(const Transaction& t) {
    transactions.push_back(t);
}

void TransactionHistory::displayTransactions() const {
    std::cout << "\n=== Transaction History ===\n";
    if (transactions.empty()) {
        std::cout << "No transactions yet.\n";
        return;
    }
    for (const auto& t : transactions) {
        std::cout << t.type << " " << t.quantity << " shares of "
            << t.stockName << " at " << std::fixed << std::setprecision(2)
            << t.price << " PLN ";

        std::time_t time_c = std::chrono::system_clock::to_time_t(t.timestamp);
        std::cout << "(" << std::put_time(std::localtime(&time_c), "%Y-%m-%d %H:%M:%S") << ")\n";
    }
}