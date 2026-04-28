#ifndef ADMIN_H
#define ADMIN_H

#include "Stock.h"
#include <memory>
#include <vector>
#include <string>

/**
 * @brief Klasa Admin reprezentuje administratora systemu.
 * Zapewnia funkcjonalnoœci do zarz¹dzania akcjami na rynku, takie jak dodawanie, usuwanie i modyfikowanie cen.
 */
class Admin {
public:
    /**
     * @brief Dodaje now¹ akcjê do listy dostêpnych akcji na rynku.
     * @param stocks Referencja do wektora akcji na rynku.
     */
    void addStock(std::vector<std::shared_ptr<Stock>>& stocks);

    /**
     * @brief Usuwa istniej¹c¹ akcjê z listy dostêpnych akcji na rynku.
     * @param stocks Referencja do wektora akcji na rynku.
     */
    void removeStock(std::vector<std::shared_ptr<Stock>>& stocks);

    /**
     * @brief Modyfikuje cenê wybranej akcji na rynku.
     * @param stocks Referencja do wektora akcji na rynku.
     */
    void modifyPrice(std::vector<std::shared_ptr<Stock>>& stocks);

    /**
     * @brief Wyœwietla listê wszystkich akcji dostêpnych na rynku.
     * @param stocks Sta³a referencja do wektora akcji na rynku.
     */
    void listStocks(const std::vector<std::shared_ptr<Stock>>& stocks) const;
};

#endif // ADMIN_H