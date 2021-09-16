#include "Future/TriggerNode.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

TriggerNode::TriggerNode(Command::Action action)
	: mRect({ 40.f, 40.f })
    , mAction(action)
{
    mRect.setFillColor(sf::Color(0u, 255u, 0u, 120u));
}

sf::FloatRect TriggerNode::getBoundingRect() const
{
	return sf::FloatRect(getWorldPosition(), mRect.getSize());
}

void TriggerNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rect;
	rect.setPosition(0.f,0.f);
	rect.setSize({ getBoundingRect().width, getBoundingRect().height });
	rect.setFillColor(sf::Color(0U, 255U, 0U, 120U));

	target.draw(rect, states);
}

Command::Action TriggerNode::getAction() const
{
	return mAction;
}

Category::Type TriggerNode::getCategory() const
{
	return Category::Type::Trigger;
}
