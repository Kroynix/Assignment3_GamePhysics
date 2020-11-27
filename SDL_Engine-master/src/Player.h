#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;


	void moveleft();
	void moveright();
	void moveup();
	void movedown();
	void movestopX();
	void movestopY();
	void m_checkBounds();


	// setters
	void setAnimationState(PlayerAnimationState new_state);

private:
	void m_buildAnimations();
	PlayerAnimationState m_currentAnimationState;

	// Movement vector
	glm::vec2 m_direction;
	const float ACCELERATION = 10.F;

};

#endif /* defined (__PLAYER__) */