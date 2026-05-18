import os
import pandas as pd
import matplotlib.pyplot as plt

# 1. Dynamiczne ustalanie ścieżek (żeby skrypt działał niezależnie od tego skąd go odpalasz)
current_dir = os.path.dirname(os.path.abspath(__file__))
csv_path = os.path.join(current_dir, '../results/wyniki.csv')
plots_dir = os.path.join(current_dir, '../results/plots')

# Upewniamy się, że folder na wykresy istnieje (jak nie ma, to go tworzy)
os.makedirs(plots_dir, exist_ok=True)

# 2. Wczytanie surowych danych z C++
try:
    df = pd.read_csv(csv_path, sep=';')
except FileNotFoundError:
    print(f"Błąd: Nie znaleziono pliku {csv_path}!")
    print("Upewnij się, że najpierw uruchomiłeś program w C++ i wygenerowałeś dane!")
    exit(1)

# Pobieramy unikalne scenariusze z kolumny w pliku CSV
scenarios = df['Scenariusz'].unique()

print("Generowanie wykresów...")

# 3. Pętla rysująca osobny wykres dla każdego scenariusza ruchu sieciowego
for scenario in scenarios:
    # Filtrujemy dane tylko dla obecnego scenariusza
    scenario_data = df[df['Scenariusz'] == scenario]
    
    # Tworzymy nowe płótno wykresu (wielkość 10x6 cali)
    plt.figure(figsize=(10, 6))
    
    # Konwertujemy czasy z mikrosekund na milisekundy (dzieląc przez 1000) dla czytelności raportu
    time_array_ms = scenario_data['Czas_Tablicy'] / 1000
    time_heap_ms = scenario_data['Czas_Kopca'] / 1000
    
    # Rysujemy linie (marker 'o' dodaje kropki na zgięciach linii dla Tablicy, a 's' to kwadraty dla Kopca)
    plt.plot(scenario_data['Rozmiar'], time_array_ms, marker='o', linewidth=2.5, color='#e74c3c', label='Tablica Nieuporządkowana O(N)')
    plt.plot(scenario_data['Rozmiar'], time_heap_ms, marker='s', linewidth=2.5, color='#2ecc71', label='Kopiec Binarny O(log N)')
    
    # Nadajemy profesjonalny tytuł i opisy osi
    plt.title(f'Wydajność algorytmów QoS - Scenariusz: {scenario}', fontsize=14, fontweight='bold', pad=15)
    plt.xlabel('Liczba pakietów w kolejce (N)', fontsize=11, labelpad=10)
    plt.ylabel('Całkowity czas przetwarzania [ms]', fontsize=11, labelpad=10)
    
    # Dodajemy siatkę pomocniczą w tle (dla inżynierskiego sznytu)
    plt.grid(True, linestyle='--', alpha=0.6)
    
    # Dodajemy legendę
    plt.legend(fontsize=11, loc='upper left')
    
    # Formatujemy liczby na osi X, żeby pokazywały np. 100000 zamiast 1e5
    plt.ticklabel_format(style='plain', axis='x')
    
    # Zapisujemy plik PNG w najwyższej rozdzielczości (dpi=300 - idealne do Worda/PDF)
    plot_filename = f'wykres_{scenario.lower()}.png'
    plot_save_path = os.path.join(plots_dir, plot_filename)
    
    # bbox_inches='tight' zapobiega ucinaniu napisów na brzegach obrazka
    plt.savefig(plot_save_path, dpi=300, bbox_inches='tight')
    plt.close() # Czyścimy pamięć przed następną iteracją pętli
    
    print(f"-> Zapisano: results/plots/{plot_filename}")

print("\nWszystkie wykresy zostały pomyślnie wygenerowane i zapisane!")