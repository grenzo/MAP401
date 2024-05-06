#include "geometrie2d.h"


int main(int argc, char** argv){

    Point A;
    Point B;
    Point P;

    printf("Entrer les coordonnées du point P :\n");
    printf("x :");
    scanf("%lf", &(P.x));
    printf("y :");
    scanf("%lf", &(P.y));

    printf("Entrer les coordonnées du point A :\n");
    printf("x :");
    scanf("%lf", &(A.x));
    printf("y :");
    scanf("%lf", &(A.y));

    printf("Entrer les coordonnées du point B :\n");
    printf("x :");
    scanf("%lf", &(B.x));
    printf("y :");
    scanf("%lf", &(B.y));

    Segment S = set_segment(A, B);

    printf("dp = %lf\n", distance_point_segment(P, S));
}