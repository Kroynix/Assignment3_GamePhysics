#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "SDL_mixer.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include <string.h>
#include <iostream>

using namespace std;

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
		TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);
		GUI_Function();

		drawDisplayList();
		SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 0, 255, 0, 255);
}



void PlayScene::update()
{
	float deltaTime = 1.0f / 60.0f;

	updateDisplayList();

	if (SDL_GetTicks() - bulletspawnTimerStart >= bulletspawnTimeDuration) {
		spawnBullet();
	}

	std::vector<Bullet*>& activeBullets = m_pBulletPool->active;
	for (std::vector<Bullet*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); ++myiter) {
		Bullet* bullet = *myiter;

		

		if ((*myiter)->getTransform()->position.y >= 750) {
			m_pBulletPool->despawn(bullet);
			removeChild(bullet);
			break;
		}

		if (bullet->active) {
			CollisionManager::circleAABBCheck(m_pPlayer, bullet);
		}
	}

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)) {
		m_pPlayer->moveleft();
		m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
		m_playerFacingRight = false;
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D)) {
		m_pPlayer->moveright();
		m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
		m_playerFacingRight = true;
	}
	else
	{
		m_pPlayer->movestopX();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->moveup();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->movedown();
	}
	else
	{
		m_pPlayer->movestopY();
	}


	if (m_playerFacingRight)
	{
		m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
	}
	else
	{
		m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";



	m_pPlayer = new Player();
	addChild(m_pPlayer);

	m_pBulletPool = new BulletPool(10);

	
	bulletspawnTimerStart = SDL_GetTicks();



	//m_pInstructionsLabel = new Label("Press the backtick (`) character to Render ", "Consolas");
	//m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 600.0f);
	//addChild(m_pInstructionsLabel);

	TextureManager::Instance()->load("../Assets/textures/Background.png", "background");
	SoundManager::Instance().load("../Assets/explosion.wav", "explosion", SOUND_SFX);
}

void PlayScene::spawnBullet() {
		Bullet* bullet = m_pBulletPool->spawn();
		if (bullet) {
			addChild(bullet);
			bullet->getTransform()->position = glm::vec2(50 + rand() % 700, rand() % 100 * -1);
		}
		bulletspawnTimerStart = SDL_GetTicks();
}



void PlayScene::GUI_Function() const
{
	
}
