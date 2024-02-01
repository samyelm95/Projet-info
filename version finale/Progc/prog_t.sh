#!/bin/bash
fichier_resultat="Demo/prog_t.csv"

gnuplot -persist <<EOF
set datafile separator ";"
set ylabel 'NB ROUTES'
set xlabel 'TOWN NAMES'
set terminal pngcairo enhanced font 'Times New Roman,12' size 800, 640
set output 'Image/histogramme_t.png'
set title "Option -t"
set style histogram clustered gap 1
set bmargin 5
set yrange [0:]
set boxwidth 0.5
set xtics rotate by 45 right font ",8"
set style fill solid 0.8 border
plot '$fichier_resultat' using (\$0):2:xticlabel(1) with boxes lc rgbcolor 'orange' notitle,\
    '' using (\$0+0.2):(\$3) with boxes lc rgbcolor 'yellow' notitle
#plot for [COL=2:3] '$fichier_resultats_test' using COL:xticlabels(1) with boxes
EOF
chmod 777 Image/histogramme_t.png
xdg-open Image/histogramme_t.png
