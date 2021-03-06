#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("GAME 2005 - ASSIGNMENT 3", "Consolas", 60, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pStudentLabel = new Label("Tyler Miles - 101251005", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pStudentLabel->setParent(this);
	addChild(m_pStudentLabel);


	m_pStudentLabel2 = new Label("Nathan Nguyen - 101268067", "Consolas", 40, blue, glm::vec2(400.0f, 160.0f));
	m_pStudentLabel2->setParent(this);
	addChild(m_pStudentLabel2);


	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton2 = new Button2();
	m_pStartButton2->getTransform()->position = glm::vec2(400.0f, 500.0f);

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});


	
	m_pStartButton2->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton2->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});

	m_pStartButton2->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton2->setAlpha(128);
	});

	m_pStartButton2->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton2->setAlpha(255);
	});





	addChild(m_pStartButton);
	addChild(m_pStartButton2);



	
}

