#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "DisplayObject.h"
#include "Util.h"
#define PPM 5
#define PI 3.141519
#define GRAV 9.8
class Bullet final : public DisplayObject {
public: // Public Defaults
	Bullet();
	~Bullet();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;



public: // Public Variables 

	// Rise Run Variables
	glm::vec2 m_RiseRun;
	float m_Run, m_Rise;


	// Ungiven Variables
	float m_Rotation,
		  m_Angle,
		  m_Accel,
		  m_Fnet;
		
		

	// Start and Restart for PlayScene.cpp
	void m_Active();
	void m_Restart();

private:
	// Functions
	void m_move();
	void m_checkBounds();
	void m_reset();


private: // Private Variables
	// Given Constant Variables 
	const float m_FrictionCo = 0.42,
				m_Mass = 12.8;

	// State and Active Booleans
	bool m_Running = false,
		 m_Decel = false;
};



#endif /* defined (__TARGET__) */