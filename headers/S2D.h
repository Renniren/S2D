#ifndef S2D_MAIN_HEADER
#define S2D_MAIN_HEADER

#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#ifndef S2D_DEFINES
#define S2D_DEFINES

#define S2D_DEBUG

#endif // !S2D_DEFINES

#ifndef S2D_SETTINGS
#define S2D_SETTINGS

string game_name = "S2D Game";
string game_debug_name = "S2D Test Game (Debug): ";

#endif

#ifndef S2D_EVENTS
#define S2D_EVENTS

class object
{
public:
	int instance_id;

	virtual string to_string()
	{

		return "";
	}
};

#endif

#ifndef S2D_MACROS
#define S2D_MACROS

#define init_behavior active_objects.push_back(&(*this))

#endif

RenderWindow* GAME_WINDOW;
sf::Event event;

bool doClear = true;

enum simulate_flags { SimulateOnlyWhenLevelActive, SimulateAlways, SimulateAlwaysDontDraw };

class time
{
	static Clock global_clock;
	static Time _time;
public:
	static Int64 delta;

	static void init()
	{
		global_clock = Clock();
	}

	static void update()
	{
		static Int64 last;
		_time = global_clock.getElapsedTime();
		static Int64 current = _time.asMilliseconds();
		delta = current - last;
		last = current;
	}
};

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

	level(string name, world settings)
	{
		this->name = name;
		this->world_settings = settings;
	}
};

world default_world = { "World", Color::Black };
world current_world = default_world;

level* default_level = new level(string("Default Level"), default_world);
level* current_level = default_level;

//keeps record of every loaded texture, and their accompanying sprite to keep textures alive
vector<pair<Texture*, Sprite*>> textures;
void create_texture_pair(Texture* tex, Sprite* spr)
{
	textures.push_back(pair<Texture*, Sprite*>(tex, spr));
}

Sprite create_sprite(string texturepath)
{
	Texture* texture = new Texture();
	Sprite* ret;
	if (!texture->loadFromFile(texturepath)) return Sprite();
	ret = new Sprite(*texture);
	create_texture_pair(texture, ret);
	ret->setOrigin(0.25f, 0.25f);
	return *ret;
}

class world_object
{
public:
	static vector<world_object*> active_objects;
	Vector2f position, scale;
	level* parent_level;
	Sprite sprite;
	simulate_flags flags = simulate_flags::SimulateOnlyWhenLevelActive;
	string name;
	float rotation;

	void levelChanged()
	{

	}

	virtual void update(){}

	void tick()
	{
		switch (this->flags)
		{
		case SimulateAlways:
				sprite.setPosition(position);
				sprite.setRotation(rotation);
				sprite.setScale(scale);
				GAME_WINDOW->draw(sprite);
				update();
			break;

		case SimulateAlwaysDontDraw:
			update();
			break;

		case SimulateOnlyWhenLevelActive:
			if (parent_level->name != current_level->name) return;
				sprite.setPosition(position);
				sprite.setRotation(rotation);
				sprite.setScale(scale);
				GAME_WINDOW->draw(sprite);
				update();
			break;
		}
	}

	world_object()
	{
		parent_level = nullptr;
		rotation = 0;
		position = Vector2f(0, 0);
		name = "new WorldObject";
	}
};

class player : public world_object, public object
{
public:
	float speed = 0.9f;

	player()
	{
		init_behavior;

		scale = Vector2f(0.03, 0.03);
		sprite = create_sprite("sprites\\circle.png");
	}

	void update()
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			position.y -= speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			position.y += speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			position.x -= speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			position.x += speed;
		}
	}
};

class camera : public world_object
{
	float zoom = 10;

	camera()
	{
		init_behavior;
	}
};

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

vector<world_object*> world_object::active_objects = vector<world_object*>();

void update_active_objects()
{
	for (size_t i = 0; i < world_object::active_objects.size(); i++)
	{
		world_object::active_objects[i]->tick();
	}
}

#endif
