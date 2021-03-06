#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Future/ResourceHolder.hpp"
#include "Future/ResourceIdentifiers.hpp"
#include "Future/Player.hpp"
#include "states/StateStack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>


class Application {

public:
    Application();
    
public:
    void    run();

private:
    void    processEvents();
    void    update(sf::Time dt);
    void    render();
    void     loadInitialResources();

    void    updateStatistics(sf::Time dt);
    void    registerStates(); 

    void    updateMousePositionCoord();

private:
    static const sf::Time       TimePerFrame;

    sf::RenderWindow            mWindow;
    TextureHolder               mTextures;
    FontHolder                  mFonts;
    Player                      mPlayer;

    StateStack                  mStateStack;

    bool                        mWindowHasFocus;

    sf::Text                    mStatisticsText;
    sf::Time                    mStatisticsUpdateTime;
    std::size_t                 mStatisticsFrameCount;
    std::size_t                 mStatisticsFramesPerSecond;
    sf::Text                    mMousePositionText;
    sf::Vector2i                mMousePosition;
};

#endif // APPLICATION_HPP
