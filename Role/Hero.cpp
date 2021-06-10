
#include "Hero.h"

Hero* Hero::createHero(Point position)
{
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->heroInit(position);
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

void Hero::heroInit(cocos2d::Point position)
{
	pHero = Sprite::create("Hero/Hero1.png",
		Rect(0, 0, 50, 100));
	pHero->setScale(2.0f);
	pHero->setAnchorPoint(Vec2(0.5f, 0.5f));
	pHero->setPosition(position);
	addChild(pHero);

}
//
//Animate* Hero::actionStand()
//{
//	Vector<SpriteFrame*> frameVec;
//	SpriteFrame* frame = nullptr;
//	for (int i = 0; i < 4; i++) {
//		frame = SpriteFrame::create("Hero/Hero1.png",
//			Rect(i * 50, 0, 50, 100));
//		{
//			log("i: %d", i);
//			frameVec.pushBack(frame);
//		}
//		frame = nullptr;
//	}
//
//	auto* animation = Animation::createWithSpriteFrames(frameVec);
//
//	animation->setLoops(-1);
//	animation->setDelayPerUnit(0.15f);
//	auto* action = Animate::create(animation);
//	return action;
//}


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


void Hero::update(float delta) {//detect every seconds what have done

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
			move(m_nowFacing, QS::kHero1);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D: {
			m_nowFacing = QS::kRight;
			move(m_nowFacing, QS::kHero1);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W: {
			m_nowFacing = QS::kUp;
			move(m_nowFacing, QS::kHero1);
			//m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S: {
			m_nowFacing = QS::kDown;
			move(m_nowFacing, QS::kHero1);
			//m_nowFacing = -1;
			break;
		}
		default:
			break;
	}

}
void Hero::move(int face, const char* pAnimateName,
	int width, int height, int frames) {
	log("move!!");
	// 0.3s duration
	int offsetX = 0, offsetY = 0;
	Animate* pMoveAction = nullptr;//animate is also a action


	Vector<SpriteFrame*> frameVec;
	int beginHeight = 0;
	const int speedEveryPress = 10;

	log("face %d", face);
	switch (face) {
		case QS::kDown: {
			offsetY = -speedEveryPress;
			beginHeight = 0;
			log("pMoveAction down end!");
			break;
		}
		case QS::kUp: {
			offsetY = speedEveryPress;
			beginHeight = 300;
			log("pMoveAction up end!");
			break;
		}
		case QS::kLeft: {
			offsetX = -speedEveryPress;
			beginHeight = 100;

			log("pMoveAction left end!");
			break;
		}
		case QS::kRight: {
			offsetX = speedEveryPress;
			beginHeight = 200;

			log("pMoveAction right end!");
			break;
		}
		default: {
			log("invalid keybpard");
		}
	}

	SpriteFrame* frame = nullptr;
	for (int i = 0; i < frames; i++) {
		frame = SpriteFrame::create("Hero/Hero1.png",
			Rect(i * width, beginHeight, width, height));
		if (frame == nullptr)
		{
			log("animate %s.png lost", pAnimateName, i);
		}
		else
		{
			log("i: %d", i);
			//frame->setAnchorPoint(Vec2(0.5f, 0.f));
			frameVec.pushBack(frame);
		}
		frame = nullptr;
	}

	auto p_Animation = Animation::createWithSpriteFrames(frameVec, 0.1f, 1);
	p_Animation->setRestoreOriginalFrame(false);//not back to the original image
	//p_Animation->setLoops(1);
	//p_Animation->setDelayPerUnit(0.1f);
	Animate* p_AnimateAction = Animate::create(p_Animation);

	pMoveAction = p_AnimateAction;
	if (pMoveAction == nullptr) {
		log("a failed animation create");
	}
	auto moveBy = MoveBy::create(0.5f, Vec2(offsetX, offsetY));

	auto finalAction = Spawn::createWithTwoActions(moveBy, p_AnimateAction);


	this->pHero->runAction(finalAction);
	//m_pRole->runAction(p_AnimateAction);

}





