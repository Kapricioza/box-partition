# Box Partition

Program do generowania i wizualizacji partycji prostopadłościanu (box-a) na mniejsze bloki.

##  Opis

**Box Partition** to aplikacja składająca się z:
- **Backend C++**: Program optymalizacyjny generujący wszystkie możliwe partycje prostopadłościanu o wymiarach m×n×k
- **Serwer Node.js**: API Express, które uruchamia program C++ i serwuje interfejs webowy
- **Frontend Web**: Interaktywna wizualizacja 3D partycji za pomocą Three.js

## Zasady partycjonowania

Multizbiór: Partycja to multizbiór klocków. Dwa ułożenia są takie same, jeśli zestaw klocków jest identyczny. * Rotacja: Klocek a×b×c to ten sam obiekt co b×a×c czy c×b×a. * Weryfikacja: Każda partycja musi spełniać warunek objętościowy (∑Vi​=mnk) oraz posiadać fizyczne ułożenie .

##  Wymagania

Przed uruchomieniem upewnij się, że masz zainstalowane:
- **Node.js** (v14+) - [Pobierz tutaj](https://nodejs.org/)
- **C++ Compiler** (MSVC, GCC lub Clang)


##  Instalacja

### Krok 1: Klonuj repozytorium
```bash
git clone https://github.com/Kapricioza/box-partition
cd box-partition
```

### Krok 2: Zainstaluj zależności Node.js
```bash
npm install
```

### Krok 3: Skompiluj program C++

#### Opcja A: Automatycznie (na Windows z VS Code)
```bash
# Otwórz projekt w VS Code i uruchom task build
# Ctrl+Shift+B → wybierz "C/C++: cl.exe kompiluj wszystkie pliki"
```

#### Opcja B: Ręcznie z wiersza poleceń (Windows)
```bash
cd source
cl.exe /Zi /EHsc /nologo /Fe.. \bin\main.exe main.cpp solver.cpp exporter.cpp /I.. \includes
cd ..
```

#### Opcja C: Linux/Mac (GCC)
```bash
cd source
g++ -o ../bin/main main.cpp solver.cpp exporter.cpp -I../includes -std=c++17
cd ..
```

##  Uruchomienie

### Uruchom serwer
```bash
node server.js
```

Serwer uruchomi się na `http://localhost:3000`

### W przeglądarce
1. Otwórz `http://localhost:3000`
2. Wprowadź wymiary prostopadłościanu (m, n, k)
3. Kliknij **GENERUJ NOWE**
4. Czekaj na wygenerowanie partycji
5. Nawiguj strzałkami i przeglądaj wizualizację 3D

##  Sterowanie 3D

- **Mysz**: Obracaj model (lewy przycisk) i przybliż/oddal (scroll)
- **Suwaki**: Przecinaj bryłę wzdłuż osi X, Y, Z

##  Dane wyjściowe

Wyniki są zapisywane w pliku `web/data/results.json` z informacjami o:
- Wymiarach prostopadłościanu
- Liczbie znalezionych partycji
- Układzie bloków dla każdej partycji

##  Uwagi

- Większe wartości (m, n, k) mogą znacząco zwiększyć czas obliczeń
- Program przechowuje wszystkie partycje w pamięci
- Kompilacja wymaga zainstalowanego kompilatora C++

##  Struktura projektu

```
box-partition/
├── bin/                    
│   └── main.exe
├── includes/              
│   ├── exporter.h
│   ├── solver.h
│   └── types.h
├── source/               
│   ├── main.cpp
│   ├── solver.cpp
│   └── exporter.cpp
├── web/                  
│   ├── index.html
│   ├── style.css
│   ├── js/
│   │   └── main.js
│   └── data/
│       └── results.json
├── server.js             
├── package.json
└── README.md
```

##  Licencja

Projekt dostępny na licencji MIT
