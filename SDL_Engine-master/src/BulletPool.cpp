#pragma once 
#ifndef __BULLETPOOL__
#define __BULLETPOOL__

#include "BulletPool.h"
#include <vector>

BulletPool::BulletPool(int size) {
	for (int i = 0; i < size; i++) {
		inactive.push_back(new Bullet());
	}

	std::cout << "Bullet pool created with a size of " << size << std::endl;
}



Bullet* BulletPool::spawn()
{
	Bullet* bullet = NULL;
	if (inactive.size() > 0) {
		bullet = inactive.back();
		bullet->active = true;
		inactive.pop_back();
		active.push_back(bullet);
		std::cout << "Bullet Spawned: " << std::to_string(active.size()) << std::endl;
	}
	else
	{
		std::cout << "ERROR: Max Bullets spawned." << std::endl;
	}
	return bullet;
}



void BulletPool::despawn(Bullet* bullet) {
	bullet->Reset();
	inactive.push_back(bullet);

	for (std::vector<Bullet*>::iterator myiter = active.begin(); myiter != active.end(); myiter++) {
		if (*myiter == bullet) {
			active.erase(myiter);
			std::cout << "Bullet Despawned" << std::endl;
			return;
		}
	}

}

#endif __BULLETPOOL__