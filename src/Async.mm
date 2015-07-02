//
//  Async.mm
//  Cinder-Async
//
//  Created by Adrià Navarro López on 6/30/15.
//

// some GCD references
// https://xenakios.wordpress.com/2014/09/29/concurrency-in-c-the-cross-platform-way/
// https://developer.apple.com/library/prerelease/ios/documentation/General/Conceptual/ConcurrencyProgrammingGuide/


#include "Async.h"

#ifndef USE_STD

#include "dispatch/dispatch.h"

void Async::call(std::function<void()> func, std::function<void()> callback)
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        if (func) func();
        if (callback) {
            dispatch_async(dispatch_get_main_queue(), ^{
                callback();
            });
        }
    });
}

#endif

