#ifndef TRIGGERNODE_HPP
#define TRIGGERNODE_HPP

#include "Future/SceneNode.hpp"
#include "Future/Command.hpp"

class TriggerNode: public SceneNode
{
public:
	explicit TriggerNode(Command::Action action);

public:
	virtual sf::FloatRect 		getBoundingRect() const override;
	virtual Category::Type 		getCategory() const override;
	Command::Action				getAction() const;

private:
	virtual void 				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Command::Action 			mAction;

};

#endif // TRIGGERNODE_HPP
