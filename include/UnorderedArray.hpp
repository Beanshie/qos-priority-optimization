#pragma once
#include <vector>
#include "Packet.hpp"

class UnorderedArray
{
private:
    std::vector<Packet> queue;

public:
    // Wstawianie pakietu (Operacja PUSH)
    void push(const Packet &packet);

    // Pobieranie najważniejszego pakietu (Operacja POP)
    Packet pop();

    // Funkcje pomocnicze
    bool isEmpty() const;
    size_t size() const;
};