#ifndef PILE_HPP
#define PILE_HPP
#include <stdbool.h>

// TODO

#define TAILLE_MAX 100
#define declarer_pile(Type)                               \
typedef struct Pile##Type Pile##Type;                     \
typedef struct MetaPile##Type MetaPile##Type;             \
                                                          \
struct MetaPile##Type {                                   \
    void (*empiler)(struct Pile##Type*, Type);            \
    Type (*depiler)(struct Pile##Type*);                  \
    bool (*estVide)(struct Pile##Type*);                  \
    Type (*sommet)(struct Pile##Type*);                   \
    Pile##Type (*construire)(void);                       \
};                                                        \
                                                          \
extern MetaPile##Type C_MetaPile##Type;                   \
                                                          \
struct Pile##Type {                                       \
    Type pile[TAILLE_MAX];                                \
    Type *top;                                            \
    MetaPile##Type *myClass;                              \
};                                                        \
                                                          \
/* création de la pile */                                 \
Type make_pile##Type(struct Pile##Type* this);            \
                                                          \
/* empile la valeur */                                    \
void empiler##Type(struct Pile##Type* this, Type valeur); \
                                                          \
/* dépile en retournant le sommet */                      \
Type depiler##Type(struct Pile##Type* this);              \
                                                          \
/* Prédicat : la pile est-elle vide ? */                  \
bool estVide##Type(struct Pile##Type* this);              \
                                                          \
/* renvoie le sommet de pile */                           \
Type sommet##Type(struct Pile##Type* this);               \
                                                          \
/* constructeur */                                        \
Pile##Type construirePile##Type(void);

#define implementer_pile(Type)                             \
MetaPile##Type C_MetaPile##Type = {                        \
    .empiler = &empiler##Type,                             \
    .depiler = &depiler##Type,                             \
    .estVide = &estVide##Type,                             \
    .sommet = &sommet##Type,                               \
    .construire = &construirePile##Type,                   \
};                                                         \
                                                           \
Pile##Type construirePile##Type(void) {                    \
    return (Pile##Type) {                                  \
        .top = 0,                                          \
        .myClass = &C_MetaPile##Type,                      \
    };                                                     \
}                                                          \
                                                           \
/* empile la valeur */                                     \
void empiler##Type(struct Pile##Type* this, Type valeur) { \
    if (this->top == 0) {                                  \
        this->top = &this->pile[0];                        \
    } else {                                               \
        this->top++;                                       \
    }                                                      \
    if (this->top < &this->pile[TAILLE_MAX]) {             \
        *this->top = valeur;                               \
    }                                                      \
}                                                          \
                                                           \
/* dépile en retournant le sommet */                       \
Type depiler##Type(struct Pile##Type* this) {              \
    Type output = *this->top;                              \
    if (this->top == &this->pile[0]) {                     \
        this->top = 0;                                     \
    } else {                                               \
        this->top--;                                       \
    }                                                      \
    return output;                                         \
}                                                          \
                                                           \
/* Prédicat : la pile est-elle vide ? */                   \
bool estVide##Type(struct Pile##Type* this) {              \
    return this->top == 0;                                 \
}                                                          \
                                                           \
/* renvoie le sommet de pile */                            \
Type sommet##Type(struct Pile##Type* this) {               \
    if (*this->top == 0) return -1;                        \
    return *this->top;                                     \
}


#endif
