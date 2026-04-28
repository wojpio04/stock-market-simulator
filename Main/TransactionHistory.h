#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "Transaction.h"    

/**
 * @brief Klasa TransactionHistory zarz¹dza histori¹ transakcji inwestora.
 */
class TransactionHistory {
private:
    std::vector<Transaction> transactions; ///< Wektor przechowuj¹cy wszystkie transakcje.

public:
    /**
     * @brief Domyœlny konstruktor klasy TransactionHistory.
     */
    TransactionHistory() = default;

    /**
     * @brief Dodaje now¹ transakcjê do historii. U¿ywa aktualnego czasu jako timestamp.
     * @param type Typ transakcji (Kupno/Sprzeda¿).
     * @param stockName Nazwa akcji.
     * @param quantity Iloœæ akcji.
     * @param price Cena transakcji.
     */
    void addTransaction(const std::string& type, const std::string& stockName, int quantity, double price);

    /**
     * @brief Dodaje istniej¹cy obiekt Transaction do historii.
     * Przydatne przy wczytywaniu historii z pliku.
     * @param t Obiekt transakcji do dodania.
     */
    void addTransaction(const Transaction& t);

    /**
     * @brief Wyœwietla wszystkie transakcje z historii.
     */
    void displayTransactions() const;

    /**
     * @brief Zwraca sta³¹ referencjê do wektora transakcji.
     * @return Sta³a referencja do std::vector<Transaction>.
     */
    const std::vector<Transaction>& getTransactions() const { return transactions; }
};

#endif // TRANSACTIONHISTORY_H