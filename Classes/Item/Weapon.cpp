#include "Weapon.h"
#include "Role/Hero.h"
extern Hero* pHero;

Bullet* Weapon::createBullet()
{
	return nullptr;
}

void Weapon::update(float dt)
{
	log("update Weapon");
	auto pickBox = EventKeyboard::KeyCode::KEY_E;
	if (isKeyPressed(pickBox)) 
	{
		log("Your weapon's keycode are OK");
		if (pHero == nullptr) 
		{
			log("in treasure.cpp,the hero's pointor is null");
			return;
		}
		else 
		{
			if (false == this->getState())
			{
				auto weaponPos = this->getPosition();
				auto heroPos = pHero->getPosition() + pHero->getSprite()->getPosition();
				auto offset = weaponPos - heroPos;
				(offset.x < 0.f) ? (offset.x *= (-1)) : true;
				(offset.y < 0.f) ? (offset.y *= (-1)) : true;
				if (offset.x < 50 && offset.y < 50)
				{
					//only when you are close to the box, and press the space,
					 //the box would open
					interact();
					log("finish interact");
				}
			}
		}
	}
}

Sprite* Weapon::getWeaponSprite()
{
	return m_pSpriteWeapon;
}

void Weapon::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) 
{
	log("Weapon Pressed! %d", int(keyCode));
	m_keys[keyCode] = true;
}

void Weapon::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events) 
{
	log("Weapon Unpressed! %d", int(keyCode));
	m_keys[keyCode] = false;
}

bool Weapon::isKeyPressed(EventKeyboard::KeyCode keyCode) 
{
	if (m_keys[keyCode]) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}
void Weapon::interact()
{
	auto floorWeapon = pHero->getMainWeapon();
	auto bulletCount = pHero->getMainWeapon()->getBulletCount();
	auto bulletCountMax = pHero->getMainWeapon()->getBulletCountMax();
	//没有立即add又想使用，则要retain()
	floorWeapon->retain();
	floorWeapon->removeFromParent();
	//floorWeapon->setPosition(Point(this->getPosition()));
	floorWeapon->setState(false);
	//pHero->getParent()->addChild(floorWeapon,2);
	if (QS::Name::kShotgunWeapon == floorWeapon->getWeaponName()) 
	{
		auto pNewWeapon = ShotGun::create();
		this->getParent()->addChild(pNewWeapon, QS::kFloorGunPriority);
		pNewWeapon->setPosition(this->getPosition());
		pNewWeapon->setScale(1.0f);
		pNewWeapon->setBulletCount(bulletCount);
		pNewWeapon->setBulletCountMax(bulletCountMax);
	}
	else if (QS::Name::kNormalGunWeapon == floorWeapon->getWeaponName()) 
	{
		auto pNewWeapon = NormalGun::create();
		this->getParent()->addChild(pNewWeapon, QS::kFloorGunPriority);
		pNewWeapon->setPosition(this->getPosition());
		pNewWeapon->setScale(1.0f);
		pNewWeapon->setBulletCount(bulletCount);
		pNewWeapon->setBulletCountMax(bulletCountMax);
	}
	else if (QS::Name::kSwordWeapon == floorWeapon->getWeaponName()) 
	{
		auto pNewWeapon = Sword::create();
		this->getParent()->addChild(pNewWeapon, QS::kFloorGunPriority);
		pNewWeapon->setPosition(this->getPosition());
		pNewWeapon->setScale(1.0f);
		pNewWeapon->setBulletCount(bulletCount);
		pNewWeapon->setBulletCountMax(bulletCountMax);
	}
	this->retain();
	this->removeFromParent();
	pHero->setMainWeapon(this);
	log("weapon changed %d",this);
	/*if (gIsEffectPlaying)
		AudioEngine::play2d(sk::files::kWeaponPickup);*/
}


