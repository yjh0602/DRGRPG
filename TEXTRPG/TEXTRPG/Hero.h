#pragma once
#include"header.h"

class Monster;

class Hero
{
public:
	string name;
	int hp = 500;
	int minDamage = 1;
	int maxDamage = 30;
	int money = 100;
	int _randomDamege;

	//히어로의 데미지 정의
	void Attack(Monster* monster, Hero* hero);
	//HeroInfo
	void HeroInfo();
	
	
};