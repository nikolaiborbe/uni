/*
 * The Rubber Article Template.
 *
 * Here is a quick run-down of the template.
 * Some example content has been added for you to see what the template looks like and how it works.
 * Some features of this template are explained here, so you might want to check it out.
 */

#import "@preview/rubber-article:0.5.2": *

// Layout and styling
#show: article.with(
  cols: none, // Tip: use #colbreak() instead of #pagebreak() to seamlessly toggle columns
  eq-chapterwise: true,
  eq-numbering: "(1.1)",
  header-display: true,
  header-title: "Skytemetoden",
  lang: "no",
  page-margins: 1.75in,
  page-paper: "us-letter",
)

#show link: set text(fill: blue)
#show link: underline
 
// Frontmatter
#maketitle(
  title: "Bruk av skytemetoden til løsning av randverdiproblemer.",
  authors: ("Nikolai Grytvik Borbe",),
  date: datetime.today().display("[day]. [month repr:long] [year]"),
)

#image("assets/D.png")

#pagebreak()

// Actual Content starts here.
// REMOVE BELOW THIS LINE TO START YOUR OWN CONTENT.
= Introduction

Skytemetoden kan bli brukt til å gjette løsninger, se hvor godt de stemmer, for å så bruke denne informasjonen til et nytt, og bedre, gjett.

== Bakgrunn

Vi skal forsøke å løse randverdiproblemet,

$
  epsilon y'' = y y' - y, quad y(0) = 1, quad y(1) = -1
$ <eq:randverdi_prob>

ved hjelp av en IVP-løser og Newtoniterasjon (skytemetoden). Vi har to ligninger,

$
  v'' = 1/epsilon (v(y'-1) + v'y), quad v(0) = 0, quad v'(0) = 1
$ <eq:løsn_2a>

$
  y'' = 1/epsilon (y y'-y), quad y(a) = alpha, quad y'(a) = s
$ <eq:løsn_3a>

her er @eq:løsn_3a[] initialverdiproblemet til @eq:randverdi_prob[], og @eq:løsn_2a[] variasjonslikningen. Vi skriver om disse til et førsteordens likningssystem som vi senere kan bruke for å finne en løsning,

$
  bold(y) = vec(y_1, y_2, y_3, y_4) = vec(y, y', v, v')
$ <eq:likningsystemet>

og om vi skriver om @eq:løsn_3a[] og @eq:løsn_2a[] med bruk av $y_1,..., y_4$ får vi,

#set math.equation(numbering: none)
$
  bold(y') = vec(y', y'', v', v'') = vec(y_2, epsilon^(-1) (y_1 y_2 - y_1), y_4, epsilon^(-1) (y_3(y_2 - 1) + y_4 y_1))
$

Vi forsikrer oss om at initialbetingelsene $bold(y_0) = (1, s, 0, 1)^T$. $y_1(0)$ og $y_2(0)$ oppfylles. Da kan vi se at ble oppgitt fra initialbetingelsene $y(0) = 1$ og $y'(a) = s$. Siden $v(x;s) := partial/(partial S) y(x;s)$ ser vi også at $partial/(partial S) y(0; s) = 0$, og $v' = partial/(partial S) partial/(partial x) y(0; s) = partial/(partial S) s = 1$. Så initialbetingelsene $bold(y_0)$ stemmer.


== Numerisk løsning ved skytemetoden

Vi bruker `scipy.integrate.solve_ivp`, og plotter løsningen,

#image("assets/diff_epsilon.png")

Vi får en svært god løsning for $x$ etter bare 2 steg, altså er BVP-et vårt relativt enkelt å løse med $epsilon = 1$. Om vi videre prøver å bruke mindre epsilon vil ikke Skytemetoden lenger fungere, det blir for mange mulige løsninger og NM blir svært stor svært fort.
Vi kan få en bedre intuisjon av hvorfor vi ikke greier å numerisk løse @eq:likningsystemet[] om vi visualiserer problemet i faseplott,

#image("assets/faseplott.png")

kan vi klart se at det fort blir svært vanskelig å finne løsninger for $epsilon$ når $epsilon arrow 0$.

#show: appendix.with(title: "Appendix")

Kodefiler kan bli funnet #link("https://github.com/nikolaiborbe/uni/tree/main/VITBER/ovinger/O3")[her].

