#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category
{
	enum class Type
	{
		None                = 0,
		Static              = 1 << 0,
		PlayerActor         = 1 << 1,
		AlliedActor         = 1 << 2,
		EnemyActor          = 1 << 3,
		Door                = 1 << 5,
		SceneAirLayer       = 1 << 7,
		Unknown             = 1 << 8,
		Trigger             = 1 << 9,

        test = 1 << 30, //! a ver a ver
		
		Actor = PlayerActor | EnemyActor | AlliedActor,
		All = 0xFFFFFF,
	};
};

#endif // CATEGORY_HPP
