#pragma once

namespace mvl {
    template<class Parent> class Singleton {
    public:
        static Parent& get() {
            static Parent instance;
            return instance;
        }
    };
}