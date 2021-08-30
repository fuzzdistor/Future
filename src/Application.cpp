#include "Future/Application.hpp"
#include "states/TitleState.hpp"
#include "states/MenuState.hpp"
#include "states/GameState.hpp"
#include "states/PauseState.hpp"
#include "states/SettingsState.hpp"
#include "states/GameOverState.hpp"

#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#ifndef NDEBUG
#define WIN_TITLE "!!!DEBUG!!! Future Game"
#else
#define WIN_TITLE "Future Game"
#endif

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
	: mWindow(sf::VideoMode(1280, 720), WIN_TITLE)
	, mTextures()
	, mFonts()
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
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
	std::ifstream i("../src/Textures.json");
	nlohmann::json data;
	i >> data;

	// load textures
	for (auto elem: data["Title"]["Textures"])
		mTextures.load(elem["ID"].get<Textures::ID>(), elem["file"].get<std::string>());

	// load fonts
	for (auto elem: data["Title"]["Fonts"])
		mFonts.load(elem["ID"].get<Fonts::ID>(), elem["file"].get<std::string>());
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	bool p_open = false;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);

		
	
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
			
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