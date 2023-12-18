#ifndef GATTACA_HPP
#define GATTACA_HPP
#include <CLHEP/Random/MTwistEngine.h>

void gattaca(int nbThreads = 10, long maxIterPerThread = 1'000'000'000, std::string
        fileName = "mt_", std::string sequence = "GATTACA");

#endif
