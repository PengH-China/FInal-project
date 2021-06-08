/**
*@file Hero.cpp
*@author ≈Ì∫∆(peng hao)
*@time 2021-05-28
*/
#include "Hero.h"



void Hero::move(int face, const char* pAnimateName,
				int width, int height, int frames) {
	log("move!!");
	// 0.3s duration
	int offsetX = 0, offsetY = 0;
	Animate* pMoveAction = nullptr;//animate is also a action

	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameVec;
	int beginHeight = 0;
	const int speedEveryPress = 20;

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

	for (int i = 0; i < frames; i++) {
		frame = SpriteFrame::create(pAnimateName,//"Soldier/Soldier1.png",
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

	Animation* p_Animation = Animation::createWithSpriteFrames(frameVec);
	p_Animation->setRestoreOriginalFrame(true);//back to the original image
	p_Animation->setLoops(1);
	p_Animation->setDelayPerUnit(0.05f);
	Animate* p_AnimateAction = Animate::create(p_Animation);
	pMoveAction = p_AnimateAction;

	if (pMoveAction == nullptr) {
		log("a failed animation create");
	}
	auto moveBy = MoveBy::create(0.4f, Vec2( offsetX, offsetY));
	
	auto finalAction = Spawn::create(moveBy, p_AnimateAction, nullptr);
	
	m_pRole->runAction(finalAction);
	//m_pRole->runAction(moveBy);
	
}

void Hero::stopMove() {
	m_pRole->stopAction(m_pMoveAnimation);
}

void Hero::rest() {
	m_pRole->runAction(m_pRestAnimation);
}

void Hero::die()
{
#if 0
    SafeMap::m_nowID = Hero::m_ID;
    m_pPresentHero = nullptr;
    this->removeFromParentAndCleanup(false);
    RoomMap::m_mapNumber = 1;
    auto safeMap = SafeMap::createScene();
    Director::getInstance()->replaceScene(safeMap);

    m_alive = true;
#endif
}


void Hero::dieToStartMenu(){
#if 0
    m_pPresentHero = nullptr;
    this->removeFromParentAndCleanup(false);
    auto start = Start::createScene();
    Director::getInstance()->replaceScene(start);
#endif
}

int Hero::getFacing() {
    return m_nowFacing;
}

//Weapon* Hero::getMainWeapon()
//{
//	return this->m_pMainWeapon;
//	
//}

//void Hero::setMainWeapon(Weapon* pNewWeapon)
//{
//	pNewWeapon->setState(true);
//	pNewWeapon->setPosition(Point(20.0, 20.0));
//	m_pMainWeapon = pNewWeapon;
//	this->addChild(pNewWeapon, 2);
//}
//
//void Hero::setSecondWeapon(Weapon* pNewWeapon)
//{
//	pNewWeapon->setState(true);
//	pNewWeapon->setPosition(Point(20.0, 20.0));
//	m_pSecWeapon = pNewWeapon;
//	this->addChild(pNewWeapon, 2);
//}
//
//void Hero::shiftWeapon()
//{
//	if (m_pSecWeapon != nullptr)
//	{
//		m_pMainWeapon->setVisible(false);
//		m_pSecWeapon->setVisible(true);
//		Weapon* pTemp = m_pSecWeapon;
//		m_pSecWeapon = m_pMainWeapon;
//		m_pMainWeapon = pTemp;
//		//if (gIsEffectPlaying)//play music effect
//			//AudioEngine::play2d(sk::files::kWeaponSwitch);
//	}
//}

/*
void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    log("Key %d pressed.", keyCode);


	if (keyCode == EventKeyboard::KeyCode::KEY_D ||
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_isKeyDown[QS::kRight] = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W ||
			 keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_isKeyDown[QS::kUp] = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A ||
			 keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_isKeyDown[QS::kLeft] = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S ||
			 keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_isKeyDown[QS::kDown] = true;
	}
#if 0
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{

		if (m_skillTime >= m_skillCD)
		{
			m_skillRemainTime = this->skill();
			m_skillTime = -m_skillRemainTime;
		}
		else
		{
			log("skill CDing");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		this->shiftWeapon();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_F)
	{
		if (m_pPresentContactItem != nullptr)
		{
			m_pPresentContactItem->interact();
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->pushScene(PauseMenu::create(m_ID));
	}
#endif
}

void Hero::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	m_ifStateChanged = true;
	using namespace cocos2d;
	if (keyCode == EventKeyboard::KeyCode::KEY_D ||
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_isKeyDown[QS::kRight] = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W ||
			 keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_isKeyDown[QS::kUp] = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A ||
			 keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_isKeyDown[QS::kLeft] = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S ||
			 keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_isKeyDown[QS::kDown] = false;
	}
}*/
/*
bool Hero::reduceHealth(int damage)
{
	if (m_ifMortal)
	{
		m_recoverArmorTime = -4;
		if (m_armor != 0)
		{
			if (damage > m_armor)
			{
				damage -= m_armor;
				m_armor = 0;
			}
			/*else//music file ,wait after
			{
				m_armor -= damage;
				if (gIsEffectPlaying)
					AudioEngine::play2d(sk::files::kHeroHurt);
				return true;
			}*/
			/*}
		if (damage >= m_health)
		{
			m_health = 0;
			m_alive = false;
			die();
			return false;
		}
		else
		{/*
			m_health -= damage;
			if (gIsEffectPlaying)
				AudioEngine::play2d(sk::files::kHeroHurt);
			return true;*/
		/*}
	}
	return true;
}
*/
		/*
void Hero::recoverHealth(int healAmount)
{
	if (m_health + healAmount <= m_maxHealth)
	{
		m_health += healAmount;
	}
	else
	{
		m_health = m_maxHealth;
	}
}

void Hero::addArmor(int addAmount)
{
	m_maxArmor += addAmount;
}

bool Hero::ifInjured()
{
	return m_health < m_maxHealth;
}

bool Hero::costCoins(int coin)
{
	if (m_coinNumber >= coin)
	{
		m_coinNumber -= coin;
		return true;
	}
	else
	{
		return false;
	}
}

void Hero::gainCoins(int coin)
{
	m_coinNumber += coin;
}

int Hero::getBaseDamage()
{
	return m_baseDamage;
}

void Hero::raiseDamage(int raiseAmount)
{
	m_baseDamage += raiseAmount;
}

void Hero::setSpeed(float speed)
{
	m_speed = speed;
}

void Hero::clearKeyPress()
{
	for (auto key : m_isKeyDown)
	{
		key = false;
	}
}*/

/*
void Hero::update(float dt)
{
	auto v = Vec2(0, 0);
	if (m_ifStateChanged)
	{
		if (m_isKeyDown[QS::Move::kUp])
			v.y += m_speed;
		if (m_isKeyDown[QS::Move::kDown])
			v.y -= m_speed;
		if (m_isKeyDown[QS::Move::kLeft])
			v.x -= m_speed;
		if (m_isKeyDown[QS::Move::kRight])
			v.x += m_speed;

		v = v.getNormalized() * m_speed;

		getPhysicsBody()->setVelocity(v);
	}
	m_ifStateChanged = false;

	if (v.x < 0 && m_nowFacing == QS::Move::kRight)
	{
		m_pRole->setFlippedX(true);
		m_pMainWeapon->getSprite()->setFlippedX(true);
		m_pMainWeapon->setPosition(Point(-20.0, 20.0));
		m_pSecWeapon->getSprite()->setFlippedX(true);
		m_pSecWeapon->setPosition(Point(-20.0, 20.0));
		if (m_pMainWeapon->getSprite()->getName() == QS::Name::kSwordWeapon)
		{
			m_pMainWeapon->getSprite()->setRotation(60.f);
		}
		if (m_pSecWeapon->getSprite()->getName() == QS::Name::kSwordWeapon)
		{
			m_pSecWeapon->getSprite()->setRotation(60.f);
		}
		m_nowFacing = QS::Move::kLeft;
	}
	else if (v.x > 0 && m_nowFacing == QS::Move::kLeft)
	{
		m_pRole->setFlippedX(false);
		m_pMainWeapon->getSprite()->setFlippedX(false);
		m_pMainWeapon->setPosition(Point(20.0, 20.0));
		m_pSecWeapon->getSprite()->setFlippedX(false);
		m_pSecWeapon->setPosition(Point(20.0, 20.0));
		if (m_pMainWeapon->getSprite()->getName() == QS::Name::kSwordWeapon)
		{
			m_pMainWeapon->getSprite()->setRotation(-60.f);
		}
		if (m_pSecWeapon->getSprite()->getName() == QS::Name::kSwordWeapon)
		{
			m_pSecWeapon->getSprite()->setRotation(-60.f);
		}
		m_nowFacing = QS::Move::kRight;
	}

	/*
	if (getPhysicsBody()->getVelocity() != Vec2::ZERO)
	{
		if (!m_ifMoved)
		{
			m_ifMoved = true;
			move();
		}
	}
	else
	{
		if (m_ifMoved)
		{
			m_ifMoved = false;
			stopMove();
			rest();
		}
	}

	if (m_skillTime < m_skillCD)
	{
		m_skillTime += dt;
	}
	if (m_skillRemainTime > 0)
	{
		m_skillRemainTime -= dt;
		if (m_skillRemainTime <= 0)
		{
			//skillEnd();
		}
	}

	if (m_recoverArmorTime < 1)
	{
		m_recoverArmorTime += dt;
	}
	else if (m_armor < m_maxArmor)
	{
		m_armor += 1;
		log("armor regain");
		m_recoverArmorTime = 0;
	}
	*/
/*
}

void Hero::setSpeed(float speed)
{
	m_speed = speed;
}

void Hero::clearKeyPress()
{
	for (auto key : m_isKeyDown)
	{
		key = false;
	}
}*/

void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) {
	log("Pressed! %d", int(keyCode));
	m_keys[keyCode] = true;
	this->schedule(CC_SCHEDULE_SELECTOR(Hero::roleMoveUpdate), 0.4f);//update every 0.4 s
}
void Hero::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events) {
	log("Unpressed! %d", int(keyCode));
	m_keys[keyCode] = false;
	this->schedule(CC_SCHEDULE_SELECTOR(Hero::roleMoveUpdate), 0.4f);
}

