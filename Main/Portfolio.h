#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <map>
#include <vector>    

/**
 * @brief Struktura OwnedStockDetails przechowuje szczegó³y o posiadanych akcjach.
 */
struct OwnedStockDetails {
    int quantity;           ///< Iloœæ posiadanych akcji.
    double averageBuyPrice; ///< Œrednia cena, po której akcje zosta³y zakupione.

    /**
     * @brief Konstruktor struktury OwnedStockDetails.
     * @param q Pocz¹tkowa iloœæ.
     * @param price Pocz¹tkowa œrednia cena zakupu.
     */
    OwnedStockDetails(int q = 0, double price = 0.0) : quantity(q), averageBuyPrice(price) {}
};

/**
 * @brief Klasa Portfolio reprezentuje portfel inwestora.
 * Zarz¹dza posiadanymi akcjami (nazwa akcji -> szczegó³y).
 */
class Portfolio {
private:
    std::map<std::string, OwnedStockDetails> ownedStocks;    ///< Mapa przechowuj¹ca posiadane akcje i ich szczegó³y.

public:
    /**
     * @brief Dodaje akcje do portfela lub aktualizuje istniej¹c¹ pozycjê.
     * @param stockName Nazwa akcji do dodania.
     * @param quantity Iloœæ akcji do dodania.
     * @param buyPrice Cena zakupu pojedynczej akcji.
     */
    void addStock(const std::string& stockName, int quantity, double buyPrice);

    /**
     * @brief Usuwa okreœlon¹ iloœæ akcji z portfela.
     * @param stockName Nazwa akcji do usuniêcia.
     * @param quantity Iloœæ akcji do usuniêcia.
     * @return true jeœli usuniêcie siê powiod³o, false w przeciwnym razie (np. za ma³o akcji).
     */
    bool removeStock(const std::string& stockName, int quantity);

    /**
     * @brief Zwraca iloœæ posiadanych akcji o danej nazwie.
     * @param stockName Nazwa akcji.
     * @return Iloœæ posiadanych akcji.
     */
    int getStockQuantity(const std::string& stockName) const;

    /**
     * @brief Sprawdza, czy portfel jest pusty.
     * @return true jeœli portfel nie zawiera ¿adnych akcji, false w przeciwnym razie.
     */
    bool isEmpty() const;

    /**
     * @brief Zwraca nazwê akcji na podstawie jej indeksu w posortowanej liœcie unikalnych akcji.
     * Przydatne do interakcji z u¿ytkownikiem, gdy akcje s¹ numerowane.
     * @param index Indeks akcji (1-bazowy).
     * @return Nazwa akcji lub pusty string, jeœli indeks jest nieprawid³owy.
     */
    std::string getStockNameByIndex(int index) const;

    /**
     * @brief Zwraca sta³¹ referencjê do mapy posiadanych akcji.
     * @return Sta³a referencja do std::map<std::string, OwnedStockDetails>.
     */
    const std::map<std::string, OwnedStockDetails>& getOwnedStocks() const {
        return ownedStocks;
    }

    /**
     * @brief Zwraca liczbê unikalnych typów akcji w portfelu.
     * @return Liczba unikalnych akcji.
     */
    size_t getUniqueStockCount() const {
        return ownedStocks.size();
    }
};

#endif // PORTFOLIO_H