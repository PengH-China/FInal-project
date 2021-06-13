/**
*@file Hero.cpp
*@author 张子涵(Zhang Zihan),蔡明宏,彭浩
*@time 2021-06-11
*/
#include "Hero.h"

Item* Hero::m_pPresentContactItem = nullptr;

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
	auto listenerKeyboard = EventListenerKeyboard::create();
	//键盘事件响应函数
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);
	//注册键盘监听
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	//鼠标事件
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseUp = CC_CALLBACK_1(Hero::onMouseUp, this);
	listenerMouse->onMouseDown = CC_CALLBACK_1(Hero::onMouseDown, this);
	listenerMouse->onMouseMove = CC_CALLBACK_1(Hero::onMouseMove, this);
	//注册到场景图中
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	
	this->scheduleUpdate();

	if (!Layer::init())
	{
		return false;
	}
	return true;
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

void Hero::onMouseDown(EventMouse* event)
{
	log("mouseDown");

}
void Hero::onMouseUp(EventMouse* event)
{
	log("mouseUp");

}
//返回两个向量的夹角
float Hero::angle(const Vec2& v1, const Vec2& v2)
{
	float dz = v1.x * v2.y - v1.y * v2.x;
	return atan2f(fabsf(dz) + MATH_FLOAT_SMALL, Vec2::dot(v1, v2));
}
//以指定的点point旋转angle角（以线段的锚点为中心旋转）
void Hero::rotate(Vec2& point, float angle)
{
	float sinAngle = std::sin(angle);
	float cosAngle = std::cos(angle);
	auto x = point.x;
	auto y = point.y;
	//如果旋转点为（0，0）点
	if (point.isZero())
	{
		float tempX = x * cosAngle - y * sinAngle;
		y = y * cosAngle + x * sinAngle;
		x = tempX;
	}
	//旋转点不在原点
	else
	{
		//先移动到原点
		float tempX = x - point.x;
		float tempY = y - point.y;

		//旋转完再移动回去
		x = tempX * cosAngle - tempY * sinAngle + point.x;
		y = tempY * cosAngle + tempX * sinAngle + point.y;
	}
}

void Hero::onMouseMove(EventMouse* e)
{
	log("mouseMove");
	//获得openGL的坐标
	Vec2 pos = this->convertToNodeSpaceAR(e->getLocation());
	//注意父节点人物虚拟的是定坐标的，我们操纵的是实物人物精灵图片在计算
	Vec2 vecHero = this->convertToNodeSpaceAR(m_pHeroSprite->getPosition());
	//鼠标相对于人物的位置向量
	Vec2 dirTo = pos - vecHero;
	//武器相对于父节点人物的位置向量
	Vec2 dirFrom= this->convertToNodeSpaceAR(this->getMainWeapon()->getPosition());
	log("pos x: %d ,y: %d", pos.x, pos.y);
	log("vecHero x: %d ,y: %d", vecHero.x, vecHero.y);
	log("dirTo x: %d ,y: %d", dirTo.x, dirTo.y);
	log("disFrom x: %d ,y: %d", dirFrom.x, dirFrom.y);
	//Vec2 now = this->getMainWeapon()->getPosition();
	//0<=jiaodu<=pi
	float jiaodu = angle(dirTo, dirFrom);
	this->getMainWeapon()->setRotation(jiaodu);


	b_isMouseMove = true;
}
bool Hero::isMouseMove()
{
	return b_isMouseMove;
}
void Hero::soldierPositionInit(cocos2d::Point position)
{
	m_pHeroSprite = Sprite::create("Hero/" + m_pHeroSpriteName + ".png",
		Rect(0, 0, 50, 100));
	m_pHeroSprite->setScale(2.0f);
	m_pHeroSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
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
			move(m_nowFacing, m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D: {
			m_nowFacing = QS::kRight;
			move(m_nowFacing, m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W: {
			m_nowFacing = QS::kUp;
			move(m_nowFacing, m_pHeroSpriteName);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S: {
			m_nowFacing = QS::kDown;
			move(m_nowFacing, m_pHeroSpriteName);
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

	if (getIsHitWall())
	{
		log("Hit Wall!!!");
		offsetX = -offsetX ;
		offsetY = -offsetY;
		setHitWall(false);
	}

	auto moveBy = MoveBy::create(0.5f, Vec2(offsetX, offsetY));

	auto finalAction = Spawn::createWithTwoActions(moveBy, movingAction);

	this->m_pHeroSprite->runAction(finalAction);
}

void Hero::setHitWall(bool isHitWall)
{
	m_isHitWall = isHitWall;
}
bool Hero::getIsHitWall()
{
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





