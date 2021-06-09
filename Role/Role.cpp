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

Animate* Role::createRoleAnimate(const char* pAnimateName, int width, int height, int frames)
{
	log("Trying to create actor");
	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameVec;
	for (int i = 1; i <= frames; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("%s%d.png", pAnimateName, i),
			Rect(0, 0, width, height));
		if (frame == nullptr)
		{
			log("animate %s%d.png lost", pAnimateName, i);
		}
		else
		{
			frame->setAnchorPoint(Vec2(0.5f, 0.f));
			frameVec.pushBack(frame);
		}
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.2f);
	Animate* action = Animate::create(animation);
	action->retain();
	return action;
}
