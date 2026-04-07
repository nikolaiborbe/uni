// TMA4320 Exam Preparation Checklist — Based on 2026 Forelesningsplan
#set document(title: "TMA4320 Eksamensforberedelse V2026", author: "")
#set page(margin: (x: 2cm, y: 1.8cm), numbering: "1 / 1")
#set text(font: "New Computer Modern", size: 10.5pt, lang: "nb")
#set heading(numbering: "1.1")
#set par(justify: true)

#let checkbox() = box(width: 10pt, height: 10pt, stroke: 0.5pt)
#let task(body) = {
  grid(columns: (14pt, 1fr), column-gutter: 4pt, checkbox(), body)
}

#let prio(level) = {
  let (col, label) = if level == 1 { (rgb("#c0392b"), "KRITISK") }
    else if level == 2 { (rgb("#e67e22"), "HØY") }
    else if level == 3 { (rgb("#2980b9"), "MIDDELS") }
    else { (rgb("#7f8c8d"), "LAV") }
  box(fill: col, radius: 3pt, inset: (x: 5pt, y: 2pt))[#text(fill: white, size: 8pt, weight: "bold")[#label]]
}

#let freq(n) = {
  text(size: 8pt, fill: luma(100))[ (på #n av 4 nylige eksamener)]
}

#let topic-box(priority, title, frequency, ..tasks) = {
  let items = tasks.pos()
  block(width: 100%, inset: 10pt, radius: 4pt, stroke: 0.5pt + luma(180), above: 8pt, below: 2pt)[
    #grid(columns: (auto, 1fr, auto), align: (left, left, right),
      prio(priority),
      h(6pt) + text(weight: "bold", size: 11pt)[#title],
      if frequency != none { freq(frequency) },
    )
    #v(5pt)
    #for t in items {
      task(t)
      v(2.5pt)
    }
  ]
}

// ============================================================
// TITLE
// ============================================================

#align(center)[
  #text(size: 20pt, weight: "bold")[TMA4320 Eksamensforberedelse]
  #v(2pt)
  #text(size: 13pt, fill: luma(80))[Introduksjon til vitenskapelige beregninger --- Vår 2026]
  #v(2pt)
  #text(size: 10pt, fill: luma(120))[Eksamen: 11. mai 2026, kl. 15--19 | 55% av karakter | Kalkulator + formelark]
  #v(3pt)
  #line(length: 50%, stroke: 0.5pt + luma(150))
]

#v(4pt)

#block(width: 100%, inset: 10pt, radius: 4pt, fill: rgb("#eef6ff"), stroke: 0.5pt + rgb("#b0d0f0"))[
  #text(weight: "bold")[Om dette dokumentet] \
  Basert på *forelesningsplanen 2026* (5 moduler) og analyse av 4 nylige eksamener (2022--2023). Prioritering reflekterer både forelesningsvekt og eksamenfrekvens. Pensum = alle utlagte notater + øvinger med løsningsforslag.

  #v(3pt)
  #grid(columns: 4, column-gutter: 8pt,
    [#prio(1) Kjernetema],
    [#prio(2) Viktig],
    [#prio(3) Bør kunne],
    [#prio(4) Kjenn til],
  )
]

// ============================================================
// MODULE 1: NEURAL NETWORKS & FUNCTION APPROXIMATION
// ============================================================

= Modul 1: Nevrale nettverk og funksjonsapproksimasjon #text(size: 9pt, fill: luma(100))[(uke 3--4)]

#topic-box(2, "Arkitektur og forward propagation", none,
  [Forstå strukturen: input-lag, skjulte lag (hidden layers), output-lag],
  [Definere bredde (antall neuroner per lag) og dybde (antall lag)],
  [Forward propagation: $bold(x)^((i+1)) = sigma(W_(i+1) bold(x)^((i)) + bold(b)_(i+1))$, $i = 0, dots, L-1$],
  [Kjenne aktiveringsfunksjoner: sigmoid $sigma(z) = 1/(1+e^(-z))$, ReLU, $z^2$],
  [Kunne gjennomføre forward pass for hånd med gitte vekter og bias],
)

#topic-box(2, "Trening og kostfunksjon", none,
  [Definere kostfunksjon (objektfunksjon): $C = 1/(2m) sum_(i=1)^m ||y_i - hat(y)_i||^2$],
  [Forstå supervised learning: treningsdata $(arrow(x)_i, arrow(y)_i)$, $i = 1, dots, m$],
  [Parametre $Theta = [W_1, b_1, W_2, b_2, dots, W_L, b_L]$ som optimaliseres],
  [Forstå prinsippet bak gradientbasert optimalisering (minimere $C$ mhp $Theta$)],
  [Kjenne til Physics-Informed Neural Networks (PINN) fra Prosjekt 1],
)

