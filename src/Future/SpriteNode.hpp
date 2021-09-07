#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

#include "Future/SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

    sf::FloatRect       getGlobalBounds() const;

private:
	virtual void 		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite 			mSprite;
};

#endif // SPRITENODE_HPP
