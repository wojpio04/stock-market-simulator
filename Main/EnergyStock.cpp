#include "EnergyStock.h"
#include <random>
#include <chrono>
#include <limits>
#include <iostream>

EnergyStock::EnergyStock(const std::string& name, double initialPrice)
    : Stock(name, initialPrice) {
}

void EnergyStock::updatePrice() {
    std::lock_guard<std::mutex> lock(stockMutex);

    static std::mt19937 gen(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()
        ));
    std::uniform_real_distribution<> dist(-0.07, 0.07);

    double actual_change_percentage = dist(gen);
    double final_change_value;

    if (actual_change_percentage >= 0.066) {
        final_change_value = price * 0.10;
        std::cout << "\n==================== ENERGY - " << name << " ====================\n";
        std::cout << "New resource deposits discovered! Stock jumped by 10%!\n";
        std::cout << "=======================================================\n";
    }
    else if (actual_change_percentage <= -0.066) {
        final_change_value = price * -0.09;
        std::cout << "\n==================== ENERGY - " << name << " ====================\n";
        std::cout << "Major power plant malfunction! Stock FELL BY 9%!\n";
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