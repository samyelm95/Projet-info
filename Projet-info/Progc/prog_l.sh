#!/bin/bash

#chemin des fichiers 
fichier_trajets="Data/data.csv"
fichier_resultats="Demo/resultat.txt"

# Tri des trajets par identifiant croissant
sort -t';' -k1,1n "$fichier_trajets" | \
# Traitement L : les 10 trajets les plus longs
awk -F ';' '{distances[$1]+=$5} END {for (route_id in distances) print distances[route_id], route_id}' | \
sort -nr | head -n 10 > "$fichier_resultats"
sort -k2,2nr -o Demo/resultat.txt Demo/resultat.txt


# Utilisation de gnuplot pour la création du graphe
gnuplot -persist <<EOF
set terminal pngcairo enhanced font 'Times New Roman ,10' size 800, 640
set title "Option -l"
set xlabel 'ROUTE ID'
set ylabel 'DISTANCE (Km)'
set style fill solid
set yrange [0:]
set boxwidth 0.8
set output 'Image/histogramme_l.png'

plot '$fichier_resultats' using 1:xtic(2) with boxes lc rgbcolor 'red' notitle
EOF

xdg-open Image/histogramme_l.png
