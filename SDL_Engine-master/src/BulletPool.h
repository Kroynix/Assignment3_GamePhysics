#pragma once

#include "Bullet.h"
#include <iostream>

class BulletPool
{
public:

	BulletPool(int);
	~BulletPool();

	int size;
	int index = 0;

	Bullet* spawn();
	void despawn(Bullet*);

	std::vector<Bullet*> active;

private:
	std::vector<Bullet*> inactive;
};

