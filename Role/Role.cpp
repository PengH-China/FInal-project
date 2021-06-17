
#include "Role.h"
void Role::bindSprite(Sprite* pSprite) {
	m_sprite = pSprite;
	this->addChild(m_sprite);
}

bool Role::genePhysicsBody() {
	auto body = PhysicsBody::createBox(m_sprite->getContentSize(),
		PhysicsMaterial(1.0f, 1.0f, 0.0f));
	body->setMass(1e10);
	//body->setPositionOffset(Vec2(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height / 2));
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setDynamic(false);

	//set the body isn't affected by the physics world's gravitational force
	body->setGravityEnable(false);

	//set initial velocity of physicsBody


	body->setCategoryBitmask(1);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	m_sprite->setPhysicsBody(body);
	m_sprite->setTag(1);	
	//m_sprite->addComponent(body);
	return true;
}

