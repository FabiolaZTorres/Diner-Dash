//
// Created by joshu on 11/4/2020.
//

#include "Burger.h"

Burger::Burger(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Burger::addIngredient(Item *item) {
    ingredients.push_back(item);
}

void Burger::removeIngredient(){
    // removes last ingredient added to burger
    if (!ingredients.empty()){
        ingredients.pop_back();
    }
}

void Burger::render(){
    int counter = 1;
    for (Item* ingredient:ingredients){
        ingredient->sprite.draw(x-5,y-(counter * 10)+55,width*0.70,height*0.70);
        counter++;
    }
}

void Burger::clear(){
    ingredients.clear();
}

bool Burger::equals(vector<Item *> playerBurger, vector<Item *> clientBurger){
    vector<Item *> playerCopy = playerBurger;

    // checks if player burger and client burger are equal
    if (!playerCopy.empty()){
        for (unsigned int i = 0; i < clientBurger.size(); i++){
            for (unsigned int j = 0; j < playerCopy.size(); j++){
                if (clientBurger[i] == playerCopy[j]){
                    playerCopy.erase(playerCopy.begin()+j);
                    break;
                }
            }
        }
    } else { return false; }

   if (playerCopy.empty()){ return true; } else { return false; }
}