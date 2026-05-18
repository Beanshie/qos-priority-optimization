#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "Packet.hpp"
#include "Timer.hpp"
#include "DataGenerator.hpp"
#include "UnorderedArray.hpp"
#include "MaxHeap.hpp"

using namespace std;

// Funkcja pomocnicza - tłumaczy Enuma na czytelny tekst do pliku CSV
string scenarioToString(Scenario s)
{
    switch (s)
    {
    case Scenario::Uniform:
        return "Uniform";
    case Scenario::Sorted:
        return "Sorted";
    case Scenario::Burst:
        return "Burst";
    default:
        return "Unknown";
    }
}

int main()
{
    // Rozmiary testowanych kolejek (ilość pakietów w jednym teście)
    vector<size_t> test_sizes = {10000, 25000, 50000, 100000, 200000};
    // Scenariusze ruchu sieciowego
    vector<Scenario> scenarios = {Scenario::Uniform, Scenario::Sorted, Scenario::Burst};

    // Próba otwarcia pliku. Ponieważ uruchamiamy program z folderu /build,
    // plik musi zostać zapisany piętro wyżej w /results.
    ofstream csv_file("../results/wyniki.csv");
    if (!csv_file.is_open())
    {
        // Zapasowa ścieżka, gdyby ktoś odpalał prosto z głównego folderu
        csv_file.open("results/wyniki.csv");
        if (!csv_file.is_open())
        {
            cerr << "Blad: Nie mozna otworzyc pliku wyniki.csv do zapisu! Upewnij sie, ze folder 'results' istnieje." << endl;
            return 1;
        }
    }

    // Zapisujemy nagłówek (kolumny) do pliku CSV (rozdzielane średnikiem)
    csv_file << "Rozmiar;Czas_Tablicy;Czas_Kopca;Scenariusz\n";

    cout << "=========================================" << endl;
    cout << "   ROZPOCZYNAM TESTY WYDAJNOSCI QoS      " << endl;
    cout << "=========================================" << endl;

    for (Scenario scenario : scenarios)
    {
        string sc_name = scenarioToString(scenario);
        cout << "\n---> Symulacja Ruchu: " << sc_name << " <---" << endl;

        for (size_t size : test_sizes)
        {
            cout << "Przetwarzanie " << size << " pakietow... ";

            // 1. Generujemy DOKŁADNIE TEN SAM zbiór danych dla obu struktur,
            // żeby test był w 100% sprawiedliwy.
            vector<Packet> test_data = DataGenerator::generate(size, scenario);

            long long time_array = 0;
            long long time_heap = 0;
            Timer timer;

            // ==========================================
            // TEST 1: TABLICA NIEUPORZĄDKOWANA (O(N))
            // ==========================================
            {
                UnorderedArray u_array;
                timer.start(); // START STOPERA

                // Symulacja wpadania pakietów do routera (WSTAWIANIE)
                for (const auto &p : test_data)
                {
                    u_array.push(p);
                }
                // Symulacja obsługi kolejki przez router (POBIERANIE)
                while (!u_array.isEmpty())
                {
                    u_array.pop();
                }

                timer.stop(); // STOP STOPERA
                time_array = timer.elapsedMicroseconds();
            } // <- Tu tablica jest usuwana z RAM-u

            // ==========================================
            // TEST 2: KOPIEC BINARNY (O(log N))
            // ==========================================
            {
                MaxHeap m_heap;
                timer.start(); // START STOPERA

                // Symulacja wpadania pakietów do routera
                for (const auto &p : test_data)
                {
                    m_heap.push(p);
                }
                // Symulacja obsługi kolejki
                while (!m_heap.isEmpty())
                {
                    m_heap.pop();
                }

                timer.stop(); // STOP STOPERA
                time_heap = timer.elapsedMicroseconds();
            } // <- Tu kopiec jest usuwany z RAM-u

            // Zapisujemy wiersz danych do pliku CSV
            csv_file << size << ";" << time_array << ";" << time_heap << ";" << sc_name << "\n";

            // Wypisujemy wynik do konsoli (dzielimy przez 1000, żeby pokazać milisekundy zamiast mikrosekund)
            cout << "Zakonczono! [Tablica: " << time_array / 1000 << " ms | Kopiec: " << time_heap / 1000 << " ms]" << endl;
        }
    }

    csv_file.close();
    cout << "\n=========================================" << endl;
    cout << "       TESTY ZAKONCZONE SUKCESEM         " << endl;
    cout << " Wyniki zrzucono do: results/wyniki.csv  " << endl;
    cout << "=========================================" << endl;

    return 0;
}