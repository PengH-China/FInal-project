/**
*@file Hero.cpp
*@author ���Ӻ�(Zhang Zihan),������,���
*@time 2021-06-11
*/
#include "Hero.h"
#include "GlobalPara/GlobalParameter.h"
//Item* Hero::m_pPresentContactItem = nullptr;

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
	//�����¼�����
	auto listenerKeyboard = EventListenerKeyboard::create();
	//�����¼���Ӧ����
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);
	//ע����̼���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	

	setM_nowFacing(3);

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

int Hero::getCoin() const
{
	return m_icoin;
}

void Hero::setCoin(int coin)
{
	m_icoin = coin;
}

void Hero::addCoin(int coin)
{
	if (m_icoin >= 0) {
		m_icoin += coin;
	}
	else {
		log("a dangerous coin number,haven't init?");
	}
}

bool Hero::isPickBox()
{
	return m_isPickBox;
}

void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) {
	log("Pressed! %d", int(keyCode));
	m_keys[keyCode] = true;
	ableToSingleMove = true;
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


//�������������ļн�
float Hero::angle(const Vec2& v1, const Vec2& v2)
{
	float dz = v1.x * v2.y - v1.y * v2.x;
	return atan2f(fabsf(dz) + MATH_FLOAT_SMALL, Vec2::dot(v1, v2));
}
//��ָ���ĵ�point��תangle�ǣ����߶ε�ê��Ϊ������ת��
void Hero::rotate(Vec2& point, float angle)
{
	float sinAngle = std::sin(angle);
	float cosAngle = std::cos(angle);
	auto x = point.x;
	auto y = point.y;
	//�����ת��Ϊ��0��0����
	if (point.isZero())
	{
		float tempX = x * cosAngle - y * sinAngle;
		y = y * cosAngle + x * sinAngle;
		x = tempX;
	}
	//��ת�㲻��ԭ��
	else
	{
		//���ƶ���ԭ��
		float tempX = x - point.x;
		float tempY = y - point.y;

		//��ת�����ƶ���ȥ
		x = tempX * cosAngle - tempY * sinAngle + point.x;
		y = tempY * cosAngle + tempX * sinAngle + point.y;
	}
}

void Hero::soldierPositionInit(cocos2d::Point position)
{
	m_pHeroSprite = Sprite::create("Hero/" + m_pHeroSpriteName + ".png");
	m_pHeroSprite->setScale(2.0f);
	//m_pHeroSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->bindSprite(m_pHeroSprite);
	this->genePhysicsBody();
	this->setPosition(position);
	/*m_pHeroSprite->setPosition(Vec2(100,100));*/
	
	
	NormalGun* weapon = NormalGun::create();
	if (weapon == nullptr) {
		log("the weapon can't be created");
	}
	this->setMainWeapon(weapon);
}
void Hero::setMainWeapon(Weapon* pWeapon)
{
	this->m_pHeroSprite->addChild(pWeapon, 2);
	pWeapon->setState(true);
	pWeapon->setAnchorPoint(Vec2(0,0.5));
	pWeapon->setPosition(Point(20,12));
	/*auto w = m_pHeroSprite->getContentSize().width;
	auto h = m_pHeroSprite->getContentSize().height;
	pWeapon->setPosition(w/2,h/2);*/
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
	/* ����ͼƬ֡������� */
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(pActionName + ".plist", pActionName + ".png");

	int iFrameNum = 4;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	/* ��һ���б�������SpriteFrame���� */
	for (int i = 1; i <= iFrameNum; i++) {
		/* ��SpriteFrame������л�ȡSpriteFrame���� */
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

	/* ʹ��SpriteFrame�б����������� */
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.1f, 1);

	/* ��������װ��һ������ */
	Animate* action = Animate::create(animation);

	/*�������*/
	AnimationCache::destroyInstance();
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
	//TextureCache::getInstance()->removeUnusedTextures();

	return action;
}

void Hero::update(float dt ) {//detect every seconds what have done
	const auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		leftA = EventKeyboard::KeyCode::KEY_A,
		rightD = EventKeyboard::KeyCode::KEY_D,
		upW = EventKeyboard::KeyCode::KEY_W,
		downS = EventKeyboard::KeyCode::KEY_S,
		space = EventKeyboard::KeyCode::KEY_SPACE;
	
	if ((isKeyPressed(leftArrow) || isKeyPressed(leftA))&& ableToSingleMove) {
		log("Left!!");
		keyPressedDuration(leftArrow);
		ableToSingleMove = false;
		return;
	}
	else if ((isKeyPressed(rightArrow) || isKeyPressed(rightD)) && ableToSingleMove) {
		keyPressedDuration(rightArrow);
		log("Right!!");
		ableToSingleMove = false;
		return;
	}
	else if ((isKeyPressed(upArrow) || isKeyPressed(upW)) && ableToSingleMove) {
		keyPressedDuration(upArrow);
		log("Up!!");
		ableToSingleMove = false;
		return;
	}
	else if ((isKeyPressed(downArrow) || isKeyPressed(downS)) && ableToSingleMove) {
		keyPressedDuration(downArrow);
		log("Down!!");
		ableToSingleMove = false;
		return;
	}
	else if ((isKeyPressed(space) || isKeyPressed(space)) && ableToSingleMove) {
		keyPressedDuration(space);
		log("Down!!");
		ableToSingleMove = false;
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
			setM_nowFacing (QS::kLeft);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D: {
			setM_nowFacing(  QS::kRight);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W: {
			setM_nowFacing ( QS::kUp);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S: {
			setM_nowFacing(QS::kDown);
			move(getM_nowFacing(), m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_SPACE:{
			if (pBox == nullptr) {
				log("in hero.cpp,the box's pointor is null");
				break;
			}
			else {
				auto boxPos = pBox->getPosition() + pBox->getSprite()->getPosition();
				auto heroPos = this->getPosition() + this->getSprite()->getPosition();
				auto offset = heroPos - boxPos;
				offset.x < 0 ? offset.x *= (-1.) : true;
				offset.y < 0 ? offset.y *= (-1.) : true;
				log("in hero.cpp, offset.x:%f,offset.y:%f", offset.x, offset.y);
				if (offset.x < 30 && offset.y < 30) {
					m_isPickBox = true;//only when you are close to the box, and press the space,
									   //the box would open
					pBox->openBox();
					log("you are close enough to open the box");
				}
				else {
					break;
				}
			}
			//move(getM_nowFacing(), m_pHeroSpriteName);
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

	const int speedEveryPress = 20;

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
//void Hero::setPresentContactItem(Item* pItem)
//{
//	m_pPresentContactItem = pItem;
//}
//
//Item* Hero::getPresentContactItem()
//{
//	return m_pPresentContactItem;
//}
//Item�к�����ʵ��
bool Item::onContactSeparate(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != nullptr && nodeB != nullptr)
	{
		if ((nodeA->getName() == QS::Name::kHero || nodeB->getName() == QS::Name::kHero)
			&& (nodeA->getName() == this->getName() || nodeB->getName() == this->getName()))
		{
			//if (Hero::getPresentContactItem() == this)
			//{
			//	log("item seperate");
			//	Hero::setPresentContactItem(nullptr);
			//	//m_pMessage->setVisible(false);
			//}
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
			//if (Hero::getPresentContactItem() == nullptr)
			//{
			//	log("near item");
			//	Hero::setPresentContactItem(this);
			//	//m_pMessage->setVisible(true);
			//}
		}
	}
	return false;
}





