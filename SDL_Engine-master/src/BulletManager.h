#pragma once
#include "Bullet.h"
#include "BulletPool.h"
#include "PlayScene.h"
class BulletManager
{
private:
	BulletPool* m_pBulletPool;
	PlayScene* m_pScene;




	float spawnTime;
	float timer;

	void spawnBullet();

public:
	BulletManager(PlayScene*);
	void update();
};

