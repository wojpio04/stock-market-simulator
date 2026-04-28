#include "Portfolio.h"
#include <iostream>
#include <iomanip>
#include <algorithm> 

void Portfolio::addStock(const std::string& stockName, int quantity, double buyPrice) {
    if (ownedStocks.count(stockName)) {
        OwnedStockDetails& details = ownedStocks[stockName];
        double totalCostOld = details.quantity * details.averageBuyPrice;
        double totalCostNew = totalCostOld + (quantity * buyPrice);
        details.quantity += quantity;
        details.averageBuyPrice = totalCostNew / details.quantity;
    }
    else {
        ownedStocks[stockName] = OwnedStockDetails(quantity, buyPrice);
    }
}

bool Portfolio::removeStock(const std::string& stockName, int quantity) {
    if (ownedStocks.count(stockName)) {
        if (ownedStocks[stockName].quantity >= quantity) {
            ownedStocks[stockName].quantity -= quantity;
            if (ownedStocks[stockName].quantity == 0) {
                ownedStocks.erase(stockName);
            }
            return true;
        }
    }
    return false;
}

int Portfolio::getStockQuantity(const std::string& stockName) const {
    auto it = ownedStocks.find(stockName);
    if (it != ownedStocks.end()) {
        return it->second.quantity;
    }
    return 0;
}

bool Portfolio::isEmpty() const {
    return ownedStocks.empty();
}

std::string Portfolio::getStockNameByIndex(int index) const {
    if (index <= 0 || index > ownedStocks.size()) {
        return ""; 
    }
    auto it = ownedStocks.begin();
    std::advance(it, index - 1);
    return it->first;
}