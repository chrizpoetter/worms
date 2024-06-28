#ifndef USERINPUT_H
#define USERINPUT_H

#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <cctype>
#include <string>

// Funktion zum Einlesen der Benutzereingaben
std::vector<std::string> readUserInput() {
    std::string inputline;
    std::vector<std::string> order; 

    // Lies die gesamte Eingabezeile
    std::getline(std::cin, inputline);

    // Erzeuge einen String in Kleinbuchstaben
    std::string lowercaseinput;
    for (char c : inputline) {
        lowercaseinput += std::tolower(c);
    }

    // Erzeuge einen Stringstream aus der Eingabe (Zerlegt die Eingabeteile in mehrere Strings)
    std::istringstream iss(lowercaseinput); 
    std::string token;

    // Zerlege die Eingabe in einzelne Tokens
    while (iss >> token) {
        order.push_back(token);
    }

    return order;
}

#endif // USERINPUT_H
