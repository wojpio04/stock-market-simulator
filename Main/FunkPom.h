#ifndef FUNKPOM_H
#define FUNKPOM_H

#include <iostream>
#include <limits>
#include <string>
#include <algorithm>    

/**
 * @brief Czyœci bufor wejœcia, usuwaj¹c pozosta³e znaki po wczeœniejszych operacjach wejœcia.
 */
void clearInputBuffer();

/**
 * @brief Czyœci ekran konsoli. Dzia³a ró¿nie w zale¿noœci od systemu operacyjnego.
 */
void clearScreen();

/**
 * @brief Konwertuje podany ci¹g znaków na ma³e litery.
 * @param s Ci¹g znaków do konwersji.
 * @return Nowy ci¹g znaków w ma³ych literach.
 */
std::string toLower(std::string s);

#endif // FUNKPOM_H