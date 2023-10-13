#pragma once

#include "BaseCounter.h"


class StoveCounter: public BaseCounter {
    public:
        StoveCounter(int x, int y, int width, int height, Item* item, ofImage sprite);
        static bool isCooking;
        static bool isCooked;
        static int cookTime;
};