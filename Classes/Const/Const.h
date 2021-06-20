
/**
 * @file   Const.h
 * @brief  所有常量
 * @author 按需要自主添加
 */

#ifndef _CONST_H_
#define _CONST_H_

#include <string>

namespace QS
{
	const int kBarrierTag = 0,
		kHeroTag = 1,
		kHeroBulletTag = 2,
		kMonsterTag = 3,
		kMonsterBulletTag = 4,
		kHeroSwordAttackingTag = 5,
		kHeroSwordRestingTag = 6,
		kBoxTag = 7,
		kBulletBoxTag = 8,
		kHealthBoxTag = 9,
		kCapacityBoxTag=10;

	const int kMapLayerPriority = 0,
		kBarrierPriority = 1,
		kBoxPriority = 2,
		kHeroPriority = 5,
		kMonsterPriority = 5,
		kBulletPriority = 4,
		kFloorGunPriority = 4,
		kUIPriority = 6;

	enum class Kind
	{
		kSelf,
		kMonster
	};
	enum class BulletShape
	{
		kCircle,
		kRectangle
	};
	enum KeyResponse
	{
		kRight,
		kLeft,
		kUp,
		kDown,
		kSkill,
		kShiftWeapon,
		kInteract
	};
	namespace Name {
		//使用string而非integer，则后面辨别node则用getName()而非getTag();
		static const std::string kHero = "Hero";
		static const std::string kMonster = "Monster";
		static const std::string kBullet = "Bullet";
		static const std::string kMonsterBullet = "MonsterBullet";
		static const std::string kCloseDamage = "CloseDamage";
		static const std::string kMonsterClose = "MonsterClose";
		static const std::string kFreezeTrap = "FreezeTrap";
		static const std::string kFlameTrap = "FlameTrap";
		static const std::string kCoin = "Coin";
		static const std::string kHealthPotion = "HealthPotion";
		static const std::string kArmorPotion = "ArmorPotion";
		static const std::string kNormalGunWeapon = "NormalGunWeapon";
		static const std::string kShotgunWeapon = "ShotgunWeapon";
		static const std::string kSwordWeapon = "SwordWeapon";
		static const std::string kSpearWeapon = "SpearWeapon";
		static const std::string kTreasure = "Treasure";
		static const std::string kWarStatue = "WarStatue";
		static const std::string kAssassinStatue = "AssassinStatue";
		static const std::string kIncreaseDamage = "IncreaseDamage";
		static const std::string kHeroUI = "HeroUI";
		static const std::string kBoard = "Board";
		static const std::string kDoor = "Door";
		static const std::string kBarrier = "Barrier";
		static const std::string kChangeHero = "ChangeHero";
		static const std::string kBulletLayer = "BulletLayer";
		static const std::string kGidTag = "Gid";
	}
	
	namespace message {
		static const std::string kGunMessage = "Normal Gun\nDamage:1";
		static const std::string kShotgunMessage = "Shotgun\nDamage:3";
		static const std::string kSwordMessage = "Sword\nDamage:4";
		static const std::string kSpearMessage = "Spear\nDamage:5";
		static const std::string kHealthPotionMessage = "Health Potion\nHP:++2";
		static const std::string kArmorPotionMessage = "Armor Potion\nArmor:++1";
		static const std::string kMonsterMessage = "Monster\nHealth:30";
		static const std::string kMonsterCrawShootMessage = "MonsterCrawShoot\nbackUpDistance:100";
		static const std::string kMonsterWithGunMessage = "MonsterWithGun\nbackUpDistance:100";
		static const std::string kMonsterPigMessage = "MonsterPig\ndashSpeed:150\nattackRange:75";
		static const std::string kMonsterSnowMessage = "MonsterSnow\njumpDistance:50\nattackRange:75";
		static const std::string kMonsterBossMessage = "Boss\nHealth:300\nattackRange:800\nbackUpDistance:100";
		static const std::string kTreasureMessage = "TreasureBox";
	}
	namespace sound {
		static const std::string kChangeAmmuniti = "sound/changeAmmunition.mp3";
		static const std::string kHit = "sound/hit.mp3";
		static const std::string kShootPowerful = "sound/shootPowerful.mp3";
		static const std::string kSwordClash = "sound/swordClash.mp3";
		static const std::string kShoot = "sound/shoot.mp3";
		static const std::string kHurt = "sound/hurt.mp3";
		static const std::string kOpenBox = "sound/openBox.mp3";
	}
	static const char* kSoldier1 = "Soldier/Soldier1.png";
	static const char* kSoldier2 = "Soldier/Soldier2.png";


	static const std::string normalBoxClose = "Item/Box/normalBoxClose.png";
	static const std::string normalBoxOpen = "Item/Box/normalBoxOpen.png";
	static const std::string silverBoxClose = "Item/Box/silverBoxClose.png";
	static const std::string silverBoxOpen = "Item/Box/silverBoxOpen.png";
	static const std::string goldBoxClose = "Item/Box/goldBoxClose.png";
	static const std::string goldBoxOpen = "Item/Box/goldBoxOpen.png";


}


#endif

