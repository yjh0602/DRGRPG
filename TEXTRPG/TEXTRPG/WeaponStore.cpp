#include "header.h"
#include "WeaponStore.h"
#include "Hero.h"

void WeaponStore::Waepon(Hero* hero)
{
	hero->minDamage = hero->minDamage + this->minDamage;
	hero->maxDamage = hero->maxDamage + this->maxDamage;
}

void WeaponStore::WaeponInfo(string name, int minDamage, int maxDamage,int price)
{
	this->name = name;    //이름
	this->minDamage = minDamage;//데미지
	this->maxDamage = maxDamage;
	this->price = price;  //가격
}
