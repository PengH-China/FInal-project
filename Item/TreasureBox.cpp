#include "TreasureBox.h"

extern Hero* pHero;
//author peng hao
TreasureBox* TreasureBox::createBox()
{
	return TreasureBox::create();
}

bool TreasureBox::init()
{
	scheduleUpdate();

	auto listenerKeyboard = EventListenerKeyboard::create();
	//¼üÅÌÊÂ¼þÏìÓ¦º¯Êý
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(TreasureBox::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(TreasureBox::onKeyReleased, this);
	//×¢²á¼üÅÌ¼àÌý
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	const int randomBox = cocos2d::random(0, 2);
	enum Box { normal, silver, gold };
	switch (randomBox) {
		case normal: {
			log("create normal box");
			m_pSprite = Sprite::create(QS::normalBoxClose);
			whichBox = normal; 
			break;
		}
		case silver: {
			log("create silver box");
			m_pSprite = Sprite::create(QS::silverBoxClose);
			whichBox = silver;
			break;
		}
		case gold: {
			log("create gold box");
			m_pSprite = Sprite::create(QS::goldBoxClose);
			whichBox = gold;
			break;
		}
	}
	if (m_pSprite == nullptr) {
		log("create box failed,not find the image");
	}
	else {
		log("create successfully");
		this->addChild(m_pSprite);//m_pSprite bind with the box object
		this->setPosition(600, 400);
		generatePhysicalBody(QS::message::kTreasureMessage, QS::kBoxTag);
	}
	return true;
}

void TreasureBox::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) {
	log("box Pressed! %d", int(keyCode));
	m_keys[keyCode] = true;
	ableToOpenBox = true;
}

void TreasureBox::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events) {
	log("box Unpressed! %d", int(keyCode));
	m_keys[keyCode] = false;
}

bool TreasureBox::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (m_keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}


void TreasureBox::update(float dt)
{
	auto pickBox = EventKeyboard::KeyCode::KEY_E;
	if (isKeyPressed(pickBox)) {
		if (globalHero == nullptr) {
			log("in treasure.cpp,the hero's pointor is null");
			return;
		}
		else {
			auto boxPos = this->getPosition();
			auto heroPos = globalHero->getPosition() + globalHero->getSprite()->getPosition();
			auto offset = heroPos - boxPos;
			offset.x < 0 ? offset.x *= (-1.) : true;
			offset.y < 0 ? offset.y *= (-1.) : true;
			log("in box.cpp, offset.x:%f,offset.y:%f", offset.x, offset.y);
			if (offset.x < 50 && offset.y < 50) {
				//only when you are close to the box, and press the space,
				 //the box would open
				this->openBox();
				log("you are close enough to open the box");
			}
		}
	}
}
void TreasureBox::openBox() {
	std::string str_WhichBox =
		(whichBox == 0) ? (QS::normalBoxOpen)
		: (whichBox == 1) ? (QS::silverBoxOpen)
		: (QS::goldBoxOpen);
	//decide to choose which box name

	auto boxPos = this->getPosition();

	auto dropThing = Sword::create();
	dropThing->setScale(2.0f);
	if (dropThing == nullptr) {
		log("drop thing failed!!,the pointer is null");
	}

	auto myParent = this->getParent();
	//through log, the myParent is just the battleScene's address
	//log("myParent:%p", myParent);
	dropThing->setPosition(boxPos);
	myParent->addChild(dropThing, 4);

	this->removeFromParentAndCleanup(true);

	
	
	////»ñÈ¡±¦ÏäÎ»ÖÃ
	//if(1)
	//{
	//	Vec2 point = this->getPosition();
	//	auto dropThing = Sword::create();
	//	if (dropThing == nullptr) {
	//		log("drop thing failed!!,the pointer is null");
	//	}
	//	this->getParent()->addChild(dropThing, 4);
	//	log("treasure's Parent is what: %s", this->getParent());
	//	dropThing->setPosition(point);
	//	dropThing->setScale(2.0f, 2.0f);
	//	
	//}

	//this->removeFromParentAndCleanup(true);

	/*std::string str_WhichBox =
		(whichBox == 0) ? (QS::normalBoxOpen)
		: (whichBox == 1) ? (QS::silverBoxOpen)
		: (QS::goldBoxOpen);*/
	//decide to choose which box name
	//m_pSprite = Sprite::create(str_WhichBox);

	//this->addChild(m_pSprite);
}


void TreasureBox::interact()
{
	NULL;//this function is empty now;
}
