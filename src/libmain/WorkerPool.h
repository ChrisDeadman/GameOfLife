#ifndef GAMEOFLIFE_WORKERPOOL_H
#define GAMEOFLIFE_WORKERPOOL_H

#include <algorithm>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "Barrier.h"

using namespace std;
using namespace std::chrono;

class WorkerPool {
private:
    bool exit = false;
    mutex lockObj;
    vector<thread> threads;

    queue<function<void()>> backlog;
    condition_variable workPending;

public:

    explicit WorkerPool(unsigned int numWorkers) :
            threads(),
            backlog() {
        for (auto worker = 0; worker < numWorkers; worker++) {
            threads.emplace_back([this]() {
                do {
                    unique_lock<mutex> lock(lockObj);
                    workPending.wait_for(lock, milliseconds(10));
                    if (!backlog.empty()) {
                        auto work = backlog.front();
                        backlog.pop();
                        lock.unlock();
                        work();
                    } else {
                        lock.unlock();
                    }
                } while (!exit);
            });
        }
    }

    WorkerPool(const WorkerPool &that) = delete; // Forbid copying

    ~WorkerPool() {
        exit = true;
        for_each(threads.begin(), threads.end(), [](thread &t) { t.join(); });
    }

    static unsigned int getConcurentThreadsSupported() {
        return thread::hardware_concurrency();
    }

    void run_async(function<void()> work) {
        unique_lock<mutex> lock(lockObj);
        this->backlog.emplace(work);
        lock.unlock();
        workPending.notify_one();
    }

    void parallel_for(const unsigned int start, const unsigned int end, const function<void(unsigned int, unsigned int)> work) {
        auto numWorkers = this->threads.size();
        auto numValues = (end - start) + 1;
        auto increment = (unsigned int) ceil(numValues / (float) numWorkers);
        auto workCount = 0;
        auto finishedCount = 0;

        Barrier workFinished(numWorkers);

        unique_lock<mutex> lock(this->lockObj);
        for (auto worker = 0; worker < numWorkers; worker++) {
            this->backlog.emplace([worker, &increment, &end, &work, &workFinished]() {
                auto current = (worker * increment);
                if (current <= end) {
                    work(current, min(current + increment, end));
                }
                workFinished.countDown();
            });
        }
        lock.unlock();
        this->workPending.notify_all();
        workFinished.await();
    }
};

#endif //GAMEOFLIFE_WORKERPOOL_H
