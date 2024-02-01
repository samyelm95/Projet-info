#!/bin/bash

#création des fichiers nécessaires
fichier_trajets="Data/data.csv"
fichier_resultats="Demo/prog_d1.txt"

# Tri respectant la consigne
awk -F ';' '
{
  if (!seen[$6,$1]++) {
    conducteurs[$6]++;
  }
}
END {
  for (diver in conducteurs) {
    printf("%d %s\n", conducteurs[diver], diver);
  }
}' $fichier_trajets | sort -k1,1nr | head -n 10 | sort -k1,1n > $fichier_resultats

# Affichage GNUplot avec titre
gnuplot -persist <<-EOF
set terminal pngcairo enhanced font 'Times New Roman,12' size 800, 640
set output 'Image/histogramme_d1.png'
set title "Option -d1"
set ylabel 'DRIVER NAMES'
set xlabel 'NB ROUTES'
set style fill solid
set xrange [0:250]
set xtics 50
set boxwidth 0.5
set yrange [-1:10]

plot '$fichier_resultats' using (\$1*0.5):0:(\$1*0.5):(0.4):yticlabels(sprintf("%s %s", stringcolumn(2), stringcolumn(3))) with boxxyerrorbars lc rgbcolor 'blue' notitle
EOF
chmod 777 Image/histogramme_d1.png
xdg-open Image/histogramme_d1.png
