#include "MenuState.h"

MenuState::MenuState() {
	titleScreen.load("images/Burger-TitleScreen.png");
	string text = "Start";
	startButton = new Button(ofGetWidth()/2 - text.length()*8, ofGetHeight()/2 - text.length()*11, 64, 50, "Start");
}
void MenuState::tick() {
	startButton->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}
}
void MenuState::render() {
	ofSetBackgroundColor(148, 148, 105);
	ofSetColor(255);
	titleScreen.draw(0, 0, ofGetWidth(), ofGetHeight());

	if (gameInstructions == false) {
			startButton->render();
			ofSetColor(0);
			ofDrawBitmapString("'m' --- toggle menu", ofGetWidth()/2 - 60, 20);
	}

	if (gameInstructions == true) {
		// Draws transparent white rectangle
		ofEnableAlphaBlending();

		ofSetColor(255, 255, 255, 150);
		ofDrawRectRounded(ofGetWidth()/2 - 142, 233, 300, 249, 10);

		ofSetColor(0);

		// Displays text
		ofDrawBitmapString("Game Instructions", ofGetWidth()/2 - 60, 304);
		ofDrawBitmapString("'<-' --- move to the left", ofGetWidth()/2 - 124, 342);
		ofDrawBitmapString("'->' --- move to the right", ofGetWidth()/2 - 124, 362);
		ofDrawBitmapString("'e' --- pick up/cook ingredients", ofGetWidth()/2 - 124, 382);
		ofDrawBitmapString("'s' --- serve clients", ofGetWidth()/2 - 124, 402);
		ofDrawBitmapString("'u' --- undo", ofGetWidth()/2 - 124, 422);
	}
}

void MenuState::keyPressed(int key){
	if (key == 'm') {
		gameInstructions = !gameInstructions;
	}
}

void MenuState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
}

void MenuState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}