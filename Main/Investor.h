#ifndef INVESTOR_H
#define INVESTOR_H

#include "User.h"
#include "Portfolio.h"
#include "TransactionHistory.h"
#include <string>
#include <memory>    
#include <vector>

// Deklaracje wyprzedzaj¹ce, aby unikn¹æ cyklicznych zale¿noœci i przyspieszyæ kompilacjê
class Stock;
class MarketSimulator;

/**
 * @brief Klasa Investor reprezentuje inwestora w systemie symulacji rynku.
 * Dziedziczy po klasie User i zarz¹dza portfelem, histori¹ transakcji oraz funduszami.
 */
class Investor {
private:
    std::string username;           ///< Nazwa u¿ytkownika inwestora.
    double funds;                   ///< Bie¿¹ca iloœæ dostêpnych œrodków finansowych.
    Portfolio portfolio;            ///< Obiekt Portfolio, przechowuj¹cy posiadane akcje.
    TransactionHistory history;     ///< Obiekt TransactionHistory, przechowuj¹cy historiê transakcji.

public:
    /**
     * @brief Konstruktor klasy Investor.
     * @param username Nazwa u¿ytkownika inwestora.
     * @param initialFunds Pocz¹tkowa iloœæ œrodków finansowych inwestora.
     */
    Investor(const std::string& username, double initialFunds);

    /**
     * @brief Konstruktor klasy Investor, u¿ywany do wczytywania stanu na podstawie nazwy u¿ytkownika.
     * @param username_only Nazwa u¿ytkownika, dla którego ma zostaæ wczytany stan.
     */
    Investor(const std::string& username_only);

    /**
     * @brief Wyœwietla aktualn¹ iloœæ œrodków finansowych inwestora.
     */
    void displayFunds() const;

    /**
     * @brief Wyœwietla aktualny portfel inwestora, w³¹cznie z aktualnymi cenami rynkowymi.
     * @param market Referencja do obiektu MarketSimulator, aby uzyskaæ aktualne ceny.
     */
    void displayPortfolio(MarketSimulator& market) const;

    /**
     * @brief Wyœwietla historiê wszystkich transakcji wykonanych przez inwestora.
     */
    void displayHistory() const;

    /**
     * @brief Przeprowadza operacjê zakupu akcji.
     * @param stock WskaŸnik shared_ptr do akcji, któr¹ inwestor chce kupiæ.
     * @param quantity Iloœæ akcji do kupienia.
     * @param market Referencja do obiektu MarketSimulator.
     * @return true jeœli zakup siê powiód³, false w przeciwnym razie.
     */
    bool buyStock(const std::shared_ptr<Stock>& stock, int quantity, MarketSimulator& market);

    /**
     * @brief Przeprowadza operacjê sprzeda¿y akcji.
     * @param stock WskaŸnik shared_ptr do akcji, któr¹ inwestor chce sprzedaæ.
     * @param quantity Iloœæ akcji do sprzedania.
     * @param market Referencja do obiektu MarketSimulator.
     * @return true jeœli sprzeda¿ siê powiod³a, false w przeciwnym razie.
     */
    bool sellStock(const std::shared_ptr<Stock>& stock, int quantity, MarketSimulator& market);

    /**
     * @brief Zwraca modyfikowaln¹ referencjê do obiektu Portfolio inwestora.
     * @return Referencja do Portfolio.
     */
    Portfolio& getPortfolio();

    /**
     * @brief Zwraca sta³¹ referencjê do obiektu Portfolio inwestora.
     * @return Sta³a referencja do Portfolio.
     */
    const Portfolio& getPortfolio() const;

    /**
     * @brief Zwraca bie¿¹c¹ iloœæ œrodków finansowych inwestora.
     * @return Iloœæ œrodków finansowych.
     */
    double getFunds() const;

    /**
     * @brief Ustawia now¹ iloœæ œrodków finansowych dla inwestora.
     * @param newFunds Nowa wartoœæ œrodków finansowych.
     */
    void setFunds(double newFunds);

    /**
     * @brief Zapisuje aktualny stan inwestora (fundusze, portfel, historia transakcji) do pliku.
     */
    void saveState() const;

    /**
     * @brief Wczytuje stan inwestora z pliku.
     * @return true jeœli wczytywanie siê powiod³o, false w przeciwnym razie (np. brak pliku).
     */
    bool loadState();

    /**
     * @brief Zwraca nazwê u¿ytkownika inwestora.
     * @return Nazwa u¿ytkownika.
     */
    std::string getUsername() const { return username; }
};

#endif // INVESTOR_H