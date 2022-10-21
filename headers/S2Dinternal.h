#ifndef S2D_MAIN_HEADER
#define S2D_MAIN_HEADER

#include <string>
#include <vector>
#include<box2d.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include<functional>
#include <SFML/Graphics.hpp>
#include <sstream>

#ifndef GUARD_S2D_DEFINES
#define GUARD_S2D_DEFINES

//#define S2D_DEBUG

#endif // !S2D_DEFINES

#ifndef GUARD_S2D_SETTINGS
#define GUARD_S2D_SETTINGS

std::string game_name = "S2D Game";
std::string game_debug_name = "S2D Test Game (Debug): ";

#endif

#ifndef GUARD_S2D_EVENTS
#define GUARD_S2D_EVENTS

#endif

#ifndef GUARD_S2D_MACROS
#define GUARD_S2D_MACROS

//Macros for static class member definitons. Unnecessary, but sometimes convenient.
#define MStaticDefinition(type, cls, name) type cls::name = type()
#define MStaticPointerDefinition(type, cls) type cls::type = new type()

#define REGISTER_CLASS static void RegisterClass
#define Instantiate(x) new x()
#define init_gameobject \
ActiveObjects.push_back(new GameObject::GameObjectInstance(this));
#define init_updatable UpdatableObjects.push_back(this)
#define init_behavior ActiveBehaviors.push_back(new Behavior::BehaviorInstance(this))
#define debug_log(x)\
std::cout << x << std::endl
#define INITALIZE_COMPONENT Initialize
#define UNGROUPED -1

#define TOO_MANY_TEXTURES TextureManager::LoadedTextures.size() >= 256
#define S2D_DEBUG 1
#define S2D_RELEASE 0
#define IS_DEBUG (S2DRuntime::get()->release_mode == S2D_DEBUG)

#endif

