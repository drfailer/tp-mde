#include "status.hpp"
#include "utils.hpp"
#include <CLHEP/Random/MTwistEngine.h>
#include <assert.h>
#include <cstddef>

/******************************************************************************/
/*                                   config                                   */
/******************************************************************************/

constexpr size_t NB_STATUS_FILE = 5;
constexpr size_t SEPARATION_NB = 10;

/******************************************************************************/
/*                                 question 2                                 */
/******************************************************************************/

/**
 * Vérification de la reproductibilité des séquences de nombres
 * pseudo-aléatoires générés par l'implémentation de MT de la bibliothèque.
 */
void checkReproducibility() {
    CLHEP::MTwistEngine mt;
    double savedRandoms[NB_STATUS_FILE][SEPARATION_NB];

    // sauvegarde de statut et de tirages
    for (size_t i = 0; i < NB_STATUS_FILE; ++i) {
        mt.saveStatus(cat("mt_check_", i).c_str());
        for (size_t j = 0; j < SEPARATION_NB; ++j) {
            savedRandoms[i][j] = mt.flat();
        }
    }

    // test si on retrouve bien les tirages
    for (size_t i = 0; i < NB_STATUS_FILE; ++i) {
        mt.restoreStatus(cat("mt_check_", i).c_str());
        for (size_t j = 0; j < SEPARATION_NB; ++j) {
            // le assert fait planter le programme si le générateur ne génère
            // pas une séquence reproductible
            assert(savedRandoms[i][j] == mt.flat());
        }
    }
}

/******************************************************************************/
/*                                 question 3                                 */
/******************************************************************************/

/**
 * Génération de fichiers statut avec MT avec un certain nombre de tirage entre
 * les fichiers.
 */
void generateStatusFiles(size_t nbStatusFiles, size_t separarationNb,
               const std::string &fileName) {
    CLHEP::MTwistEngine mt;

    // création de répertoire si besoin
    createFileDirectory(fileName);

    // sauvegarde de statut et de tirages
    for (size_t i = 0; i < nbStatusFiles; ++i) {
        mt.saveStatus(cat(fileName, i).c_str());
        for (size_t j = 0; j < separarationNb; ++j) {
            mt.flat();
        }
    }
}
