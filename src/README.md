## Manuel d'Utilisation - Programme de Détection et Simplification de Contours

### Description
Le programme `test_contour` permet de détecter et, éventuellement, de simplifier les contours d'une image au format PBM. Il prend en entrée une image PBM, le nom du fichier EPS de sortie, ainsi que la distance-seuil pour la simplification des contours (optionnel) et l'option -s pour activer la simplification (optionnel).

### Syntaxe
```
./test_contour [image.pbm] [image.eps] [distance-seuil d] [-s]
```

### Exemples d'Utilisation

#### Tâche 5
```bash
./test_contour images_pbm/zebres-4000x3000.pbm images_eps/zebres_simpl.eps
```
**RESULTATS**
```bash
391 contours et 162312 segments et 162703 points
Terminé en 0.839011 sec
```

#### Tâche 6
```bash
./test_contour images_pbm/zebres-4000x3000.pbm images_eps/zebres_simpl.eps 2 -s
```
**RESULTATS**
```bash
391 contours et 9739 segments et 10130 points
Terminé en 0.957014 sec
```

### Notes
- L'option `-s` est facultative et permet d'activer la simplification des contours.
- La distance-seuil `d` est un paramètre nécessaire lorsque l'option `-s` est utilisée. Elle détermine le seuil de simplification des contours.
- Les résultats affichent le nombre de contours détectés, le nombre total de segments, le nombre total de points et le temps d'exécution du programme.