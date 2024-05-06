#include "geometrie2d.h"



Point set_point(double x, double y){
    Point P = {x, y};
    return P;
}

Vecteur set_vecteur(double x, double y){
    Vecteur V = {x, y};
    return V;
}


Point add_point(Point P1, Point P2){
    return set_point(P1.x+P2.x, P1.y+P2.y);
}

Point sub_point(Point P1, Point P2){
    return set_point(P1.x-P2.x, P1.y-P2.y);
}


Vecteur vect_bipoint(Point A, Point B){
    Vecteur V = {B.x-A.x, B.y-A.y};
    return V;
}


/*multiplication des coordonnees d'un point par un reel*/
Point mult_reel_point(Point P, double a){
    return set_point(a*P.x, a*P.y);
}

/*multiplication des coordonnees d'un vecteur par un reel*/
Vecteur mult_reel_vecteur(Vecteur V, double a){
    return set_vecteur(a*V.x, a*V.y);
}

/*produit scalaire de deux vecteurs*/
double produit_scalaire(Vecteur V1, Vecteur V2){
    return V1.x*V2.x + V1.y*V2.y;
}

/*norme d'un vecteur*/
double norme_vect(Vecteur V){
    return sqrt(pow((V.x),2)+pow((V.y),2));
}

/*distance entre deux points*/
double distance_point(Point P1, Point P2){
    return sqrt(pow((P1.x-P2.x),2)+pow((P1.y-P2.y),2));
}


Point calcul_q(Point A, Point B, double lbda){
    return add_point(A, mult_reel_point(sub_point(B, A), lbda));
}


double calcul_lambda(Vecteur AB, Vecteur AP){
    return produit_scalaire(AP, AB)/produit_scalaire(AB, AB);
}


Segment set_segment(Point A, Point B){
    Segment S;
    S.A = A;
    S.B = B;
    return S;
}

double distance_point_segment(Point P, Segment S){
    Point A = S.A;
    Point B = S.B;
    Vecteur AB = vect_bipoint(A, B);
    Vecteur AP = vect_bipoint(A, P);
    double lbda = calcul_lambda(AB, AP);
    
    if(lbda < 0){
        return norme_vect(AP);
    }else if(lbda <= 1){
        Point Q = calcul_q(A, B, lbda);
        Vecteur QP = vect_bipoint(Q, P);
        return norme_vect(QP);
    }else{
        Vecteur BP = vect_bipoint(B, P);
        return norme_vect(BP);
    }
}