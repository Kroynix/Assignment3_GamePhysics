#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Bullet.h"
#include <cmath>

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;


private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	float distanceLabel;
	glm::vec2 m_mousePosition;

	Bullet* m_pBullet;
	Player* m_pPlayer;
	bool m_playerFacingRight;

	// UI Items
	Label* m_pInstructionsLabel;

	






};

#endif /* defined (__PLAY_SCENE__) */