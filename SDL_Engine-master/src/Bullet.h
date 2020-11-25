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

	bool active = false;
	void Reset();


public: // Public Variables 

		
	// Start and Restart for PlayScene.cpp
	void m_Active();
	void m_Restart();

private:
	// Functions
	void m_checkBounds();

};



#endif /* defined (__TARGET__) */