#pragma once
#include "Client.h"

class Inspector: public Client{
    public:
        Inspector(int, int, int, int, ofImage, Burger*, bool);
        ~Inspector();
        static double removeEarnings(int earnings);
};