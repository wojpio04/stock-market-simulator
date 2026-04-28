#include "TechStock.h"
#include <random>
#include <chrono>
#include <limits>
#include <iostream>

TechStock::TechStock(const std::string& name, double initialPrice)
    : Stock(name, initialPrice) {
}

void TechStock::updatePrice() {
    std::lock_guard<std::mutex> lock(stockMutex);

    static std::mt19937 gen(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()
        ));
    std::uniform_real_distribution<> dist(-0.10, 0.10);

    double actual_change_percentage = dist(gen);
    double final_change_value;

    if (actual_change_percentage >= 0.09) {
        final_change_value = price * 0.15;
        std::cout << "\n==================== TECHNOLOGY - " << name << " ====================\n";
        std::cout << "WOW! Technology boom! Prices JUMPED BY 15%!\n";
        std::cout << "=======================================================\n";
    }
    else if (actual_change_percentage <= -0.09) {
        final_change_value = price * -0.12;
        std::cout << "\n==================== TECHNOLOGY - " << name << " ====================\n";
        std::cout << "Tech sector crisis! Prices FELL BY 12%!\n";
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