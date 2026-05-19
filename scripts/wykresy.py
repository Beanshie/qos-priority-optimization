import os
import pandas as pd
import matplotlib.pyplot as plt

# 1. Ustalanie ścieżek
current_dir = os.path.dirname(os.path.abspath(__file__))
csv_path = os.path.join(current_dir, '../results/wyniki.csv')
plots_dir = os.path.join(current_dir, '../results/plots')
os.makedirs(plots_dir, exist_ok=True)

# 2. Wczytanie danych z C++
try:
    df = pd.read_csv(csv_path, sep=';')
except FileNotFoundError:
    print(f"Błąd: Nie znaleziono pliku {csv_path}!")
    print("Upewnij się, że najpierw uruchomiłeś program w C++!")
    exit(1)

# Mapowanie stylów dla scenariuszy (różne symbole/markery)
scenarios = {
    'Uniform': {'marker': 'o', 'suffix': ' (Ruch Losowy)'},
    'Sorted':  {'marker': 's', 'suffix': ' (Najgorszy Przypadek)'},
    'Burst':   {'marker': '^', 'suffix': ' (Atak DDoS)'}
}

# Unikalne kolory dla każdej kombinacji, żeby wykres był czytelny
colors = {
    ('Tablica', 'Uniform'): '#e74c3c',  # Czerwony
    ('Tablica', 'Sorted'):  # Ciemnoczerwony
    '#962d22',  
    ('Tablica', 'Burst'):   '#e67e22',  # Pomarańczowy
    ('Kopiec', 'Uniform'):  '#2ecc71',  # Jasnozielony
    ('Kopiec', 'Sorted'):   '#16a085',  # Morska zieleń
    ('Kopiec', 'Burst'):    '#2980b9'   # Niebieski
}

# 3. Funkcja generująca wykres zbiorczy
def generate_combined_plot(is_log_log=False):
    plt.figure(figsize=(11, 7))
    
    # Rysujemy linie dla każdego scenariusza po kolei
    for scenario, style in scenarios.items():
        scenario_data = df[df['Scenariusz'] == scenario]
        if scenario_data.empty:
            continue
            
        sizes = scenario_data['Rozmiar']
        time_array_ms = scenario_data['Czas_Tablicy'] / 1000
        time_heap_ms = scenario_data['Czas_Kopca'] / 1000
        
        # Linia dla Tablicy (Linia ciągła)
        plt.plot(sizes, time_array_ms, 
                 marker=style['marker'], markersize=8, linewidth=2,
                 color=colors[('Tablica', scenario)], 
                 label=f"Tablica{style['suffix']}")
        
        # Linia dla Kopca (Linia przerywana dla odróżnienia struktur)
        plt.plot(sizes, time_heap_ms, 
                 marker=style['marker'], markersize=8, linewidth=2, linestyle='--',
                 color=colors[('Kopiec', scenario)], 
                 label=f"Kopiec{style['suffix']}")
        
    # Dobieranie ustawień osi i opisów
    plt.xlabel('Liczba pakietów w kolejce (N)', fontsize=11, labelpad=10)
    plt.ylabel('Całkowity czas przetwarzania [ms]', fontsize=11, labelpad=10)
    plt.grid(True, linestyle='--', alpha=0.5, which="both")
    
    if is_log_log:
        plt.xscale('log')
        plt.yscale('log')
        plt.title('Porównanie Wydajności Algorytmów QoS (Skala LOG-LOG)', fontsize=13, fontweight='bold', pad=15)
        filename = 'wykres_zbiorczy_loglog.png'
        plt.legend(fontsize=9, loc='lower right') # W log-log na dole po prawej jest pusto
    else:
        plt.ticklabel_format(style='plain', axis='x')
        plt.title('Porównanie Wydajności Algorytmów QoS (Skala Liniowa)', fontsize=13, fontweight='bold', pad=15)
        filename = 'wykres_zbiorczy_liniowy.png'
        plt.legend(fontsize=9, loc='upper left') # W liniowym u góry po lewej jest najbezpieczniej
        
    # Zapis pliku
    save_path = os.path.join(plots_dir, filename)
    plt.savefig(save_path, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"-> Pomyślnie wygenerowano: results/plots/{filename}")

# Odpalenie generatora dla obu skal
print("Uruchamianie analizy graficznej...")
generate_combined_plot(is_log_log=False)
generate_combined_plot(is_log_log=True)
print("Wykresy są gotowe do wklejenia do sprawozdania!")