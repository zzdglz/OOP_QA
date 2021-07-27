// timer.h (modified by shanjb20)

/**
 * @file timer.h
 * @Synopsis  Timer class for computing runtime
 * @author Hailong Yao
 * @version 0.1
 * @date 2015-09-25
 */
#ifndef TIMER_H__
#define TIMER_H__
#include <cassert>
#include "error.h"

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  Timer class
 */
/* ----------------------------------------------------------------------------*/
class Timer {
private:
    bool m_running;
    int m_interv;
    double m_started;
    double m_elapsed;

    double getUserTime() const;  // in seconds
    double getPrecision() const; // in seconds
public:
    Timer() : m_running(false), m_interv(0), m_started(0.0), m_elapsed(0.0) {}

    void start();
    void stop();
    void reset();
    bool isRunning() const { return m_running; }

    double time() const;
    int m_intervals() const { return m_interv; }
    double precision() const;
};

inline void Timer::start() {
    assert(!m_running);
    m_started = getUserTime();
    m_running = true;
    ++m_interv;
}

inline void Timer::stop() {
    assert(m_running);
    double t = getUserTime();
    m_elapsed += (t - m_started);
    m_started = 0.0;
    m_running = false;
}

inline void Timer::reset() {
    m_interv = 0;
    m_elapsed = 0.0;
    if (m_running) {
        m_started = getUserTime();
        ++m_interv;
    } else {
        m_started = 0.0;
    }
}

inline double Timer::time() const {
    if (m_running) {
        double t = getUserTime();
        return m_elapsed + (t - m_started);
    }
    return m_elapsed;
}

#endif
