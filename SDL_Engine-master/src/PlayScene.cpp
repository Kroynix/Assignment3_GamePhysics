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

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

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
	m_pBox = new Target();
	addChild(m_pBox);

	//m_pInstructionsLabel = new Label("Press the backtick (`) character to Render ", "Consolas");
	//m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 600.0f);
	//addChild(m_pInstructionsLabel);

	TextureManager::Instance()->load("../Assets/textures/Background.png", "background");
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("PHYSICS CONTROLLER", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);


	static int Rise = 3;
	if (ImGui::SliderInt("Rise of Ramp", &Rise, 1, 5)) {}


	static int Run = 4;
	if (ImGui::SliderInt("Run of Ramp", &Run, 1, 5));


	// Inversing Rise for Coordinate system
	int drawingScale;
	if (Rise == 5)
		drawingScale = 1;
	else if (Rise == 4)
		drawingScale = 2;
	else if (Rise == 3)
		drawingScale = 3;
	else if (Rise == 2)
		drawingScale = 4;
	else if (Rise == 1)
		drawingScale = 5;

	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), 50, 550, 50, (drawingScale)*100); // Vertical Line 
	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), 50, 550, Run * 100, 550); // Horizontal Line
	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), 50, (drawingScale) * 100, Run*100, 550); // Connecting Line


	ImGui::Separator();
	if (ImGui::Button("Reset")) {
		m_pBox->m_Restart();
		m_pBox->getTransform()->position = glm::vec2(50, ((drawingScale *100)-20));
		m_pBox->getRigidBody()->velocity = glm::vec2(0, 0);
		m_pBox->getRigidBody()->acceleration = glm::vec2(0, 0);

	}

	ImGui::Separator();
	// Gui Button
	if (ImGui::Button("Start")) {
		m_pBox->m_Rise = Rise;
		m_pBox->m_Run = Run;
		m_pBox->m_Active();
	}
	

	ImGui::End();
	ImGui::EndFrame();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
