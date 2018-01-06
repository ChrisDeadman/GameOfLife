#ifndef GAMEOFLIFE_CHRONOCLOCK_H
#define GAMEOFLIFE_CHRONOCLOCK_H

#include <chrono>
#include <ctime>

using namespace std::chrono;

class ChronoClock {
private:
    system_clock::time_point startTime = system_clock::now();

public:
    ChronoClock() = default;

    ChronoClock(const ChronoClock &that) = delete; // Forbid copying

    system_clock::duration restart() {
        auto elapsedTime = this->getElapsedTime();
        startTime = system_clock::now();
        return elapsedTime;
    }

    system_clock::duration getElapsedTime() {
        return system_clock::now() - startTime;
    }

    template<typename function>
    system_clock::duration measureDuration(function f) {
        auto before = getElapsedTime();
        f();
        auto after = getElapsedTime();
        return after - before;
    }
};

#endif //GAMEOFLIFE_CHRONOCLOCK_H
