fichier_resultats="Demo/prog_s.csv"
# Utilisation de gnuplot
gnuplot <<EOF
    set terminal pngcairo enhanced font 'Times New Roman,12' size 800, 640
    set datafile separator ";"
    set xtic rotate by 45 font '0,8' offset -2,-2.5
    set xlabel "Identifiants Trajets" font '0,12' offset 0,-2
    set ylabel "Distance (km)" font '0,12'
    set title 'Option -s'
    set tics out nomirror
    set output 'Image/histogramme_s.png'
    plot '$fichier_resultats' using 0:(\$2):(\$4) with filledcurve lc rgbcolor 'pink' title "Distance Max/Min (Km)",\
    '' using 3:xtic(1) smooth mcspline lc rgbcolor 'purple' title "Distance moyenne (Km)"
EOF
chmod 777 Image/histogramme_s.png
xdg-open Image/histogramme_s.png
