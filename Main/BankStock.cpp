#include "BankStock.h"
#include <random>
#include <chrono>
#include <limits>
#include <iostream>

BankStock::BankStock(const std::string& name, double initialPrice)
    : Stock(name, initialPrice) {
}

void BankStock::updatePrice() {
    std::lock_guard<std::mutex> lock(stockMutex);

    static std::mt19937 gen(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()
        ));
    std::uniform_real_distribution<> dist(-0.04, 0.04);

    double actual_change_percentage = dist(gen);
    double final_change_value;

    if (actual_change_percentage >= 0.038) {
        final_change_value = price * 0.08;
        std::cout << "\n==================== BANKING - " << name << " ====================\n";
        std::cout << "Large investment package announced! Prices jumped by 8%!\n";
        std::cout << "=======================================================\n";
    }
    else if (actual_change_percentage <= -0.038) {
        final_change_value = price * -0.07;
        std::cout << "\n==================== BANKING - " << name << " ====================\n";
        std::cout << "Financial sector crisis! Prices FELL BY 7%!\n";
        std::cout << "=======================================================\n";
    }
    else {
        final_change_value = price * actual_change_percentage;
    }

    price += final_change_value;

    if (price < 0.1) {
        price = 0.1;
    }

    priceHistory.push_back(price);
}