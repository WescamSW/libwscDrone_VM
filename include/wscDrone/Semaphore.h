/****************************************************************************//**
 * @file
 * @brief This file contains a basic Semaphore construct
 * @ingroup wscDrone wscDrone
 * @author Steve Lascos
 * @date Feb. 3, 2019
 * @copyright CONFIDENTIAL and PROPRIETARY to L3 Technologies Wescam. This
 * source code is copyrighted. The source code may not be copied, reproduced,
 * translated, or reduced to any electronic medium or machine-readable form
 * without the prior written consent of L-3 Wescam. This source code is
 * confidential and proprietary to L-3 Wescam and may not be reproduced,
 * published, or disclosed to others without company authorization.
 ******************************************************************************/


#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std::chrono_literals;
namespace wscDrone {

/// A semaphore based on C++11 mutex locks. This code was taken from some
/// Stackoverflow posts
class Semaphore
{
public:

    /// Construct a semaphore with the specified count
    Semaphore(int count_ = 0) : count{count_}{}

    /// Semaphore notify
    void notify()
    {
        std::unique_lock<std::mutex> lck(mtx);

        ++count;
        cv.notify_one();
    }

    /// Semaphore wait
    void wait()
    {
        std::unique_lock<std::mutex> lck(mtx);

        if(count == 0)
        {
            cv.wait(lck);
        }

        --count;
    }

    /// Semaphore wait
    // Returns TRUE if we've timed out
    bool waitTimed(unsigned int timeMilliseconds)
    {
	    bool ret = false;
        std::unique_lock<std::mutex> lck(mtx);

        if (count == 0)
        {
            auto returnValue = cv.wait_for(lck, std::chrono::milliseconds(timeMilliseconds));
            if (returnValue == std::cv_status::timeout) {
	            ret = true;
            }
        }

        --count;

        return ret;
    }

    int getCount()
    {
        return count;
    }


private:

    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

}
#endif /* SEMAPHORE_H_ */
