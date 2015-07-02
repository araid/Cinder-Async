Cinder-Async
============

Small utility class to call functions on the background and get a callback when they are done. Attempts to abstract the user from creating and destroying threads for simple tasks, by making use of [Grand Central Dispatch](https://developer.apple.com/library/ios/documentation/Performance/Reference/GCD_libdispatch_Ref/) on Mac/iOS and [std::async](http://en.cppreference.com/w/cpp/thread/async) on Windows.

Built for the [Cinder library](https://github.com/cinder/Cinder) for creative coding, version 0.9.0.
