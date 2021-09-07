#include "Future/Player.hpp"
#include "Future/Actor.hpp"

#include <SFML/System/Vector2.hpp>

struct ActorMover
{
	ActorMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Actor& actor, sf::Time) const
	{
		actor.accelerate(velocity * actor.getMaxSpeed());
	}

	sf::Vector2f velocity;
};

size_t Player::getActionsSize() const
{
	return mActionBinding.size();
}

Player::Player()
	: mCurrentMissionStatus(MissionStatus::MissionRunning)
    , mRegisteredActions()
	, mKeyBinding()
	, mActionBinding()
{
	initActions();
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealTimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
	for (auto pair: mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(ActionID action, sf::Keyboard::Key key)
{
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			itr++;
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(ActionID action) const 
{
	for (auto pair: mKeyBinding)
		if (pair.second == action)
			return pair.first;

	return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}

void Player::initActions()
{
	initAction(sf::Keyboard::Left, 		ActionID::MoveLeft, 		derivedAction<Actor>(ActorMover(-1,  0)));
	initAction(sf::Keyboard::Right, 	ActionID::MoveRight, 		derivedAction<Actor>(ActorMover(+1,  0)));
	initAction(sf::Keyboard::Up, 		ActionID::MoveUp, 			derivedAction<Actor>(ActorMover( 0, -1)));
	initAction(sf::Keyboard::Down, 		ActionID::MoveDown, 		derivedAction<Actor>(ActorMover( 0, +1)));

	initAction(sf::Keyboard::Q, 		ActionID::ToggleDebugMode, 	derivedAction<SceneNode>([] (SceneNode& s, sf::Time dt){ s.toggleDebugFlag(); }), Category::Type::All);
}

std::vector<Player::ActionID>& Player::getRegisteredActions()
{
    return mRegisteredActions;
}
void Player::initAction(sf::Keyboard::Key key, ActionID actionID, Command::Action action, Category::Type category)
{
    mRegisteredActions.push_back(actionID);
	mKeyBinding[key] = actionID;
	mActionBinding[actionID].action  = action;
	mActionBinding[actionID].category  = category;

}

bool Player::isRealTimeAction(ActionID action)
{
	switch (action)
	{
		case ActionID::MoveLeft:
		case ActionID::MoveRight:
		case ActionID::MoveDown:
		case ActionID::MoveUp:
		//case ActionID::Fire:
			return true;

		default:
			return false;
	}
}
