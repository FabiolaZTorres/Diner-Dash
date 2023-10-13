#include "GameState.h"

GameState::GameState() {
    this->restaurant = new Restaurant();
}
void GameState::tick() {
	// changes gamestate and resets all variables
	if (Client::clientsLeft == 10){
		setNextState("Lose");
		setFinished(true);
		Restaurant::money = 0;
		StoveCounter::isCooked = false;
		StoveCounter::isCooking = false;
		StoveCounter::cookTime = 0;
		Client::clientsLeft = 0;
	} else if (Restaurant::money >= 100){
		setNextState("Win");
		setFinished(true);
		Restaurant::money = 0;
		StoveCounter::isCooked = false;
		StoveCounter::isCooking = false;
		StoveCounter::cookTime = 0;
		Client::clientsLeft = 0;
	}
	restaurant->tick();
}
void GameState::render() {
	restaurant->render();
}

void GameState::keyPressed(int key){
	restaurant->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button){
}

void GameState::keyReleased(int key){
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
}