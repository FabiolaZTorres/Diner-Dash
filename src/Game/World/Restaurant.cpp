//
// Created by joshu on 11/3/2020.
//

#include "Restaurant.h"

Player *Restaurant::getPlayer() { return player; }
void Restaurant::setPlayer(Player *player) { this->player = player; }
// static variables
int Restaurant::money = 0;
bool StoveCounter::isCooking = false;
bool StoveCounter::isCooked = false;
int StoveCounter::cookTime = 0;

Restaurant::Restaurant() {
    floor.load("images/Wall-Floor.png");
    entityManager = new EntityManager();
    ofImage chefPlayerImage;
    chefPlayerImage.load("images/chef.png");
    this->player = new Player(0, 600, 64, 64, chefPlayerImage, entityManager);    
    initItems();
    initCounters();
    initClients();
    generateClient();

}
void Restaurant::initItems(){
    ofImage burgerSpriteSheet, cheeseImg, lettuceImg, tomatoImg, burgerImg, botBreadImg, topBreadImg, plateImg;
    burgerSpriteSheet.load("images/burger.png");
    topBreadImg.cropFrom(burgerSpriteSheet, 25, 16, 112, 43); // top bun
    burgerImg.cropFrom(burgerSpriteSheet, 30, 134, 103, 48); // patty
    cheeseImg.cropFrom(burgerSpriteSheet, 169, 213, 102, 39); // cheese
    tomatoImg.cropFrom(burgerSpriteSheet, 169, 158, 110, 41); // tomato
    lettuceImg.cropFrom(burgerSpriteSheet, 161, 62, 117, 34); // lettuce
    botBreadImg.cropFrom(burgerSpriteSheet, 444, 270, 115, 39); // bottom bun
    plateImg.cropFrom(burgerSpriteSheet, 575, 263, 131, 51); // plate

    cheese = new Item(cheeseImg, "cheese");
    lettuce = new Item(lettuceImg, "lettuce");
    tomato = new Item(tomatoImg, "tomato");
    burger = new Item(burgerImg, "patty");
    botBread = new Item(botBreadImg, "bottomBun");
    topBread = new Item(topBreadImg, "topBun");
    ingredientOptions = {this->cheese, this->lettuce, this->tomato, this->burger};
}
void Restaurant::initCounters(){
    int counterWidth = 96;
    int yOffset = 500;
    ofImage counterSheet, plateCounterImg, cheeseCounterImg, stoveCounterImg, lettuceCounterImg, emptyCounterImg, tomatoCounterImg, breadCounterImg;
    counterSheet.load("images/kitchen_cabinets_by_ayene_chan.png");
    stoveCounterImg.cropFrom(counterSheet, 224,12,32,43);//stoveTop
    lettuceCounterImg.cropFrom(counterSheet,96,76,32,43);//Vegetables
    emptyCounterImg.cropFrom(counterSheet,0,245,30,43);//Empty
    tomatoCounterImg.cropFrom(counterSheet,96,200,32,48);//fruit basket
    cheeseCounterImg.cropFrom(counterSheet,64,73,32,46);//cheese
    plateCounterImg.cropFrom(counterSheet,0,133,32,50);//plates
    breadCounterImg.cropFrom(counterSheet,0,63,34,56);//buns
    entityManager->addEntity(new BaseCounter(0,yOffset-16, counterWidth, 117, nullptr, plateCounterImg));
    entityManager->addEntity( new BaseCounter(counterWidth,yOffset-7, counterWidth,108, cheese, cheeseCounterImg));
    entityManager->addEntity(new StoveCounter(counterWidth*2,yOffset, counterWidth, 102, burger, stoveCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*3, yOffset, counterWidth, 102, lettuce, lettuceCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*4,yOffset, counterWidth, 102, nullptr, emptyCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*5, yOffset -10, counterWidth, 113, tomato, tomatoCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*6, yOffset-32, counterWidth, 133, botBread, breadCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*7, yOffset-32, counterWidth, 133, topBread, breadCounterImg));

}
void Restaurant::initClients(){
    ofImage temp;
    temp.load("images/People/Car_Designer3Female.png");
    people.push_back(temp);
    temp.load("images/People/Freedom_Fighter2Male.png");
    people.push_back(temp);
    temp.load("images/People/Hipster.png");
    people.push_back(temp);
    temp.load("images/People/Lawyer2Male.png");
    people.push_back(temp);
    temp.load("images/People/Mad_Scientist3Female.png");
    people.push_back(temp);
    temp.load("images/People/Programmer2Male.png");
    people.push_back(temp);
    temp.load("images/People/Songwriter3Male.png");
    people.push_back(temp);
    temp.load("images/People/Weather_Reporter2Female.png");
    people.push_back(temp);
}
void Restaurant::tick() {
    ticks++;
    if(ticks % 400 == 0){
        generateClient();
    }
    // updates counter for progress bar when cooking patty
    if(ticks % 3 == 0 && StoveCounter::isCooking && StoveCounter::cookTime <= 50){
        StoveCounter::cookTime++;
    } else if(StoveCounter::cookTime >= 50){
        StoveCounter::isCooked = true;
    }
    player->tick();
    entityManager->tick();

}


