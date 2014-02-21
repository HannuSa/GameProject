#ifndef GameState_H
#define GameState_H

enum State
{
	PAUSED = 0,
	GROUP_1_TURN,
	GROUP_2_TURN
};

class GameState
{
public:
	GameState();
	~GameState();
	void NewState(State s);
	State returnState();
private:
	State state;
};

#endif