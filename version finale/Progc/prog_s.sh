#!/bin/bash
# Création des fichiers nécessaires !
fichier_trajets="Data/data.csv"
fichier_resultats2="Demo/Resultat_s2.txt"
fichier_resultats="Demo/Resultat_s.txt"

cut -d';' -f1,5 "$fichier_trajets" | tail -n +2  | sort -t';' -k1,1n | sed 's/;/ /g'> $fichier_resultats
./Progc/prog_s
sed -i '1d' $fichier_resultats
)


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


