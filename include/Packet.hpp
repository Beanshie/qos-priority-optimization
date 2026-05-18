#pragma once // Zabezpiecza przed podwójnym wczytaniem pliku
#include <cstdint>
#include <array>

// Enum definiujący nasze 3 scenariusze dla czytelności kodu
enum class Scenario
{
    Uniform, // Rozkład jednorodny (normalny ruch)
    Sorted,  // Pakiety posortowane rosnąco (najgorszy przypadek dla kopca)
    Burst    // Zmasowany atak (90% pakietów ma najwyższy priorytet)
};

struct Packet
{
    uint32_t id;  // Unikalny numer pakietu (4 bajty)
    int priority; // Priorytet QoS (4 bajty)

    // SZTUCZNE OBCIĄŻENIE (Payload)
    // Prawdziwy pakiet w sieci ma dane. Dodajemy pustą tablicę 56 bajtów.
    // 4 + 4 + 56 = 64 bajty. Dzięki temu nasz pakiet waży w RAM-ie dokładnie 64 bajty.
    // Ułatwi to wyliczenia zużycia pamięci w raporcie!
    std::array<uint8_t, 56> payload;
};