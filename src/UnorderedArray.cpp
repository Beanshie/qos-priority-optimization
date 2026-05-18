#include "UnorderedArray.hpp"
#include <stdexcept> // Do rzucania wyjątków (np. gdy kolejka jest pusta)

using namespace std;

void UnorderedArray::push(const Packet &packet)
{
    // Wstawienie na koniec tablicy. Złożoność czasowa: O(1)
    queue.push_back(packet);
}

Packet UnorderedArray::pop()
{
    if (queue.empty())
    {
        throw runtime_error("Blad: Proba pobrania pakietu z pustej kolejki QoS!");
    }

    // 1. ZNALEZIENIE NAJWAŻNIEJSZEGO PAKIETU - Złożoność: O(N)
    // Musimy sprawdzić każdy element po kolei.
    size_t max_index = 0;
    for (size_t i = 1; i < queue.size(); ++i)
    {
        if (queue[i].priority > queue[max_index].priority)
        {
            max_index = i;
        }
    }

    // Zapisujemy zwycięzcę do zwrócenia
    Packet highest_priority_packet = queue[max_index];

    // 2. OPTYMALNE USUNIĘCIE
    // Podmieniamy usuwany element z ostatnim elementem w wektorze
    queue[max_index] = queue.back();
    // Usuwamy duplikat z końca
    queue.pop_back();

    return highest_priority_packet;
}

bool UnorderedArray::isEmpty() const
{
    return queue.empty();
}

size_t UnorderedArray::size() const
{
    return queue.size();
}