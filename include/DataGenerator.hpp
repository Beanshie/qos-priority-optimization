#pragma once
#include <vector>
#include "Packet.hpp" // Musi wiedzieć, co generuje

class DataGenerator
{
public:
    // Funkcja statyczna (nie trzeba tworzyć obiektu generatora, żeby jej użyć)
    // Zwraca gotowy wektor pakietów. Parametry: ile sztuk i jaki scenariusz.
    static std::vector<Packet> generate(size_t count, Scenario scenario);
};