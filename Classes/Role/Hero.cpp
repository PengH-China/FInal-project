
#include "Hero.h"
#include "GlobalPara/GlobalParameter.h"
Item* Hero::m_pPresentContactItem = nullptr;

Hero* Hero::createHero(Point position,std::string pName)
{
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->setHeroSpriteName(pName);
		hero->soldierPositionInit(position);
		return hero;
	}
	CC_SAFE_DELETE(hero); 
	return NULL;
}

bool Hero::init()
{
	//键盘事件创建
	auto listenerKeyboard = EventListenerKeyboard::create();
	//键盘事件响应函数
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);
	//注册键盘监听
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	setM_nowFacing(3);

	setHealth(20);
	setMaxHealth(20);
	setArmor(5);
	setMaxArmor(5);
	setScore(0);
	setBulletCountInHero(30);

	this->scheduleUpdate();

	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void Hero::setHeroSpriteName(std::string pName)
{
	this->m_pHeroSpriteName = pName;
	return;
}

std::string Hero::getHeroSpriteName()
{
	return m_pHeroSpriteName;
}

void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) 
{
	log("Pressed! %d", int(keyCode));
	m_keys[keyCode] = true;
	m_ableToSingleMove = true;
}

void Hero::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events) 
{
	log("Unpressed! %d", int(keyCode));
	m_keys[keyCode] = false;
}

bool Hero::isKeyPressed(EventKeyboard::KeyCode keyCode) 
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


void Hero::soldierPositionInit(cocos2d::Point position)
{
	m_pHeroSprite = Sprite::create("Hero/" + m_pHeroSpriteName + ".png");
	m_pHeroSprite->setScale(2.0f);
	//m_pHeroSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->bindSprite(m_pHeroSprite);
	this->genePhysicsBody(QS::kHeroTag);
	this->setPosition(position);
	
	auto* weapon = NormalGun::create();
	if (weapon == nullptr) 
	{
		log("the weapon can't be created");
	}
	this->setMainWeapon(weapon);
}
void Hero::setMainWeapon(Weapon* pWeapon)
{
	this->m_pHeroSprite->addChild(pWeapon, 2);
	pWeapon->setState(true);
	pWeapon->setPosition(Point(m_pHeroSprite->getContentSize().width / 4, m_pHeroSprite->getContentSize().height) / 4);
	pWeapon->setScale(1.0f,1.0f);
	m_pMainWeapon = pWeapon;
	log("Weapon set!!");
}

Weapon* Hero::getMainWeapon()
{
	return m_pMainWeapon;
}
Sprite* Hero::getSprite()
{
	return m_pHeroSprite;
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
	for (int i = 1; i <= iFrameNum; i++) 
	{
		/* 从SpriteFrame缓存池中获取SpriteFrame对象 */
		switch (getM_nowFacing())
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
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.1f, 1);

	/* 将动画包装成一个动作 */
	Animate* action = Animate::create(animation);

	/*清除缓存*/
	AnimationCache::destroyInstance();
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();

	return action;
}

void Hero::update(float dt )
{//detect every seconds what have done
	const auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		leftA = EventKeyboard::KeyCode::KEY_A,
		rightD = EventKeyboard::KeyCode::KEY_D,
		upW = EventKeyboard::KeyCode::KEY_W,
		downS = EventKeyboard::KeyCode::KEY_S,
		space = EventKeyboard::KeyCode::KEY_SPACE,
		r = EventKeyboard::KeyCode::KEY_R;

	if ((isKeyPressed(leftArrow) || isKeyPressed(leftA))&& m_ableToSingleMove) 
	{
		log("Left!!");
		keyPressedDuration(leftArrow);
		getMainWeapon()->getWeaponSprite()->setFlippedX(true);
		getMainWeapon()->setPosition(Point(m_pHeroSprite->getContentSize().width*0.1, m_pHeroSprite->getContentSize().height)*0.4f);
		m_ableToSingleMove = false;
		return;
	}
	else if ((isKeyPressed(rightArrow) || isKeyPressed(rightD)) && m_ableToSingleMove) 
	{
		keyPressedDuration(rightArrow);
		//getMainWeapon()->setPosition(Vec2(22, 22));
		getMainWeapon()->getWeaponSprite()->setFlippedX(false);
		getMainWeapon()->setPosition(Point((m_pHeroSprite->getContentSize().width ), m_pHeroSprite->getContentSize().height) * 0.4f);
		getMainWeapon()->setPosition(getMainWeapon()->getPosition() +Vec2(10,0));
		log("Right!!");
		m_ableToSingleMove = false;
		return;
	}
	else if ((isKeyPressed(upArrow) || isKeyPressed(upW)) && m_ableToSingleMove) 
	{
		keyPressedDuration(upArrow);
		log("Up!!");
		m_ableToSingleMove = false;
		return;
	}
	else if ((isKeyPressed(downArrow) || isKeyPressed(downS)) && m_ableToSingleMove) 
	{
		keyPressedDuration(downArrow);
		log("Down!!");
		m_ableToSingleMove = false;
		return;
	}
	else if ((isKeyPressed(space) || isKeyPressed(space)) && m_ableToSingleMove) 
	{
		keyPressedDuration(space);
		log("Down!!");
		m_ableToSingleMove = false;
		return;
	}
	else if(isKeyPressed(r))
	{
		//装弹过程
		log("R->bulletChange");
		if (isEffect)
		{
			AudioEngine::play2d(QS::sound::kChangeAmmuniti);
		}
		const int maxBullet = this->getMainWeapon()->getBulletCountMax();
		int removeBullet = maxBullet - this->getMainWeapon()->getBulletCount();
		if (removeBullet <= this->getBulletCountInHero()) 
		{
			this->setBulletCountInHero(this->getBulletCountInHero() - removeBullet);
			this->getMainWeapon()->setBulletCount(maxBullet);
		}
		else 
		{
			this->getMainWeapon()->setBulletCount(this->getBulletCountInHero()+ this->getMainWeapon()->getBulletCount());
			this->setBulletCountInHero(0);
		}
		return;
	}
	else 
	{
		return;
	}

}

