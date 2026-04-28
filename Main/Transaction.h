#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>    

/**
 * @brief Struktura Transaction reprezentuje pojedyncz¹ transakcjê akcjami.
 */
struct Transaction {
    std::string type;               ///< Typ transakcji (np. "Kupno", "Sprzeda¿").
    std::string stockName;          ///< Nazwa akcji, której dotyczy transakcja.
    int quantity;                   ///< Iloœæ akcji w transakcji.
    double price;                   ///< Cena akcji w momencie transakcji.
    std::chrono::system_clock::time_point timestamp; ///< Czas, w którym transakcja mia³a miejsce.

    /**
     * @brief Konstruktor transakcji. U¿ywa aktualnego czasu systemowego jako timestamp.
     * @param typ Typ transakcji.
     * @param name Nazwa akcji.
     * @param qty Iloœæ akcji.
     * @param prc Cena transakcji.
     */
    Transaction(const std::string& typ, const std::string& name, int qty, double prc)
        : type(typ), stockName(name), quantity(qty), price(prc), timestamp(std::chrono::system_clock::now()) {
    }

    /**
     * @brief Konstruktor transakcji. Pozwala na podanie niestandardowego timestampu (np. przy wczytywaniu z pliku).
     * @param typ Typ transakcji.
     * @param name Nazwa akcji.
     * @param qty Iloœæ akcji.
     * @param prc Cena transakcji.
     * @param ts Timestamp transakcji.
     */
    Transaction(const std::string& typ, const std::string& name, int qty, double prc, std::chrono::system_clock::time_point ts)
        : type(typ), stockName(name), quantity(qty), price(prc), timestamp(ts) {
    }
};

#endif // TRANSACTION_H