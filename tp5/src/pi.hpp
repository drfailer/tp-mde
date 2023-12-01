#ifndef PI_HPP
#define PI_HPP
#include <stddef.h>
#include <string>

void question4(size_t nbReplications = 10, size_t nbDraws = 1'000'000'000,
               const std::string &fileName = "mt3_");
void question5(const std::string &fileName = "mt3_",
               size_t nb_draws = 1'000'000'000);
void question6aFuture(const std::string &fileName = "mt3_",
                      size_t nb_draws = 1'000'000'000);
void question6aThreads(const std::string &fileName = "mt3_",
                       size_t nb_draws = 1'000'000'000);

#endif
