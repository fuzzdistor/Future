#include "Future/Application.hpp"
#include "Future/json.hpp"
#include "states/TitleState.hpp"
#include "states/MenuState.hpp"
#include "states/GameState.hpp"
#include "states/PauseState.hpp"
#include "states/SettingsState.hpp"
#include "states/GameOverState.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#ifndef NDEBUG
#define WIN_TITLE "!!!DEBUG!!! Future Game"
#else
#define WIN_TITLE "Future Game"
#endif

using json = nlohmann::json;

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);
const std::vector<sf::Vector2u> Resolutions = {{2840, 2160}, {2560, 1440}, {1920, 1080}, {1280, 720}, {854, 480}, {640, 360}, {426, 240}};

// TODO fix implementation. Desired result: retrun the appropiate resolution
// that is immediately smaller than the current one.
// Ex:  Current window size: 1300x900 -> return 1280x720
//                           900x500 -> return 854x480
sf::Vector2u getAppropiateResolution(const sf::Vector2u &size)
{
    sf::Vector2u result = size;
    for (auto res = Resolutions.rbegin(); res != Resolutions.rend(); res++)
        if (size.x >= res->x && size.y >= res->y)
            result = *res;

    return result;
}    

Application::Application()
	: mWindow(sf::VideoMode(1280, 720), WIN_TITLE)
	, mTextures()
	, mFonts()
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
    , mWindowHasFocus(true)
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsFrameCount(0)
	, mStatisticsFramesPerSecond(0)
{
	mWindow.setKeyRepeatEnabled(false);
 
	loadInitialResources();

	registerStates();

	mStatisticsText.setFont(mFonts.get(Fonts::ID::Mono));
	mStatisticsText.setCharacterSize(10U);
	mStatisticsText.setPosition(10.f,10.f);

    mStateStack.pushState(States::ID::Title);
}

void Application::loadInitialResources()
{
    // read data from file to data object. throw if file couldn't be opened.
    std::string jsonPath = "../src/Resources.json";
	std::ifstream i(jsonPath);
	if (i.fail())
		throw std::runtime_error("Could not open file: " + jsonPath);
	json data;
	i >> data;
	i.close();

	// load textures
	loadResource<Textures::ID>(mTextures, data["Title"]["Textures"]);

	// load fonts
	loadResource<Fonts::ID>(mFonts, data["Title"]["Fonts"]);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();

            // Only update if window has focus
            if (mWindowHasFocus)
                update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
        }

        updateStatistics(dt);

        render();
    }
}

void Application::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
        // application related event handling
        if (event.type == sf::Event::Closed)
            mWindow.close();
        if (event.type == sf::Event::LostFocus)
            mWindowHasFocus = false;
        if (event.type == sf::Event::GainedFocus)
            mWindowHasFocus = true;

        // don't update the states if window is out of focus
        if (mWindowHasFocus)
            mStateStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());

	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsFrameCount += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsFramesPerSecond = mStatisticsFrameCount;
		mStatisticsText.setString("FPS: " + std::to_string(mStatisticsFrameCount));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsFrameCount = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::ID::Title);
	mStateStack.registerState<MenuState>(States::ID::Menu);
	mStateStack.registerState<GameState>(States::ID::Game);
	mStateStack.registerState<PauseState>(States::ID::Pause);
	mStateStack.registerState<SettingsState>(States::ID::Settings);
	mStateStack.registerState<GameOverState>(States::ID::GameOver);
}