#topic-box(3, "Differansemetoder for PDE-er", none,
  [Forstå finite differanser: $f'(x) approx (f(x+h) - f(x-h))/(2h)$ (sentral)],
  [Diskretisere en PDE med differansemetoder],
  [Sette opp det resulterende lineære/ikke-lineære systemet],
)

// ============================================================
// MODULE 2: NUMERICAL ODEs
// ============================================================

= Modul 2: Numerisk løsning av ODE-er #text(size: 9pt, fill: luma(100))[(uke 7--8)]

#topic-box(1, "Eulers metode og forbedret Euler (Heun)", 4,
  [Eulers metode: $y_(n+1) = y_n + h f(t_n, y_n)$ --- gjennomfør steg for hånd],
  [Forbedret Euler (Heuns metode / eksplisitt trapes): \
   $k_1 = f(t_n, y_n)$, $k_2 = f(t_(n+1), y_n + h k_1)$, $y_(n+1) = y_n + h/2(k_1 + k_2)$],
  [Vite at Euler har orden 1, forbedret Euler orden 2],
)

#topic-box(1, "Systemer og omskriving av høyere ordens ODE", 3,
  [Systemnotasjon: $bold(y)'(t) = bold(f)(t, bold(y))$, $bold(y) in RR^m$],
  [Omskrive 2. ordens: $u'' = g(t,u,u')$ $=>$ sett $v_1=u, v_2=u'$],
  [Omskrive 3. ordens: sett $v_1=u, v_2=u', v_3=u''$],
  [Sette opp initialbetingelser for det nye systemet],
  [Kjenne Lipschitz-betingelse og Teorem 4.1 (eksistens/entydighet)],
  [Forstå autonome systemer: $bold(y)' = bold(f)(bold(y))$ (ingen eksplisitt $t$-avhengighet)],
)

#topic-box(1, "Runge--Kutta-metoder og Butcher-tablå", 4,
  [Generell form: $k_i = f(t_n + c_i h, y_n + h sum a_(i j) k_j)$, $y_(n+1) = y_n + h sum b_i k_i$],
  [Butcher-tablå: lese av $c_i$, $a_(i j)$, $b_i$ fra tablå],
  [Kjenne klassisk RK4: $y_(n+1) = y_n + h/6(k_1 + 2k_2 + 2k_3 + k_4)$],
  [Gjennomføre et komplett RK-steg for hånd (beregne alle $k_i$-verdier)],
  [Ordenbetingelser: $sum b_i = 1$ (orden 1), $sum b_i c_i = 1/2$ (orden 2), etc.],
  [Bestemme orden av en gitt RK-metode ved å sjekke betingelsene],
)

#topic-box(1, "Lokal og global avbruddsfeil, konvergens", 3,
  [Lokal avbruddsfeil (LTE): $tau_(n+1) = Psi_(h,f)(y_n) - phi.alt_(h,f)(y_n)$],
  [Global feil: $E_n = y_n - y(t_n)$],
  [LTE for Euler: $||tau_(n+1)|| <= 1/2 h^2 M$ der $||y''(t)|| <= M$],
  [Global feil for Euler: $||E_n|| <= C(D,L) dot h$ (orden 1)],
  [Forstå at global feil $!=$ sum av lokale feil (feilpropagering)],
  [Konvergensorden $p$: LTE $= O(h^(p+1))$ $=>$ global feil $= O(h^p)$],
)

#topic-box(1, "Skrittlengdekontroll (adaptiv)", 3,
  [Innebygd par (embedded pair): to metoder med orden $p$ og $hat(p)$, deler $k_i$-verdier],
  [Feilestimat: $"est"_(n+1) = hat(y)_(n+1) - y_(n+1)$],
  [Aksepter steg hvis $||"est"_(n+1)|| <= "tol"$, ellers forkast],
  [Steglengdejustering: $h_n = alpha ("tol" / ||"est"_n||)^(1\/hat(p)) h_(n-1)$],
  [Pessimistfaktor (safety factor): $alpha approx 0.8$--$0.9$],
  [Kjenne eksempler: (Forbedret Euler, Euler) = $2(1)$-par, Bogacki--Shampine = $3(2)$-par],
)

