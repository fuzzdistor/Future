#ifndef TEXTNODE_HPP
#define TEXTNODE_HPP

#include "Future/ResourceHolder.hpp"
#include "Future/ResourceIdentifiers.hpp"
#include "Future/SceneNode.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <string>

class TextNode : public SceneNode
{
public:
	explicit TextNode(const FontHolder& fonts, const std::string& text);

public:
	void			setString(const std::string& string);

private:
	virtual void 	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Text 		mText;
};

#endif // TEXTNODE_HPP
