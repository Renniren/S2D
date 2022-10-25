#pragma once
#ifndef S2D_INTENRAL_COMPONENTS
#define S2D_INTENRAL_COMPONENTS
#include<S2Dinternal.h>

//Test Classes -----------

class BehaviorTest : public Behavior
{
public:

	int c;
	void PreUpdate()
	{
		std::cout << "pre update works" << std::endl;
	}

	void Update()
	{
		std::cout << "update works" << std::endl;
		if (c >= 100)
		{
			RequestDestroy();
		}
	}

	void GetComponentWorksCheck()
	{
		std::cout << "get component works" << std::endl;
	}

	void LateUpdate()
	{
		c++;
		std::cout << "late update works" << std::endl;
	}
};

class BehaviorInheritanceTest : public BehaviorTest
{
public:




	void Update()
	{
		std::cout << "inheritance update works" << std::endl;
		if (c >= 100)
		{
			RequestDestroy();
		}
	}

	void GetComponentWorksCheck()
	{
		std::cout << "inheritance get component works" << std::endl;
	}

};

class PhysicsTestObject : public GameObject
{
public:
	PhysicsTestObject() : GameObject(true)
	{
		init_gameobject;
		hasPhysics = true;
		position = sf::Vector2f(1, 4);
		scale = sf::Vector2f(0.03, 0.03);
		sprite = TextureManager::CreateSprite("sprites\\circle.png");
	}

	void update()
	{
		using namespace std;
		//cout << position.y << endl;
		if (position.y > 600)
		{
			position.y = -600;
			velocity.Zero();
		}
	}
};

class Rigidbody : public Behavior
{
public:
	Vector2 velocity;
	b2BodyDef* physicsBodyDefinition;
	b2Body* physicsBody;
	b2PolygonShape* shape;
	b2FixtureDef* fixtureDef;
	
	float angularVelocity;
	float mass;

	float gravityInfluence;
	float angularDrag;
	float drag;

	bool isStatic;
	bool st;

	sf::CircleShape* debug_circle;
	sf::RectangleShape* debug_square;
	
	void Start()
	{
		velocity = Vector2::zero;
		angularVelocity = 0;
		gravityInfluence = 1;
		angularDrag = 0;
		mass = 1;
		drag = 0;

		st = isStatic;

		shape = new b2PolygonShape();
		shape->SetAsBox(gameObject->scale.x, gameObject->scale.y, gameObject->position, gameObject->rotation);
		
		physicsBodyDefinition = new b2BodyDef();
		physicsBodyDefinition->position.Set(gameObject->position.x, gameObject->position.y);
		physicsBodyDefinition->type = b2_dynamicBody;
		physicsBody = ParentLevel->physicsWorld->CreateBody(physicsBodyDefinition);
		
		fixtureDef = new b2FixtureDef();
		fixtureDef->shape = shape;
		fixtureDef->density = 1.0f;
		fixtureDef->friction = 0.3f;
		fixtureDef->restitution = 0.1f;

		physicsBody->CreateFixture(fixtureDef);
		physicsBody->SetGravityScale(1);

		physicsBody->SetLinearDamping(drag);
		physicsBody->SetAngularDamping(angularDrag);

		debug_circle = new sf::CircleShape(4);
		debug_circle->setFillColor(sf::Color(0, 255, 0, 100));

		debug_square = new sf::RectangleShape(Vector2(gameObject->scale.x, gameObject->scale.y));
		debug_square->setFillColor(sf::Color(0, 255, 0, 100));
	}


	void DrawDebugShapes()
	{
		debug_circle->setPosition((Vector2)physicsBodyDefinition->position);
		debug_square->setPosition((Vector2)physicsBodyDefinition->position);
		S2DRuntime::get()->GAME_WINDOW->draw(*debug_circle);
		S2DRuntime::get()->GAME_WINDOW->draw(*debug_square);
	}
	
	void UpdateRigidbody()
	{
		if (st != isStatic)
		{
			st = isStatic;
			if (st)
			{
				/*
				fixtureDef->density = 5;
				physicsBodyDefinition->type = b2_staticBody;
				
				*/

				b2BodyDef groundBodyDef;
				groundBodyDef.position.Set(0.0f, -10.0f);
				b2Body* groundBody = ParentLevel->physicsWorld->CreateBody(&groundBodyDef);
				b2PolygonShape groundBox;
				groundBox.SetAsBox(50.0f, 10.0f);
				groundBody->CreateFixture(&groundBox, 0.0f);
			}

			if (!st)
			{
				fixtureDef->density = 1.0f;
				physicsBodyDefinition->type = b2_dynamicBody;
			}
		}

		if (physicsBody->GetGravityScale() != gravityInfluence)
		{
			physicsBody->SetGravityScale(gravityInfluence);
		}

		if (physicsBody->GetAngularDamping() != angularDrag)
		{
			physicsBody->SetLinearDamping(angularDrag);
		}

		if (physicsBody->GetLinearDamping() != drag)
		{
			physicsBody->SetLinearDamping(drag);
		}
		velocity = physicsBody->GetLinearVelocity();
	}

