#ifndef TRIGGERNODE_HPP
#define TRIGGERNODE_HPP

#include "Future/SceneNode.hpp"
#include "Future/Command.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class TriggerNode: public SceneNode
{
public:
	explicit TriggerNode(Command::Action action);

public:
	virtual sf::FloatRect 		getBoundingRect() const override;
	virtual Category::Type 		getCategory() const override;
	Command::Action				getAction() const;

private:
	virtual void 				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape          mRect;
	Command::Action 			mAction;

};

#endif // TRIGGERNODE_HPP
