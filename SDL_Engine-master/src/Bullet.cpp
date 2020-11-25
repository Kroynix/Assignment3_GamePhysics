#include "Bullet.h"
#include "TextureManager.h"

#include <iostream>
Bullet::Bullet()
{
	TextureManager::Instance()->load("../Assets/textures/Bullet.png","circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);

	Reset();
}

Bullet::~Bullet()
= default;

void Bullet::draw()
{
	if (active) {
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		// draw the target
		TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
	}
}


void Bullet::update()
{
	if (active){
	float deltaTime = 1.0f / 60.0f;

	getRigidBody()->acceleration = glm::vec2(0, 9.8);
	getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;

	}


}

void Bullet::clean()
{
}



void Bullet::m_checkBounds()
{
}


void Bullet::m_Restart()
{
}


void Bullet::m_Active()
{
}


void Bullet::Reset()
{
	getRigidBody()->velocity = glm::vec2(0.f, 0.f);
	getRigidBody()->acceleration = glm::vec2(0.f, 9.8f);
	getRigidBody()->isColliding = false;
}
