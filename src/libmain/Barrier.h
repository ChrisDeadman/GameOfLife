#ifndef GAMEOFLIFE_BARRIER_H
#define GAMEOFLIFE_BARRIER_H

#include <condition_variable>
#include <mutex>

using namespace std;
using namespace std::chrono;

class Barrier {
private:
    unsigned long count;
    mutex lockObj;
    condition_variable finished;
public:

    explicit Barrier(unsigned long count) {
        this->count = count;
    }

    Barrier(const Barrier &that) = delete; // Forbid copying

    void await() {
        unique_lock<mutex> lock(lockObj);
        if (count <= 0) {
            return;
        }
        finished.wait(lock);
    }

    template<typename _Rep, typename _Period>
    void await(const duration<_Rep, _Period> &timeout) {
        unique_lock<mutex> lock(lockObj);
        if (count <= 0) {
            return;
        }
        finished.wait_for(lock, timeout);
    }

    void countDown() {
        unique_lock<mutex> lock(lockObj);
        if (--count <= 0) {
            finished.notify_all();
        }
    }
};

#endif //GAMEOFLIFE_BARRIER_H
