#ifndef OBJETGRAPHIQUE_HPP
#define OBJETGRAPHIQUE_HPP

/******************************************************************************/
/*                              Objet graphique                               */
/******************************************************************************/

#define NB_CLASSES 3
typedef enum {
    CERCLE = 0,
    RECTANGLE = 1,
    OG = 2
} OG_t;

typedef struct ObjetGraphique ObjetGraphique;
typedef struct MetaObjetGraphique MetaObjetGraphique;

/* Méta classe de objet graphique */
extern MetaObjetGraphique C_MetaObjetGraphique;


struct MetaObjetGraphique {
    /* attributs de classes ***************************************************/
    int NbObjetGraphique;

    /* Méthodes de classe *****************************************************/
    int (*GetNbObjetGraphique)(void);

    /* Méthodes d'instances ***************************************************/
    void (*setX)(ObjetGraphique*, int);
    void (*setY)(ObjetGraphique*, int);
    int (*getX)(ObjetGraphique*);
    int (*getY)(ObjetGraphique*);
    int (*getCentreX)(ObjetGraphique*);
    int (*getCentreY)(ObjetGraphique*);
    void (*effacer)(ObjetGraphique*);
    void (*afficher)(ObjetGraphique*);
    void (*deplacer)(ObjetGraphique*, int, int);

    /* TVMs *******************************************************************/
    void (*TVMeffacer[NB_CLASSES])(ObjetGraphique*);
    void (*TVMafficher[NB_CLASSES])(ObjetGraphique*);
    void (*TVMdeplacer[NB_CLASSES])(ObjetGraphique*, int, int);
    int (*TVMgetCentreX[NB_CLASSES])(ObjetGraphique*);
    int (*TVMgetCentreY[NB_CLASSES])(ObjetGraphique*);

    /* Constructeurs **********************************************************/
    ObjetGraphique (*ConstructorObjetGraphdique)();
};

struct ObjetGraphique {
    MetaObjetGraphique* myClass;
    int x;
    int y;
    OG_t type;
};

void setX(ObjetGraphique*, int);
void setY(ObjetGraphique*, int);
int getX(ObjetGraphique*);
int getY(ObjetGraphique*);
int GetNbObjetGraphique(void);
void afficher(ObjetGraphique*);
void afficherOG(ObjetGraphique*);
void deplacerOG(ObjetGraphique*, int, int);
ObjetGraphique ConstructorObjetGraphique();

/* méthodes virtuelles ********************************************************/

void afficher(ObjetGraphique*);
void deplacer(ObjetGraphique*, int, int);
void effacer(ObjetGraphique*);
int getCentreX(ObjetGraphique*);
int getCentreY(ObjetGraphique*);

/******************************************************************************/
/*                                   cercle                                   */
/******************************************************************************/

typedef struct Cercle Cercle;
typedef struct MetaCercle MetaCercle;

struct MetaCercle {
    MetaObjetGraphique *super;
    void (*setRayon)(Cercle*,int);
    int (*getRayon)(Cercle*);
    Cercle (*ConstructorCercle)(void);
};

extern MetaCercle C_MetaCercle;

struct Cercle {
    ObjetGraphique super;
    MetaCercle *myClass;
    int rayon;
};

void setRayon(Cercle*, int);
int getRayon(Cercle*);
void afficherCercle(ObjetGraphique*);
Cercle ConstructorCercle(void);

/* méthodes virtuelles ********************************************************/

void afficherCercle(ObjetGraphique*);
void effacerCercle(ObjetGraphique*);
int getCentreXCercle(ObjetGraphique*);
int getCentreYCercle(ObjetGraphique*);

/******************************************************************************/
/*                                 rectangle                                  */
/******************************************************************************/

typedef struct Rectangle Rectangle;
typedef struct MetaRectangle MetaRectangle;

extern MetaRectangle C_MetaRectangle;

struct MetaRectangle {
    MetaObjetGraphique *super;
    void (*setHauteur)(Rectangle*, int);
    void (*setLargeur)(Rectangle*, int);
    int (*getLageur)(Rectangle*);
    int (*getHauteur)(Rectangle*);
    Rectangle (*ConstructorRectangle)(void);
};

struct Rectangle {
    ObjetGraphique super;
    MetaRectangle *myClass;
    int lageur;
    int hauteur;
};

void setHauteur(Rectangle*, int);
void setLargeur(Rectangle*, int);
int getHauteur(Rectangle*);
int getLargeur(Rectangle*);
void afficherRectangle(ObjetGraphique*);
Rectangle ConstructorRectangle(void);

/* méthodes virtuelles ********************************************************/

void afficherRectangle(ObjetGraphique*);
void effacerRectangle(ObjetGraphique*);
int getCentreXRectangle(ObjetGraphique*);
int getCentreYRectangle(ObjetGraphique*);

#endif
