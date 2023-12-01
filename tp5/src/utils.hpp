#ifndef UTILS_HPP
#define UTILS_HPP
#include <chrono>
#include <bits/chrono.h>
#include <mutex>
#include <sstream>

/******************************************************************************/
/*                              global variable                               */
/******************************************************************************/

extern std::mutex mutex;

/******************************************************************************/
/*                                   macros                                   */
/******************************************************************************/

#define timerStart() auto _start = std::chrono::high_resolution_clock::now();
#define timerEnd() auto _end = std::chrono::high_resolution_clock::now();
#define timerCountMs()                                                         \
    std::chrono::duration_cast<std::chrono::microseconds>(_end - _start)       \
            .count() /                                                         \
        1000.0

/******************************************************************************/
/*                                 functions                                  */
/******************************************************************************/

inline std::string cat(const std::string &str, int i) {
    std::ostringstream oss;
    oss << str << i;
    return oss.str();
}


#endif
