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

== Løsningsforslag

Vi har to ligninger,

$
  v'' = 1/epsilon (v(y'-1) + v'y), quad v(0) = 1, quad v(1) = 1
$ <eq:løsn_2a>

$
  y'' = 1/epsilon (y y'-y), quad y(a) = alpha, quad y'(a) = s
$ <eq:løsn_3a>

Vi skriver om disse til et førsteordens likningssystem som vi senere kan bruke for å finne en løsning,

$
  bold(y) = vec(y_1, y_2, y_3, y_4) = vec(y, y', v, v')
$ <eq:likningsystemet>

og om vi skriver om @eq:løsn_3a[] og @eq:løsn_2a[] med bruk av $y_1 : y_4$ (denne notasjonen betyr "$y_1$ opp til og med $y_4$") får vi,

#set math.equation(numbering: none)
$
  bold(y') = vec(y', y'', v', v'') = vec(y_2, epsilon^(-1) (y_1 y_2 - y_1), y_4, epsilon^(-1) (y_3(y_2 - 1) + y_4 y_1))
$

Vi forsikrer oss om at disse løser $bold(y_0) = (1, s, 0, 1)^T$. $y_1(0)$ og $y_2(0)$ kan vi se at ble oppgitt fra initialbetingelsene $y(0) = 1$ og $y'(a) = s$. Siden $v(x;s) := partial/(partial S) y(x;s)$ ser vi også at $partial/(partial S) y(0; s) = 0$, og $v' = partial/(partial S) partial/(partial x) y(0; s) = partial/(partial S) s = 1$. Så initialbetingelsene $bold(y_0)$ stemmer.
$bold("Note:")$ dette er trolig litt feil—i alle fall upresist.

== In this paper
as shown in @eq:løsn_3a[]
#lorem(70)

#figure(rect(width: 4cm, height: 3cm), caption: shortcap(
  [A short caption of the image],
  [#lorem(30)],
))

#lorem(20)

=== Contributions
#lorem(40)

#lorem(40)

= Related Work
#balance(columns(2, [#lorem(200)]))

$
  y = k x + d
$
#lorem(50)

// Example of a custom table
#figure(
  ctable(cols: "l|cr", [A], [B], [C], ..range(1, 16).map(str)),
  caption: shortcap(
    "Short caption",
    "This is a custom table",
  ),
)

#colbreak()
#show: appendix.with(title: "Appendix")

= Appendix 1
#lorem(35)

== Some more details
#lorem(20)

#fig-outline()
#tab-outline()
