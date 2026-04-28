#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include <mutex>    
#include <memory>    

/**
 * @brief Klasa bazowa reprezentuj¹ca pojedyncz¹ akcjê na rynku.
 * Zarz¹dza nazw¹, cen¹, histori¹ cen i zapewnia podstawowe metody.
 */
class Stock {
protected:
    std::string name;             ///< Nazwa akcji (np. "Apple", "PKO BP")
    double price;                 ///< Bie¿¹ca cena akcji
    std::vector<double> priceHistory; ///< Historia cen akcji
    mutable std::mutex stockMutex; ///< Mutex do ochrony danych akcji w œrodowisku wielow¹tkowym

public:
    /**
     * @brief Konstruktor klasy Stock.
     * @param name Nazwa akcji.
     * @param initialPrice Pocz¹tkowa cena akcji.
     */
    Stock(const std::string& name, double initialPrice);

    /**
     * @brief Wirtualny destruktor klasy Stock.
     * Zapewnia prawid³owe zwalnianie zasobów w klasach pochodnych.
     */
    virtual ~Stock() = default;

    /**
     * @brief Czysto wirtualna metoda do aktualizacji ceny akcji.
     * Musi byæ zaimplementowana w klasach pochodnych (np. TechStock, BankStock).
     */
    virtual void updatePrice() = 0;

    /**
     * @brief Zwraca nazwê akcji.
     * @return Nazwa akcji.
     */
    virtual std::string getName() const;

    /**
     * @brief Zwraca bie¿¹c¹ cenê akcji.
     * @return Bie¿¹ca cena akcji.
     */
    virtual double getPrice() const;

    /**
     * @brief Zwraca historiê cen akcji.
     * @return Sta³a referencja do wektora historii cen.
     */
    virtual const std::vector<double>& getPriceHistory() const;

    /**
     * @brief Ustawia now¹ cenê akcji i dodaje j¹ do historii.
     * @param newPrice Nowa cena do ustawienia.
     */
    void setPrice(double newPrice);
};

#endif // STOCK_H