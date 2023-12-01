#include "gattaca.hpp"
#include <iostream>
#include <future>
#include "utils.hpp"

/******************************************************************************/
/*                              word generation                               */
/******************************************************************************/

/**
 * Génère un mot de `nbLetters` en utilisant le PRNG donné en paramètre.
 */
std::string generateWord(CLHEP::HepRandomEngine &generator, int nbLetters = 7) {
    std::string output = "";

    for (int i = 0; i < nbLetters; ++i) {
        output.push_back('A' + generator.flat() * 26);
    }
    return output;
}

long G_CountIter = 0;
bool G_run = true;

/**
 * Génère `nbWords` mots de 7 lettre et s'arrête quand le mote GATTACA est
 * trouvé. Le générateur est initialisé avec le fichier de status `fileName`.
 * Cette fonction est fait pour être parallélisée.
 */
void generateNWords(const std::string& fileName, int nbWords) {
    std::string lasGeneratedWord = "";
    CLHEP::MTwistEngine mt;
    long tmpCounter = 0;
    long localCounter = 0;

    mt.restoreStatus(fileName.c_str());
    while (G_run && lasGeneratedWord != "GATTACA" && localCounter < nbWords) {
        lasGeneratedWord = generateWord(mt);
        mutex.lock();
        tmpCounter = ++G_CountIter;
        localCounter++;
        if (localCounter % 1'000'000 == 0) {
            std::cout << "countIter = " << tmpCounter
                << ", word: " << lasGeneratedWord << std::endl;
        }
        mutex.unlock();
    }

    if (lasGeneratedWord == "GATTACA") {
        mutex.lock();
        std::cout << "GATTACA has been found, countIter = " << tmpCounter
                  << std::endl;
        G_run = false;
        mutex.unlock();
    }
}

/******************************************************************************/
/*                                  gattaca                                   */
/******************************************************************************/

/**
 * Génère des mots de 7 lettres jusqu'à ce que le mot GATTACA soit trouvé. La
 * génération des mots se fait sur plusieurs threads pour aller plus vite.
 *
 * Par défaut, on réutilise les fichiers générés à la question 3:
 * - 10 fichiers => 10 threads.
 * - fichiers sépararés de 2 milliards de tirages => 2 milliards d'itération par
 *   thread.
 *
 * On peut configurer la fonction si besoin.
 */
void gattaca(long maxIter, int nbThreads, std::string fileName) {
    std::future<void> *threads = new std::future<void>[nbThreads];

    for (int i = 0; i < nbThreads; ++i) {
        threads[i] = std::async(std::launch::async, generateNWords,
                cat(fileName, i), maxIter / nbThreads);
    }
    delete[] threads;
}
