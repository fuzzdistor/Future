#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Future/Command.hpp"

#include <SFML/Window/Event.hpp>

#include <map>

class CommandQueue;

class Player
{
public:
	enum class ActionID
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		ToggleDebugMode,
		Connect,
		ActionCount
	};

	enum class MissionStatus
	{
		MissionRunning,
		MissionSuccess,
		MissionFailure,
	};

public:
	Player();

public:
	void                handleEvent(const sf::Event& event, CommandQueue& commands);
	void                handleRealTimeInput(CommandQueue& commands);

	void                assignKey(ActionID action, sf::Keyboard::Key key);
	sf::Keyboard::Key   getAssignedKey(ActionID action) const;

	void                setMissionStatus(MissionStatus status);
	MissionStatus       getMissionStatus() const;

private:
	void                initActions();
	void                initAction(sf::Keyboard::Key key, ActionID actionID, Command::Action action, Category::Type category = Category::Type::PlayerActor);
	static bool         isRealTimeAction(ActionID action);

private:
	std::map<sf::Keyboard::Key, ActionID>     mKeyBinding;
	std::map<ActionID, Command>               mActionBinding;
	MissionStatus 							mCurrentMissionStatus;
};

#endif // PLAYER_HPP