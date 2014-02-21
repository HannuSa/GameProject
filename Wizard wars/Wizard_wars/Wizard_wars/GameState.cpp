#include "GameState.h"

GameState::GameState()
{
	state = PAUSED;
}

GameState::~GameState()
{}

void GameState::NewState(State s)
{
	state = s;
}

State GameState::returnState()
{
	return state;
}