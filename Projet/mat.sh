#!/bin/bash

fichier_trajets="data.csv"
fichier_resultats="resultat.txt"

# Extraire la 6ème colonne, compter les occurrences, trier et prendre les 10 premiers
awk -F ';' '!seen[$6,$1]++ { conducteurs[$6]++} END { for (diver in conducteurs) print conducteurs[diver], diver}' $fichier_trajets |sort -k1,1nr | head -n 10 | sort -k1,1n > $fichier_resultats 


gnuplot -persist <<EOF
set terminal pngcairo enhanced font 'arial,10' size 700, 600
set output '/home/marzaguina/Travail/Projet/mat.png'
set style fill solid
set yrange [-1:10]

plot '$fichier_resultats' using (\$1*0.5):0:(\$1*0.5):(0.4):yticlabels(sprintf("%s %s", stringcolumn(2), stringcolumn(3))) with boxxyerrorbars lc rgbcolor 'spring-green' notitle
EOF
