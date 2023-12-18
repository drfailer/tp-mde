#ifndef STATUS_HPP
#define STATUS_HPP
#include <string>

void checkReproducibility();
void generateStatusFiles(size_t nbStatusFiles = 10, size_t separarationNb = 2'000'000'000,
               const std::string &fileName = "mt_");

#endif
