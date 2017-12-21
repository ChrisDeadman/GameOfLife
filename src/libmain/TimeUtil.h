#ifndef GAMEOFLIFE_TIMEUTIL_H
#define GAMEOFLIFE_TIMEUTIL_H

#include <SFML/System/Clock.hpp>

using namespace sf;

template<typename function>
Time measureDuration(Clock &clock, function f) {
    Time before = clock.getElapsedTime();
    f();
    Time after = clock.getElapsedTime();
    return after - before;
}

#endif //GAMEOFLIFE_TIMEUTIL_H
