#include "Client.h"

Client::Client(int x, int y, int width, int height, ofImage sprite, Burger* burger, bool inspector): Entity(x, y, width, height, sprite){
    this->burger = burger;
    this->inspector = inspector;
}
Client::~Client(){
    delete burger;
}
void Client::render(){
    burger->render();
    patienceColorCounter++;
    ofSetColor(255, 255-(patienceColorCounter/10), 255-(patienceColorCounter/10)); // client turns red as patience decreases
    sprite.draw(x, y, width, height);
    ofSetColor(255);
    if(nextClient != nullptr){
        nextClient->render();
    }
}

void Client::tick(){
    patience--;
    burger->setY(y);
    if(patience == 0){
        isLeaving = true;
        clientsLeft++;
    }
    if(nextClient != nullptr){
        nextClient->tick();
    }
}

int Client::serve(std::vector<Item*> playerBurger, std::vector<Item*> ingOpt){
       
    std::vector <Item*> clientIng = this->getOrder()->getIngredients();
    if(this->getOrder()->equals(playerBurger, clientIng)){
        int money = 0;
        money += 2; // adds top and bottom price to money
        for (unsigned int i = 1; i < clientIng.size()-1; i++) { // checks what the ingredient is and charges accordingly
            if (clientIng[i] == ingOpt[0]) {
                money += 3;
            } else if (clientIng[i] == ingOpt[1]) {
                money += 2;
            } else if (clientIng[i] == ingOpt[2]) {
                money += 2;
            } else if (clientIng[i] == ingOpt[3]) {
                money += 4;
            }
        }
        isLeaving = true;
        return money;
    } else {
        if(this->nextClient == nullptr){ return 0; }
        return this->nextClient->serve(playerBurger, ingOpt);
    }
}


int Client::clientsLeft = 0;