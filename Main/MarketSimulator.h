#ifndef MARKETSIMULATOR_H
#define MARKETSIMULATOR_H

// Deklaracja wyprzedzaj¹ca dla Stock, aby unikn¹æ cyklicznych zale¿noœci
class Stock;

#include <vector>
#include <thread>
#include <atomic>
#include <memory> // Dla std::shared_ptr
#include <mutex>
#include <map>
#include <condition_variable>    

/**
 * @brief Klasa MarketSimulator symuluje rynek akcji.
 * Zarz¹dza kolekcj¹ akcji, aktualizuje ich ceny i dostarcza interfejs do interakcji.
 */
class MarketSimulator {
private:
    std::vector<std::shared_ptr<Stock>> stocks; ///< Kolekcja wszystkich akcji na rynku.
    std::thread simulationThread;            ///< W¹tek odpowiedzialny za symulacjê cen.
    std::atomic<bool> running;               ///< Flaga kontroluj¹ca dzia³anie w¹tku symulacji.
    mutable std::mutex marketMutex;          ///< Mutex do ochrony danych rynku (np. wektora akcji).
    std::condition_variable cv;              ///< Zmienna warunkowa do sterowania w¹tkiem symulacji.

    /**
     * @brief Prywatna metoda uruchamiaj¹ca g³ówn¹ pêtlê symulacji rynku.
     * Aktualizuje ceny akcji w okreœlonych interwa³ach.
     */
    void simulate();

public:
    /**
     * @brief Konstruktor klasy MarketSimulator.
     * Inicjalizuje stan symulatora.
     */
    MarketSimulator();

    /**
     * @brief Destruktor klasy MarketSimulator.
     * Zatrzymuje w¹tek symulacji i czeka na jego zakoñczenie.
     */
    ~MarketSimulator();

    /**
     * @brief Dodaje now¹ akcjê do symulatora rynku.
     * @param stock WskaŸnik shared_ptr do obiektu akcji.
     */
    void addStock(const std::shared_ptr<Stock>& stock);

    /**
     * @brief Usuwa akcjê z symulatora rynku na podstawie jej nazwy.
     * @param name Nazwa akcji do usuniêcia.
     */
    void removeStock(const std::string& name);

    /**
     * @brief Wyszukuje akcjê po nazwie.
     * @param name Nazwa akcji do wyszukania.
     * @return WskaŸnik shared_ptr do znalezionej akcji lub nullptr jeœli nie znaleziono.
     */
    std::shared_ptr<Stock> getStockByName(const std::string& name);

    /**
     * @brief Wyszukuje akcjê po indeksie podanym przez u¿ytkownika (1-bazowy).
     * @param index Indeks akcji (1-bazowy).
     * @return WskaŸnik shared_ptr do znalezionej akcji lub nullptr jeœli indeks jest nieprawid³owy.
     */
    std::shared_ptr<Stock> getStockByIndex(int index);

    /**
     * @brief Wyœwietla aktualne notowania wszystkich akcji na rynku, pogrupowane typem.
     * Wraz z krótk¹ histori¹ zmian cen.
     */
    void displayStocks() const;

    /**
     * @brief Zwraca modyfikowaln¹ referencjê do wektora wszystkich akcji.
     * @return Referencja do wektora shared_ptr do obiektów Stock.
     */
    std::vector<std::shared_ptr<Stock>>& getStocksRef();

    /**
     * @brief Zwraca sta³¹ referencjê do wektora wszystkich akcji.
     * @return Sta³a referencja do wektora shared_ptr do obiektów Stock.
     */
    const std::vector<std::shared_ptr<Stock>>& getStocksRef() const; // Dodano, jeœli nie by³o wczeœniej

    /**
     * @brief Rozpoczyna w¹tek symulacji rynku.
     */
    void start();

    /**
     * @brief Zatrzymuje w¹tek symulacji rynku.
     */
    void stop();
};

#endif // MARKETSIMULATOR_H