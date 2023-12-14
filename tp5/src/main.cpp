#include "gattaca.hpp"
#include "pi.hpp"
#include "status.hpp"
#include "utils.hpp"
#include <CLHEP/Random/MTwistEngine.h>
#include <iomanip>
#include <iostream>

/******************************************************************************/
/*                             variables globales                             */
/******************************************************************************/

std::mutex mutex;

/******************************************************************************/
/*                             parse command line                             */
/******************************************************************************/

enum ACTIONS {
    TEST,
    GEN_STATUS,
    PI_SEC,
    PI_PAR,
    GATTACA,
    GATTACA_GEN,
    PI_INPUT_FILE,
};

ACTIONS parseCommandLine(int argc, char **argv) {
    if (argc >= 2) {
        std::string firstArg = std::string(argv[1]);

        if (firstArg == "test") {
            return TEST;
        } else if (firstArg == "pi") {
            if (argc >= 3 && std::string(argv[2]) == "par") {
                return PI_PAR;
            } else {
                return PI_SEC;
            }
        } else if (firstArg == "gattaca") {
            if (argc >= 3 && std::string(argv[2]) == "gen") {
                return GATTACA_GEN;
            } else {
                return GATTACA;
            }
        } else {
            return PI_INPUT_FILE;
        }
    }
    return GEN_STATUS;
}

/******************************************************************************/
/*                                    main                                    */
/******************************************************************************/

/* options ********************************************************************/
constexpr long GATTACA_NUMBERS = 10'000;
constexpr long GATTACA_THREADS = 40;
constexpr const char* GATTACA_SEQUENCE = "GATTACA";

int main(int argc, char **argv) {
    std::cout << std::setprecision(10);

    switch (parseCommandLine(argc, argv)) {
    case TEST:
        std::cout << "testing reapetability of the genrator:" << std::endl;
        checkReproducibility();
        break;
    case GEN_STATUS:
        std::cout << "questions 3 (generate files)" << std::endl;
        generateStatusFiles();
        break;
    case PI_SEC:
        std::cout << "compute pi (sequencial):" << std::endl;
        question4();
        break;
    case PI_PAR:
        std::cout << "pi calculus with threads:" << std::endl;
        // on peut essayer les deux version mais elle font la même chose
        /* question6aThreads(); */
        question6aFuture();
        break;
    case GATTACA_GEN:
        std::cout << "gattaca status generation:" << std::endl;
        generateStatusFiles(GATTACA_THREADS, GATTACA_NUMBERS, "gattaca/gattaca_");
        break;
    case GATTACA:
        std::cout << "gattaca generation:" << std::endl;
        gattaca(GATTACA_THREADS, GATTACA_NUMBERS, "gattaca/gattaca_", GATTACA_SEQUENCE);
        break;
    case PI_INPUT_FILE:
        question5(argv[1]);
        break;
    }
    return 0;
}
