#include "ShotGun.h"
#include "GlobalPara/GlobalParameter.h"
Bullet* ShotGun::createBullet() {
	Bullet* pBullet = ShotGunBullet::create();
	//调用一次子弹创建，则枪的子弹数减少
	m_bulletCount--;
	pBullet->Bullet::setDamage(ShotGun::getDamage());
	if (isEffect)
	{
		AudioEngine::play2d(QS::sound::kShootPowerful);
	}
	return pBullet;
}

bool ShotGun::init() {
	scheduleUpdate();

	auto listenerKeyboard = EventListenerKeyboard::create();
	//键盘事件响应函数
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Weapon::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Weapon::onKeyReleased, this);
	//注册键盘监听
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	Sprite* pSprite = Sprite::create("Item/ShotGun.png");
	if (pSprite == nullptr)
	{
		log("weapons.png not found");
	}
	m_pSpriteWeapon = pSprite;
	bindSprite(pSprite);
	pSprite->setScale(.4f);
	pSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	pSprite->setPosition(0, 0);
	generatePhysicalBody(QS::message::kShotgunMessage, QS::kHeroSwordRestingTag);
	setWeaponName(QS::Name::kShotgunWeapon);
	Weapon::setDamage(3);
	Weapon::setInterval(.2f);
	Weapon::setState(false);
	//弹夹设为20
	Weapon::setBulletCount(20);
	Weapon::setBulletCountMax(20);
	return true;
}