#include "Future/TriggerNode.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

TriggerNode::TriggerNode(Command::Action action)
	:mAction(action)
{
}

sf::FloatRect TriggerNode::getBoundingRect() const
{
	return sf::FloatRect(getPosition(), { 40.f,40.f });
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
