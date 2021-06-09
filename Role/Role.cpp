/**
*@file Role.cpp
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#include "Role.h"
#include "Const/Const.h"
void Role::bindSprite(Sprite* pSprite) {
	m_pRole = pSprite;
	this->addChild(m_pRole);
}

bool Role::genePhysicsBody() {

	auto body = PhysicsBody::createBox(m_pRole->getContentSize());
	body->setMass(1e10);
	body->setPositionOffset(Vec2(0.f, m_pRole->getContentSize().height / 2));
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setCategoryBitmask(QS::bitMask::kHeroCategory);
	body->setCollisionBitmask(QS::bitMask::kHeroCollision);
	body->setContactTestBitmask(QS::bitMask::kHeroContact);
	this->setPhysicsBody(body);

	return 0;
}