void Hero::keyPressedDuration(EventKeyboard::KeyCode code) 
{
	log("keyPressedDuration");

	switch (code) 
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A: 
		{
			setM_nowFacing (QS::kLeft);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D: 
		{
			setM_nowFacing(  QS::kRight);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W: 
		{
			setM_nowFacing ( QS::kUp);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S: 
		{
			setM_nowFacing(QS::kDown);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_SPACE:
		{
			move(getM_nowFacing(), m_pHeroSpriteName);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		default:
			break;
	}

}
void Hero::move(int face, const std::string pAnimateName) 
{
	log("move!!");
	// 0.3s duration
	int offsetX = 0, offsetY = 0;

	const int speedEveryPress = 32;

	Animate* movingAction;

	log("face %d", face);
	switch (face) 
	{
		case QS::kDown: 
		{
			offsetY = -speedEveryPress;
			movingAction = createAnimate("Hero/" + pAnimateName + "Down");
			log("pMoveAction down end!");
			break;
		}
		case QS::kUp: 
		{
			offsetY = speedEveryPress;
			movingAction = createAnimate("Hero/" + pAnimateName + "Up");
			log("pMoveAction up end!");
			break;
		}
		case QS::kLeft: 
		{
			offsetX = -speedEveryPress;
			movingAction = createAnimate("Hero/" + pAnimateName + "LeftDown");
			log("pMoveAction left end!");
			break;
		}
		case QS::kRight: 
		{
			offsetX = speedEveryPress;
			movingAction = createAnimate("Hero/" + pAnimateName + "RightDown");
			log("pMoveAction right end!");
			break;
		}
		default: 
		{
			log("invalid keybpard");
		}
	}

	if (getIsHitWall())
	{
		log("Move Hit Wall!!!");
		offsetX = -offsetX;
		offsetY = -offsetY;
		setHitWall(false);
		this->m_pHeroSprite->runAction(MoveBy::create(0.2f, Vec2(offsetX, offsetY)));
		return;
	}

	auto moveBy = MoveBy::create(0.2f, Vec2(offsetX, offsetY));

	auto finalAction = Spawn::createWithTwoActions(moveBy, movingAction);
	
	this->m_pHeroSprite->runAction(finalAction);
	return;
}

void Hero::setHitWall(bool isHitWall)
{
	m_isHitWall = isHitWall;
	log("is hit");
}
bool Hero::getIsHitWall()
{
	log("get hit");
	return m_isHitWall;
}
void Hero::setPresentContactItem(Item* pItem)
{
	m_pPresentContactItem = pItem;
}

Item* Hero::getPresentContactItem()
{
	return m_pPresentContactItem;
}
//Item中函数的实现
bool Item::onContactSeparate(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != nullptr && nodeB != nullptr)
	{
		if ((nodeA->getName() == QS::Name::kHero || nodeB->getName() == QS::Name::kHero)
			&& (nodeA->getName() == this->getName() || nodeB->getName() == this->getName()))
		{
			if (Hero::getPresentContactItem() == this)
			{
				log("item seperate");
				Hero::setPresentContactItem(nullptr);
				//m_pMessage->setVisible(false);
			}
		}
	}
	return true;
}

bool Item::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != nullptr && nodeB != nullptr)
	{
		if ((nodeA->getName() == QS::Name::kHero || nodeB->getName() == QS::Name::kHero)
			&& (nodeA->getName() == this->getName() || nodeB->getName() == this->getName()))
		{
			if (Hero::getPresentContactItem() == nullptr)
			{
				log("near item");
				Hero::setPresentContactItem(this);
				//m_pMessage->setVisible(true);
			}
		}
	}
	return false;
}





bool Hero::judgeHeroDie()
{
	if (getHealth() <= 0)
	{

		return true;
	}
	return false;
}
