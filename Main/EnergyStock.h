#ifndef ENERGYSTOCK_H
#define ENERGYSTOCK_H

#include "Stock.h"

/**
 * @brief Klasa EnergyStock reprezentuje akcjê energetyczn¹.
 * Dziedziczy po klasie Stock i implementuje specyficzn¹ logikê aktualizacji ceny.
 */
class EnergyStock : public Stock {
public:
    /**
     * @brief Konstruktor klasy EnergyStock.
     * @param name Nazwa akcji energetycznej.
     * @param initialPrice Pocz¹tkowa cena akcji energetycznej.
     */
    EnergyStock(const std::string& name, double initialPrice);

    /**
     * @brief Aktualizuje cenê akcji energetycznej.
     * Implementuje specyficzn¹ logikê zmian cen dla akcji energetycznych.
     */
    void updatePrice() override;
};

#endif // ENERGYSTOCK_H