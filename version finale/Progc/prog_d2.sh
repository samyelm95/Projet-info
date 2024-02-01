#!/bin/bash
# chemin des fichiers
fichier_csv="Data/data.csv"
fichier_trajet="Demo/prog_d2.txt"

# tri du fichier data
awk -F ';' '{sum[$6]+=$5} END {for (i in sum) print sum[i],i}' "$fichier_csv" | sort -nr | head -n 10 | sort -k1,1 > $fichier_trajet

# Affichage GNUplot avec titre
gnuplot -persist <<-EOF
set terminal pngcairo enhanced font 'Times New Roman,12' size 800, 640
set output 'Image/histogramme_d2.png'
set title "Option -d2"
set ylabel 'DRIVER NAMES'
set xlabel 'DISTANCE (Km)'
set style fill solid
set xrange [0:160000] 
set xtics 20000        
set boxwidth 0.5
set yrange [-1:10]

plot '$fichier_trajet' using (\$1*0.5):0:(\$1*0.5):(0.4):yticlabels(sprintf("%s %s", stringcolumn(2), stringcolumn(3))) with boxxyerrorbars lc rgbcolor 'purple' notitle
EOF
chmod 777 Image/histogramme_d2.png
xdg-open Image/histogramme_d2.png
