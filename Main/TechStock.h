#ifndef TECHSTOCK_H
#define TECHSTOCK_H

#include "Stock.h"

/**
 * @brief Klasa TechStock reprezentuje akcjê technologiczn¹.
 * Dziedziczy po klasie Stock i implementuje specyficzn¹ logikê aktualizacji ceny.
 */
class TechStock : public Stock {
public:
    /**
     * @brief Konstruktor klasy TechStock.
     * @param name Nazwa akcji technologicznej.
     * @param initialPrice Pocz¹tkowa cena akcji technologicznej.
     */
    TechStock(const std::string& name, double initialPrice);

    /**
     * @brief Aktualizuje cenê akcji technologicznej.
     * Implementuje specyficzn¹ logikê zmian cen dla akcji technologicznych.
     */
    void updatePrice() override;
};

#endif // TECHSTOCK_H