# Minioppgavesett: filskriving, fillesing og tilfeldige tall

Dette er et lite øvingssett laget i samme stil som tidligere TDT4102-eksamensoppgaver. Oppgavene er isolert til:

- lese fra fil med `std::ifstream`
- skrive til fil med `std::ofstream`
- parse enkle linjer med `std::stringstream`
- generere tilfeldige heltall med `<random>`
- bruke tilfeldige tall til å lage data som kan skrives til fil
- lage en enkel klasse med constructor, destructor, copy constructor og `operator<<`

Du skal skrive svarene i `src/Tasks.cpp` mellom `// BEGIN: Tn` og `// END: Tn`.

## Bygg og kjør

Fra denne mappa:

```bash
cmake --preset debug
cmake --build --preset debug
./build/oving_fil_random
```

`compile_commands.json` blir generert i `build/`, og `.vscode/settings.json` peker dit. Det gir IntelliSense/type hinting i VS Code med enten C/C++ extension eller clangd.

## Oppgavene

### T1: Lese hele fila

Implementer `read_file`. Funksjonen skal åpne fila gitt som parameter og returnere hele innholdet som én `std::string`.

Krav:

- bruk `std::ifstream`
- kast `std::runtime_error` hvis fila ikke kan åpnes
- behold linjeskift i fila

### T2: Lese målinger fra fil

Implementer `read_measurements`. Fila `data/measurements.txt` har én måling per linje:

```text
temperature 18.5
humidity 41.0
```

Funksjonen skal returnere en `std::vector<Measurement>`.

Krav:

- ignorer tomme linjer
- bruk `std::stringstream` eller `operator>>` på filstrømmen
- kast `std::runtime_error` hvis fila ikke kan åpnes

### T3: Skrive rapport til fil

Implementer `write_report`. Funksjonen skal skrive målinger til fil på formen:

```text
temperature:18.5
humidity:41
```

Krav:

- bruk `std::ofstream`
- kast `std::runtime_error` hvis fila ikke kan åpnes
- skriv én måling per linje
- returner `true` når skrivingen er ferdig

### T4: Tilfeldig heltall

Implementer `random_int`. Funksjonen skal returnere et tilfeldig heltall i intervallet `[min, max]`.

Krav:

- bruk `<random>`
- både `min` og `max` skal kunne trekkes
- kast `std::invalid_argument` hvis `min > max`

### T5: Generere tilfeldige målinger

Implementer `generate_random_measurements`.

Funksjonen får inn:

- navn på måling, for eksempel `"temperature"`
- antall målinger
- minimumsverdi
- maksimumsverdi

Den skal returnere en vektor med `count` målinger hvor verdiene er tilfeldige heltall konvertert til `double`.

Krav:

- bruk `random_int`
- kast `std::invalid_argument` hvis `count < 0`
- alle målinger skal ha navnet som ble sendt inn

### T6: Måleserie som klasse

Implementer klassen `MeasurementSeries`. Klassen skal representere en serie med måleverdier, for eksempel temperaturmålinger.

Klassen er deklarert i `src/Tasks.h`:

```cpp
class MeasurementSeries {
public:
    MeasurementSeries(const std::string& name, const std::vector<double>& values);
    ~MeasurementSeries();
    MeasurementSeries(const MeasurementSeries& other);

    const std::string& name() const;
    std::size_t size() const;
    double at(std::size_t index) const;
    void set(std::size_t index, double value);

private:
    std::string name_;
    double* values_;
    std::size_t count_;

    friend std::ostream& operator<<(std::ostream& os, const MeasurementSeries& series);
};
```

Du skal implementere constructor, destructor, copy constructor og `operator<<` i `src/Tasks.cpp`.

#### T6A: Constructor

Implementer constructoren:

```cpp
MeasurementSeries::MeasurementSeries(const std::string& name, const std::vector<double>& values)
```

Constructoren skal:

- lagre `name` i `name_`
- lagre antall verdier i `count_`
- allokere en dynamisk array med `new double[count_]`
- kopiere alle verdiene fra `values` inn i den dynamiske arrayen

Hvis `values` er tom, skal `count_` bli `0` og `values_` være `nullptr`.

#### T6B: Destructor

Implementer destructoren:

```cpp
MeasurementSeries::~MeasurementSeries()
```

Destructoren skal frigjøre arrayen som ble allokert i constructoren.

Krav:

- bruk `delete[]`
- det skal være trygt å destruere et objekt der `values_ == nullptr`

#### T6C: Copy Constructor

Implementer copy constructoren:

```cpp
MeasurementSeries::MeasurementSeries(const MeasurementSeries& other)
```

Copy constructoren skal lage en dyp kopi.

Krav:

- kopier `name_`
- kopier `count_`
- alloker ny egen array for kopien
- kopier alle verdiene fra `other`
- kopien og originalen skal ikke dele samme array

Dette skal fungere:

```cpp
MeasurementSeries original{"temperature", {18.5, 19.25}};
MeasurementSeries copy{original};
original.set(0, -100.0);

// copy.at(0) skal fortsatt være 18.5
```

#### T6D: Utskriftsoperator

Implementer `operator<<`:

```cpp
std::ostream& operator<<(std::ostream& os, const MeasurementSeries& series)
```

Operatoren skal skrive måleserien på denne formen:

```text
temperature: 18.5, 19.25, 20
```

Hvis serien ikke har noen verdier, skal bare navnet og kolon skrives:

```text
humidity:
```

Krav:

- skriv til streamen `os`, ikke direkte til `std::cout`
- returner `os`
- ikke skriv linjeskift til slutt

## Når du har løst alt

Kjør programmet. Det vil teste oppgavene med `assert` og skrive en kort status i terminalen.
