//
//  Async.CPP
//  Cinder-Async
//
//  Created by Adrià Navarro López
//

// some std::async intro https://code4thought.wordpress.com/2013/03/03/cpp-async/

#include "Async.h"

#ifdef USE_STD

int Async::idCount = 0;
std::map<int, std::shared_future<void>> Async::futures;

void Async::call(std::function<void()> func, std::function<void()> callback)
{
    int futureId = idCount++;
    
    futures[futureId] = std::async(std::launch::async, [func, callback, futureId] {
        func();
        
        ci::app::App::get()->dispatchAsync([callback, futureId] {  // called on main thread
            callback();
            futures.erase(futureId);
        });
    });
}

#endif