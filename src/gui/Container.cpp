#include "gui/Container.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

GUI::Container::Container()
    : mChildren()
    , mSelectedChild(std::nullopt)
{
}

void GUI::Container::pack(Component::Ptr component)
{
    mChildren.push_back(component);

    if (!mSelectedChild && component->isSelectable())
        selectIndex(mChildren.size() - 1);
}

bool GUI::Container::isSelectable() const
{
    return false;
}

void GUI::Container::handleEvent(const sf::Event &event)
{
    //TODO figure out how to fix this stuff of add it to player or smthing
    // If we have selected a child then give it events
    if (mSelectedChild && mChildren[mSelectedChild.value()]->isActive())
    {
        mChildren[mSelectedChild.value()]->handleEvent(event);
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        {
            selectPrevious();
        }
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        {
            selectNext();
        }
        else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
        {
            if (mSelectedChild)
                mChildren[mSelectedChild.value()]->activate();
        }
    }
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (auto& child : mChildren)
        target.draw(*child, states);
}

void GUI::Container::selectIndex(size_t index)
{
    if (mChildren[index]->isSelectable())
    {
        if (mSelectedChild)
            mChildren[mSelectedChild.value()]->deselect();

        mChildren[index]->select();
        mSelectedChild = index;
    }
}

void GUI::Container::selectNext()
{
    if (!mSelectedChild)
        return;

    // Search next component that is selectable, wrap around if necessary
    size_t next = mSelectedChild.value();
    do
        next = (next + 1) % mChildren.size();
    while (!mChildren[next]->isSelectable());

    // Select that component
    selectIndex(next);
}

void GUI::Container::selectPrevious()
{
    if (!mSelectedChild)
        return;

    // Search previous component that is selectable, wrap around if necessary
    size_t prev = mSelectedChild.value();
    do
        prev = (prev + mChildren.size() - 1) % mChildren.size();
    while (!mChildren[prev]->isSelectable());

    // Select that component
    selectIndex(prev);
}
