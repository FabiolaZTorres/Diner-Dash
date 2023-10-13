#include "Player.h"

Player::Player(int x, int y, int width, int height, ofImage sprite, EntityManager* em) : Entity(x, y, width, height, sprite){

    vector<ofImage> chefAnimframes;
    ofImage temp;
    this->burger = new Burger(ofGetWidth()-110, 100, 100, 50);
    temp.cropFrom(sprite, 30,3,66,120);
    chefAnimframes.push_back(temp);
    temp.cropFrom(sprite, 159,3,66,120);
    chefAnimframes.push_back(temp);
    temp.cropFrom(sprite, 287, 3,67,120);
    chefAnimframes.push_back(temp);
    temp.cropFrom(sprite, 31,129,66,120);
    chefAnimframes.push_back(temp);
    this->chefAnim = new Animation(50, chefAnimframes);
    this->entityManager = em;
    
}
void Player::tick(){
    chefAnim->tick();
}

void Player::render(){
    BaseCounter *ac = getActiveBase();
    if (ac != nullptr) {
        ac->showItem();
    }
    ofSetColor(256, 256, 256);
    ofImage currentFrame = chefAnim->getCurrentFrame();
    if (facing == "left") {
        currentFrame.mirror(false, true);
    }
    currentFrame.draw(x, y, width, height);
    burger->render();
}

void Player::keyPressed(int key){
    if(key == 'e'){
        BaseCounter* ac = getActiveBase();
        StoveCounter* stove = getActiveStove();
        if(stove != nullptr){
            Item* item = ac->getItem();
            if(item != nullptr){
                if(StoveCounter::isCooked){ // adds patty if cooked and resets variables
                    burger->addIngredient(item);
                    StoveCounter::isCooked = false;
                    StoveCounter::isCooking = false;
                    StoveCounter::cookTime = 0;
                } else {    // starts cooking patty
                    StoveCounter::isCooking = true;
                }
            }
        }else if(ac != nullptr){
            Item* item = ac->getItem();
            if(item != nullptr){
                burger->addIngredient(item);
            }
        }
    } 
    else if (key == 'u'){
        burger->removeIngredient();
    }
    else if (key == OF_KEY_LEFT){
        facing = "left";
        if(x > 0){
           x -= speed; 
        }
    }
    else if (key == OF_KEY_RIGHT){
        facing = "right";
        if (x + width < ofGetWidth()){
            x += speed;
        }
    }
}
BaseCounter* Player::getActiveBase(){
    for(Entity* e:entityManager->entities){
        BaseCounter* c = dynamic_cast<BaseCounter*>(e);
        if(x + e->getWidth()/2 >= e->getX() && x +e->getWidth()/2 <e->getX() + e->getWidth()){
            return c;
        }
    }
    return nullptr;
}
StoveCounter* Player::getActiveStove(){
    for(Entity* e:entityManager->entities){
        StoveCounter* c = dynamic_cast<StoveCounter*>(e);
        if(x + e->getWidth()/2 >= e->getX() && x +e->getWidth()/2 <e->getX() + e->getWidth()){
            return c;
        }
    }
    return nullptr;
}

void Player::keyReleased(int key) {
}
void Player::mousePressed(int x, int y, int button) {
}

void Player::setFacing(string facing){ this->facing = facing; }