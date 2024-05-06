#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "geometrie2d.h"
#include "sequence_point.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation;

/*Fonction qui trouve le pixel de depart pour commencer parcours du contour
pour une meilleure optimisation startx, starty sont les points de depart pour ne
pas recommencer le parcours d'une image entiere*/
Point trouver_pixel_depart(Image I, int x, int y);

/*Fonction qui fait avancer le robot en donction de son orientation*/
void avancer(Point *P, Orientation O);

/*Fonction qui fait tourner le robot*/
Orientation tourner_orientation(Orientation O, int deg);

/*Fonction qui renvoie la valeur du pixel gauche en fonction de la
position et orientation du robot*/
Pixel val_gauche(Orientation O, Image I,  double x, double y);

/*Fonction qui renvoie la valeur du pixel droit en fonction de la
position et orientation du robot*/
Pixel val_droit(Orientation O, Image I, double x, double y);

/*Fonction qui calcule la nouvelle orentation du robot afin de bien suivre le contour*/
Orientation nouvelle_orientation(Orientation O, Image I, double x, double y);

/*Fonction qui calcule l'image masque*/
Image image_masque(Image I);

/*Fonction qui parcours le.s contour.s (fonction principale du programme)*/
Tableau_Contour parcours_contour(Image I);

/*Fonction qui écrit en format eps les contours d'un tableau de contours*/
void ecrire_EPS(FILE *f, Tableau_Contour T, Image I);

#endif