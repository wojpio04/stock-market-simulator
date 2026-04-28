# Stock Market Simulator (C++20)

## Opis projektu
Konsolowa aplikacja napisana w C++20 symulująca działanie rynku akcji.  
System umożliwia zarządzanie spółkami, inwestorami oraz przeprowadzanie transakcji kupna i sprzedaży akcji.

Projekt został zrealizowany w celach edukacyjnych w ramach studiów informatycznych.

---

## Funkcjonalności

### Tryb użytkownika (Investor)
- tworzenie nowego użytkownika
- wczytywanie zapisanej gry
- kupno i sprzedaż akcji
- zarządzanie portfelem inwestycyjnym
- historia transakcji
- zapis stanu gry do pliku

### Tryb administratora (Admin)
- dodawanie nowych spółek
- usuwanie spółek
- ręczna zmiana cen akcji
- przegląd wszystkich dostępnych akcji

### System rynku
- różne typy akcji:
  - TechStock
  - BankStock
  - EnergyStock
- dynamiczne zarządzanie listą spółek
- symulacja działania rynku

---

## Mechanizm zmian cen (zdarzenia losowe)

W projekcie zastosowano losową symulację zmian cen akcji, która różni się w zależności od sektora spółki. Każdy typ akcji posiada własny zakres wahań oraz możliwość wystąpienia rzadkich zdarzeń rynkowych.

### Ogólny mechanizm
- każda spółka generuje losową zmianę procentową (w zależności od sektora)
- na jej podstawie wyliczana jest zmiana ceny akcji
- w określonych przypadkach uruchamiane są specjalne zdarzenia rynkowe
- cena akcji nie może spaść poniżej wartości minimalnej (0.1)
- każda zmiana ceny zapisywana jest do historii (priceHistory)

### TechStock
- losowy zakres zmian: -10% do +10%
- zdarzenia specjalne:
  - wzrost ceny o 15% → boom technologiczny
  - spadek ceny o 12% → kryzys sektora technologicznego
- sektor charakteryzuje się wysoką zmiennością i dużym ryzykiem

### BankStock
- losowy zakres zmian: -4% do +4%
- zdarzenia specjalne:
  - wzrost ceny o 8% → pozytywne informacje finansowe / pakiet inwestycyjny
  - spadek ceny o 7% → kryzys finansowy
- sektor bardziej stabilny niż technologie

### EnergyStock
- losowy zakres zmian: -7% do +7%
- zdarzenia specjalne:
  - wzrost ceny o 10% → odkrycie nowych złóż / wzrost produkcji energii
  - spadek ceny o 9% → awaria infrastruktury energetycznej
- sektor umiarkowanie stabilny, podatny na zdarzenia losowe

### Charakterystyka systemu
- każdy sektor ma własny zakres zmienności cen
- zdarzenia specjalne mają mniejsze prawdopodobieństwo, ale większy wpływ na cenę
- używany jest generator liczb losowych (std::mt19937)
- system symuluje uproszczone zachowanie realnego rynku finansowego

---

## Technologie i koncepcje

- **C++20**
- **Programowanie obiektowe (OOP)**
  - dziedziczenie
  - polimorfizm
  - enkapsulacja
- **Smart pointers** (`std::shared_ptr`, `std::unique_ptr`)
- **Wielowątkowość**
  - `std::async`
  - zapisywanie stanu w tle
- **Filesystem**
  - `std::filesystem` (obsługa plików użytkowników)
- **Regex**
  - walidacja nazw użytkowników
- **STL**
  - `vector`, `algorithm`, `string`
- **Obsługa błędów wejścia**
  - walidacja danych użytkownika

---

## Struktura projektu

- `main.cpp` – główny punkt wejścia i logika menu
- `MarketSimulator` – zarządzanie rynkiem
- `Investor` – logika użytkownika
- `Admin` – operacje administracyjne
- `Stock` + pochodne:
  - `TechStock`
  - `BankStock`
  - `EnergyStock`
- `Portfolio` – zarządzanie aktywami użytkownika
- `TransactionHistory` – historia operacji

---

## Jak uruchomić

1. Sklonuj repozytorium: https://github.com/wojpio04/stock-market-simulator.git
2. Przejdź do katalogu projektu: cd stock-market-simulator/Main
3. Skompiluj: g++ *.cpp -o app
4. Uruchom: ./app

---

## System zapisu

- dane użytkowników zapisywane są w folderze `saves/`
- każdy użytkownik posiada osobny plik `.txt`
- aplikacja umożliwia:
  - wczytywanie stanu
  - usuwanie użytkowników

---

## Czego się nauczyłem

- projektowania aplikacji w stylu obiektowym
- zarządzania pamięcią w C++ (smart pointers)
- pracy z plikami i systemem operacyjnym
- podstaw wielowątkowości
- walidacji danych wejściowych

---

## Możliwe usprawnienia

- interfejs graficzny (GUI)
- bardziej zaawansowany silnik symulacji rynku
- baza danych zamiast plików
- system logowania i autoryzacji
- testy jednostkowe

---

## Autor

Piotr Wójcik
