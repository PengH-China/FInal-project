
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
	/*enum Move
	{
		kUp,
		kDown,
		kLeft,
		kRight
	};*/
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
	enum HeroID
	{
		kKnight,
		kAssassin,
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
		static const std::string kGunWeapon = "GunWeapon";
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
	namespace bitMask {
		/*
		* @brief 暂未实现人与人之间的攻击交互，前面Kind::Self的定义不太准确，还需要分类
		*/
		static const int kHeroCategory = 0x4;
		static const int kHeroCollision = 0x1;
		static const int kHeroContact = 0x63;

		static const int kMonsterCategory = 0x8;
		static const int kMonsterContact = 0x13;
		static const int kMonsterCollision = 0x1b;

		static const int kItemCategory = 0x40;
		static const int kItemCollision = 0x00;
		static const int kItemContact = 0x4;

		static const int kMapCategory = 0x1;
		static const int kMapCollision = 0x0;
		static const int kMapContact = 0x3c;

		//static const int kDoorCategory = 0x2;
		//static const int kDoorCollision = 0x0;
		//static const int kDoorContact = 0x34;

		static const int kSelfBulletCategory = 0x10;
		static const int kSelfBulletCollision = 0xb;
		static const int kSelfBulletContact = 0xb;

		static const int kMonsterBulletCategory = 0x20;
		static const int kMonsterBulletCollision = 0x3;
		static const int kMonsterBulletContact = 0x7;
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
	}
	static const char* kHero1 = "Soldier/Soldier1.png";
	static const char* kHero2 = "Soldier/Soldier2.png";

	constexpr int kSoldierHeight = 100;
	constexpr int kSoldierWidth = 50;


}


#endif

