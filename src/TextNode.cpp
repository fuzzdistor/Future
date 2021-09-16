#include "Future/TextNode.hpp"
#include "Future/Utils.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

    
TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
    mText.setFont(fonts.get(Fonts::ID::Main));
    mText.setCharacterSize(20);
    setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);
}

void TextNode::setString(const std::string& text)
{
    mText.setString(text);
    util::centerOrigin(mText);
}
