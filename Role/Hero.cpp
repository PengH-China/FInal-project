#include "Hero.h"


void Hero::move(){
	m_role->stopAction(m_pRestAnimation);
	m_role->runAction(m_pMoveAnimation);
}

void Hero::stopMove() {
	m_role->stopAction(m_pMoveAnimation);
}

void Hero::rest() {
	m_role->runAction(m_pRestAnimation);
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

void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    log("Key %d pressed.", keyCode);


	if (keyCode == EventKeyboard::KeyCode::KEY_D ||
		keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_isKeyDown[JDQS::kRight] = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W ||
			 keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_isKeyDown[JDQS::kUp] = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A ||
			 keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_isKeyDown[JDQS::kLeft] = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S ||
			 keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_isKeyDown[JDQS::kDown] = true;
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
		m_isKeyDown[JDQS::kRight] = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W ||
			 keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_isKeyDown[JDQS::kUp] = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A ||
			 keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_isKeyDown[JDQS::kLeft] = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S ||
			 keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_isKeyDown[JDQS::kDown] = false;
	}
}

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
		}
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
		}
	}
	return true;
}

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
}