#topic-box(1, "Stabilitet av Runge--Kutta-metoder", 4,
  [Testproblemet: $y' = lambda y$, $lambda in CC$ --- eksakt løsning $y(t) = e^(lambda t) y_0$],
  [Stabilitetsfunksjon: anvend metode på testproblemet $=>$ $y_(n+1) = R(z) y_n$, $z = h lambda$],
  [Stabilitetsområde: $S = {z in CC : |R(z)| <= 1}$],
  [Euler: $R(z) = 1+z$, stabilitetsområde er sirkelskive $|1+z| <= 1$],
  [Heun: $R(z) = 1 + z + 1/2 z^2$],
  [RK4: $R(z) = 1 + z + 1/2 z^2 + 1/6 z^3 + 1/24 z^4$],
  [Bestemme maks steglengde $h_"max"$ for stabilitet gitt $lambda$ (egenverdier)],
  [Forklare stabil vs. ustabil løsning fra figurer med ulike $h$],
)

#topic-box(1, "Implisitte metoder og stive ligninger", 3,
  [Baklengs Euler: $y_(n+1) = y_n + h f(t_(n+1), y_(n+1))$ --- implisitt!],
  [Baklengs Euler: $R(z) = 1/(1-z)$, stabilitetsområde $= CC \\ {|z-1| < 1}$ --- inneholder $CC^-$],
  [Trapesmetoden: $y_(n+1) = y_n + h/2(f(t_n,y_n) + f(t_(n+1),y_(n+1)))$],
  [Trapes: $R(z) = (1 + z\/2)/(1 - z\/2)$, stabilitetsområde $= CC^-$ (A-stabil)],
  [Implisitt midtpunktmetode og dens egenskaper],
  [A-stabilitet: $CC^- subset S$ --- metoden er stabil for alle $"Re"(lambda) < 0$ uansett $h$],
  [Stive ligninger: egenverdier med svært ulik $|"Re"(lambda)|$ --- krever A-stabile metoder],
  [Løse ikkelineære ligninger i hvert steg med Newton / fikspunktiterasjon],
  [Jacobi-matrisen ved Newton: $D F(x) = I - h D f(x)$],
)

// ============================================================
// MODULE 3: BOUNDARY VALUE PROBLEMS
// ============================================================

= Modul 3: Topunkts randverdiproblemer #text(size: 9pt, fill: luma(100))[(uke 11)]

#topic-box(2, "Formulering av randverdiproblemer (BVP)", none,
  [BVP: $y' = f(x, y)$, $y in RR^n$, med randbetingelse $A dot y(a) + B dot y(b) = c$],
  [Forstå forskjellen fra initialverdiproblemer (IVP)],
  [Eksistens/entydighet er mer komplisert for BVP enn IVP],
  [Kunne gi eksempler der BVP har unik, uendelig mange, eller ingen løsning],
)

