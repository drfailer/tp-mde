#include <assert.h>
#include <bits/chrono.h>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <future>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include "CLHEP/Random/MTwistEngine.h"

#define timerStart() auto _start = std::chrono::high_resolution_clock::now();
#define timerEnd() auto _end = std::chrono::high_resolution_clock::now();
#define timerCountMs()                                                         \
    std::chrono::duration_cast<std::chrono::microseconds>(_end - _start)       \
            .count() /                                                         \
        1000.0

/******************************************************************************/
/*                             variables globales                             */
/******************************************************************************/

std::mutex mutex;

/******************************************************************************/
/*                             utility functions                              */
/******************************************************************************/

std::string cat(const std::string &str, int i) {
    std::ostringstream oss;
    oss << str << i;
    return oss.str();
}

/**
 * @brief  Calucule de pi en utilisant la méthode de Monte-Carlo.
 * @param  generator  PRNG
 * @param  numberOfDraw  Nombre de nombres pseudo-aléatoires tirés pour réaliser
 *                       le calcule.
 * @return  Valeur approchée de pi.
 */
double computPi(CLHEP::HepRandomEngine &generator, int numberOfDraw) {
    long nbValidDraw = 0;

    for (int i = 0; i < numberOfDraw; ++i) {
        double x = generator.flat();
        double y = generator.flat();

        if (x * x + y * y < 1) {
            ++nbValidDraw;
        }
    }
    return 4 * (double)nbValidDraw / numberOfDraw;
}

/******************************************************************************/
/*                                 questions                                  */
/******************************************************************************/

/**
 * @brief  Vérification de la reproductibilité des séquences de nombres
 *         pseudo-aléatoires générés par l'implémentation de MT de la
 *         bibliothèque.
 */
void question2() {
    /* config **************************************/
    constexpr size_t NB_STATUS_FILE = 5;
    constexpr size_t SEPARATION_NB = 10;
    /***********************************************/
    CLHEP::MTwistEngine mt;
    double randoms[NB_STATUS_FILE][SEPARATION_NB];

    // sauvegarde de statut et de tirages
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
            // le assert fait planter le programme si le générateur ne génère
            // pas une séquence reproductible
            assert(randoms[i][j] == mt.flat());
        }
    }
}

/**
 * @brief  Archive de fichiers statut avec MT.
 */
void question3(size_t nbStatusFiles = 10, size_t separarationNb = 2'000'000'000,
               const std::string &fileName = "mt3_") {
    CLHEP::MTwistEngine mt;

    // sauvegarde de statut et de tirages
    for (size_t i = 0; i < nbStatusFiles; ++i) {
        mt.saveStatus(cat(fileName, i).c_str());
        for (size_t j = 0; j < separarationNb; ++j) {
            mt.flat();
        }
    }
}

/**
 * @brief  Réplication du calcule de pi selon la méthode de Monte-Carlo. On
 *         calcule et on affiche la moyenne des valeurs trouvées ainsi que le
 *         temps de calcule.
 */
void question4(size_t nbReplications = 10, size_t nbDraws = 1'000'000'000,
               const std::string &fileName = "mt3_") {
    CLHEP::MTwistEngine mt;
    double sumPI = 0;

    timerStart();
    for (size_t i = 0; i < nbReplications; ++i) {
        mt.restoreStatus(cat(fileName, i).c_str());
        sumPI += computPi(mt, nbDraws);
    }
    timerEnd();

    std::cout << std::setprecision(10) << "pi: " << sumPI / nbReplications
              << "; time: " << timerCountMs() << std::endl;
}

/**
 * @brief  Réalisation d'une réplication du calcule de pi avec initialisation de
 *         MT à partir d'un fichier de statut pré-généré. Cette fonction
 *         peut-être utilisé dans le script permettant le lancement de plusieurs
 *         programmes en parallèle.
 */
void question5(const std::string &fileName = "mt3_",
               size_t nb_draws = 1'000'000'000) {
    CLHEP::MTwistEngine mt;
    double pi = 0;

    timerStart();
    mt.restoreStatus(fileName.c_str());
    pi = computPi(mt, nb_draws);
    timerEnd();

    /* mutex lock on std::cout */ {
        std::unique_lock<std::mutex> lock(mutex);
        std::cout << "pi: " << pi << " (with " << fileName
            << "); time: " << timerCountMs() << "ms" << std::endl;
    }
}

/**
 * @brief  Paraléllisation du calcule éffectué par question5 en utilisant
 *         std::future.
 */
void question6aFuture(const std::string &fileName = "mt3_",
                      size_t nb_draws = 1'000'000'000) {
    /* config **************************************/
    constexpr size_t NB_REPLICATION = 10;
    /***********************************************/
    CLHEP::MTwistEngine mt;
    size_t i;

    timerStart();
    /* threads scope */ {
        std::future<void> pis[NB_REPLICATION];
        for (i = 0; i < NB_REPLICATION; ++i) {
            pis[i] = std::async(std::launch::async, question5, cat(fileName, i),
                                nb_draws);
        }
    } // on attent la fin des threads pour sortir
    timerEnd();
    std::cout << "total time: " << timerCountMs() / 1000.0 << "s" << std::endl;
}

/**
 * @brief  Paraléllisation du calcule éffectué par question5 en utilisant
 *         std::thread.
 */
void question6aThreads(const std::string &fileName = "mt3_",
                       size_t nb_draws = 1'000'000'000) {
    /* config **************************************/
    constexpr size_t NB_REPLICATION = 10;
    /***********************************************/
    std::thread thread[NB_REPLICATION];
    CLHEP::MTwistEngine mt;
    size_t i;

    timerStart();
    for (i = 0; i < NB_REPLICATION; ++i) {
        thread[i] = std::thread(question5, cat(fileName, i), nb_draws);
    }
    for (i = 0; i < NB_REPLICATION; ++i) {
        thread[i].join();
    }
    timerEnd();
    std::cout << "total time: " << timerCountMs() / 1000.0 << "s" << std::endl;
}

/******************************************************************************/
/*                                    main                                    */
/******************************************************************************/

int main(int argc, char **argv) {
    std::cout << std::setprecision(10);
    if (argc == 2) {
        question5(argv[1]);
    } else {
        /* question2(); */
        /* question3(); */
        /* question4(); */
        /* question6aFuture(); */
        question6aThreads();
    }

    return 0;
}
