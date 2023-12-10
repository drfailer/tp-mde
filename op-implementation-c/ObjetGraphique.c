#include "ObjetGraphique.h"
#include <stdio.h>

/******************************************************************************/
/*                              Objet graphique                               */
/******************************************************************************/

MetaObjetGraphique C_MetaObjetGraphique = {
    .NbObjetGraphique = 0,
    .getX = &getX,
    .getY = &getY,
    .setX = &setX,
    .setY = &setY,
    .TVMeffacer = {
        [CERCLE] = &effacerCercle,
        [RECTANGLE] = &effacerRectangle,
        [OG] = NULL,
    },
    .TVMafficher = {
        [CERCLE] = &afficherCercle,
        [RECTANGLE] = &afficherRectangle,
        [OG] = &afficherOG
    },
    .TVMdeplacer = {
        [CERCLE] = &deplacerOG,
        [RECTANGLE] = &deplacerOG,
        [OG] = &deplacerOG,
    },
    .TVMgetCentreX = {
        [CERCLE] = &getCentreXCercle,
        [RECTANGLE] = getCentreXRectangle,
        [OG] = NULL,
    },
    .TVMgetCentreY = {
        [CERCLE] = &getCentreYCercle,
        [RECTANGLE] = &getCentreYRectangle,
        [OG] = NULL,
    },
    .afficher = &afficher,
    .effacer = &effacer,
    .deplacer = &deplacer,
    .getCentreX = &getCentreX,
    .getCentreY = &getCentreY,
    .GetNbObjetGraphique = &GetNbObjetGraphique,
    .ConstructorObjetGraphdique = &ConstructorObjetGraphique
};

void setX(ObjetGraphique* this, int inX) {
    this->x = inX;
}

void setY(ObjetGraphique* this, int inY) {
    this->y = inY;
}

int getX(ObjetGraphique* this) {
    return this->x;
}

int getY(ObjetGraphique* this) {
    return this->y;
}

int GetNbObjetGraphique(void) {
    return C_MetaObjetGraphique.NbObjetGraphique;
}

void afficherOG(ObjetGraphique* this) {
    (void) this;
    printf("afficher objet graphique");
}

void deplacerOG(ObjetGraphique* this, int x, int y) {
    this->x = x;
    this->y = y;
}

ObjetGraphique ConstructorObjetGraphique() {
    C_MetaObjetGraphique.NbObjetGraphique++;
    return (ObjetGraphique) {
        .x = 0,
        .y = 0,
        .myClass = &C_MetaObjetGraphique,
        .type = OG
    };
}

/* méthodes virtuelles ********************************************************/

void afficher(ObjetGraphique* this) {
    C_MetaObjetGraphique.TVMafficher[this->type](this);
}

void deplacer(ObjetGraphique* this, int x, int y) {
    C_MetaObjetGraphique.TVMdeplacer[this->type](this, x, y);
}

void effacer(ObjetGraphique* this) {
    C_MetaObjetGraphique.TVMeffacer[this->type](this);
}

int getCentreX(ObjetGraphique* this) {
    return C_MetaObjetGraphique.TVMgetCentreX[this->type](this);
}

int getCentreY(ObjetGraphique* this) {
    return C_MetaObjetGraphique.TVMgetCentreY[this->type](this);
}

/******************************************************************************/
/*                                   cercle                                   */
/******************************************************************************/

MetaCercle C_MetaCercle = {
    .super = &C_MetaObjetGraphique,
    .setRayon = &setRayon,
    .getRayon = &getRayon,
    .ConstructorCercle = &ConstructorCercle,
};

void setRayon(Cercle* this, int inRayon) {
    this->rayon = inRayon;
}

int getRayon(Cercle* this) {
    return this->rayon;
}

/* méthodes virtuelles ********************************************************/

void afficherCercle(ObjetGraphique* this) {
    Cercle* thisCercle = (Cercle*) this;
    printf("cercle: [ x: %d, y: %d, r: %d ]\n",
            thisCercle->super.x, thisCercle->super.y, thisCercle->rayon);
}

void effacerCercle(ObjetGraphique* this) {
    Cercle* thisCercle = (Cercle*) this;
    printf("On éfface le cercle: ");
    thisCercle->super.myClass->afficher(&thisCercle->super);
}

int getCentreXCercle(ObjetGraphique* this) {
    Cercle* thisCercle = (Cercle*) this;
    return thisCercle->super.x;
}

int getCentreYCercle(ObjetGraphique* this) {
    Cercle* thisCercle = (Cercle*) this;
    return thisCercle->super.y;
}

/* constructeur ***************************************************************/

Cercle ConstructorCercle(void) {
    Cercle c = {
        .super = ConstructorObjetGraphique(),
        .myClass = &C_MetaCercle,
        .rayon = 0
    };
    c.super.type = CERCLE;
    return c;
}

/******************************************************************************/
/*                                 rectangle                                  */
/******************************************************************************/

MetaRectangle C_MetaRectangle = {
    .super = &C_MetaObjetGraphique,
    .setHauteur = &setHauteur,
    .setLargeur = &setLargeur,
    .getHauteur = &getHauteur,
    .getLageur = &getLargeur,
    .ConstructorRectangle = &ConstructorRectangle
};

void setHauteur(Rectangle* this, int hauteur) {
    this->hauteur = hauteur;
}

void setLargeur(Rectangle* this, int largeur) {
    this->lageur = largeur;
}

int getHauteur(Rectangle* this) {
    return this->hauteur;
}

int getLargeur(Rectangle* this) {
    return this->lageur;
}

/* méthodes virtuelles ********************************************************/

void afficherRectangle(ObjetGraphique* this) {
    Rectangle* thisRectangle = (Rectangle*) this;
    printf("rectangle: [ x: %d, y: %d, l: %d, h: %d ]\n",
            thisRectangle->super.x, thisRectangle->super.y,
            thisRectangle->lageur, thisRectangle->hauteur);
}

void effacerRectangle(ObjetGraphique* this) {
    Rectangle* thisRectangle = (Rectangle*) this;
    printf("On efface le rectangle: ");
    thisRectangle->super.myClass->afficher(&thisRectangle->super);
}

int getCentreXRectangle(ObjetGraphique* this) {
    Rectangle* thisRectangle = (Rectangle*) this;
    return thisRectangle->super.x + thisRectangle->lageur / 2;
}

int getCentreYRectangle(ObjetGraphique* this) {
    Rectangle* thisRectangle = (Rectangle*) this;
    return thisRectangle->super.y + thisRectangle->hauteur / 2;
}

/* constructeur ***************************************************************/

Rectangle ConstructorRectangle(void) {
    Rectangle rec = {
        .super = ConstructorObjetGraphique(),
        .myClass = &C_MetaRectangle,
        .lageur = 0,
        .hauteur = 0
    };
    rec.super.type = RECTANGLE;
    return rec;
}
