#include "contour.h"
#include "sequence_point.h"
#include "simplification.h"
#include <time.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
    /* Partie pour afficher le temps d'execution */
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    /* Gestion d'erreur d'utilisation */
    if (argc != 3 && argc != 5) {
        fprintf(stderr, "Erreur d'utilisation, ./test_contour image.pbm image.eps d [-s]\n");
        return 0;
    }

    /* Lecture de l'image donnée en argument et initialisation du tableau de contours */
    Image I = lire_fichier_image(argv[1]);
    Tableau_Contour T;

    /* Passage de l'image.pbm à un tableau de contours contenant tous les points de l'image */
    T = parcours_contour(I);

    /* Simplification Douglas si l'option -s est présente */
    Tableau_Contour T_simpl;
    if (argc == 5 && strcmp(argv[4], "-s") == 0) {
        double d = atof(argv[3]);
        T_simpl = simplification_totale2(T, d);
    } else {
        T_simpl = T; // Pas de simplification, on garde les contours originaux
    }

    /* Ecriture en format EPS de l'image dans le nom de fichier donné en argument */
    FILE *f;
    f = fopen(argv[2], "w");
    ecrire_EPS(f, T_simpl, I);

    /* Partie temps d'execution */
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Terminé en %f sec \n", cpu_time_used);

    return 0;
}