void Restaurant::generateClient(){
    Burger* b = new Burger(72, 100, 50, 25);
    b->addIngredient(botBread);
    ingredientAmount = ofRandom(3)+1; // determines how many ingredients
    for (int i = 0; i < ingredientAmount; i++){
        b->addIngredient(ingredientOptions[ofRandom(4)]); // chooses random ingredient
    }
    b->addIngredient(topBread);
    clientAmount++;
    if(clientAmount % 10 == 0 && clientAmount != 0){ // generates inspector every 10 clients
        inspectorSprite.load("images/People/Inspector.png");
        entityManager->addClient(new Inspector(0, 50, 64, 72, inspectorSprite, b, true));
    } else {
        entityManager->addClient(new Client(0, 50, 64, 72,people[ofRandom(8)], b, false));
    }
}
void Restaurant::render() {
    floor.draw(0,0, ofGetWidth(), ofGetHeight());
    player->render();
    entityManager->render();
    table.load("images/Table.png");
    table.draw(170,170);
    table.draw(170,300);
    table.draw(446,170);
    table.draw(446,300);
    plant.load("images/Plant.png");
    plant.draw(296, 39);
    hangingPlant.load("images/Hanging-Plant.png");
    hangingPlant.draw(619, -29);
    ofSetColor(255);
    ofDrawBitmapStringHighlight("Money: " + to_string(money), ofGetWidth()/2, 10, ofColor(0));
    ofSetColor(256, 256, 256);
    if (StoveCounter::isCooking){   // draws progress bar when cooking patty
        ofDrawRectangle(215, ofGetHeight()-315, 50, 10);
        ofSetColor(255, 148, 180);
        ofDrawRectangle(215, ofGetHeight()-315, StoveCounter::cookTime, 10);
        ofSetColor(255);
    }
}
void Restaurant::serveClient(){
    if(entityManager->firstClient != nullptr){
        vector<Item *> playerBurger = player->getBurger()->getIngredients();
        money += entityManager->firstClient->serve(playerBurger, ingredientOptions); // changes isLeaving to true
    }
    player->getBurger()->clear();
}
void Restaurant::keyPressed(int key) {
    player->keyPressed(key);
    if (key == 's') {
        serveClient();
    } else if (key == 'e') { // substracts $1 for every ingredient added
        if (player->getActiveStove() != nullptr && StoveCounter::isCooked) {
            if (player->getActiveStove()->getItem() != nullptr) {
                money--;
                StoveCounter::isCooked = false;
            }
        } else if (player->getActiveBase() != nullptr && player->getActiveStove() == nullptr) {
            if (player->getActiveBase()->getItem() != nullptr) {
                money--;
            }
        }
    } 
}
