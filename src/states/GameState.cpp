#include "states/GameState.hpp"


GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mRoom(*context.window, *context.fonts)
, mPlayer(*context.player)
{
	mPlayer.setMissionStatus(Player::MissionStatus::MissionRunning);
}

void GameState::draw()
{
	mRoom.draw();
}

bool GameState::update(sf::Time dt)
{
	mRoom.update(dt);

	if(!mRoom.hasAlivePlayer())
	{
		mPlayer.setMissionStatus(Player::MissionStatus::MissionFailure);
		requestStackPush(States::ID::GameOver);
	}
	else if(mRoom.isWinConditionMet())
	{
		mPlayer.setMissionStatus(Player::MissionStatus::MissionSuccess);
		requestStackPush(States::ID::GameOver);
	}

	CommandQueue& commands = mRoom.getCommandQueue();
	mPlayer.handleRealTimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = mRoom.getCommandQueue();
	
	// Game input handling
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::ID::Pause);

	return true;
}