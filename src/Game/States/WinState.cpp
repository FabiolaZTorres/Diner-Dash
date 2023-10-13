#include "WinState.h"

WinState::WinState(){
    youWinImage.load("images/YouWin.png");
    std::string returnTitle = "Return to title screen";
    titleButton = new Button(ofGetWidth()/2-288, ofGetHeight()/2+70, returnTitle.length()*18, 20, returnTitle);
}
void WinState::tick(){
    titleButton->tick();
    if (titleButton->wasPressed()){ // returns to title screen
        setNextState("Menu");
        setFinished(true);
    }
}
void WinState::render(){
    ofSetBackgroundColor(195, 177, 225);
    ofSetColor(255);
    youWinImage.draw(0, 0, ofGetWidth(), ofGetHeight());
    titleButton->render();
}
void WinState::keyPressed(int key){
}
void WinState::mousePressed(int x, int y, int button){
    titleButton->mousePressed(x, y);
}
void WinState::reset(){
    setFinished(false);
    setNextState("");
    titleButton->reset();
}