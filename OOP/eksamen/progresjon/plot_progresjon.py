import csv
from html import escape
from pathlib import Path


ROOT = Path(__file__).resolve().parent
DATA_FILE = ROOT / "prover.csv"
SUMMARY_FILE = ROOT / "progresjon_oppsummering.csv"
PLOT_FILE = ROOT / "progresjon.svg"
MAX_PER_PART = 60


def read_rows():
    with DATA_FILE.open(newline="", encoding="utf-8") as file:
        rows = list(csv.DictReader(file))

    for index, row in enumerate(rows, start=1):
        row["nr"] = index
        row["del1"] = float(row["del1"])
        row["del2"] = float(row["del2"])
        row["total"] = row["del1"] + row["del2"]
        row["del1_pct"] = row["del1"] / MAX_PER_PART * 100
        row["del2_pct"] = row["del2"] / MAX_PER_PART * 100
        row["total_pct"] = row["total"] / (MAX_PER_PART * 2) * 100

    return rows


def write_summary(rows):
    fields = [
        "nr",
        "dato",
        "prove",
        "del1",
        "del2",
        "total",
        "del1_pct",
        "del2_pct",
        "total_pct",
        "notat",
    ]

    with SUMMARY_FILE.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=fields)
        writer.writeheader()
        for row in rows:
            writer.writerow({
                "nr": row["nr"],
                "dato": row["dato"],
                "prove": row["prove"],
                "del1": f"{row['del1']:.2f}",
                "del2": f"{row['del2']:.2f}",
                "total": f"{row['total']:.2f}",
                "del1_pct": f"{row['del1_pct']:.1f}",
                "del2_pct": f"{row['del2_pct']:.1f}",
                "total_pct": f"{row['total_pct']:.1f}",
                "notat": row["notat"],
            })


def points(rows, key, chart):
    left, top, width, height = chart
    step = width / max(len(rows) - 1, 1)
    return [
        (
            left + index * step,
            top + height - (row[key] / MAX_PER_PART * height),
        )
        for index, row in enumerate(rows)
    ]


def polyline(points_):
    return " ".join(f"{x:.1f},{y:.1f}" for x, y in points_)


def render_series(rows, key, name, color, chart, label_offset):
    series_points = points(rows, key, chart)
    svg = [f'<polyline points="{polyline(series_points)}" fill="none" stroke="{color}" stroke-width="3"/>']
    for row, (x, y) in zip(rows, series_points):
        svg.append(f'<circle cx="{x:.1f}" cy="{y:.1f}" r="5" fill="{color}"/>')
        svg.append(
            f'<text x="{x:.1f}" y="{y + label_offset:.1f}" text-anchor="middle" '
            f'font-size="12" fill="{color}">{row[key]:.1f}</text>'
        )
    svg.append(f'<circle cx="720" cy="{46 if name == "Del 1" else 70}" r="5" fill="{color}"/>')
    svg.append(f'<text x="735" y="{50 if name == "Del 1" else 74}" font-size="13">{name}</text>')
    return "\n".join(svg)


def plot(rows):
    chart = (70, 55, 690, 330)
    left, top, width, height = chart
    bottom = top + height
    right = left + width

    grid = []
    for value in range(0, MAX_PER_PART + 1, 10):
        y = bottom - value / MAX_PER_PART * height
        grid.append(f'<line x1="{left}" y1="{y:.1f}" x2="{right}" y2="{y:.1f}" stroke="#e5e7eb"/>')
        grid.append(f'<text x="{left - 12}" y="{y + 4:.1f}" text-anchor="end" font-size="12" fill="#4b5563">{value}</text>')

    step = width / max(len(rows) - 1, 1)
    labels = []
    for index, row in enumerate(rows):
        x = left + index * step
        labels.append(f'<line x1="{x:.1f}" y1="{top}" x2="{x:.1f}" y2="{bottom}" stroke="#f3f4f6"/>')
        labels.append(
            f'<text x="{x:.1f}" y="{bottom + 28}" text-anchor="middle" font-size="12" fill="#111827">'
            f'{escape(str(row["nr"]))}. {escape(row["prove"])}</text>'
        )

    average_rows = [{**row, "average": row["total"] / 2} for row in rows]
    avg_points = points(average_rows, "average", chart)

    svg = f'''<svg xmlns="http://www.w3.org/2000/svg" width="840" height="470" viewBox="0 0 840 470">
<rect width="100%" height="100%" fill="white"/>
<text x="420" y="28" text-anchor="middle" font-size="22" font-family="Arial, sans-serif" fill="#111827">OOP-progresjon: del 1 og del 2</text>
<g font-family="Arial, sans-serif">
{"".join(grid)}
{"".join(labels)}
<line x1="{left}" y1="{top}" x2="{left}" y2="{bottom}" stroke="#9ca3af"/>
<line x1="{left}" y1="{bottom}" x2="{right}" y2="{bottom}" stroke="#9ca3af"/>
<text x="20" y="230" text-anchor="middle" font-size="13" fill="#111827" transform="rotate(-90 20 230)">Poeng av 60</text>
{render_series(rows, "del1", "Del 1", "#2563eb", chart, -12)}
{render_series(rows, "del2", "Del 2", "#16a34a", chart, 20)}
<polyline points="{polyline(avg_points)}" fill="none" stroke="#7c3aed" stroke-width="3" stroke-dasharray="8 6"/>
<circle cx="720" cy="94" r="5" fill="#7c3aed"/>
<text x="735" y="98" font-size="13">Snitt</text>
</g>
</svg>
'''

    PLOT_FILE.write_text(svg, encoding="utf-8")


def main():
    rows = read_rows()
    write_summary(rows)
    plot(rows)
    print(f"Skrev {SUMMARY_FILE}")
    print(f"Skrev {PLOT_FILE}")


if __name__ == "__main__":
    main()