#topic-box(2, "Skytemetoden (shooting method)", none,
  [Enkel versjon: BVP $w'' = f(x,w,w')$, $w(a)=alpha$, $w(b)=beta$],
  [Formuler som IVP med ukjent $s$: $w(a) = alpha$, $w'(a) = s$],
  [Definer $F(s) = w(b; s) - beta$, finn $s$ slik at $F(s) = 0$],
  [Bruk Newton: $s^((i+1)) = s^((i)) - F(s^((i))) / F'(s^((i)))$],
  [For hvert Newton-steg: løs IVP med RK-metode for å finne $F(s^((i)))$],
  [Generell skytemetode: diskretiser $[a,b]$ i $m$ punkt, løs stort system med Newton],
  [Jacobi-matrisen $D F$ har blokk-struktur som kan utnyttes],
)

// ============================================================
// MODULE 4: NUMERICAL LINEAR ALGEBRA
// ============================================================

= Modul 4: Numerisk lineær algebra #text(size: 9pt, fill: luma(100))[(uke 12--13)]

#topic-box(1, "Gausseliminasjon og LU-faktorisering", 4,
  [Gausseliminasjon: reduser $A$ til øvre-triangulær $U$ med radoperasjoner],
  [Multiplikatorene $l_(i k)$ definerer nedre-triangulær $L$ med 1 på diag: $A = L U$],
  [Pivotering: radbytting for numerisk stabilitet $=>$ $P A = L U$],
  [Skalert delvis pivotering: velg pivotrad basert på skalerte elementer],
  [Løse $A x = b$ via $L U$: (1) $L c = P b$ (foroversubst.), (2) $U x = c$ (bakoversubst.)],
  [Kompleksitet: $O(n^3)$ for faktorisering, $O(n^2)$ for substitusjon],
  [Gjennomføre LU-faktorisering for hånd for $3 times 3$ eller $4 times 4$ matriser],
)

#topic-box(1, "Cholesky-faktorisering", 2,
  [SPD-matrise (symmetrisk positivt definitt): $A = A^top$ og $x^top A x > 0$ for $x != 0$],
  [Cholesky: $A = W W^top$ der $W$ er nedre-triangulær --- bevis via $L D L^top$],
  [Algoritme: $w_(i j) = (a_(i j) - sum_(k=1)^(j-1) w_(i k) w_(j k)) / w_(j j)$ og $w_(i i) = sqrt(a_(i i) - sum_(k=1)^(i-1) w_(i k)^2)$],
  [Gjennomføre Cholesky for hånd for $2 times 2$ og $3 times 3$ matriser],
  [Kompleksitet: $1/6 n^3$ (halvert sammenlignet med LU)],
  [Pivotering ikke nødvendig for SPD-matriser],
)

#topic-box(1, "Vektornormer og matrisenormer", 3,
  [Vektornormer: $||x||_1 = sum |x_i|$, $||x||_2 = sqrt(sum x_i^2)$, $||x||_infinity = max |x_i|$],
  [Normarksiomer: (1) $||x|| >= 0$, (2) $||x|| = 0 <=> x = 0$, (3) $||alpha x|| = |alpha| ||x||$, (4) trekantulikheten],
  [Matrisenormer: samme aksiomer + submultiplikativitet $||A B|| <= ||A|| ||B||$],
  [Naturlig (tilordnet) matrisenorm: $||A||_m = max_(x != 0) (||A x||_v) / (||x||_v)$],
  [Kompatibilitet: $||A x||_v <= ||A||_m ||x||_v$],
  [$||A||_1 = max_j sum_i |a_(i j)|$ (maks kolonnesum av absoluttverider)],
  [$||A||_infinity = max_i sum_j |a_(i j)|$ (maks radsum)],
  [Frobeniusnormen: $||A||_F = (sum_(i,j) |a_(i j)|^2)^(1/2)$],
)

#topic-box(1, "Kondisjonstall og feilanalyse", 3,
  [Kondisjonstall: $kappa(A) = ||A|| dot ||A^(-1)||$],
  [Feilulikhet: $||delta x|| / ||x|| <= kappa(A) dot ||delta b|| / ||b||$],
  [Velkondisjonert: $kappa(A)$ liten --- illkondisjonert: $kappa(A)$ stor],
  [Beregne $kappa_1(A)$ og $kappa_infinity (A)$ for gitte matriser],
  [Kjenne til Hilbert-matrisen som eksempel på illkondisjonert system],
)

#topic-box(2, "Singulærverdidekomposisjon (SVD)", 2,
  [Definisjon: $A = U Sigma V^top$, $U in RR^(m times m)$ ortogonal, $V in RR^(n times n)$ ortogonal, $Sigma$ diagonal],
  [Singulærverdier $sigma_1 >= sigma_2 >= dots >= 0$ på diagonalen av $Sigma$],
  [$U$-kolonner = ortonormale, $V$-kolonner = ortonormale],
  [Verifisere om en gitt faktorisering er gyldig SVD (sjekk alle krav)],
  [Beregne SVD for enkle matriser via $A^top A$ (egenverdier $= sigma_i^2$)],
)

#topic-box(3, "Iterative metoder", none,
  [Direkte metoder ($O(n^3)$) vs. iterative metoder for store systemer],
  [Jacobi-metoden: $x_i^((k+1)) = 1/a_(i i)(b_i - sum_(j!=i) a_(i j) x_j^((k)))$],
  [Forstå konvergensbetingelser og når iterative metoder er å foretrekke],
)

// ============================================================
// MODULE 5: PROJECTS (examinable content)
// ============================================================

= Modul 5: Prosjektrelatert stoff #text(size: 9pt, fill: luma(100))[(eksamen kan inneholde spørsmål fra prosjektene)]

#topic-box(3, "Prosjekt 1: Matematikk --- PINN / Temperaturmodell", none,
  [Physics-Informed Neural Networks: bruk NN til å løse differensialligninger],
  [JAX og automatisk differensiering (autograd)],
  [Implementere forward pass, trening med gradientnedstigning],
)

