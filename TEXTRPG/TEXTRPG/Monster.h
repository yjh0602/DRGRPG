#pragma once
#include "header.h"

// 선언부
class Hero;

class Monster
{
public:

	// 변수 선언부
	string name;
	string monsterSize;
	int hp;
	int minDamage;
	int maxDamage;
	int money;
	int _randomDamege;
	int GolemCountMonster = 1;
	int SlimeCountMonster = 1;
	int GoblinCountMonster = 1;
	Monster(string name, string monsterSize, int hp, int minDamage, int maxDamage,int money);
	// 멤버 함수
	// 몬스터 정의 방법
	void setMonster(string name, string monsterSize, int hp ,int minDamage,int maxDamage, int money);
	//몬스터 데미지
	void monsterAttack(Hero* hero, Monster* monster);

	// show info monster.
	void ShowMonsterInfo();
};

