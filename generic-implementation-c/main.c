#include <stdio.h>
#include "pile.h"

declarer_pile(int);
declarer_pile(double);

int main(void)
{
    Pileint pileInt = C_MetaPileint.construire();
    Piledouble pileDouble = C_MetaPiledouble.construire();

    /* basic test */

    empilerint(&pileInt, 1);
    empilerdouble(&pileDouble, 2.0);

    printf("sommet: %d\n", sommetint(&pileInt));
    printf("sommet: %lf\n", sommetdouble(&pileDouble));

    printf("estVide: %d\n", estVideint(&pileInt));
    printf("estVide: %d\n", estVidedouble(&pileDouble));

    printf("depiler: %d\n", depilerint(&pileInt));
    printf("depiler: %lf\n", depilerdouble(&pileDouble));

    printf("esVide: %d\n", estVideint(&pileInt));
    printf("esVide: %d\n", estVidedouble(&pileDouble));

    /* test OP */

    pileInt.myClass->empiler(&pileInt, 1);
    pileDouble.myClass->empiler(&pileDouble, 10.8);

    printf("----------------------------------------------\n");
    printf("sommet: %d\n", pileInt.myClass->sommet(&pileInt));
    printf("sommet: %lf\n", pileDouble.myClass->sommet(&pileDouble));

    printf("estVide: %d\n", pileInt.myClass->estVide(&pileInt));
    printf("estVide: %d\n", pileDouble.myClass->estVide(&pileDouble));

    printf("depiler: %d\n", pileInt.myClass->depiler(&pileInt));
    printf("depiler: %lf\n", pileDouble.myClass->depiler(&pileDouble));

    printf("estVide: %d\n", pileInt.myClass->estVide(&pileInt));
    printf("estVide: %d\n", pileDouble.myClass->estVide(&pileDouble));

    return 0;
}
