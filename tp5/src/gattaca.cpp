#include "gattaca.hpp"
#include "utils.hpp"
#include <future>
#include <iostream>
#include <mutex>

/******************************************************************************/
/*                            sequence generation                             */
/******************************************************************************/

/**
 * Génère un mot de `nbNucleicBase` en utilisant le PRNG donné en paramètre.
 */
std::string generateSequence(CLHEP::HepRandomEngine &generator,
                             int nbNucleicBase) {
    std::string output = "";

    for (int i = 0; i < nbNucleicBase; ++i) {
        switch (int(generator.flat() * 4)) {
        case 0:
            output.push_back('A');
            break;
        case 1:
            output.push_back('C');
            break;
        case 2:
            output.push_back('G');
            break;
        case 3:
            output.push_back('T');
            break;
        }
    }
    return output;
}

/**
 * Génère `nbSequences` séquences et s'arrête quand la séquence
 * `objectiveSequence` est trouvée. Le générateur est initialisé avec le fichier
 * de status `fileName`. Cette fonction est faite pour être parallélisée.
 */
int generateNSequences(const std::string &fileName, int nbSequences,
                        std::string objectiveSequence) {
    std::string lastGeneratedSequence = "";
    CLHEP::MTwistEngine mt;
    long counter = 0;

    mt.restoreStatus(fileName.c_str());
    while (lastGeneratedSequence != objectiveSequence &&
           counter < nbSequences) {
        lastGeneratedSequence = generateSequence(mt, objectiveSequence.size());
        counter++;
        if (counter % 100'000'000 == 0) {
            std::unique_lock<std::mutex> lock(mutex);
            std::cout << "countIter = " << counter
                      << ", sequence: " << lastGeneratedSequence << std::endl;
        }
    }

    if (lastGeneratedSequence == objectiveSequence) {
        std::unique_lock<std::mutex> lock(mutex);
        std::cout << objectiveSequence
                  << " has been found, countIter = " << counter << std::endl;
    }
    return counter;
}

/******************************************************************************/
/*                                  gattaca                                   */
/******************************************************************************/

/**
 * Génère des séquences jusqu'à ce que la séquence GATTACA soit trouvée. La
 * génération des séquence se fait sur plusieurs threads pour aller plus vite.
 *
 * Par défaut, on réutilise les fichiers générés à la question 3:
 * - 10 fichiers => 10 threads.
 * - fichiers sépararés de 2 milliards de tirages => 2 milliards d'itération par
 *   thread.
 *
 * On peut configurer la fonction si besoin.
 */
void gattaca(int nbThreads, long maxIterPerThread, std::string fileName) {
    std::future<int> *threads = new std::future<int>[nbThreads];
    long long sum = 0;

    for (int i = 0; i < nbThreads; ++i) {
        threads[i] =
            std::async(std::launch::async, generateNSequences, cat(fileName, i),
                       maxIterPerThread, "AAATTTGCGTTCGATTAG");
    }

    for (int i = 0; i < nbThreads; ++i) {
        sum += threads[i].get();
    }
    std::cout << "mean: " << sum / nbThreads << std::endl;
    delete[] threads;
}
