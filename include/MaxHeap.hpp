#pragma once
#include <vector>
#include "Packet.hpp"

class MaxHeap
{
private:
    std::vector<Packet> heap;

    // Prywatne metody naprawiające strukturę drzewa
    void heapifyUp(size_t index);
    void heapifyDown(size_t index);

public:
    // Identyczny interfejs jak w zwykłej tablicy
    void push(const Packet &packet);
    Packet pop();

    bool isEmpty() const;
    size_t size() const;
};