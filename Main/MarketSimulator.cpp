#include <chrono>
#include <iostream>
#include <algorithm> 
#include <iomanip>   
#include <vector>

#include "TechStock.h"
#include "BankStock.h"
#include "EnergyStock.h"
#include "MarketSimulator.h"
#include "Stock.h" 

MarketSimulator::MarketSimulator() : running(false) {}

MarketSimulator::~MarketSimulator() {
    stop();
}

void MarketSimulator::simulate() {
    while (running) {
        std::unique_lock<std::mutex> lock(marketMutex); 
        for (auto& stock : stocks) {
            stock->updatePrice();
        }
        std::cout << "  (Stocks updated)  ";

        cv.wait_for(lock, std::chrono::seconds(20), [&] { return !running; });
    }
    std::cout << "Market simulation thread stopped.\n";
}

void MarketSimulator::start() {
    if (!running) {
        running = true;
        simulationThread = std::thread(&MarketSimulator::simulate, this);
    }
}

void MarketSimulator::stop() {
    if (running) {
        running = false;
        cv.notify_one();
        if (simulationThread.joinable()) {
            simulationThread.join();
        }
    }
}

void MarketSimulator::addStock(const std::shared_ptr<Stock>& stock) {
    std::lock_guard<std::mutex> lock(marketMutex);
    stocks.push_back(stock);
}

void MarketSimulator::removeStock(const std::string& name) {
    std::lock_guard<std::mutex> lock(marketMutex);
    stocks.erase(
        std::remove_if(stocks.begin(), stocks.end(),
            [&name](const std::shared_ptr<Stock>& s) { return s->getName() == name; }),
        stocks.end()
    );
}

std::shared_ptr<Stock> MarketSimulator::getStockByName(const std::string& name) {
    std::lock_guard<std::mutex> lock(marketMutex);
    for (auto& stock : stocks) {
        if (stock->getName() == name) return stock;
    }
    return nullptr;
}

std::shared_ptr<Stock> MarketSimulator::getStockByIndex(int userIndex) {
    std::lock_guard<std::mutex> lock(marketMutex);
    size_t actualIndex = static_cast<size_t>(userIndex - 1); 

    if (userIndex > 0 && actualIndex < stocks.size()) { 
        return stocks[actualIndex];
    }
    return nullptr;
}


void MarketSimulator::displayStocks() const {
    std::lock_guard<std::mutex> lock(marketMutex);
    std::cout << "\n=== Current Stock Quotes ===\n";
    if (stocks.empty()) {
        std::cout << "No companies registered.\n";
        return;
    }

    std::vector<std::shared_ptr<Stock>> techStocks;
    std::vector<std::shared_ptr<Stock>> bankStocks;
    std::vector<std::shared_ptr<Stock>> energyStocks;

    for (const auto& stock : stocks) {
        if (dynamic_cast<TechStock*>(stock.get())) {
            techStocks.push_back(stock);
        }
        else if (dynamic_cast<BankStock*>(stock.get())) {
            bankStocks.push_back(stock);
        }
        else if (dynamic_cast<EnergyStock*>(stock.get())) {
            energyStocks.push_back(stock);
        }
    }

    auto displayStockWithHistory = [&](const std::shared_ptr<Stock>& stock) {
        auto it = std::find(stocks.begin(), stocks.end(), stock);
        size_t index = std::distance(stocks.begin(), it);

        std::cout << (index + 1) << ". " << stock->getName() << " : "
            << std::fixed << std::setprecision(2) << stock->getPrice() << " PLN";

        const auto& history = stock->getPriceHistory();

        if (history.size() > 1) { 
            std::cout << " |Previous Prices| ";

            const size_t max_history_display = 10;
            size_t last_hist_index = history.size() - 2;

            size_t start_index_to_display = std::max(static_cast<size_t>(0),
                last_hist_index > (max_history_display - 1) ?
                last_hist_index - (max_history_display - 1) : 0);

            size_t actual_start_index;
            if (history.size() <= max_history_display + 1) { 
                actual_start_index = 0;
            }
            else {
                actual_start_index = history.size() - (max_history_display + 1);
            }

            std::cout << std::fixed << std::setprecision(2) << history[actual_start_index];

            for (size_t i = actual_start_index + 1; i <= last_hist_index; ++i) {

                double prev_price_in_sequence = history[i - 1];
                double current_price_in_sequence = history[i];

                if (current_price_in_sequence > prev_price_in_sequence) {
                    std::cout << " /> "; 
                }
                else if (current_price_in_sequence < prev_price_in_sequence) {
                    std::cout << " \\> "; 
                }
                else {
                    std::cout << " = "; 
                }
                std::cout << std::fixed << std::setprecision(2) << current_price_in_sequence;
            }
        }
        std::cout << "\n";
        };

    if (!techStocks.empty()) {
        std::cout << "\n========== Technology Stocks ==========\n";
        for (const auto& stock : techStocks) {
            displayStockWithHistory(stock);
        }
    }

    if (!bankStocks.empty()) {
        std::cout << "\n============== Bank Stocks ==============\n";
        for (const auto& stock : bankStocks) {
            displayStockWithHistory(stock);
        }
    }

    if (!energyStocks.empty()) {
        std::cout << "\n============ Energy Stocks ============\n";
        for (const auto& stock : energyStocks) {
            displayStockWithHistory(stock);
        }
    }
}


std::vector<std::shared_ptr<Stock>>& MarketSimulator::getStocksRef() {
    return stocks;
}