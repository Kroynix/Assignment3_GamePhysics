#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

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
	updateDisplayList();
	m_pPlayer->update();

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
    EventManager::Instance().update();

    // handle player movement with GameController
    if (SDL_NumJoysticks() > 0)
    {
        if (EventManager::Instance().getGameController(0) != nullptr)
        {
            const auto deadZone = 10000;
            if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
            {
                m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
                m_playerFacingRight = true;
            }
            else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
            {
                m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
                m_playerFacingRight = false;
            }
            else
            {
                if (m_playerFacingRight)
                {
                    m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
                }
                else
                {
                    m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
                }
            }
        }
    }
    // handle player movement if no Game Controllers found
    if (SDL_NumJoysticks() < 1)
    {
        if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
        {
            m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
            m_playerFacingRight = false;
        }
        else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
        {
            m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
            m_playerFacingRight = true;
        }
        else
        {
            if (m_playerFacingRight)
            {
                m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
            }
            else
            {
                m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
            }
        }
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

	//Ball sprite
	m_pBullet = new Target();
	addChild(m_pBullet);

	m_pPlayer = new Player();
	addChild(m_pPlayer);

	//m_pInstructionsLabel = new Label("Press the backtick (`) character to Render ", "Consolas");
	//m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 600.0f);
	//addChild(m_pInstructionsLabel);

	TextureManager::Instance()->load("../Assets/textures/Background.png", "background");
}

void PlayScene::GUI_Function() const
{

}
