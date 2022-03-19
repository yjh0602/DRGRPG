#include"Hero.h"
#include"Monster.h"


//히어로의 데미지 시스템 구현
void Hero::Attack(Monster* monster,Hero* hero)
{	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(minDamage, hero->maxDamage);
	hero->_randomDamege = dis(gen);
	monster->hp= monster->hp - hero->_randomDamege;
}
//히어로의 정보 구현
void Hero::HeroInfo()
{
	cout << "-----------------------" << endl;
	cout << "  이름 : " << this->name << endl;
	cout << "  체력 : " << this->hp << endl;
	cout << "  공격력 : " <<this->minDamage << " ~ " << this->maxDamage << endl;
	cout << "  소지금 : " << this->money << endl;
	cout << "-----------------------" << endl;

}
