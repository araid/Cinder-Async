//
//  Async.CPP
//  Cinder-Async
//
//  Created by Adrià Navarro López
//

// some std::async intro https://code4thought.wordpress.com/2013/03/03/cpp-async/

#include "Async.h"

#ifdef USE_STD

bool Async::bInitialized = false;
std::vector<Async::FutureCallback> Async::futureCallbacks;

void Async::call(std::function<void()> func, std::function<void()> callback)
{
    if (!bInitialized) {
        bInitialized = true;
        ci::app::App::get()->getSignalUpdate().connect([](){ Async::checkFutures(); });
    }
    
    std::shared_future<void> future = std::async(std::launch::async, func);
    futureCallbacks.push_back(FutureCallback(future, callback));
}

void Async::checkFutures()
{
    auto fc = std::begin(futureCallbacks);
    
    while (fc != std::end(futureCallbacks)) {
        if (futureReady(fc->first)) {
            if (fc->second) fc->second();   // callback on main thread - should it be called with dispatchAsync?
            fc = futureCallbacks.erase(fc);      // remove element from vector
        }
        else {
            ++fc;
        }
    }
}

bool Async::futureReady(std::shared_future<void> future)
{
    return future.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}



#endif