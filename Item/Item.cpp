#include "Item.h"
#include "GlobalPara/GlobalParameter.h"

extern Hero* pHero;

void Item::bindSprite(Sprite* pSprite)
{
    m_pSprite = pSprite;
    this->addChild(m_pSprite);
}

Sprite* Item::getSprite()
{
    return m_pSprite;
}

void Item::generatePhysicalBody(std::string message, const std::string itemName) {
	m_pSprite->setName(itemName);
	//m_pMessage = showMessage(message);
	//m_pMessage->setVisible(false);
	//m_pMessage->setPosition(0., 40.);
	//this->addChild(m_pMessage);
	auto size = m_pSprite->getContentSize();
	size.width *= 1.2;
	size.height *= 1.2;
	auto body = PhysicsBody::createBox(size);
	body->setDynamic(false);
	body->setGravityEnable(false);
	body->setCategoryBitmask(QS::bitMask::kItemCategory);
	body->setCollisionBitmask(QS::bitMask::kItemCollision);
	body->setContactTestBitmask(QS::bitMask::kItemContact);
	m_pSprite->setPhysicsBody(body);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Item::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Item::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool Item::isAbleOpen()
{
	if (pHero->isPickBox()) {
		return true;
	}
}