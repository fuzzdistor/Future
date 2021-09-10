#include "states/StateStack.hpp"
#include "states/State.hpp"


State::Context::Context(sf::RenderWindow& window_, TextureHolder& textures_, FontHolder& fonts_, Player& player_)
: window(&window_)
, textures(&textures_)
, fonts(&fonts_)
, player(&player_)
{
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
