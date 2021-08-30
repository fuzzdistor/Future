#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include "Future/Actor.hpp"
#include "Future/ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <functional>
#include <map>
#include <vector>


struct Direction
{
	Direction(float angle, float distance)
		: angle(angle)
		, distance(distance)
	{
	}

	float   angle;
	float   distance;
};

struct ActorData
{
	float                       speed;
	Textures::ID                texture;
	std::vector<Direction>      directions;
};

std::map<Actor::Type, ActorData>  initActorData();

template <typename Type, typename Data>
const Data& getDataTableOf(Type type, const std::map<Type, Data>& table);

#include "DataTables.ipp"
#endif // DATATABLES_HPP