#pragma once
#include"header.h"
#include"Hero.h"

class WeaponStore
{
 public:
	 string name;
	 int minDamage;
	 int maxDamage;
	 int price;

	 void WaeponInfo(string name, int minDamage ,int maxDamage, int price);
	 void Waepon(Hero* hero);
	 
};