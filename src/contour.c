#include <stdio.h>
#include <stdlib.h>
#include "contour.h"
#include "image.h"
#include "sequence_point.h"

/*Fonction qui trouve le pixel de depart pour commencer parcours du contour
pour une meilleure optimisation startx, starty sont les points de depart pour ne
pas recommencer le parcours d'une image entiere*/
Point trouver_pixel_depart(Image I, int startX, int startY) {
    int l = largeur_image(I);
    int h = hauteur_image(I);
    for (int i = startY; i <= h; i++) {
        for (int j = (i == startY ? startX : 1); j <= l; j++) {
            if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i - 1) == BLANC) {
                return set_point(j - 1, i - 1);
            }
        }
    }
    return set_point(-1, -1); // erreur pas de dessin
}

/*Fonction qui fait avancer le robot en donction de son orientation*/
void avancer(Point *P, Orientation O){
    switch (O){
    case Ouest:
        P->x = P->x - 1;
        break;
    case Est:
        P->x = P->x + 1;
        break;
    case Nord:
        P->y = P->y - 1;
        break;
    case Sud:
        P->y = P->y + 1;
        break;

    }
}

/*Fonction qui fait tourner le robot*/
Orientation tourner_orientation(Orientation O, int deg){
    switch (O){
    case Ouest:
        if(deg == 90){
            return Sud;
        }else if(deg == 270){
            return Nord;
        }
        break;
    case Est:
        if(deg == 90){
            return Nord;
        }else if(deg == 270){
            return Sud;
        }
        break;
    case Nord:
        if(deg == 90){
            return Ouest;
        }else if(deg == 270){
            return Est;
        }
        break;
    case Sud:
        if(deg == 90){
            return Est;
        }else if(deg == 270){
            return Ouest;
        }
        break;

    }
return Est; //n'arrivera jamais
}

/*Fonction qui renvoie la valeur du pixel gauche en fonction de la
position et orientation du robot*/
Pixel val_gauche(Orientation O, Image I,  double x, double y){
    switch (O){
    case Ouest:
        return get_pixel_image(I, x, y+1);
        break;
    case Est:
        return get_pixel_image(I, x+1, y);
        break;
    case Nord:
        return get_pixel_image(I, x, y);
        break;
    case Sud:
        return get_pixel_image(I, x+1, y+1);
        break;

    }
}

/*Fonction qui renvoie la valeur du pixel droit en fonction de la
position et orientation du robot*/
Pixel val_droit(Orientation O, Image I, double x, double y){
    switch (O){
    case Ouest:
        return get_pixel_image(I, x, y);
        break;
    case Est:
        return get_pixel_image(I, x+1, y+1);
        break;
    case Nord:
        return get_pixel_image(I, x+1, y);
        break;
    case Sud:
        return get_pixel_image(I, x, y+1);
        break;

    }
}

/*Fonction qui calcule la nouvelle orentation du robot afin de bien suivre le contour*/
Orientation nouvelle_orientation(Orientation O, Image I, double x, double y){
    Pixel pG = val_gauche(O, I, x, y);
    Pixel pD = val_droit(O, I, x, y);
    if (pG == NOIR){
        return tourner_orientation(O, 90);
    }else if(pD == BLANC){
        return tourner_orientation(O, 270);
    }
    return O;
    
}

/*Fonction qui calcule l'image masque*/
Image image_masque(Image I){
    int h = hauteur_image(I);
    int l = largeur_image(I);
    Image M = creer_image((UINT)l, (UINT)h);

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= l; j++) {
                if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i - 1) == BLANC) {
                    set_pixel_image(M, j, i, NOIR);
                }
            }
        }
    return M;
}

/*Fonction qui parcours le.s contour.s (fonction principale du programme)*/
Tableau_Contour parcours_contour(Image I) {
    Image M = image_masque(I);

    /*Utilisation d'une nouvelle structure de donnée, le tableau de contours
    contenant des tableaux de points (des contours)*/
    Tableau_Contour tableau_contour;
    tableau_contour.taille = 0;
    tableau_contour.tab_contours = NULL;

    bool boucle0 = true;
    int startX = 1, startY = 1; // Coordonnées du dernier pixel de départ
    while (boucle0) {
        Point P = trouver_pixel_depart(M, startX, startY);

        /*on arrete lorsque le pixel depart est (-1,-1) (il y en a plus)
        on utilise un continue au lieu de mettre de if a la fin pour ne
        pas appeler trouver_pixel une seconde fois*/
        
        if (P.x == -1 && P.y == -1) {
            boucle0 = false; // 
            continue;
        }
        startX = P.x + 1; // Mettre à jour les coordonnées du dernier pixel de départ trouvé
        startY = P.y;

        double x0 = P.x;
        double y0 = P.y; //Position du robot au début du contour

        Orientation O = Est;
        bool boucle = true;
        Tableau_Point contour;
        contour.taille = 0;
        contour.tab = NULL;

        while (boucle) {
            ajouter_point(&contour, P);
            if ((get_pixel_image(M, P.x + 1, P.y + 1) == NOIR) && (O == Est)) {
                set_pixel_image(M, P.x + 1, P.y + 1, BLANC);
            }
            avancer(&P, O);
            O = nouvelle_orientation(O, I, P.x, P.y);

            if (((P.x == x0) && (P.y == y0)) && O == Est) {
                boucle = false;
                ajouter_point(&contour, P);
            }
        }
        ajouter_contour(&tableau_contour, contour);
    }
    return tableau_contour;
}



/*Fonction qui écrit en format eps les contours d'un tableau de contours*/
void ecrire_EPS(FILE *f, Tableau_Contour tableau_contour, Image I){
    int h = hauteur_image(I);
    int l = largeur_image(I);

    fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %d %d\n", l, h);
    fprintf(f,"newpath\n");
    int nb_contour = tableau_contour.taille;
    int nb_point = 0;
    
    for (unsigned int i = 0; i < tableau_contour.taille; i++) {
        Tableau_Point contour = tableau_contour.tab_contours[i];
        nb_point += contour.taille;
        for (unsigned int j = 0; j < contour.taille; j++) {
            Point P = contour.tab[j];
            if (j == 0) {
                fprintf(f,"%d %d moveto\n", (int)P.x, h-(int)P.y);
            } else {
                fprintf(f,"%d %d lineto\n", (int)P.x, h-(int)P.y);
            }
        }
    }
    printf("%d contours et %d segments et %d points\n", nb_contour, nb_point - nb_contour, nb_point);
    fprintf(f,"fill\n");
    fprintf(f,"showpage\n");
}

