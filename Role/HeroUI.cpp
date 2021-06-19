/**
*@file   HeroUI.cpp
*@author 
*@date   
*/

#include "HeroUI.h"

bool HeroUI::init()
{
	m_pBoard = Sprite::create("Item/UI/UI-board.png");
	m_pBoard->setScale(0.8f);
	this->addChild(m_pBoard, 1);

	//m_pPresentHero = Hero::getInstance();
	m_pPresentHero = globalHero;
	m_presentHP = m_pPresentHero->getHealth();
	m_presentArmor = m_pPresentHero->getArmor();
	m_presentAttack = m_pPresentHero->getFirePower();
	m_presentCoin = m_pPresentHero->getCoinNumber();
	m_presentSpeed = m_pPresentHero->getspeed();
	m_presentScore = m_pPresentHero->getScore();


	m_pHealth = ProgressTimer::create(Sprite::create("Item/UI/HP-UI.png"));
	m_pHealth->setScale(0.58f);
	m_pHealth->setPosition(-37.5f, 36.f);
	m_pHealth->setType(ProgressTimer::Type::BAR);
	m_pHealth->setMidpoint(Point(0, 0.5));
	m_pHealth->setBarChangeRate(Point(1, 0));
	m_pHealth->setPercentage(static_cast<float>(m_pPresentHero->getHealth())
		/ static_cast<float>(m_pPresentHero->getMaxHealth()) * 100);
	this->addChild(m_pHealth, 2);

	m_pArmor = ProgressTimer::create(Sprite::create("Item/UI/Armor-UI.png"));
	m_pArmor->setScale(0.58f);
	m_pArmor->setPosition(-37.5f, 3.f);
	m_pArmor->setType(ProgressTimer::Type::BAR);
	m_pArmor->setMidpoint(Point(0, 0.5));
	m_pArmor->setBarChangeRate(Point(1, 0));
	m_pArmor->setPercentage(static_cast<float>(m_pPresentHero->getArmor())
		/ static_cast<float>(m_pPresentHero->getMaxArmor()) * 100);
	this->addChild(m_pArmor, 2);

	m_pFirepower = ProgressTimer::create(Sprite::create("Item/UI/Attack-UI.png"));
	m_pFirepower->setScale(0.58f);
	m_pFirepower->setPosition(-37.5f, -30.f);
	m_pFirepower->setType(ProgressTimer::Type::BAR);
	m_pFirepower->setMidpoint(Point(0, 0.5));
	m_pFirepower->setBarChangeRate(Point(1, 0));
	m_pFirepower->setPercentage(static_cast<float>(m_pPresentHero->getFirePower())
		/ static_cast<float>(m_pPresentHero->getMaxFirePower()) * 100);
	this->addChild(m_pFirepower, 2);

	std::string healthMessage = std::to_string(m_pPresentHero->getHealth()) + "/" +
		std::to_string(m_pPresentHero->getMaxHealth());
	m_pHealthMessage = Label::createWithTTF(healthMessage, "fonts/IRANYekanBold.ttf", 18.f);
	m_pHealthMessage->setPosition(- 37.5f, 36.f);
	this->addChild(m_pHealthMessage, 3);

	std::string armorMessage = std::to_string(m_pPresentHero->getArmor()) + "/" +
		std::to_string(m_pPresentHero->getMaxArmor());
	m_pArmorMessage = Label::createWithTTF(armorMessage, "fonts/IRANYekanBold.ttf", 18.f);
	m_pArmorMessage->setPosition(-37.5f, 3.f);
	this->addChild(m_pArmorMessage, 3);

	std::string attackMessage = std::to_string(m_pPresentHero->getFirePower()) + "/" +
		std::to_string(m_pPresentHero->getMaxFirePower());
	m_pAttackMessage = Label::createWithTTF(attackMessage, "fonts/IRANYekanBold.ttf", 18.f);
	m_pAttackMessage->setPosition(-37.5f, -30.f);
	this->addChild(m_pAttackMessage, 3);

	std::string coinMessage = std::to_string(m_pPresentHero->getCoinNumber());
	m_pCoinMessage = Label::createWithTTF(coinMessage, "fonts/IRANYekanBold.ttf", 24.f);
	m_pCoinMessage->setPosition(150.f, 40.f);
	this->addChild(m_pCoinMessage, 3);

	std::string speedMessage = std::to_string(m_pPresentHero->getspeed());
	m_pSpeedMessage = Label::createWithTTF(speedMessage, "fonts/IRANYekanBold.ttf", 24.f);
	m_pSpeedMessage->setPosition(150.f, 3.f);
	this->addChild(m_pSpeedMessage, 3);

	std::string scoreMessage = std::to_string(m_pPresentHero->getScore());
	m_pScoreMessage = Label::createWithTTF(scoreMessage, "fonts/IRANYekanBold.ttf", 24.f);
	m_pScoreMessage->setPosition(150.f, -35.f);
	this->addChild(m_pScoreMessage, 3);

	schedule(CC_SCHEDULE_SELECTOR(HeroUI::scheduleUpdateUI), 0.1f);


	return true;
}

void HeroUI::scheduleUpdateUI(float dt)
{
	if (m_pPresentHero->getHealth() != m_presentHP)
	{
		m_presentHP = m_pPresentHero->getHealth();
		m_pHealth->setPercentage(static_cast<float>(m_pPresentHero->getHealth())
			/ static_cast<float>(m_pPresentHero->getMaxHealth()) * 100);
		std::string healthMessage = std::to_string(m_pPresentHero->getHealth()) + "/" +
			std::to_string(m_pPresentHero->getMaxHealth());
		m_pHealthMessage->setString(healthMessage);
	}

	if (m_pPresentHero->getArmor() != m_presentArmor)
	{
		m_presentArmor = m_pPresentHero->getArmor();
		m_pArmor->setPercentage(static_cast<float>(m_pPresentHero->getArmor())
			/ static_cast<float>(m_pPresentHero->getMaxArmor()) * 100);
		std::string armorMessage = std::to_string(m_pPresentHero->getArmor()) + "/" +
			std::to_string(m_pPresentHero->getMaxArmor());
		m_pArmorMessage->setString(armorMessage);
	}

	if (m_pPresentHero->getFirePower() != m_presentAttack)
	{
		m_presentAttack = m_pPresentHero->getFirePower();
		m_pFirepower->setPercentage(static_cast<float>(m_pPresentHero->getFirePower())
			/ static_cast<float>(m_pPresentHero->getMaxFirePower()) * 100);
		std::string attackMessage = std::to_string(m_pPresentHero->getFirePower()) + "/" +
			std::to_string(m_pPresentHero->getMaxFirePower());
		m_pArmorMessage->setString(attackMessage);
	}
	if (m_pPresentHero->getCoinNumber() != m_presentCoin)
	{
		m_presentCoin = m_pPresentHero->getCoinNumber();
		std::string coinMessage = std::to_string(m_pPresentHero->getCoinNumber());
		m_pCoinMessage->setString(coinMessage);
	}
	if (m_pPresentHero->getspeed() != m_presentSpeed)
	{
		m_presentSpeed = m_pPresentHero->getspeed();
		std::string speedMessage = std::to_string(m_pPresentHero->getspeed());
		m_pCoinMessage->setString(speedMessage);
	}
	if (m_pPresentHero->getScore() != m_presentScore)
	{
		m_presentScore = m_pPresentHero->getScore();
		std::string scoreMessage = std::to_string(m_pPresentHero->getScore());
		m_pCoinMessage->setString(scoreMessage);
	}
}
