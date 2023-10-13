#pragma once

#include "Entity.h"
#include "Burger.h"

class Client: public Entity{
    private:
        Burger* burger;
        int originalPatience;
        int patience=2000;
        int patienceColorCounter=0;
        bool inspector;
    public:
        Client(int, int, int, int, ofImage, Burger*, bool);
        virtual ~Client();
        void tick();
        void render();
        int serve(std::vector<Item*> playerBurger, std::vector<Item*> ingOpt);
        Client* nextClient=nullptr;
        bool isLeaving=false;
        Burger* getOrder() { // gets client's order
            return burger;
        }
        static int clientsLeft;

        // getters
        Burger* getBurger(){ return burger; }
        int getOriginalPatience(){ return originalPatience; }
        int getPatience(){ return patience; }
        int getPatienceColorCounter(){ return patienceColorCounter; }
        bool getInspector(){ return inspector; }

        // setters
        void setBurger(Burger* burger){ this->burger = burger; }
        int setPatienceColorCounter(){ return patienceColorCounter++; }
};