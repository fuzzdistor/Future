#ifndef LABEL_HPP
#define LABEL_HPP

#include "gui/Component.hpp"
#include "Future/ResourceIdentifiers.hpp"
#include "Future/ResourceHolder.hpp"

#include <SFML/Graphics/Text.hpp>

#include <memory>
#include <string>

namespace sf
{
	class Event;
}

namespace GUI
{
class Label : public Component
{	
public:
	typedef std::shared_ptr<Label> Ptr;

public:
	Label(const std::string& text, const FontHolder& font);
	
public:
	virtual bool    isSelectable() const override;
	void            setText(const std::string& text);

	virtual void    handleEvent(const sf::Event& event) override;

private:
	void		    draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Text        mText;
};
}

#endif // LABEL_HPP
