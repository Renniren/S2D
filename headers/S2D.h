#ifndef S2D_MAIN_HEADER
#define S2D_MAIN_HEADER
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#ifndef S2D_DEFINES
#define S2D_DEFINES

#define S2D_DEBUG

#endif // !S2D_DEFINES

#ifndef S2D_SETTINGS
#define S2D_SETTINGS

string game_name = "S2D Game - ";

#endif

#ifndef S2D_EVENTS
#define S2D_EVENTS

template <typename type>
class Event
{
	type returnType;
	type fn;
	vector<type> events;
public:
	Event(void* func)
	{
		type (*function)(type){ func };
		fn = function;
	}

	Event(vector<void*> events)
	{
		for (int i = 0; i < events.size(); int i++)
		{
			type(*function)(type) { events[i] };
			this->events.push_back(function);
		}
	}

	void Subscribe(void* method)
	{
		type(*function)(type) { method };
		events.push_back(function);
	}

	void Invoke()
	{
		(*fn)();
	}
};

#endif

RenderWindow* GAME_WINDOW;
bool doClear = true;
class S2D_event_handler
{
public:
	__event void game_tick();

};

S2D_event_handler* evh;

class world
{
public:
	string name;
	Color clear_color;
};

enum simulate_flags { SimulateOnlyWhenLevelActive, SimulateAlways, SimulateAlwaysDontDraw };

class level
{
public:
	string name;
	world world_settings;
};

level* current_level;

class world_object
{
public:
	Vector2f position, scale;
	level* parent_level;
	Sprite sprite;
	simulate_flags flags = simulate_flags::SimulateOnlyWhenLevelActive;
	string name;
	float rotation;

	void levelChanged()
	{

	}

	void tick()
	{
		printf("t");
		switch (flags)
		{
		case SimulateAlways:
			sprite.setPosition(position);
			sprite.setRotation(rotation);
			sprite.setScale(scale);
			GAME_WINDOW->draw(sprite);
			break;

		case SimulateAlwaysDontDraw:

			break;

		case SimulateOnlyWhenLevelActive:
			if (parent_level != current_level) return;
				sprite.setPosition(position);
				sprite.setRotation(rotation);
				sprite.setScale(scale);
				GAME_WINDOW->draw(sprite);
			break;
		}
	}

	world_object()
	{
		parent_level = nullptr;
		rotation = 0;
		position = Vector2f(0, 0);
		name = "new WorldObject";
		//__hook(&S2D_event_handler::game_tick, evh, &world_object::tick);
		printf("\nd");
	}
};

class player
{
public:
	void update()
	{
		printf("\ng");
	}
};

world default_world = { "No World", Color::Black };
world current_world = default_world;


void set_current_level(level* destination)
{
	if (destination == nullptr)
	{
		printf("\nError when setting level: provided level was null.");
		return;
	}
	if (current_level != nullptr)
	{
		if (destination->name != current_level->name)
		{
			current_level = destination;
		}
	}
}

//keeps record of every loaded texture, and their accompanying sprite to keep textures alive
vector<pair<Texture*, Sprite*>> textures;
void create_texture_pair(Texture* tex, Sprite* spr)
{
	textures.push_back(pair<Texture*, Sprite*>(tex, spr));
}

Sprite* create_sprite(string texturepath)
{
	Texture* texture = new Texture();
	Sprite* ret;
	if(!texture->loadFromFile(texturepath)) return nullptr;
	ret = new Sprite(*texture);
	create_texture_pair(texture, ret);
	ret->setOrigin(0.25f, 0.25f);
	return ret;
}


#endif
