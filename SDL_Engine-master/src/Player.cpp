#include "Player.h"
#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"

Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
	
	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
	
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	//Normalize direction vector
	float dirMag = Util::magnitude(m_direction);
	if (dirMag > 0) { // Speeding Up
		getRigidBody()->acceleration = Util::normalize(m_direction) * ACCELERATION;
	}
	else if (Util::magnitude(getRigidBody()->velocity) < ACCELERATION) // Stopping
	{
		getRigidBody()->acceleration = glm::vec2(0.f, 0.f);
		getRigidBody()->velocity = glm::vec2(0.f, 0.f);
	}
	else if (Util::magnitude(getRigidBody()->velocity) > 0) 
	{
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * -ACCELERATION;
	}

	getRigidBody()->velocity += getRigidBody()->acceleration;
	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;
	getTransform()->position = pos;


	m_checkBounds();

}

void Player::clean()
{
}


 // Movement
void Player::moveleft()
{
	m_direction.x = -1;
}

void Player::moveright()
{
	m_direction.x = 1;
}

void Player::moveup()
{
	m_direction.y = -1;
}

void Player::movedown()
{
	m_direction.y = 1;
}

void Player::movestopX()
{
	m_direction.x = 0;
}

void Player::movestopY()
{
	m_direction.y = 0;
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(runAnimation);
}

void Player::m_checkBounds()
{

	if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(Config::SCREEN_WIDTH, getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(0, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, Config::SCREEN_HEIGHT);
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}

}
