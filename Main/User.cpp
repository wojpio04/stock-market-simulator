#include "User.h"
#include <iostream>
#include <iomanip>

User::User(const std::string& name, double initialFunds)
    : name(name), funds(initialFunds) {
}

std::string User::getName() const {
    return name;
}

double User::getFunds() const {
    return funds;
}

void User::displayFunds() const {
    std::cout << "\nAvailable funds: " << std::fixed << std::setprecision(2)
        << funds << " PLN\n";
}

void User::addFunds(double amount) {
    funds += amount;
}

void User::removeFunds(double amount) {
    funds -= amount;
}