	void SetLinearVelocity(Vector2 v)
	{
		physicsBody->SetLinearVelocity(v);
	}

	Vector2 GetLinearVelocity()
	{
		physicsBody->GetLinearVelocity();
	}

	void SetAngularVelocity(float v)
	{
		physicsBody->SetAngularVelocity(v);
	}

	Vector2 GetAngularVelocity()
	{
		physicsBody->GetAngularVelocity();
	}

	void MakeStatic()
	{
		SetLinearVelocity(Vector2::zero);
		isStatic = true;
		UpdateRigidbody();
	}

	void PreUpdate()
	{
		UpdateRigidbody();
		DrawDebugShapes();
		if (!isStatic)
		{
			float ts = ((time::delta * 10) * time::Scale);

			//gameObject->position = physicsBody->GetPosition();
			//gameObject->rotation = physicsBody->GetAngle();
			gameObject->position += velocity * ts;
			gameObject->rotation += physicsBody->GetAngularVelocity() * ts;
			//physicsBody->SetLinearVelocity(gameObject->position - physicsBodyDefinition->position);
			
		}	
		physicsBodyDefinition->position.Set(gameObject->position.x, gameObject->position.y);
		//physicsBodyDefinition->position = gameObject->position - physicsBodyDefinition->position;
		physicsBodyDefinition->angle = gameObject->rotation;
	}
};


class TestPlayer : public GameObject
{
public:
	float speed = 100.0f;
	Rigidbody* body;
	TestPlayer() : GameObject(true)
	{
		init_gameobject
			scale = sf::Vector2f(0.03, 0.03);
		sprite = TextureManager::CreateSprite("sprites\\square.png");
		body = AddComponent<Rigidbody>(this);
		body->gravityInfluence = 0;
		//body->MakeStatic();
	}

	void onDestroyed()
	{
		printf("\nNOOOOOOOOOOOOoooooooo");
	}

	void post_update()
	{
		using namespace sf;
		RectangleShape bb = RectangleShape(scale);
		bb.setFillColor(Color(0, 255, 0, 200));
		bb.setPosition(position);
		S2DRuntime::get()->GAME_WINDOW->draw(bb);
	}

	void update()
	{
		using namespace sf;
		using namespace std;

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			position.y -= speed * time::deltaUnscaled;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			position.y += speed * time::deltaUnscaled;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			position.x -= speed * time::deltaUnscaled;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			position.x += speed * time::deltaUnscaled;
		}

		if (Keyboard::isKeyPressed(Keyboard::X))
		{
			printf("test");
			RequestDestroy();
		}


		float incr = 2.0f;
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			time::Scale += incr * time::deltaUnscaled;
			debug_log(time::Scale);
			//s2dlog(&time::Scale, true);
			//cout << time::Scale << endl;
		}

		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			time::Scale -= incr * time::deltaUnscaled;
			debug_log(time::Scale);
			//s2dlog(&time::Scale, true);
			//cout << time::Scale << endl;
		}

		if (isKeyPressedTap(Keyboard::Y))
		{

		}
	}
};

class Particle : public GameObject
{
	float p;
public:
	float lifetime;
	Vector2 velocity;
	float angularVelocity;

	Particle(float l) : GameObject(true)
	{
		init_gameobject;
		name = "Particle";
		lifetime = l;
		p = 0;
	}

	void update()
	{
		//std::cout << "fuck" << std::endl;
		p += time::delta;
		if (p >= lifetime)
		{
			p = 0;
			//RequestDestroy();
		}
	}
};

class ParticleSystem : public GameObject
{
private:
	float d;
public:
	bool emitting;
	int maxParticles;
	float duration;
	float speed = 20;
	float delay = 0.2f;
	float lifetime = 3;
	GameObjectSprite sprite;
	std::vector<Particle*> particles = std::vector<Particle*>();

	ParticleSystem() : GameObject(true)
	{
		init_gameobject;
		sprite = TextureManager::CreateSprite("sprites\\square.png");
		maxParticles = 34;
	}

	void emit(int amt = 1)
	{
		for (size_t i = 0; i < amt; i++)
		{
			Particle* particle = new Particle(lifetime);
			particle->position = position;


			/*
				particle->velocity += sf::Vector2f(s2random(-speed, speed),
					s2random(-speed, speed));
				particle->angularVelocity += s2random(-10, 10);
				particle->hasPhysics = true;
			*/
			
			particle->active = true;
			particle->sprite = sprite;
			particle->scale = sf::Vector2f(0.02f, 0.02f);
			particle->drawMode = DrawWhenLevelActive;
			particles.push_back(particle);
			
			if (particle != nullptr)
			{
				Rigidbody* rb = AddComponent<Rigidbody>(particle);
				//rb->SetLinearVelocity(Vector2(s2random(-speed, speed),s2random(-speed, speed)));
			}
		}
	}

	void update()
	{
		if (emitting)
		{
			d += time::delta;
			if (d >= delay)
			{
				emit();
				d = 0;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			emit(20);
		}
	}
};




#endif // !S2D_INTENRAL_COMPONENTS