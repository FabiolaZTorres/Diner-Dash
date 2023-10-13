#include "LoseState.h"

LoseState::LoseState(){
    gameOverImage.load("images/GameOver.png");
    std::string returnTitle = "Return to title screen";
    titleButton = new Button(ofGetWidth()/2-288, ofGetHeight()/2+70, returnTitle.length()*18, 20, returnTitle);
}
void LoseState::tick(){
    titleButton->tick();
    if (titleButton->wasPressed()){ // returns to title screen
        setNextState("Menu");
        setFinished(true);
    }
}
void LoseState::render(){
    ofSetBackgroundColor(195, 177, 225);
    ofSetColor(255);
    gameOverImage.draw(0,0,ofGetWidth(),ofGetHeight());
    titleButton->render();
}
void LoseState::keyPressed(int key){
}
void LoseState::mousePressed(int x, int y, int button){
    titleButton->mousePressed(x, y);
}
void LoseState::reset(){
    setFinished(false);
	setNextState("");
    titleButton->reset();
}