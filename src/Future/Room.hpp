#ifndef ROOM_HPP
#define ROOM_HPP

#include "Future/ResourceHolder.hpp"
#include "Future/ResourceIdentifiers.hpp"
#include "Future/SceneNode.hpp"
#include "Future/SpriteNode.hpp"
#include "Future/Actor.hpp"
#include "Future/CommandQueue.hpp"
#include "Future/Command.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

#include <array>
#include <vector>

namespace sf
{
	class RenderWindow;
}


class Room : private sf::NonCopyable
{
public:
	Room(sf::RenderWindow& window, FontHolder& fonts);

public:
	void			update(sf::Time dt);
	void			draw();

	CommandQueue& 	getCommandQueue();

	bool            hasAlivePlayer() const;
	bool 			hasFinishedLevel() const;
	bool		    isWinConditionMet() const;
	
private:
	void		    loadTextures();
	void            adaptPlayerPosition();
	void            adaptPlayerVelocity();
	void            handleCollisions();
	
	void            buildScene();
	void            addEnemies();
	void            addEnemy(Actor::Type type, float relX, float relY);
	void            spawnEnemies();
	sf::FloatRect   getViewBounds() const;

private:
	enum class Layer
	{
		Background,
		Playfield,
		Cables,
	};

	struct SpawnPoint
	{
		SpawnPoint(Actor::Type pType, float pX, float pY)
			: type(pType)
			, x(pX)
			, y(pY)
		{
		}

		Actor::Type     type;
		float x;
		float y;
	};

private:
	sf::RenderWindow&                   mWindow;
	sf::View                            mWorldView;
	TextureHolder                       mTextures;
	FontHolder&                         mFonts;

	SceneNode                           mSceneGraph;
	std::map<Layer, SceneNode*>			mSceneLayers;
	CommandQueue 						mCommandQueue;

	sf::FloatRect                       mWorldBounds;
	sf::Vector2f                        mSpawnPosition;
	float                               mScrollSpeed;
	Actor*                              mFinishLine;
	Actor*                              mPlayerCharacter;
	Actor*                              mArrow;

	bool 								mWinFlag;

	std::vector<SpawnPoint>             mEnemySpawnPoints;
	std::vector<Actor*>                 mActiveEnemies;
};

#endif // ROOM_HPP