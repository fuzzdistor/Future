#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "gui/Component.hpp"

#include <optional>
#include <vector>
#include <memory>

namespace sf
{
    class Event;
}

namespace GUI
{

class Container : public Component
{
public:
    typedef std::shared_ptr<Container> Ptr;

public:
    Container();

public:
    // adds the component param and points mSelectedChild to it 
    void            pack(Component::Ptr component);

    virtual bool    isSelectable() const override;
    virtual void    handleEvent(const sf::Event& event) override;

private:
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void    selectIndex(size_t index);
    void    selectNext();
    void    selectPrevious();

private:
    std::vector<Component::Ptr>     mChildren;
    std::optional<size_t>           mSelectedChild;
};

}

#endif // CONTAINER_HPP
