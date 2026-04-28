#include "Admin.h"
#include "TechStock.h"
#include "EnergyStock.h"
#include "BankStock.h"
#include "FunkPom.h"
#include <iostream>
#include <limits>   
#include <algorithm> 

void Admin::addStock(std::vector<std::shared_ptr<Stock>>& stocks) {
    std::string name;
    double price;
    int type;

    std::cout << "\nEnter company name: ";
    std::getline(std::cin, name); 

    std::cout << "Enter initial price: ";
    while (!(std::cin >> price) || price <= 0) {
        std::cout << "Invalid price. Please enter a positive number: ";
        std::cin.clear();
        clearInputBuffer();
    }

    std::cout << "Select sector:\n1. Technology\n2. Energy\n3. Banking\nYour choice: ";
    while (!(std::cin >> type) || type < 1 || type > 3) {
        std::cout << "Invalid choice. Please enter a number between 1 and 3: ";
        std::cin.clear();
        clearInputBuffer();
    }
    clearInputBuffer(); 

    std::shared_ptr<Stock> newStock;
    switch (type) {
    case 1:
        newStock = std::make_shared<TechStock>(name, price);
        break;
    case 2:
        newStock = std::make_shared<EnergyStock>(name, price);
        break;
    case 3:
        newStock = std::make_shared<BankStock>(name, price);
        break;
    default:
        std::cout << "Invalid sector choice.\n";
        return;
    }

    stocks.push_back(newStock);
    std::cout << "Added company: " << name << " with price " << price << " PLN.\n";
}

void Admin::removeStock(std::vector<std::shared_ptr<Stock>>& stocks) {
    std::string name;
    std::cout << "\nEnter company name to remove: ";
    std::getline(std::cin, name); 

    auto it = std::remove_if(stocks.begin(), stocks.end(), [&](const auto& stock) {
        return stock->getName() == name;
        });

    if (it != stocks.end()) {
        stocks.erase(it, stocks.end());
        std::cout << "Removed company: " << name << ".\n";
    }
    else {
        std::cout << "Company not found: " << name << ".\n";
    }
}

void Admin::modifyPrice(std::vector<std::shared_ptr<Stock>>& stocks) {
    std::string name;
    double newPrice;
    std::cout << "\nEnter company name to change price: ";
    std::getline(std::cin, name); 

    for (auto& stock : stocks) {
        if (stock->getName() == name) {
            std::cout << "Current price: " << stock->getPrice() << " PLN\n";
            std::cout << "Enter new price: ";
            while (!(std::cin >> newPrice) || newPrice <= 0) {
                std::cout << "Invalid price. Please enter a positive number: ";
                std::cin.clear();
                clearInputBuffer();
            }
            clearInputBuffer();

            stock->setPrice(newPrice);
            std::cout << "Changed price of " << name << " to " << newPrice << " PLN.\n";
            return;
        }
    }

    std::cout << "Company not found: " << name << ".\n";
}

void Admin::listStocks(const std::vector<std::shared_ptr<Stock>>& stocks) const {
    std::cout << "\n=== List of Companies ===\n";
    if (stocks.empty()) {
        std::cout << "No companies registered.\n";
        return;
    }

    for (const auto& stock : stocks) {
        std::cout << stock->getName() << ": " << stock->getPrice() << " PLN\n";
    }
}