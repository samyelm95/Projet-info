#!/bin/bash

chmod 777 Progc/prog_d1.sh Progc/prog_d2.sh Progc/prog_l.sh Progc/prog_t.sh Progc/prog_t.c Progc/prog_s.c Progc/prog_s.sh
chmod 777 script_principal.sh
fichier_data="Data/data.csv"

# Chemins des exécutables
exe_prog_t="Progc/prog_t"
exe_prog_s="Progc/prog_s"

# Fonction pour la vérification
verification() {
    # Vérifier la présence du fichier data.csv
    if [ ! -f "$fichier_data" ]; then
        echo "Le fichier data n'existe pas."
    fi

    # Vérifier l'existence des exécutables
    for exe in "$exe_prog_t"; do
        if [ ! -x "$exe" ]; then
            echo "L'exécutable $exe n'existe pas."
            echo "Compilation de $exe en cours ..."
        #gcc Progc/prog_t.c -o Progc/prog_t
            
        fi
    done
    for exe in "$exe_prog_s"; do
        if [ ! -x "$exe" ]; then
            echo "L'exécutable $exe n'existe pas."
            echo "Compilation de $exe en cours ..."
        #gcc Progc/prog_s.c -o Progc/prog_s
            
        fi
    done

    # Vérifier l'existence des répertoires et les vider
    for dir in "Image" "Temp" "Demo"; do
        if [ ! -d "$dir" ]; then
            mkdir "$dir"
        else
            rm -f "$dir"/*
        fi
    done
}

# Fonction pour afficher l'aide
aide() {
    echo " Ce programme se lance avec des options qui sont décrites ci-dessous  :
    - Le traitement d1 expose les conducteurs avec le plus de trajet
    - Le traitement d2 donne les conducteurs ayant la plus grande distance réalisée
    - Le traitement l permet de voir les 10 trajets les plus longs
    - Le traitement t montre les 10 villes les plus traversées
    - Le traitement s nous donne les statistiques sur les étapes
    "
exit 0
}

# Fonction pour le traitement d1
prog_d1() {
    echo "Vous avez choisi l'option d1 
Affichage du graphique en cours ..."
    #lancer les verif et le traitement demandé
    verification;
    ./Progc/prog_d1.sh
}

# Fonction pour le traitement d2
prog_d2() {
    echo "Vous avez choisi l'option d2 
Affichage du graphique en cours ..."
    # lancer les vérifications et le traitement demandé
    verification;
    ./Progc/prog_d2.sh
}

# Fonction pour le traitement l
prog_l() {
    echo "Vous avez choisi l'option l 
Affichage du graphique en cours ..."
    # lancer les vérifications et le traitement demandé
    verification;
    ./Progc/prog_l.sh
}

# Fonction pour le traitement t
prog_t() {
    echo "Vous avez choisi l'option t 
Affichage du graphique en cours ..."
    # lancer les vérifications et le traitement demandé
    verification;
    tail -n +2 Data/data.csv | cut -d';' -f1,2,3,4 | "$exe_prog_t" > Demo/prog_t.csv
    ./Progc/prog_t.sh
}

# Fonction pour le traitement s
prog_s() {
    echo "Vous avez choisi l'option s 
Affichage du graphique en cours ..."
    # lancer les verif et le traitement demandé
    verification;
    ./Progc/prog_s.sh
}

# Mesure du temps
start_time=$(date +%s)

# Lancer le traitement en fonction de l'argument donné
if [ "$1" == "d1" ]; then
    prog_d1
elif [ "$1" == "d2" ]; then
    prog_d2
elif [ "$1" == "l" ]; then
    prog_l
elif [ "$1" == "t" ]; then
    prog_t
elif [ "$1" == "s" ]; then
    prog_s
elif [ "$1" == "h" ]; then
    aide
else
    echo "Argument invalide. Utilisez l'option h pour afficher l'aide."
fi

# Mesure du temps
end_time=$(date +%s)
elapsed_time=$((end_time - start_time))
echo "Temps d'execution : $elapsed_time secondes."
