#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geometrie2d.h"


int main(int argc, char** argv){
    double x = 5;
    double y = 3;
    Point P1 = set_point(x, y);
    Point P2 = set_point(x,y);
    Vecteur V1 = set_vecteur(x, y);
    Vecteur V2 = set_vecteur(x, y);


Point p = set_point(x, y);

Vecteur V = set_vecteur(x, y);

 p = add_point(P1, P2);

Vecteur v = vect_bipoint(P1,P2);

double a = 4;
 p = mult_reel_point(p, a);

 v = mult_reel_vecteur(V, a);

double ps = produit_scalaire(V1, V2);

double nV = norme_vect(V);

double nv = norme_vect(V);

double ds = distance_point(P1, P2);

printf("%f \n %f \n %f \n", ps, nV, ds);

return 0;
}