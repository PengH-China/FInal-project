#include "NormalGun.h"
Bullet* NormalGun::createBullet() {
	Bullet* pBullet = NormalBullet::create();
	//if (gIsEffectPlaying)
	//	AudioEngine::play2d(QS::files::kGunShot);
	return pBullet;
}

bool NormalGun::init() {
	Sprite* pSprite = Sprite::create("NormalGun.png");
	if (pSprite == nullptr)
	{
		log("weapons.png not found");
	}
	bindSprite(pSprite);
	generatePhysicalBody(QS::message::kGunMessage, QS::Name::kGunWeapon);
	setDamage(1);
	setInterval(.2f);
	setBulletCount(1);
	this->addChild(pSprite);
	return true;
}