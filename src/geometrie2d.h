#ifndef _GEOMETRIE2D_H_
#define _GEOMETRIE2D_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



typedef struct Vecteur_{
    double x, y;
} Vecteur;

typedef struct Point_{
    double x, y;
} Point;


typedef struct Segment_{
    Point A, B;
} Segment;




/*créé le point de coordonnées (x,y)*/
Point set_point(double x, double y);

Vecteur set_vecteur(double x, double y);

/*Somme de deux points*/
Point add_point(Point P1, Point P2);

Point sub_point(Point P1, Point P2);


/*création d'un vecteur a partir de deux points*/
Vecteur vect_bipoint(Point A, Point B);


/*multiplication des coordonnees d'un point par un reel*/
Point mult_reel_point(Point P, double a);

/*multiplication des coordonnees d'un vecteur par un reel*/
Vecteur mult_reel_vecteur(Vecteur V, double a);

/*produit scalaire de deux vecteurs*/
double produit_scalaire(Vecteur V1, Vecteur V2);

/*norme d'un vecteur*/
double norme_vect(Vecteur V);

/*distance entre deux points*/
double distance_point(Point P1, Point P2);

Point calcul_q(Point A, Point B, double lbda);

double calcul_lambda(Vecteur AB, Vecteur AP);

Segment set_segment(Point A, Point B);

double distance_point_segment(Point P, Segment S);

#endif /* _GEOMETRIE2D_H_ */