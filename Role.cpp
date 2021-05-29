/**
*@file Role.cpp
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#include "Role.h"
void Role::bindSprite(Sprite* pSprite) {
	m_role = pSprite;
	this->addChild(m_role);
}

bool Role::genePhysicsBody() {

	auto body = PhysicsBody::createBox(m_role->getContentSize());
	body->setMass(1e10);
	body->setPositionOffset(Vec2(0.f, m_role->getContentSize().height / 2));
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x01);
	body->setContactTestBitmask(0x01);
	this->setPhysicsBody(body);

	return 0;
}