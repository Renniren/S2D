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
		shape->SetAsBox(gameObject->scale.x / 2, gameObject->scale.y / 2, gameObject->position, gameObject->rotation);
		
		physicsBodyDefinition = new b2BodyDef();
		physicsBodyDefinition->position.Set(gameObject->position.x, gameObject->position.y);
		physicsBodyDefinition->type = b2_dynamicBody;
		
		fixtureDef = new b2FixtureDef();
		fixtureDef->shape = shape;
		fixtureDef->density = 1.0f;
		fixtureDef->friction = 0.3f;
		fixtureDef->restitution = 0.1f;

		physicsBody = ParentLevel->physicsWorld->CreateBody(physicsBodyDefinition);
		physicsBody->CreateFixture(fixtureDef);
		physicsBody->SetGravityScale(1);

		physicsBody->SetLinearDamping(drag);
		physicsBody->SetAngularDamping(angularDrag);

		debug_circle = new sf::CircleShape(4);
		debug_circle->setFillColor(sf::Color(0, 255, 0, 100));

		debug_square = new sf::RectangleShape(Vector2(gameObject->scale.x / 2, gameObject->scale.y / 2));
		debug_square->setFillColor(sf::Color(0, 255, 0, 100));
	}

	void DrawDebugShapes()
	{
		debug_circle->setPosition((Vector2)physicsBody->GetPosition());
		debug_square->setPosition((Vector2)physicsBody->GetPosition());

		S2DRuntime::get()->GAME_WINDOW->draw(*debug_circle);
		S2DRuntime::get()->GAME_WINDOW->draw(*debug_square);
	}
	
	void UpdateRigidbody()
	{
		if (st != isStatic)
		{
			st = isStatic;
			if (!st)
			{
				fixtureDef->density = 0;
				physicsBodyDefinition->type = b2_staticBody;
			}

			if (st)
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

	void PreUpdate()
	{
		UpdateRigidbody();
		//float ts = ((time::delta * 100) * time::Scale);

		gameObject->position = physicsBody->GetPosition();
		gameObject->rotation = physicsBody->GetAngle();

		physicsBodyDefinition->position.Set(gameObject->position.x, gameObject->position.y);
		physicsBodyDefinition->angle = gameObject->rotation;
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
