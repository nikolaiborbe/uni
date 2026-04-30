# OOP-progresjon

Dette er en enkel oversikt over progresjon på del 1 og del 2.

## Legg til ny prøve

Åpne `prover.csv` og legg til en ny linje nederst:

```csv
dato,prove,del1,del2,notat
2026-05-01,25V,48,42,"Kort kommentar"
```

`del1` og `del2` er poeng av 60.

## Lag nytt plott

Kjør fra denne mappen:

```sh
python3 plot_progresjon.py
```

Scriptet lager:

- `progresjon.svg`
- `progresjon_oppsummering.csv`
