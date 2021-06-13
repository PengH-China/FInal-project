
#include "Role.h"
void Role::bindSprite(Sprite* pSprite) {
	m_sprite = pSprite;
	this->addChild(m_sprite);
}

bool Role::genePhysicsBody() {
	auto body = PhysicsBody::createBox(m_sprite->getContentSize());
	body->setMass(1e10);
	body->setPositionOffset(Vec2(0.f, m_sprite->getContentSize().height / 2));
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setCategoryBitmask(QS::bitMask::kHeroCategory);
	body->setCollisionBitmask(QS::bitMask::kHeroCollision);
	body->setContactTestBitmask(QS::bitMask::kHeroContact);
	this->setPhysicsBody(body);

	return 0;
}

