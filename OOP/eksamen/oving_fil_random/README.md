# Minioppgavesett: filskriving, fillesing og tilfeldige tall

Dette er et lite øvingssett laget i samme stil som tidligere TDT4102-eksamensoppgaver. Oppgavene er isolert til:

- lese fra fil med `std::ifstream`
- skrive til fil med `std::ofstream`
- parse enkle linjer med `std::stringstream`
- generere tilfeldige heltall med `<random>`
- bruke tilfeldige tall til å lage data som kan skrives til fil

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

## Når du har løst alt

Kjør programmet. Det vil teste oppgavene med `assert` og skrive en kort status i terminalen.
