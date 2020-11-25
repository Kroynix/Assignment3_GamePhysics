#include "Target.h"
#include "TextureManager.h"

#include <iostream>
Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/Circle.png","circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, m_Rotation, 255, true);
}

void Target::update()
{
	m_move();
}

void Target::clean()
{
}

void Target::m_move()
{
	float deltaTime = 1.0f / 60.f; // Fixed Time Step
	m_RiseRun = glm::vec2(m_Run, m_Rise);

	if (m_Running)
	{
		// Check if the Position of the Box in the Y direction is >= 550 (Floor Hieght)
		if (getTransform()->position.y >= 550) // Checking if Box hit floor
		{
			m_Rotation = 0;
			m_Decel = m_FrictionCo * GRAV;
			getRigidBody()->velocity.y = 0;
			if (getRigidBody()->velocity.x > 0)
				getRigidBody()->velocity.x -= m_Decel * deltaTime * PPM; // PPM for only Deceleration on Floor
			else if (getRigidBody()->velocity.x <= 0)
				getRigidBody()->velocity.x = 0;

			
		}
		else // Check if the position of the Box is anywhere else but the floor
		{
			m_Angle = atan(m_Rise / m_Run);
			m_Rotation = (180 / PI) * m_Angle;
			m_Accel = GRAV * sin(m_Angle);
			getRigidBody()->acceleration = (m_Accel) * Util::normalize(m_RiseRun) ;
			getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
		}
		getTransform()->position.x += getRigidBody()->velocity.x;
		getTransform()->position.y += getRigidBody()->velocity.y;

		std::cout << "Run: " << m_Run << std::endl;
		std::cout << "Rise: " << m_Rise << std::endl;
	}
}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
	
}

void Target::m_Restart()
{
	m_Running = false;
}


void Target::m_Active()
{
	m_Running = true;
}