double dist(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((double)(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

int random(int min, int max)
{
	std::random_device rseed;
	std::mt19937 rng(rseed());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

bool isKeyPressedTap(sf::Keyboard::Key query)
{
	static bool res = false;
	if (sf::Keyboard::isKeyPressed(query))
	{
		if (!res)
		{
			res = true;
			return true;
		}
	}
	else
	{
		res = false;
	}
	return false;
}

void s2derror(const char* c)
{
	std::cout << "Error: " << c << std::endl;
}

void s2dlog(void* txt, bool newline = true)
{
	using namespace std;
	cout << *&txt;
	if (newline) cout << endl;
}


void clamp(float& num, float&& lower, float&& upper)
{
	if (num < lower) num = lower;
	if (num > upper) num = upper;
}

void clamp(int& num, int lower, int upper)
{
	if (num < lower) num = lower;
	if (num > upper) num = upper;
}

float s2random(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

enum SimulationMode { SimulateOnlyWhenLevelActive, SimulateAlways };

enum DrawMode { DrawWhenLevelActive, DrawAlways, DontDraw };

enum LoadLevelType { Override, Background };

struct Vector2
{
public:
	float x, y;
	static Vector2 zero;

	static float Distance(Vector2 a, Vector2 b)
	{
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}

	float Distance(Vector2 b)
	{
		return sqrt(pow(this->x - b.x, 2) + pow(this->y - b.y, 2));
	}

	void Zero()
	{
		x = 0;
		y = 0;
	}

	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}


	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(const Vector2& d)
	{
		this->x = d.x;
		this->y = d.y;
	}

	Vector2(const b2Vec2& d)
	{
		this->x = d.x;
		this->y = d.y;
	}

	Vector2(const sf::Vector2f& d)
	{
		this->x = d.x;
		this->y = d.y;
	}

	float magnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}


	inline Vector2 operator * (float n)
	{
		Vector2 r = Vector2(this->x, this->y);
		r.x *= n;
		r.y *= n;
		return r;
	}

	inline Vector2 operator = (Vector2 n)
	{
		this->x = n.x;
		this->y = n.y;
		return *this;
	}

	inline Vector2 operator *= (float n)
	{
		this->x *= n;
		this->y *= n;
		return *this;
	}

	inline Vector2 operator += (Vector2 other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	inline Vector2 operator -= (Vector2 other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
	
	//Operators defined for compatibility

	inline Vector2 operator += (sf::Vector2f other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	inline Vector2 operator += (b2Vec2 other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	inline Vector2 operator + (sf::Vector2f other)
	{
		Vector2 r = Vector2(this->x, this->y);
		r.x += other.x;
		r.y += other.y;
		return r;
	}

	inline Vector2 operator + (b2Vec2 other)
	{
		Vector2 r = Vector2(this->x, this->y);
		r.x += other.x;
		r.y += other.y;
		return r;
	}

	inline Vector2 operator -= (sf::Vector2f other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	inline Vector2 operator = (sf::Vector2f n)
	{
		this->x = n.x;
		this->y = n.y;
		return *this;
	}

	inline operator sf::Vector2f()
	{
		return sf::Vector2f(this->x, this->y);
	}

	inline operator b2Vec2()
	{
		return b2Vec2(this->x, this->y);
	}
};

void s2dPrintVector2(Vector2 v)
{
	printf("\n(%4.2f %4.2f)", v.x, v.y);
	printf("\n(%4.2f %4.2f)", v.x, v.y);
}

struct S2DTextureSpritePair
{
public:
	int id;
	sf::Texture* tex;
	sf::Sprite* sprite;

	S2DTextureSpritePair(int n, sf::Texture* t, sf::Sprite* s)
	{
		this->id = n;
		this->tex = t;
		this->sprite = s;
	}
};

struct GameObjectSprite
{
public:
	int tsp_id;
	sf::Sprite s;

	GameObjectSprite()
	{
		tsp_id = -1;
		s = sf::Sprite();
	}

	GameObjectSprite(int tsp_id, sf::Sprite s)
	{
		this->tsp_id = tsp_id;
		this->s = s;
	}
};

class Updatable
{
public:
	SimulationMode flags = SimulateOnlyWhenLevelActive;

	bool u_active;
	virtual void update() {}
	virtual void post_update() {}
	virtual void onDestroyed(){}
	void u_tick()
	{
		if(u_active)update();
	}

	void u_post_update()
	{
		if (this == nullptr) return;

		if (u_active)post_update();
	}

	void destroyed() { onDestroyed(); }

	static std::vector<Updatable*> UpdatableObjects;
};

class Physics
{
public:
	static Vector2 Gravity;
	enum collisionShape { Box, Circle, Triangle, None };

	bool CheckCirclevsCircle(sf::Vector2f a, sf::Vector2f b, float rad1, float rad2)
	{
		return dist(a, b) < rad1 || dist(b, a) < rad2;
	}
};

class World
{
public:
	std::string name;
	sf::Color clear_color;

	World()
	{

	}

	World(std::string name, sf::Color bg)
	{
		this->name = name;
		this->clear_color = bg;
	}
};

class Level
{
public:
	std::string name;
	World world_settings;
	int id;

	Level(std::string name, World settings)
	{
		this->name = name;
		this->world_settings = settings;
	}
};

class LevelInstance
{
public:
	Level* level;
	b2World* physicsWorld = nullptr;
	LevelInstance(Level* levelToInstance)
	{
		this->level = levelToInstance;
		physicsWorld = new b2World(Physics::Gravity);
	}
};

class S2DRuntime
{
public:
	int release_mode = S2D_RELEASE;
	sf::RenderWindow* GAME_WINDOW = nullptr;
	
	static S2DRuntime* Instance;
	static S2DRuntime* get()
	{
		static bool n = (Instance == nullptr);
		if (n)
		{
			Instance = new S2DRuntime();
		}

		return Instance;
	}
};

class LevelManager
{
public:
	static LevelInstance* DefaultLevel;
	static LevelInstance* ActiveLevel;
	std::vector<LevelInstance*>LoadedLevels = std::vector<LevelInstance*>();
	
	void LoadLevel(Level level, LoadLevelType mode = LoadLevelType::Override)
	{
		switch (mode)
		{
			case LoadLevelType::Override:

			break;

			case LoadLevelType::Background:

			break;
		}
	}

	void SetLevel(Level* destination)
	{
		if (destination == nullptr)
		{
			printf("\nError when setting level: provided level was null.");
			return;
		}
		if (ActiveLevel != nullptr)
		{
			if (destination->name != ActiveLevel->level->name)
			{
				ActiveLevel = new LevelInstance(destination);
			}
		}
	}
};

bool doClear = true;

class time
{
	static sf::Clock global_clock;
	static sf::Time _time;
	static sf::Int64 last, current;

public:
	static float delta, deltaUnscaled, physicsDelta;
	static float Scale;

	static void init()
	{
		static bool n = false;
		if (n) return;
		global_clock = sf::Clock();
		n = true;
	}

	static void update()
	{
		clamp(Scale, 0, 1);

		_time = global_clock.getElapsedTime();
		current = _time.asMilliseconds();
		delta = current - last;
		deltaUnscaled = delta;

		delta /= 1000;
		deltaUnscaled /= 1000;

		delta *= Scale;
		last = current;
	}
};

//Created so that when a GameObject needs to be destroyed, we can also clean up the Sprite/Texture it also created.

class TextureManager
{
public:
	static std::vector<S2DTextureSpritePair> LoadedTextures;
	const static int null_id = -1;

	static S2DTextureSpritePair CreateTexturePair(sf::Texture* tex, sf::Sprite* spr)
	{
		S2DTextureSpritePair tsp = S2DTextureSpritePair(LoadedTextures.size(), tex, spr);
		LoadedTextures.push_back(tsp);
		return tsp;
	}

	static void RegenerateLoadedTextureList()
	{
		std::vector<S2DTextureSpritePair> new_list = std::vector<S2DTextureSpritePair>();
		for (int i = 0; i < LoadedTextures.size(); i++)
		{
			if (&LoadedTextures[i] == nullptr) continue;
			if (LoadedTextures[i].id != null_id)
			{
				new_list.push_back(LoadedTextures[i]);
			}
		}
		LoadedTextures.clear();
		LoadedTextures = new_list;
	}

	static void CleanUpTexturePair(int id)
	{
		for (size_t i = 0; i < LoadedTextures.size(); i++)
		{
			if (LoadedTextures[i].id == id)
			{
				delete LoadedTextures[i].tex;
				delete LoadedTextures[i].sprite;
				LoadedTextures[i].id = null_id;
				break;
			}
		}
	}

	static GameObjectSprite CreateSprite(std::string texturepath)
	{
		sf::Texture* texture = new sf::Texture();
		sf::Sprite* ret;
		if (!texture->loadFromFile(texturepath)) return GameObjectSprite(-1, sf::Sprite());
		ret = new sf::Sprite(*texture);
		S2DTextureSpritePair s = CreateTexturePair(texture, ret);
		ret->setOrigin(0.25f, 0.25f);
		return GameObjectSprite(s.id, *ret);
	}
};

class GameObject 
{
public:
	SimulationMode flags = SimulateOnlyWhenLevelActive;
	Vector2 position, scale;
	LevelInstance* parent_level;
	GameObjectSprite sprite;
	std::string name;
	
	float mass					= 1;
	float drag					= 0;
	float gravityInfluence = 1;

	bool active;
	bool isStatic				= false;
	bool hasPhysics			= false;
	bool respectsTime		= true;
	bool awaitingDestroy = false;

	DrawMode drawMode = DrawWhenLevelActive;
	Physics::collisionShape CollisionShape;
	Vector2							velocity;
	
	int id = 0, group = UNGROUPED;
	float rotation;
	float angularVelocity;
	
	struct GameObjectInstance
	{
	public:
		GameObject* obj;
		bool destroyed;
		int id;

		GameObjectInstance(GameObject* g)
		{
			this->obj = g;
			this->destroyed = false;
			this->obj->instance = this;
			this->id = random((int)0, (int)INT_MAX - 500);
			g->id = id;
		}
	};

	GameObjectInstance* instance;

	static std::vector<GameObjectInstance*> ActiveObjects;

	//----------------------------------------------------

	struct DestroyRequest
	{
	public:
		GameObject* des;
		bool destroyed;

		DestroyRequest(GameObject* g)
		{
			this->des = g;
		}
	};

	static std::vector<DestroyRequest*> DestroyRequests;

	static void RebuildDestroyRequestList()
	{
		std::vector<DestroyRequest*> old = std::vector<DestroyRequest*>(DestroyRequests);
		std::vector<DestroyRequest*> _new = std::vector<DestroyRequest*>();
		for (size_t i = 0; i < old.size(); i++)
		{
			if (!old[i]->destroyed)
			{
				_new.push_back(old[i]);
			}
		}

		DestroyRequests = _new;
	}

	static void MakeDestroyRequest(GameObject* g)
	{
		DestroyRequests.push_back(new DestroyRequest(g));
	}

	static void ManageDestroyRequests()
	{
		for (size_t i = 0; i < DestroyRequests.size(); i++)
		{
			if (DestroyRequests[i]->des != nullptr)
			{
				DestroyRequests[i]->des->DestroyImmediate();
				DestroyRequests[i]->destroyed = true;
			}
		}

		RebuildDestroyRequestList();
	}

	static GameObjectInstance* GetObject(int id)
	{
		using namespace std;
		/*
			if (id >= ActiveObjects.size())
			{
				stringstream s;
				s << "GameObject ID out of range: " << id << ", can't be higher than " << ActiveObjects.size() - 1;
				error(s.str().c_str());
				id = ActiveObjects.size() - 1;
				if (id < 0) id = 0;
			}
		*/

		for (size_t i = 0; i < ActiveObjects.size(); i++)
		{
			if (ActiveObjects[i]->id == id)
			{
				return ActiveObjects[i];
			}
		}

		return nullptr;
	}

	//----------------------------------------------------

	void levelChanged()
	{

	}

	void updatePhysics()
	{
		if (!hasPhysics) return;
		if (respectsTime)
		{
			velocity += (sf::Vector2f)Physics::Gravity * gravityInfluence * time::delta * time::Scale;
			position += velocity * (time::delta * 100) * time::Scale;
			angularVelocity += -angularVelocity * 0.02f;
			rotation += angularVelocity * (time::delta * 100) * time::Scale;
		}
		else
		{
			velocity -= (sf::Vector2f)Physics::Gravity * gravityInfluence * time::delta;
			position += velocity * (time::delta * 100);
			rotation += angularVelocity * (time::delta * 100);
		}
	}

	/*
		GameObjects that want to be destroyed must a request to be destroyed, which is then handled at the very start of 
		the game loop. 
		This cannot simply be handled within an Update loop as code that runs on a GameObject that's meant
		to have been destroyed will likely cause an access violation.
		This also could not have been done within Post Update as sending the OnDestroy event led to another access violation.

		Then, the Class Updater will flush destroyed/null GameObjects from the list of active GameObjects to further prevent this
		from happening.
	*/

	virtual void update() {}
	virtual void post_update() {}
	virtual void onDestroyed() {}

	void RequestDestroy()
	{
		MakeDestroyRequest(this);
		GetObject(id)->destroyed = true;
		awaitingDestroy = true;
		onDestroyed();
		//ManageDestroyRequests();
	}

	void DestroyImmediate()
	{
		active = false;
		//aau_active = false;
		
		TextureManager::CleanUpTexturePair(sprite.tsp_id);
		delete this;
	}

	void checkSceneValid()
	{
		if (parent_level == nullptr)
		{
			//printf((std::string("\nGameObject \"").append(name).append("\" has no parent Scene!")).c_str());
			__debugbreak();
			return;
		}
	}

	void draw(bool forceDraw = false)
	{
		if (drawMode == DontDraw && !forceDraw) return;
		sprite.s.setPosition(position);
		sprite.s.setRotation(rotation);
		sprite.s.setScale(scale);
		S2DRuntime::get()->GAME_WINDOW->draw(sprite.s);
	}

	void tick()
	{
		if (!active) return;
		
		switch (this->flags)
		{
		case SimulateAlways:
				checkSceneValid();
				updatePhysics();
				update();
				
			break;

		case SimulateOnlyWhenLevelActive:
			if (parent_level->level->name == LevelManager::ActiveLevel->level->name)
			{
				checkSceneValid();
				updatePhysics();
				update();
			}
			break;
		}

		switch (drawMode)
		{
		case DrawMode::DrawAlways:
			if (&sprite.s != nullptr)
			{
				draw();
			}
			break;

		case DrawMode::DrawWhenLevelActive:
			if (parent_level->level->name == LevelManager::ActiveLevel->level->name)
			{
				if (&sprite.s != nullptr)
				{
					draw();
				}
			}
			break;
		}
	}

	void after_tick()
	{

	}

	GameObject(bool setActive = true)
	{
		
		active = setActive;
		parent_level = LevelManager::ActiveLevel;
		rotation = 0;
		position = sf::Vector2f(0, 0);
		name = "new WorldObject";

	}

	void MakeStandalone()
	{
		init_gameobject;
	}

	static GameObject* Spawn(Vector2 pos, float rotation = 0.0f, float spawnActive = true)
	{
		GameObject* r = new GameObject(spawnActive);
		r->MakeStandalone();
		return r;
	}
};

struct Group
{
public:
	int id;
	Vector2 offset;
	std::vector<GameObject*> objects;
};

//Behaviors act as hooks onto GameObjects in a way similar to Unity's MonoBehaviors.
class Behavior
{
private:
	bool awaitingDestroy;

public:
	void* host_type;
	std::string type_name;
	GameObject* gameObject;
	LevelInstance* ParentLevel;
	bool enabled;
	bool requireGameObject = true;
	bool RunsInBackground = false;
	int id;
	

	//------------------------------------

	struct DestroyRequest
	{
	public:
		Behavior* b;
		bool destroyed;

		DestroyRequest(Behavior* b)
		{
			this->b = b;
			destroyed = false;
		}
	};

	struct BehaviorInstance
	{
	public:
		Behavior* b;
		bool destroyed;

		BehaviorInstance(Behavior* b)
		{
			this->b = b;
			destroyed = false;
		}
	};
	
	static std::vector<BehaviorInstance*> ActiveBehaviors;
	static std::vector<DestroyRequest> DestroyRequests;

	static void RebuildDestroyRequestList()
	{
		std::vector<DestroyRequest> old = std::vector<DestroyRequest>(DestroyRequests);
		std::vector<DestroyRequest> _new = std::vector<DestroyRequest>();
		for (size_t i = 0; i < old.size(); i++)
		{
			if (!old[i].destroyed)
			{
				_new.push_back(old[i]);
			}
		}

		DestroyRequests = _new;
	}

	static void MakeDestroyRequest(Behavior* g)
	{
		DestroyRequests.push_back(DestroyRequest(g));
	}

	static void ManageDestroyRequests()
	{
		for (size_t i = 0; i < DestroyRequests.size(); i++)
		{
			if (DestroyRequests[i].b != nullptr)
			{
				DestroyRequests[i].b->DestroyImmediate();
				DestroyRequests[i].destroyed = true;
			}
		}
		RebuildDestroyRequestList();
	}
	
	//------------------------------------

	void RequestDestroy()
	{
		MakeDestroyRequest(this);
		ActiveBehaviors[id]->destroyed = true;
		awaitingDestroy = true;
		//destroyed();
	}

	void DestroyImmediate()
	{
		delete this;
	}

	virtual void OnDestroy() {};
	virtual void Start() {};
	virtual void PreUpdate() {};
	virtual void Update() {};
	virtual void PhysicsUpdate() {};
	virtual void LateUpdate() {};

	void DestroyRequested()
	{
		OnDestroy();
	}

	void bStart()
	{
		Start();
	}

	bool CanUpdate()
	{
		if (!enabled)return false;
		if (gameObject == nullptr && requireGameObject)return false;
		if (!RunsInBackground && (ParentLevel != gameObject->parent_level )) return false;
		return true;
	}

	bool HasParent()
	{
		return gameObject != nullptr;
	}

	void PreTick()
	{
		if (!CanUpdate()) return;
		if (gameObject != NULL) ParentLevel = gameObject->parent_level;
		PreUpdate();
	}

	void Tick()
	{
		//cunt
		if (!CanUpdate()) return;
		if (gameObject != NULL) ParentLevel = gameObject->parent_level;
		Update();
	}

	void PhysicsTick()
	{
		if (!CanUpdate()) return;
		if(gameObject != NULL) ParentLevel = gameObject->parent_level;
		PhysicsUpdate();
	}

	void PostTick()
	{
		if (!CanUpdate()) return;
		if (gameObject != NULL) ParentLevel = gameObject->parent_level;
		LateUpdate();
	}

	void INITALIZE_COMPONENT(void* host)
	{
		host_type = host;
		type_name = typeid(host).name();
		id = ActiveBehaviors.size();
		init_behavior;

		if (gameObject != nullptr)
		{
			ParentLevel = gameObject->parent_level;
		}
	}

	//Making a Behavior stand-alone will allow it to operate on its own 
	void MakeStandalone()
	{
		requireGameObject = false;
	}

	void SetParent(GameObject* obj)
	{
		gameObject = obj;
	}

protected:

	Behavior()
	{
		
	}

};

class Camera : public GameObject
{
public:
	bool isMain;
	float zoom = 1;
	sf::View view;

	void buildView()
	{
		if (isMain)
		{
			sf::Vector2u rect = S2DRuntime::get()->GAME_WINDOW->getSize();
			view = sf::View(position, (sf::Vector2f)rect);
			view.setRotation(rotation);
			view.zoom(zoom);
			S2DRuntime::get()->GAME_WINDOW->setView(view);
		}
	}


	Camera() : GameObject(true)
	{
		init_gameobject;
		drawMode = DrawMode::DontDraw;

		name = "new Camera";
		buildView();
	}
	

	void update()
	{
		using namespace sf;
		buildView();
	}
};

class ClassUpdater
{
public:

	static void UpdateUpdatables()
	{
		for (size_t i = 0; i < Updatable::UpdatableObjects.size(); i++)
		{
			if (Updatable::UpdatableObjects[i] == nullptr)
			{
				continue;
			}
			Updatable::UpdatableObjects[i]->u_tick();
		}
	}

	static void PostUpdateUpdatables()
	{
		for (size_t i = 0; i < Updatable::UpdatableObjects.size(); i++)
		{
			if (Updatable::UpdatableObjects[i] == nullptr)
			{
				continue;
			}
			Updatable::UpdatableObjects[i]->u_post_update();
		}
	}

	static void RebuildGameObjectList() noexcept
	{
		std::vector<GameObject::GameObjectInstance*> old = GameObject::ActiveObjects;
		std::vector<GameObject::GameObjectInstance*> _new = std::vector<GameObject::GameObjectInstance*>();
		for (size_t i = 0; i < old.size(); i++)
		{
			if (old[i] == nullptr) continue;

			if (!old[i]->destroyed)
			{
				_new.push_back(old[i]);
			}
		}

		GameObject::ActiveObjects = _new;
	}

	static void RebuildBehaviorList()
	{
		std::vector<Behavior::BehaviorInstance*> old = Behavior::ActiveBehaviors;
		std::vector<Behavior::BehaviorInstance*> _new = std::vector<Behavior::BehaviorInstance*>();
		for (size_t i = 0; i < old.size(); i++)
		{
			if (old[i] == nullptr) continue;

			if (!old[i]->destroyed)
			{
				_new.push_back(old[i]);
			}
			else
			{
				delete old[i];
			}
		}

		Behavior::ActiveBehaviors = _new;
	}
	
	static void UpdateGameObjects()
	{
		for (size_t i = 0; i < GameObject::ActiveObjects.size(); i++)
		{
			if (GameObject::ActiveObjects[i] == nullptr || GameObject::ActiveObjects[i]->destroyed)
			{
				continue;
			}
			GameObject::ActiveObjects[i]->obj->tick();
		}
	}

	static void PreUpdateBehaviors()
	{
		for (size_t i = 0; i < Behavior::ActiveBehaviors.size(); i++)
		{
			if (Behavior::ActiveBehaviors[i] == nullptr)
			{
				continue;
			}
			Behavior::ActiveBehaviors[i]->b->PreTick();
		}
	}

	static void UpdateBehaviors()
	{
		for (size_t i = 0; i < Behavior::ActiveBehaviors.size(); i++)
		{
			if (Behavior::ActiveBehaviors[i] == nullptr)
			{
				continue;
			}
			Behavior::ActiveBehaviors[i]->b->Tick();
		}
	}



	static void PostUpdateBehaviors()
	{
		for (size_t i = 0; i < Behavior::ActiveBehaviors.size(); i++)
		{
			if (Behavior::ActiveBehaviors[i] == nullptr)
			{
				continue;
			}
			Behavior::ActiveBehaviors[i]->b->PostTick();
		}
	}



	static void PostUpdateGameObjects()
	{
		for (size_t i = 0; i < GameObject::ActiveObjects.size(); i++)
		{
			if (GameObject::ActiveObjects[i] == nullptr || GameObject::ActiveObjects[i]->destroyed)
			{
				continue;
			}
			GameObject::ActiveObjects[i]->obj->after_tick();
		}
	}
};

class UpdatableTest : public Updatable
{
public:
	UpdatableTest()
	{
		init_updatable;
	}

	void update()
	{
		
	}

	void post_update()
	{
		//std::cout << "\nfuck";
	}
};



//------------------------s

void UpdatePhysics(LevelInstance* inLevel)
{
	using namespace std;
	LevelInstance* L = inLevel;
	if (L->physicsWorld == nullptr)
	{
		stringstream s;
		s << "Level " << L->level->name << " does not have a Physics World. ";
		s2derror(s.str().c_str());
	}

	float ts = 1.0f / 13.0f;
	L->physicsWorld->Step(ts, 20, 20);
}

void UpdateEngine()
{
	time::update();
	LevelManager::ActiveLevel->physicsWorld->SetGravity(Physics::Gravity);
	UpdatePhysics(LevelManager::ActiveLevel);
	Behavior::ManageDestroyRequests();
	GameObject::ManageDestroyRequests();

	ClassUpdater::RebuildGameObjectList();
	ClassUpdater::RebuildBehaviorList();
	ClassUpdater::PreUpdateBehaviors();

	ClassUpdater::UpdateUpdatables();
	ClassUpdater::UpdateGameObjects();
	ClassUpdater::UpdateBehaviors();
	ClassUpdater::RebuildGameObjectList();
	ClassUpdater::RebuildBehaviorList();

	ClassUpdater::PostUpdateUpdatables();
	ClassUpdater::PostUpdateGameObjects();
	ClassUpdater::PostUpdateBehaviors();
	ClassUpdater::RebuildGameObjectList();
	ClassUpdater::RebuildBehaviorList();

	Behavior::ManageDestroyRequests();
	GameObject::ManageDestroyRequests();
}

void InitializeEngine()
{
	using namespace sf;
	using namespace std;
	srand(time(NULL));

	time::init();
	S2DRuntime* runtime = new S2DRuntime();
	RenderWindow* window = new RenderWindow(VideoMode(800, 600), "window");
	runtime->GAME_WINDOW = window;
	S2DRuntime::Instance = runtime;

	if (S2DRuntime::Instance->release_mode == S2D_RELEASE)
	{
		S2DRuntime::Instance->GAME_WINDOW->setTitle(game_name);
	}

	if (S2DRuntime::Instance->release_mode == S2D_DEBUG)
	{
		S2DRuntime::Instance->GAME_WINDOW->setTitle(game_debug_name + LevelManager::ActiveLevel->level->world_settings.name);
	}
}

template<typename T>
T* AddComponent(GameObject* to)
{
	T* c = new T();
	c->enabled = true;
	if (to == NULL)
	{
		std::stringstream ss;
		ss << " Tried to add a component to a null GameObject.";
		s2derror(ss.str().c_str());
	}
	c->gameObject = to->instance->obj;
	c->INITALIZE_COMPONENT(c);
	c->bStart();
	return c;
}



template<typename T>
T* GetComponent(GameObject* on)
{
	std::string desired_type = typeid(T).name();
	for (size_t i = 0; i < Behavior::ActiveBehaviors.size(); i++)
	{
		if (Behavior::ActiveBehaviors[i]->b->gameObject == on)
		{
			if (Behavior::ActiveBehaviors[i]->b->type_name == desired_type)
			{
				return (T*)Behavior::ActiveBehaviors[i]->b->host_type;
			}
		}
	}
	return nullptr;
}

float			time::Scale						= 1;
float			time::delta						= 0,
				time::physicsDelta				= 0.02f,
				time::deltaUnscaled		= 0;
sf::Int64	time::current			= 0,
				time::last					= 0;
sf::Time	time::_time				= sf::Time();
sf::Clock	time::global_clock	= sf::Clock();

std::vector<GameObject::GameObjectInstance*> GameObject::ActiveObjects = std::vector<GameObject::GameObjectInstance*>();
std::vector<Updatable*> Updatable::UpdatableObjects = std::vector<Updatable*>();

LevelInstance* LevelManager::DefaultLevel = new LevelInstance(new Level(std::string("Default Level"), World("World", sf::Color::Black)));
LevelInstance* LevelManager::ActiveLevel = LevelManager::DefaultLevel;
Vector2 Physics::Gravity = Vector2(0, 9.81f);
Vector2 Vector2::zero = Vector2(0, 0);


S2DRuntime* S2DRuntime::Instance = nullptr;

MStaticDefinition(std::vector<GameObject::DestroyRequest*>, GameObject, DestroyRequests);
MStaticDefinition(std::vector<S2DTextureSpritePair>, TextureManager, LoadedTextures);
MStaticDefinition(std::vector<Behavior::BehaviorInstance*>, Behavior, ActiveBehaviors);
MStaticDefinition(std::vector<Behavior::DestroyRequest>, Behavior, DestroyRequests);


#endif