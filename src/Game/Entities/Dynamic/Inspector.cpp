#include "Inspector.h"

Inspector::Inspector(int x, int y, int width, int height, ofImage sprite, Burger* burger, bool inspector): Client(x, y, width, height, sprite, burger, inspector){}

Inspector::~Inspector(){
    delete getBurger();
}

double Inspector::removeEarnings(int earnings){
    return earnings/2;
}