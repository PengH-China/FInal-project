#include "NormalGun.h"

//Bullet* NormalGun::createBullet() {
//	Bullet* pBullet = NormalBullet::create();
//	//if (gIsEffectPlaying)
//	//	AudioEngine::play2d(QS::files::kGunShot);
//	return pBullet;
//}

bool NormalGun::init() {
	Sprite* pSprite = Sprite::create("Item/NormalGun.png");
	if (pSprite == nullptr)
	{
		log("weapons.png not found");
	}
	bindSprite(pSprite);
	pSprite->setScale(.4f);
	pSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	pSprite->setPosition(0, 0);
	/*generatePhysicalBody(QS::message::kGunMessage, QS::Name::kGunWeapon);*/
	setDamage(1);
	setInterval(.2f);
	setBulletCount(1);
	return true;
}