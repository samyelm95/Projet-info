#!/bin/bash
# Création des fichiers nécessaires 
fichier_resultats="Demo/prog_s.csv"


# Utilisation de gnuplot
gnuplot -persist <<EOF
set terminal pngcairo enhanced font 'arial,10' size 1200, 600
set output 'Image/histogramme_s.png'
set title "Option -S : Distance = f(Route)"
set ylabel 'DISTANCE (km)'
set yrange [0:]
set xtics rotate by 45 right #offset -3,-1.5
set bmargin 3

plot '$fichier_resultats' using 0:(\$2):(\$4) with filledcurve lc rgbcolor 'spring-green' title "Distance Max/Min (Km)",\
    ''using 3:xtic(1) smooth mcspline lc rgbcolor 'dark-green' title "Distance average (Km)"
EOF

chmod 777 Image/histogramme_s.png
xdg-open Image/histogramme_s.png


