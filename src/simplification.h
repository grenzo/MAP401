#ifndef _SIMPLIFICATION_H_
#define _SIMPLIFICATION_H_
#include "contour.h"
#include "geometrie2d.h"
#include "sequence_point.h"

/*Fonction qui renvoie un contour après avori appliqué la simplification de douglas*/
Tableau_Point simplification_douglas_peucker(Tableau_Point CONT, int j1, int j2, double d);

/*Fonction qui applique l'algorithme de douglas sur tous les contours d'une image*/
Tableau_Contour simplification_totale2(Tableau_Contour T, double d);

#endif