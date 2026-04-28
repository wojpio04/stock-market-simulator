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

1. Sklonuj repozytorium:
2. Przejdź do katalogu projektu: cd stock-market-simulator
3. Skompiluj: g++ -std=c++20 main.cpp -o app
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
