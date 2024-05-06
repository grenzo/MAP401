#include <stdio.h>
#include <stdlib.h>
#include "contour.h"
#include "geometrie2d.h"
#include "sequence_point.h"

/*Fonction qui renvoie un contour après avori appliqué la simplification de douglas*/
Tableau_Point simplification_douglas_peucker(Tableau_Point CONT, int j1, int j2, double d) {
  if (d == 0) {
    return CONT;
    }
    Point Pj1 = CONT.tab[j1];
    Point Pj2 = CONT.tab[j2];
    Segment S = set_segment(Pj1, Pj2);
    double dmax = 0;
    int k = j1;
    for (int j = j1+1; j <= j2; j++) {
        Point Pj = CONT.tab[j];
        int dj = distance_point_segment(Pj, S);
        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }
    Tableau_Point T;
    T.taille = 0;
    T.tab = NULL;
    if (dmax <= d) {
        ajouter_point(&T, Pj1);
        ajouter_point(&T,Pj2);
    } else {
        Tableau_Point T1 = simplification_douglas_peucker(CONT, j1, k, d);
        Tableau_Point T2 = simplification_douglas_peucker(CONT, k, j2, d);
        T.taille = T1.taille + T2.taille;
        T.tab = malloc(T.taille * sizeof(Point));
        for (int i = 0; i < T1.taille; i++) {
            T.tab[i] = T1.tab[i];
        }
        for (int i = 0; i < T2.taille; i++) {
            T.tab[T1.taille + i] = T2.tab[i];
        }
        free(T1.tab);
        free(T2.tab);
    }
    return T;
}

/*Fonction qui applique l'algorithme de douglas sur tous les contours d'une image*/
Tableau_Contour simplification_totale2(Tableau_Contour CONT, double d) {
    unsigned int nb_contour = CONT.taille;
    Tableau_Contour tableau_simplifie;
    tableau_simplifie.taille = 0;
    tableau_simplifie.tab_contours = NULL;

    for (unsigned int i = 0; i < nb_contour; i++) {
        Tableau_Point contour = CONT.tab_contours[i];
        Tableau_Point contour_simplifie = simplification_douglas_peucker(contour, 0, contour.taille - 1, d);
        ajouter_contour(&tableau_simplifie, contour_simplifie);
    }
    return tableau_simplifie;
}