bool Hero::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (m_keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}


void Hero::roleMoveUpdate(float delta ) {//detect every seconds what have done

	const auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		leftA = EventKeyboard::KeyCode::KEY_A,
		rightD = EventKeyboard::KeyCode::KEY_D,
		upW = EventKeyboard::KeyCode::KEY_W,
		downS = EventKeyboard::KeyCode::KEY_S;

	if (isKeyPressed(leftArrow)|| isKeyPressed(leftA)) {
		log("Left!!");
		keyPressedDuration(leftArrow);
		return;
	}
	else if (isKeyPressed(rightArrow)|| isKeyPressed(rightD)) {
		keyPressedDuration(rightArrow);
		log("Right!!");
		return;
	}
	else if (isKeyPressed(upArrow)|| isKeyPressed(upW)) {
		keyPressedDuration(upArrow);
		log("Up!!");
		return;
	}
	else if (isKeyPressed(downArrow)|| isKeyPressed(downS)) {
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
		case EventKeyboard::KeyCode::KEY_A:{
			m_nowFacing = QS::kLeft;
			move(m_nowFacing,QS::kSoldier1);
			m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: 
		case EventKeyboard::KeyCode::KEY_D:{
			m_nowFacing = QS::kRight;
			move(m_nowFacing, QS::kSoldier1);
			m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW: 
		case EventKeyboard::KeyCode::KEY_W:{
			m_nowFacing = QS::kUp;
			move(m_nowFacing, QS::kSoldier1);
			m_nowFacing = -1;
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW: 
		case EventKeyboard::KeyCode::KEY_S:{
			m_nowFacing = QS::kDown;
			move(m_nowFacing, QS::kSoldier1);
			m_nowFacing = -1;
			break;
		}
		default:
			break;
	}
	
}