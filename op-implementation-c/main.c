#include <stdio.h>
#include "ObjetGraphique.h"

#define newObjetGraphique() C_MetaObjetGraphique.ConstructorObjetGraphdique();
#define newCercle() C_MetaCercle.ConstructorCercle();
#define newRectangle() C_MetaRectangle.ConstructorRectangle()
#define callMethod(var, method) var.myClass->method(&var)
#define callMethodA(var, method, ...) var.myClass->method(&var, __VA_ARGS__)
#define callSuperMethod(var, method) var.super.myClass->method(&var.super)
#define callSuperMethodA(var, method, ...) var.super.myClass->method(&var.super, __VA_ARGS__)
#define callSuperStaticMethod(var, method) var.super.myClass->method()
#define callSuperStaticMethodA(var, method, ...) var.super.myClass->method(__VA_ARGS__))

int main(void)
{
    ObjetGraphique obj = newObjetGraphique(); // this shouldn't be instanciated, this is just for the test

    callMethodA(obj, setX, 1);
    callMethodA(obj, setY, 1);
    printf("x: %d, y: %d, nb_obj: %d\n", obj.myClass->getX(&obj),
            obj.myClass->getY(&obj),
            obj.myClass->GetNbObjetGraphique());

    Rectangle rec = newRectangle();
    callMethodA(rec, setLargeur, 20);
    callMethodA(rec, setHauteur, 12);
    printf("x: %d, y: %d, lageur: %d, hauteur: %d, nb_obj: %d\n",
            callSuperMethod(rec, getX),
            callSuperMethod(rec, getY),
            callMethod(rec, getLageur),
            callMethod(rec, getHauteur),
            callSuperStaticMethod(rec, GetNbObjetGraphique)
            );

    Cercle c = newCercle();
    printf("x: %d, y: %d, rayon: %d, nb_obj: %d\n",
            callSuperMethod(c, getX),
            callSuperMethod(c, getY),
            callMethod(c, getRayon),
            callSuperStaticMethod(rec, GetNbObjetGraphique)
            );

    // virtual method
    callSuperMethod(rec, afficher);
    callSuperMethod(c, afficher);
    printf("déplacement:\n");
    callSuperMethodA(rec, deplacer, 2, 2);
    callSuperMethodA(c, deplacer, 3, 2);
    callSuperMethod(rec, afficher);
    callSuperMethod(c, afficher);
    printf("centre rec: (%d, %d)\n",
            callSuperMethod(rec, getCentreX), callSuperMethod(rec, getCentreY));
    printf("centre c: (%d, %d)\n",
            callSuperMethod(c, getCentreX), callSuperMethod(c, getCentreY));

    return 0;
}
