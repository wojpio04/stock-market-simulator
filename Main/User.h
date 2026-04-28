#ifndef USER_H
#define USER_H

#include <string>

/**
 * @brief Klasa bazowa User reprezentuje ogólnego u¿ytkownika systemu.
 * Przechowuje podstawowe informacje, takie jak nazwa i dostêpne fundusze.
 */
class User {
protected:
    std::string name;       ///< Nazwa u¿ytkownika.
    double funds;           ///< Iloœæ œrodków finansowych u¿ytkownika.

public:
    /**
     * @brief Konstruktor klasy User.
     * @param name Nazwa u¿ytkownika.
     * @param initialFunds Pocz¹tkowa iloœæ œrodków finansowych (domyœlnie 10000.0).
     */
    User(const std::string& name, double initialFunds = 10000.0);

    /**
     * @brief Wirtualny destruktor klasy User.
     * Zapewnia prawid³owe zwalnianie zasobów w klasach pochodnych.
     */
    virtual ~User() = default;

    /**
     * @brief Zwraca nazwê u¿ytkownika.
     * @return Nazwa u¿ytkownika.
     */
    std::string getName() const;

    /**
     * @brief Zwraca bie¿¹c¹ iloœæ œrodków finansowych u¿ytkownika.
     * @return Iloœæ œrodków finansowych.
     */
    double getFunds() const;

    /**
     * @brief Wyœwietla bie¿¹c¹ iloœæ œrodków finansowych u¿ytkownika.
     */
    void displayFunds() const;

    /**
     * @brief Dodaje okreœlon¹ kwotê do œrodków finansowych u¿ytkownika.
     * @param amount Kwota do dodania.
     */
    void addFunds(double amount);

    /**
     * @brief Usuwa okreœlon¹ kwotê ze œrodków finansowych u¿ytkownika.
     * @param amount Kwota do usuniêcia.
     */
    void removeFunds(double amount);
};

#endif // USER_H