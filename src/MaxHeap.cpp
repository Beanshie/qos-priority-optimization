#include "MaxHeap.hpp"
#include <stdexcept>
#include <utility> // Dla std::swap

using namespace std;

// === BĄBELKOWANIE W GÓRĘ (Po dodaniu na koniec) ===
void MaxHeap::heapifyUp(size_t index)
{
    while (index > 0)
    {
        size_t parent = (index - 1) / 2; // Wyliczamy indeks rodzica

        // Jeśli dziecko (obecny pakiet) jest ważniejsze od rodzica -> zamieniamy!
        if (heap[index].priority > heap[parent].priority)
        {
            swap(heap[index], heap[parent]);
            index = parent; // Przeskakujemy poziom wyżej i badamy dalej
        }
        else
        {
            // Złota zasada spełniona, pakiet znalazł swoje miejsce
            break;
        }
    }
}

// === OPADANIE W DÓŁ (Po usunięciu szefa) ===
void MaxHeap::heapifyDown(size_t index)
{
    size_t size = heap.size();

    while (true)
    {
        size_t largest = index;       // Zakładamy, że obecny węzeł jest największy
        size_t left = 2 * index + 1;  // Lewe dziecko
        size_t right = 2 * index + 2; // Prawe dziecko

        // Czy lewe dziecko istnieje i jest większe od obecnego lidera?
        if (left < size && heap[left].priority > heap[largest].priority)
        {
            largest = left;
        }
        // Czy prawe dziecko istnieje i jest większe od lidera?
        if (right < size && heap[right].priority > heap[largest].priority)
        {
            largest = right;
        }

        // Jeśli znalazło się większe dziecko, zamieniamy się z nim miejscami
        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            index = largest; // Schodzimy poziom niżej i badamy dalej
        }
        else
        {
            break; // Król jest na swoim miejscu
        }
    }
}

// === PUBLICZNE METODY ===

void MaxHeap::push(const Packet &packet)
{
    heap.push_back(packet);     // Wrzucamy na sam koniec
    heapifyUp(heap.size() - 1); // Zmuszamy do bąbelkowania
}

Packet MaxHeap::pop()
{
    if (heap.empty())
    {
        throw runtime_error("Blad: Proba pobrania pakietu z pustego kopca!");
    }

    Packet root = heap[0]; // Zapisujemy najważniejszy pakiet (zawsze na szczycie)

    heap[0] = heap.back(); // Wrzucamy najsłabszy pakiet z końca na szczyt
    heap.pop_back();       // Usuwamy ten sklonowany z końca

    if (!heap.empty())
    {
        heapifyDown(0); // Zmuszamy fałszywego szefa do opadania
    }

    return root; // Oddajemy prawowitego szefa światu
}

bool MaxHeap::isEmpty() const
{
    return heap.empty();
}

size_t MaxHeap::size() const
{
    return heap.size();
}