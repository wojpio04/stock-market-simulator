#include "Stock.h"
#include <iostream>

Stock::Stock(const std::string& name, double initialPrice)
    : name(name), price(initialPrice) {
    priceHistory.push_back(initialPrice);
}

std::string Stock::getName() const {
    std::lock_guard<std::mutex> lock(stockMutex); 
    return name;
}

double Stock::getPrice() const {
    std::lock_guard<std::mutex> lock(stockMutex); 
    return price;
}

const std::vector<double>& Stock::getPriceHistory() const {
    std::lock_guard<std::mutex> lock(stockMutex); 
    return priceHistory;
}

void Stock::setPrice(double newPrice) {
    std::lock_guard<std::mutex> lock(stockMutex); 
    price = newPrice;
    priceHistory.push_back(newPrice);
}
