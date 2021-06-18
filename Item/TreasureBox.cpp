#include "TreasureBox.h"
#include "GlobalPara/GlobalParameter.h"
#include "Const/Const.h"
extern Hero* pHero;
//author peng hao
TreasureBox* TreasureBox::createBox()
{
	return TreasureBox::create();
}

bool TreasureBox::init()
{
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
		this->setPosition(200, 200);
		generatePhysicalBody(QS::message::kTreasureMessage, QS::Name::kTreasure);
	}
	return true;
	
}

void TreasureBox::openBox() {
	m_pSprite->removeFromParentAndCleanup(true);
	std::string str_WhichBox =
		(whichBox == 0) ? (QS::normalBoxOpen)
		: (whichBox == 1) ? (QS::silverBoxOpen)
		: (QS::goldBoxOpen);
	//decide to choose which box name
	m_pSprite = Sprite::create(str_WhichBox);

	this->addChild(m_pSprite);
	int gainCoin = (whichBox + 1) * 10;
	pHero->addCoin(gainCoin);
}


void TreasureBox::interact()
{
	NULL;//this function is empty now;
}
