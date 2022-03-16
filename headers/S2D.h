#ifndef S2D_MAIN_HEADER
#define S2D_MAIN_HEADER
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#ifndef S2D_DEFINES
#define S2D_DEFINES

#define S2D_DEBUG

#endif // !S2D_DEFINES

#ifndef S2D_SETTINGS
#define S2D_SETTINGS

string game_name = "S2D Empty - ";

#endif

RenderWindow* GAME_WINDOW;
bool doClear = true;

class world
{
public:
	string name;
	Color clear_color;

};

class level
{
public:
	string name;
	world world_settings;
	class world_object
	{
		Vector2<float> position, scale;
		level* current_level;
	};
};

world default_world = { "Default World", Color::Black };
world current_world = default_world;


level* current_level;
void set_current_level(level* destination)
{
	current_level = destination;
}

#endif
