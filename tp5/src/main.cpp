#include <sstream>
#include <iostream>
#include <assert.h>
#define NB_STATUS_FILE 5
#define SEPARATION_NB 10

#include "CLHEP/Random/MTwistEngine.h"

/******************************************************************************/
/*                             utility functions                              */
/******************************************************************************/

std::string cat(std::string&& str, int i) {
    std::ostringstream oss;
    oss << str << i;
    return oss.str();
}

/******************************************************************************/
/*                                 questions                                  */
/******************************************************************************/

/**
 * @brief  Le assert ne fait pas planté le code donc le générateur fonctionne
 *         bien.
 */
void question2() {
    CLHEP::MTwistEngine mt;
    double randoms[NB_STATUS_FILE][SEPARATION_NB];

    // savegarde de status et de tirages
    for (int i = 0; i < NB_STATUS_FILE; ++i) {
        mt.saveStatus(cat("mt2_", i).c_str());
        for (int j = 0; j < SEPARATION_NB; ++j) {
            randoms[i][j] = mt.flat();
        }
    }
    // test si on retrouve bien les tirages
    for (int i = 0; i < NB_STATUS_FILE; ++i) {
        mt.restoreStatus(cat("mt2_", i).c_str());
        for (int j = 0; j < SEPARATION_NB; ++j) {
            assert(randoms[i][j] == mt.flat());
        }
    }
}

/**
 * @brief  Le assert ne fait pas planté le code donc le générateur fonctionne
 *         bien.
 */
void question3() {
    CLHEP::MTwistEngine mt;

    // savegarde de status et de tirages
    for (int i = 0; i < NB_STATUS_FILE; ++i) {
        mt.saveStatus(cat("mt3_", i).c_str());
        for (int j = 0; j < 2'000'000'000; ++j) {
            mt.flat();
        }
    }
}

/******************************************************************************/
/*                                    main                                    */
/******************************************************************************/

int main () {
    /* question2(); */
    question3();
    return 0;
}
