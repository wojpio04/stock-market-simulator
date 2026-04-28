#ifndef BANKSTOCK_H
#define BANKSTOCK_H

#include "Stock.h"

/**
 * @brief Klasa BankStock reprezentuje akcjê bankow¹.
 * Dziedziczy po klasie Stock i implementuje specyficzn¹ logikê aktualizacji ceny.
 */
class BankStock : public Stock {
public:
    /**
     * @brief Konstruktor klasy BankStock.
     * @param name Nazwa akcji bankowej.
     * @param initialPrice Pocz¹tkowa cena akcji bankowej.
     */
    BankStock(const std::string& name, double initialPrice);

    /**
     * @brief Aktualizuje cenê akcji bankowej.
     * Implementuje specyficzn¹ logikê zmian cen dla akcji bankowych.
     */
    void updatePrice() override;
};

#endif // BANKSTOCK_H