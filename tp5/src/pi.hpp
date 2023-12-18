#ifndef PI_HPP
#define PI_HPP
#include <stddef.h>
#include <string>

void piSequential(size_t nbReplications = 10, size_t nbDraws = 1'000'000'000,
               const std::string &fileName = "mt_");
void piFromStatusFile(const std::string &fileName = "mt_",
               size_t nb_draws = 1'000'000'000);
void piParallel(const std::string &fileName = "mt_",
                      size_t nb_draws = 1'000'000'000);
void piParallelThreads(const std::string &fileName = "mt_",
                       size_t nb_draws = 1'000'000'000);

#endif
