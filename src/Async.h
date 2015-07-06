//
//  Async.h
//  Cinder-Async
//
//  Created by Adrià Navarro López on 6/30/15.
//

#pragma once

#include "cinder/app/App.h"

// By default the block will use Grand Central Dispatch if available
// uncomment this to not use GCD on Mac or iOS
//#define USE_STD

#ifndef CINDER_COCOA
#define USE_STD
#endif

class Async {
public:
    static void call(std::function<void()> func, std::function<void()> callback);

private:
    
#ifdef USE_STD
    static int idCount;
    static std::map<int, std::shared_future<void>> futures;
#endif
};