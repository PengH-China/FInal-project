
#include "ShotGunBullet.h"

void ShotGunBullet::attack(float direX, float direY, Point heroPoint, int curFacing, Node* sprite)
{
	float x = heroPoint.x;
	float y = heroPoint.y + 15 ; 

	this->setPosition(x, y);
	//log("posAA x: %d  posAA y: %d", pos.x, pos.y);
	auto v = Vec2(direX, direY);
	//单位化
	v.normalize();
	//速度设置
	v *= 400;
	m_pBulletSprite->getPhysicsBody()->setVelocity(v);
}

bool ShotGunBullet::init()
{
	auto pShotGunBullet = Sprite::create("Item/ShotGunBullet.png");
	if (pShotGunBullet == nullptr)
	{
		log("pShotGunBullet.png not found");
	}
	//子弹精灵绑定在了子弹里
	bindSprite(pShotGunBullet, QS::Kind::kSelf, QS::BulletShape::kCircle);

	setBulletSpeed(3);

	return true;
}