#topic-box(3, "Prosjekt 2: Biofysikk --- Motorproteiner", none,
  [Modellering med ODE-systemer],
  [Numerisk løsning med RK-metoder og skrittlengdekontroll],
)

#topic-box(3, "Prosjekt 3: Fysikk --- Josephson-effekten", none,
  [Randverdiproblemer i fysisk kontekst],
  [Skytemetoden anvendt på konkret problem],
)

// ============================================================
// EXAM STRATEGY
// ============================================================

= Eksamenstrategi

#block(width: 100%, inset: 10pt, radius: 4pt, fill: rgb("#fef9e7"), stroke: 0.5pt + rgb("#f0e0a0"))[
  #text(weight: "bold", size: 11pt)[Forventet oppgavefordeling basert på forelesninger + eksamener:]
  #v(3pt)
  #table(
    columns: (1fr, auto, auto),
    stroke: 0.5pt + luma(200),
    inset: 5pt,
    align: (left, center, center),
    table.header([*Tema*], [*Eksamenfrekvens*], [*Typisk vekt*]),
    [Runge--Kutta (tablå, steg for hånd, orden)], [4/4], [15--20%],
    [Stabilitet (stabilitetsområder, A-stabilitet)], [4/4], [10--15%],
    [LU-faktorisering / Gausseliminasjon], [4/4], [10--15%],
    [Lokal/global feil + adaptiv steglengde], [3/4], [10--15%],
    [Omskriving av ODE til system], [3/4], [5--10%],
    [Kondisjonstall / matrisenormer], [3/4], [10--15%],
    [Implisitte metoder (trapes, baklengs Euler)], [3/4], [10--15%],
    [SVD (definisjon, verifisering)], [2/4], [10--15%],
    [Cholesky-faktorisering], [2/4], [5--10%],
    [Nevrale nettverk, BVP, skytemetoden], [Nytt], [???],
  )
]

#v(6pt)

#block(width: 100%, inset: 10pt, radius: 4pt, fill: rgb("#f0faf0"), stroke: 0.5pt + rgb("#a0d0a0"))[
  #text(weight: "bold", size: 11pt)[Anbefalt forberedelsesplan:]
  #v(3pt)
  + *Fase 1 (ODE --- størst vekt):* Euler, Heun, RK4, Butcher-tablå, steg for hånd, ordenbetingelser. Stabilitet: testproblem, stabilitetsområder, $h_"max"$. LTE/global feil. Skrittlengdekontroll. Implisitte metoder + A-stabilitet.
  + *Fase 2 (Lineær algebra):* LU med pivotering, Cholesky, normer, kondisjonstall, SVD.
  + *Fase 3 (Nye temaer):* Nevrale nettverk (forward pass, kostfunksjon). BVP og skytemetoden.
  + *Fase 4 (Prøveeksamen):* Gjennomfør mai 2023 og august 2023 under tidspress (4 timer).

  #v(3pt)
  *Tips:* Øv spesielt på å *beregne for hånd* --- RK-steg, LU-faktorisering, Cholesky, stabilitetsfunksjoner. Dette er det som tar tid på eksamen.
]

#v(6pt)

= Tidligere eksamener

#table(
  columns: (auto, 1fr, auto),
  stroke: 0.5pt + luma(200),
  inset: 6pt,
  align: (center, left, center),
  table.header([*Gjort?*], [*Eksamen*], [*Relevans for 2026*]),
  checkbox(), [Mai 2023 -- Teori + Programmering], [#text(fill: rgb("#27ae60"), weight: "bold")[Svært relevant]],
  checkbox(), [August 2023 -- Teori + Programmering], [#text(fill: rgb("#27ae60"), weight: "bold")[Svært relevant]],
  checkbox(), [Mai 2022 -- Teori + Programmering], [#text(fill: rgb("#2980b9"))[Relevant (noe annet pensum)]],
  checkbox(), [August 2022 -- Teori + Programmering], [#text(fill: rgb("#2980b9"))[Relevant (noe annet pensum)]],
  checkbox(), [2016--2018 eksamener], [#text(fill: rgb("#e67e22"))[Delvis --- velg relevante oppgaver]],
)

#v(4pt)
#text(size: 9pt, fill: luma(120))[_NB: Kurssiden sier at mange oppgaver fra eldre eksamener ikke lenger er relevante. Konsentrer deg om 2022--2023._]
