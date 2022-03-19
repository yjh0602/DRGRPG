#include "Monster.h"
#include "Hero.h"

// 구현부

// 멤버 함수
// 몬스터 정의 방법
Monster::Monster(string name, string monsterSize, int hp, int minDamage ,int maxDamage, int money)
{
	this->name = name;
	this->monsterSize = monsterSize;
	this->hp = hp;
	this->minDamage = minDamage;
	this->maxDamage = maxDamage;
	this->money = money;
}
void Monster::setMonster(string name, string monsterSize, int hp, int minDamage , int maxDamage, int money)
{
	this->name = name;
	this->monsterSize = monsterSize;
	this->hp = hp;
	this->minDamage = minDamage;
	this->maxDamage = maxDamage;
	this->money = money;
	
}
void Monster::monsterAttack(Hero* hero, Monster* monster)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(monster->minDamage, monster->maxDamage);
	monster->_randomDamege = dis(gen);
	hero->hp = hero->hp - monster->_randomDamege;
	

}

	// show info monster.
void Monster::ShowMonsterInfo()
{
	cout << "-----------------------" <<endl;
	cout << "  크기 : " << this->monsterSize << endl;
	cout << "  이름 : " << this->name << endl;
	cout << "  체력 : " << this->hp << endl;
	cout << "  공격력 : " << this->minDamage << " ~ " << this->maxDamage << endl;
	cout << "  골드량 : " << this->money << endl;
	cout << "-----------------------" << endl;
}
