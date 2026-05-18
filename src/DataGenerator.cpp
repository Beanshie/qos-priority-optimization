#include "DataGenerator.hpp"
#include <random>
#include <algorithm> // do std::sort

using namespace std; // W .cpp pozwalamy sobie na ten luksus!

vector<Packet> DataGenerator::generate(size_t count, Scenario scenario)
{
    // vector z góry rezerwuje sobie miejsce w RAM-ie. (Mega optymalizacja!)
    // Bez tego wektor by się rozszerzał w trakcie dodawania i tracił na to czas CPU.
    vector<Packet> packets;
    packets.reserve(count);

    // Nowoczesny i piekielnie szybki generator liczb pseudolosowych w C++ (Mersenne Twister)
    random_device rd;
    mt19937 gen(rd());

    // Dystrybuanty dla konkretnych zakresów priorytetów
    uniform_int_distribution<> uniform_dist(1, 100);
    uniform_int_distribution<> high_dist(95, 100);  // Do zmasowanego ataku
    uniform_int_distribution<> chance_dist(1, 100); // Rzut kostką w %, np. do szansy na atak

    for (size_t i = 0; i < count; ++i)
    {
        Packet p;
        p.id = static_cast<uint32_t>(i);

        // Zapełniamy payload zerami, żeby w pamięci RAM nie było śmieci
        p.payload.fill(0);

        // Logika scenariuszy
        if (scenario == Scenario::Uniform || scenario == Scenario::Sorted)
        {
            p.priority = uniform_dist(gen);
        }
        else if (scenario == Scenario::Burst)
        {
            // 90% szans na priorytet 95-100, 10% szans na priorytet 1-100
            if (chance_dist(gen) <= 90)
            {
                p.priority = high_dist(gen);
            }
            else
            {
                p.priority = uniform_dist(gen);
            }
        }

        packets.push_back(p);
    }

    // Jeśli scenariusz to "Sorted" (najgorszy przypadek), sortujemy wygenerowane pakiety rosnąco
    if (scenario == Scenario::Sorted)
    {
        // Używamy wyrażenia lambda do wskazania, że sortujemy po parametrze 'priority'
        sort(packets.begin(), packets.end(), [](const Packet &a, const Packet &b)
             { return a.priority < b.priority; });
    }

    return packets;
}