#include "TreasureBox.h"
#include "cocos2d.h"
#include "Role/Hero.h"
extern Hero* pHero;

const std::string normalBoxClose = "Item/Box/normalBoxClose.png";
const std::string normalBoxOpen = "Item/Box/normalBoxOpen.png";
const std::string silverBoxClose = "Item/Box/silverBoxClose.png";
const std::string silverBoxOpen = "Item/Box/silverBoxOpen.png";
const std::string goldBoxClose = "Item/Box/goldBoxClose.png";
const std::string goldBoxOpen = "Item/Box/goldBoxOpen.png";

bool TreasureBox::init()
{
	scheduleUpdate();
	const int randomBox = cocos2d::random(0, 2);
	enum Box { normal, silver, gold };
	switch (randomBox) {
		case normal: {
			log("create normal box");
			m_pSprite = Sprite::create(normalBoxClose);
			whichBox = normal; 
			break;
		}
		case silver: {
			log("create silver box");
			m_pSprite = Sprite::create(silverBoxClose);
			whichBox = silver;
			break;
		}
		case gold: {
			log("create gold box");
			m_pSprite = Sprite::create(goldBoxClose);
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
		this->setPosition(200, 200);
		generatePhysicalBody(QS::message::kTreasureMessage, QS::Name::kTreasure);
	}
	return true;
	
}

void TreasureBox::update()
{
	auto boxPos = this->getPosition() + this->getSprite()->getPosition();
	auto heroPos = pHero->getPosition() + pHero->getSprite()->getPosition();
	auto offset = heroPos - boxPos;
	offset.x < 0 ? offset.x *= (-1.) : true;
	offset.y < 0 ? offset.y *= (-1.) : true;

	if (offset.x < 5 && offset.y < 5&& isAbleOpen()) {
		m_pSprite->removeFromParentAndCleanup(true);
		std::string str_WhichBox =
			(whichBox == 0) ? normalBoxOpen
			: (whichBox == 1) ? silverBoxOpen
			: goldBoxOpen;
		//decide to choose which box name
		m_pSprite = Sprite::create(str_WhichBox);

		this->addChild(m_pSprite);
		int gainCoin = (whichBox + 1) * 10;
		pHero->addCoin(gainCoin);
	}
}

void TreasureBox::interact()
{
	if (isAbleOpen()) {
		m_pSprite->removeFromParentAndCleanup(true);
		std::string str_WhichBox =
			(whichBox == 0) ? normalBoxOpen
			: (whichBox == 1) ? silverBoxOpen
			: goldBoxOpen;
		//decide to choose which box name
		m_pSprite = Sprite::create(str_WhichBox);

		this->addChild(m_pSprite);
		int gainCoin = (whichBox + 1) * 10;
		pHero->addCoin(gainCoin);
	}
}
