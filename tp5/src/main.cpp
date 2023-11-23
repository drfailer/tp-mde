#include <bits/chrono.h>
#include <cmath>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <iomanip>
#include <chrono>
/* #define NB_STATUS_FILE 5 */

#include "CLHEP/Random/MTwistEngine.h"

/******************************************************************************/
/*                             utility functions                              */
/******************************************************************************/

std::string cat(const std::string& str, int i) {
    std::ostringstream oss;
    oss << str << i;
    return oss.str();
}

double computPi(CLHEP::HepRandomEngine& generator, int numberOfDraw) {
    long nbValidDraw = 0;

    for (int i = 0; i < numberOfDraw; ++i) {
        double x = generator.flat();
        double y = generator.flat();

        if (x*x + y*y < 1) {
            ++nbValidDraw;
        }
    }
    return 4 * (double) nbValidDraw / numberOfDraw;
}

/******************************************************************************/
/*                                 questions                                  */
/******************************************************************************/

/**
 * @brief  Le assert ne fait pas planté le code donc le générateur fonctionne
 *         bien.
 */
void question2() {
    /* config **************************************/
    constexpr size_t NB_STATUS_FILE = 5;
    constexpr size_t SEPARATION_NB = 10;
    /***********************************************/
    CLHEP::MTwistEngine mt;
    double randoms[NB_STATUS_FILE][SEPARATION_NB];

    // savegarde de status et de tirages
    for (size_t i = 0; i < NB_STATUS_FILE; ++i) {
        mt.saveStatus(cat("mt2_", i).c_str());
        for (size_t j = 0; j < SEPARATION_NB; ++j) {
            randoms[i][j] = mt.flat();
        }
    }
    // test si on retrouve bien les tirages
    for (size_t i = 0; i < NB_STATUS_FILE; ++i) {
        mt.restoreStatus(cat("mt2_", i).c_str());
        for (size_t j = 0; j < SEPARATION_NB; ++j) {
            assert(randoms[i][j] == mt.flat());
        }
    }
}

void question3(size_t nbStatusFile = 10, size_t separarationNb = 2'000'000'000, const std::string& fileName = "mt3_") {
    CLHEP::MTwistEngine mt;

    // savegarde de status et de tirages
    for (size_t i = 0; i < nbStatusFile; ++i) {
        mt.saveStatus(cat(fileName, i).c_str());
        for (size_t j = 0; j < separarationNb; ++j) {
            mt.flat();
        }
    }
}

void question4(size_t nbReplication = 10, size_t nbDraws = 1'000'000'000, const std::string& fileName = "mt3_") {
    CLHEP::MTwistEngine mt;
    double sumPI = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < nbReplication; ++i) {
        mt.restoreStatus(cat(fileName, i).c_str());
        sumPI += computPi(mt, nbDraws);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << std::setprecision(10)
        << "pi: " << sumPI / nbReplication << "; time: "
        << duration.count() << std::endl;
}

void question5(const std::string& fileName = "mt3_", size_t nb_draws = 1'000'000'000) {
    CLHEP::MTwistEngine mt;
    double pi = 0;

    auto start = std::chrono::high_resolution_clock::now();
    mt.restoreStatus(fileName.c_str());
    pi = computPi(mt, nb_draws);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << std::setprecision(10)
        << "pi: " << pi << " (with " << fileName << "); time: "
        << duration.count() / 1000.0 << "ms" << std::endl;
}

/******************************************************************************/
/*                                    main                                    */
/******************************************************************************/

int main (int argc, char** argv) {
    if (argc == 2) {
        question5(argv[1]);
    } else {
        question2();
        question3();
        question4();
    }

    return 0;
}
