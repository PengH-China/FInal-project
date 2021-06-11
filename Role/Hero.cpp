/**
*@file Hero.cpp
*@author 张子涵(Zhang Zihan),蔡明宏,彭浩
*@time 2021-06-11
*/

#include "Hero.h"

Hero* Hero::createHero(Point position)
{
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->soldierPositionInit(position);
		return hero;
	}
	CC_SAFE_DELETE(hero); 
	return NULL;
}

bool Hero::init()
{
	//键盘事件创建
	auto listener = EventListenerKeyboard::create();
	//键盘事件响应函数
	listener->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);
	//注册键盘监听
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void Hero::soldierPositionInit(cocos2d::Point position)
{
	m_pHero = Sprite::create("Hero/" + m_pHeroName + ".png",
		Rect(0, 0, 50, 100));
	m_pHero->setScale(2.0f);
	m_pHero->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_pHero->setPosition(position);
	addChild(m_pHero);
	NormalGun* weapon = NormalGun::create();
	if (weapon == nullptr) {
		log("the weapon can't be created");
	}
	this->setMainWeapon(weapon);
}
void Hero::setMainWeapon(Weapon* pWeapon)
{
	this->m_pHero->addChild(pWeapon, 5);
	pWeapon->setState(true);
	pWeapon->setAnchorPoint(Vec2(0.5,0.5));
	pWeapon->setPosition(Point(0, 0));
	pWeapon->setScale(.4f, .4f);
	m_pMainWeapon = pWeapon;
	log("Weapon set!!");
}

Weapon* Hero::getMainWeapon()
{
	return m_pMainWeapon;
}
Sprite* Hero::getSprite()
{
	return m_pHero;
}

Animate* Hero::createAnimate(const std::string pActionName)
{
	/* 加载图片帧到缓存池 */
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(pActionName + ".plist", pActionName + ".png");

	int iFrameNum = 4;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	/* 用一个列表保存所有SpriteFrame对象 */
	for (int i = 1; i <= iFrameNum; i++) {
		/* 从SpriteFrame缓存池中获取SpriteFrame对象 */
		switch (m_nowFacing)
		{
			case QS::kUp:
				frame = frameCache->getSpriteFrameByName(StringUtils::format("W0%d.png", i));
				break;
			case QS::kDown:
				frame = frameCache->getSpriteFrameByName(StringUtils::format("S0%d.png", i));
				break;
			case QS::kRight:
				frame = frameCache->getSpriteFrameByName(StringUtils::format("D0%d.png", i));
				break;
			case QS::kLeft:
				frame = frameCache->getSpriteFrameByName(StringUtils::format("A0%d.png", i));
				break;
			default:
				log("didn't find ");
		}
		frameVec.pushBack(frame);
	}

	/* 使用SpriteFrame列表创建动画对象 */
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.1f, -1);


	/* 将动画包装成一个动作 */
	Animate* action = Animate::create(animation);

	/*清除缓存*/
	AnimationCache::destroyInstance();
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
	//TextureCache::getInstance()->removeUnusedTextures();

	return action;
}



void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) {
	log("Pressed! %d", int(keyCode));
	m_keys[keyCode] = true;
}

void Hero::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events) {
	log("Unpressed! %d", int(keyCode));
	m_keys[keyCode] = false;
}

bool Hero::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (m_keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

void Hero::update(float dt ) {//detect every seconds what have done
	const auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		leftA = EventKeyboard::KeyCode::KEY_A,
		rightD = EventKeyboard::KeyCode::KEY_D,
		upW = EventKeyboard::KeyCode::KEY_W,
		downS = EventKeyboard::KeyCode::KEY_S;

	if (isKeyPressed(leftArrow) || isKeyPressed(leftA)) {
		log("Left!!");
		keyPressedDuration(leftArrow);
		return;
	}
	else if (isKeyPressed(rightArrow) || isKeyPressed(rightD)) {
		keyPressedDuration(rightArrow);
		log("Right!!");
		return;
	}
	else if (isKeyPressed(upArrow) || isKeyPressed(upW)) {
		keyPressedDuration(upArrow);
		log("Up!!");
		return;
	}
	else if (isKeyPressed(downArrow) || isKeyPressed(downS)) {
		keyPressedDuration(downArrow);
		log("Down!!");
		return;
	}
	else {
		return;
	}
}



void Hero::keyPressedDuration(EventKeyboard::KeyCode code) {
	log("keyPressedDuration");

	switch (code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A: {
			m_nowFacing = QS::kLeft;
			move(m_nowFacing, m_pHeroName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D: {
			m_nowFacing = QS::kRight;
			move(m_nowFacing, m_pHeroName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W: {
			m_nowFacing = QS::kUp;
			move(m_nowFacing, m_pHeroName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S: {
			m_nowFacing = QS::kDown;
			move(m_nowFacing, m_pHeroName);
			//m_nowFacing = -1;
			break;
		}
		default:
			break;
	}

}
void Hero::move(int face, const std::string pAnimateName) {
	log("move!!");
	// 0.3s duration
	int offsetX = 0, offsetY = 0;

	const int speedEveryPress = 10;

	Animate* movingAction;

	log("face %d", face);
	switch (face) {
		case QS::kDown: {
			offsetY = -speedEveryPress;
			movingAction = createAnimate("Hero/" + pAnimateName + "Down");
			log("pMoveAction down end!");
			break;
		}
		case QS::kUp: {
			offsetY = speedEveryPress;
			movingAction = createAnimate("Hero/" + pAnimateName + "Up");
			log("pMoveAction up end!");
			break;
		}
		case QS::kLeft: {
			offsetX = -speedEveryPress;
			movingAction = createAnimate("Hero/" + pAnimateName + "LeftDown");
			log("pMoveAction left end!");
			break;
		}
		case QS::kRight: {
			offsetX = speedEveryPress;
			movingAction = createAnimate("Hero/" + pAnimateName + "RightDown");
			log("pMoveAction right end!");
			break;
		}
		default: {
			log("invalid keybpard");
		}
	}

	auto moveBy = MoveBy::create(0.5f, Vec2(offsetX, offsetY));

	auto finalAction = Spawn::createWithTwoActions(moveBy, movingAction);

	this->m_pHero->runAction(finalAction);
}




