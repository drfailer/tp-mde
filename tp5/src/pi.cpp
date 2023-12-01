#include "pi.hpp"
#include "utils.hpp"
#include <CLHEP/Random/MTwistEngine.h>
#include <thread>
#include <future>

/******************************************************************************/
/*                                 compute pi                                 */
/******************************************************************************/

/**
 * Calucule de pi en utilisant la méthode de Monte-Carlo.
 */
double computePi(CLHEP::HepRandomEngine &generator, int nbDraw) {
    long nbValidPoints = 0;

    for (int i = 0; i < nbDraw; ++i) {
        double x = generator.flat();
        double y = generator.flat();

        if (x * x + y * y < 1) {
            ++nbValidPoints;
        }
    }
    return 4 * (double)nbValidPoints / nbDraw;
}

/******************************************************************************/
/*                                 question 4                                 */
/******************************************************************************/

/**
 * Réplication du calcule de pi selon la méthode de Monte-Carlo. On calcule et
 * on affiche la moyenne des valeurs trouvées ainsi que le temps de calcule.
 */
void question4(size_t nbReplications, size_t nbDraws,
               const std::string &fileName) {
    CLHEP::MTwistEngine mt;
    double sumPI = 0;

    timerStart();
    for (size_t i = 0; i < nbReplications; ++i) {
        mt.restoreStatus(cat(fileName, i).c_str());
        sumPI += computePi(mt, nbDraws);
    }
    timerEnd();

    std::cout << std::setprecision(10) << "pi: " << sumPI / nbReplications
              << "; time: " << timerCountMs() << std::endl;
}

/******************************************************************************/
/*                                 question 5                                 */
/******************************************************************************/

/**
 * Réalisation d'une réplication du calcule de pi avec initialisation de MT à
 * partir d'un fichier de statut pré-généré. Cette fonction peut-être utilisé
 * dans le script permettant le lancement de plusieurs programmes en parallèle.
 */
void question5(const std::string &fileName, size_t nb_draws) {
    CLHEP::MTwistEngine mt;
    double pi = 0;

    timerStart();
    mt.restoreStatus(fileName.c_str());
    pi = computePi(mt, nb_draws);
    timerEnd();

    /* mutex lock on std::cout */ {
        std::unique_lock<std::mutex> lock(mutex);
        std::cout << "pi: " << pi << " (with " << fileName
                  << "); time: " << timerCountMs() << "ms" << std::endl;
    }
}

/******************************************************************************/
/*                                question 6a                                 */
/******************************************************************************/

constexpr size_t NB_REPLICATION = 10;

/**
 * Paraléllisation du calcule éffectué par question5 en utilisant std::future.
 */
void question6aFuture(const std::string &fileName, size_t nbDraws) {
    CLHEP::MTwistEngine mt;
    size_t i;

    timerStart();
    /* threads scope */ {
        std::future<void> pis[NB_REPLICATION];
        for (i = 0; i < NB_REPLICATION; ++i) {
            pis[i] = std::async(std::launch::async, question5, cat(fileName, i),
                                nbDraws);
        }
    }
    timerEnd();
    std::cout << "total time: " << timerCountMs() / 1000.0 << "s" << std::endl;
}

/**
 * Paraléllisation du calcule éffectué par question5 en utilisant std::thread.
 */
void question6aThreads(const std::string &fileName, size_t nbDraws) {
    /* config **************************************/
    constexpr size_t NB_REPLICATION = 10;
    /***********************************************/
    std::thread thread[NB_REPLICATION];
    CLHEP::MTwistEngine mt;
    size_t i;

    timerStart();
    for (i = 0; i < NB_REPLICATION; ++i) {
        thread[i] = std::thread(question5, cat(fileName, i), nbDraws);
    }

    for (i = 0; i < NB_REPLICATION; ++i) {
        thread[i].join();
    }
    timerEnd();

    std::cout << "total time: " << timerCountMs() / 1000.0 << "s" << std::endl;
}
