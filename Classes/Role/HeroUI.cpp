
#include "HeroUI.h"
#include "GlobalPara/GlobalParameter.h"
bool HeroUI::init()
{
	m_pBoard = Sprite::create("Item/UI/UI-board.png");
	m_pBoard->setScale(0.8f);
	this->addChild(m_pBoard, 1);

	//m_pPresentHero = Hero::getInstance();
	m_pPresentHero = globalHero;
	m_presentHP = m_pPresentHero->getHealth();
	m_presentArmor = m_pPresentHero->getArmor();
	m_presentBulletHero = m_pPresentHero->getBulletCountInHero();
	m_presentBulletWeapon = m_pPresentHero->getMainWeapon()->getBulletCount();
	m_presentTime = g_iDuration;
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

	//子弹列表的统计
	m_pWeaponBullet = ProgressTimer::create(Sprite::create("Item/UI/Bullet-UI.png"));
	m_pWeaponBullet->setScale(0.58f);
	m_pWeaponBullet->setPosition(-37.5f, -30.f);
	m_pWeaponBullet->setType(ProgressTimer::Type::BAR);
	m_pWeaponBullet->setMidpoint(Point(0, 0.5));
	m_pWeaponBullet->setBarChangeRate(Point(1, 0));
	m_pWeaponBullet->setPercentage(static_cast<float>(m_presentBulletWeapon)
		/ static_cast<float>(m_presentBulletHero) * 100);
	this->addChild(m_pWeaponBullet, 2);

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

	std::string bulletWeaponMessage = std::to_string(m_presentBulletWeapon) + "/" +
		std::to_string(m_pPresentHero->getMainWeapon()->getBulletCountMax());
	m_pBulletWeaponMessage = Label::createWithTTF(bulletWeaponMessage, "fonts/IRANYekanBold.ttf", 18.f);
	m_pBulletWeaponMessage->setPosition(-37.5f, -30.f);
	this->addChild(m_pBulletWeaponMessage, 3);

	std::string bulletHeroMessage = std::to_string(m_pPresentHero->getBulletCountInHero());
	m_pBulletHeroMessage = Label::createWithTTF(bulletHeroMessage, "fonts/IRANYekanBold.ttf", 24.f);
	m_pBulletHeroMessage->setPosition(150.f, 40.f);
	this->addChild(m_pBulletHeroMessage, 3);

	std::string timeMessage = "0:00";//+std::to_string(m_iDuration);
	m_pTimeMessage = Label::createWithTTF(timeMessage, "fonts/IRANYekanBold.ttf", 24.f);
	m_pTimeMessage->setPosition(150.f, 3.f);
	this->addChild(m_pTimeMessage, 3);

	std::string scoreMessage = std::to_string(m_pPresentHero->getScore());
	m_pScoreMessage = Label::createWithTTF(scoreMessage, "fonts/IRANYekanBold.ttf", 24.f);
	m_pScoreMessage->setPosition(150.f, -35.f );
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

	if (m_pPresentHero->getMainWeapon()->getBulletCount()!=m_presentBulletWeapon)
	{
		m_presentBulletWeapon = m_pPresentHero->getMainWeapon()->getBulletCount();
		m_pWeaponBullet->setPercentage(static_cast<float>(m_presentBulletWeapon)
			/ static_cast<float>(m_pPresentHero->getMainWeapon()->getBulletCountMax()) * 100);
		std::string bulletMessage = std::to_string(m_presentBulletWeapon) + "/" +
			std::to_string(m_pPresentHero->getMainWeapon()->getBulletCountMax());
		m_pBulletWeaponMessage->setString(bulletMessage);
	}
	
	if (m_pPresentHero->getBulletCountInHero() != m_presentBulletHero)
	{
		m_presentBulletHero = m_pPresentHero->getBulletCountInHero();
		std::string bulletHeroMessage = std::to_string(m_presentBulletHero);
		m_pBulletHeroMessage->setString(bulletHeroMessage);
	}
	if (1)
	{
		std::string speedMessage;
		if (g_iDuration % 60 < 10) {
			speedMessage = std::to_string(g_iDuration / 60) + ":0" + std::to_string(g_iDuration % 60);
		}
		else {
			speedMessage = std::to_string(g_iDuration / 60) + ':' + std::to_string(g_iDuration % 60);
		}
		m_pTimeMessage->setString(speedMessage);
	}
	if (m_pPresentHero->getScore() != m_presentScore)
	{
		m_presentScore = m_pPresentHero->getScore();
		std::string scoreMessage = std::to_string(m_pPresentHero->getScore());
		m_pScoreMessage->setString(scoreMessage);
	}
}
