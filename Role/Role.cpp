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

Animate* Role::creatActorUpAnimate(const char* pAnimateName,
								   int width, int height, int frames)
{
	log("Trying to create actor");
	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameVec;

	for (int i = 0; i < frames; i++){
		frame = SpriteFrame::create(pAnimateName,
									Rect(i * width, 300, width, height));
		if (frame == nullptr)
		{
			log("animate %s.png lost", pAnimateName, i);
		}
		else
		{
			log("i: %d", i);
			frame->setAnchorPoint(Vec2(0.5f, 0.f));
			frameVec.pushBack(frame);
		}
	}
	
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	Animate* action = Animate::create(animation);
	
	return action;
}

Animate* Role::creatActorDownAnimate(const char* pAnimateName,
								   int width, int height, int frames)
{
	log("Trying to create actor");
	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameVec;

	for (int i = 0; i < frames; i++) {
		frame = SpriteFrame::create(pAnimateName,
									Rect(i * width, 0, width, height));
		if (frame == nullptr)
		{
			log("animate %s.png lost", pAnimateName, i);
		}
		else
		{
			log("i: %d", i);
			frame->setAnchorPoint(Vec2(0.5f, 0.f));
			frameVec.pushBack(frame);
		}
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	Animate* action = Animate::create(animation);
	
	return action;
}

Animate* Role::creatActorLeftAnimate(const char* pAnimateName,
								   int width, int height, int frames)
{
	log("Trying to create actor");
	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameVec;

	for (int i = 0; i < frames; i++) {
		frame = SpriteFrame::create(pAnimateName,
									Rect(i * width, 100, width, height));
		if (frame == nullptr)
		{
			log("animate %s.png lost", pAnimateName, i);
		}
		else
		{
			log("i: %d", i);
			frame->setAnchorPoint(Vec2(0.5f, 0.f));
			frameVec.pushBack(frame);
		}
		frame = nullptr;//for the if 
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);//once
	animation->setDelayPerUnit(0.2f);
	Animate* action = Animate::create(animation);
	
	return action;
}

Animate* Role::creatActorRightAnimate(const char* pAnimateName,
								   int width, int height, int frames)
{
	log("Trying to create actor");
	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameVec;

	for (int i = 0; i < frames; i++) {
		frame = SpriteFrame::create(pAnimateName,
									Rect(i * width, 200, width, height));
		if (frame == nullptr)
		{
			log("animate %s.png lost", pAnimateName, i);
		}
		else
		{
			log("i: %d", i);
			frame->setAnchorPoint(Vec2(0.5f, 0.f));
			frameVec.pushBack(frame);
		}
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	Animate* action = Animate::create(animation);
	//action->retain();
	return action;
}

