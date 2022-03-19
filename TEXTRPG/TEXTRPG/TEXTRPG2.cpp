#include "헤더.h"
#include "Monster.h"
#include "Hero.h"

using namespace std;

// Test Git
//영웅의 정의 데미지 값 입력

//전투 시스템 구축, 사망 시스템
void BattleSet(Monster* monster, Hero* hero)
{
	int selBattle;

	while (true)
	{
		cout << monster->name << "의 남은 체력 : " << monster->hp << endl;
		cout << hero->name << "의 남은 체력 : " << hero->hp << endl;
		cout << "     공격  0" << endl;
		cout << "  그만두기  1" << endl;
		cin >> selBattle;
		switch (selBattle)
		{
		case 0:
		{
			hero->Attack(monster);
			monster->monsterAttack(hero);
			if (monster->hp <= 0)
			{
				cout << "   " << monster->name << "이 사망 했습니다." << endl;
				return;
			}

			else if (hero->hp <= 0)
			{
				cout << "   " << hero->name << "이 사망 했습니다." << endl;
				return;
			}
			break;
		}
		case 1:
		{
			return;
		}
		}
	}
}

//마을 귀환 몬스터 정보
void FinishMonster(Monster* monsters, Hero* hero)
{  
	cout << " 마을 귀환 몬스터 정보   " << endl;
	cout << "-----------------------" << endl;


	cout << monsters[0].name << "남은 체력 " << monsters[0].hp << '\n';
	cout << monsters[1].name << "남은 체력 " << monsters[1].hp << '\n';
	cout << monsters[2].name << "남은 체력 " << monsters[2].hp << '\n';
	

	cout << "-----------------------" << endl;
	cout << "       사망 정보        " << endl;
	cout << "-----------------------" << endl;
	
	for (int i = 0; i <= 2; i++)
	{
		if (monsters[i].hp <= 0)
		{
			cout <<monsters[i].name << "사망 했습니다." << endl;
		}
	}	

	    cout << "-----------------------" << '\n' << '\n';
		cout << " 물약 마시기 1 " << endl;
		cout << " 그냥 나가기 2 " << endl;
		int i;
		cin >> i;
		if (i == 1)
		{
			hero->potion();
			cout << hero->name <<"의 체력 +100" << endl;
		}			

}

int main()
{
	// 변수 선언
	string name;
	Hero heroA;
	int selMenu = 0;
	int selCombatMenu;

	vector<Monster*> monsters;
	monsters.push_back(new Monster("골렘", "대형", 500, 80, 1.2f));
	monsters.push_back(new Monster("고블린", "중형", 200, 30, 5.8f));
	monsters.push_back(new Monster("슬라임", "소형", 100, 10, 2.2f));
	// 몬스터 초기화
	

	// 영웅 초기화
	cout << "-------------------------" << '\n';
	cout << " 용사의 이름을 입력하세요." << '\n';
	cout << "-------------------------" << '\n';
	cin >> name;
	heroA.name = name;
	
	// 영웅 정보 확인
	cout << "-------------------------" << '\n';
	cout << "용사의 이름 :" << heroA.name << '\n';
	cout << "HP : " << heroA.hp << '\n';
	cout << "Damage : " << heroA.damage << '\n';

	// 메인 메뉴
	while (true)
	{
		cout << "----------------------------" << '\n';
		cout << "몬스터 상세 정보 보기 0" << '\n';
		cout << "      전투 하기      1" << '\n';
		cin >> selMenu;

			switch (selMenu)
			{
				case 0: // 도감 메뉴
				{
					cout << "      몬스터 정보       " << endl;
					cout << "----------------------------" << endl;
					monsters[0]->ShowMonsterInfo();
					monsters[1]->ShowMonsterInfo();
					monsters[2]->ShowMonsterInfo();
					break;
				}

				case 1: // 전투 메뉴
				{
					while (true)
					{
						if (heroA.hp < 0)
						{
							cout << "전투 불능" << endl;
							break;
						}
						cout << "----------------------------" << endl;
						cout << "             전투메뉴    " << endl;
						cout << "1.골렘  2.고블린 3.슬라임 4.마을로 5.게임종료" << endl;
						cout << "----------------------------" << '\n';
				
						cin >> selCombatMenu;

						switch (selCombatMenu)
						{   
						
							case 1:
							{
								BattleSet(monsters[0], &heroA);
								break;
							}
							case 2:
							{
								BattleSet(monsters[1], &heroA);
								break;
							}
							case 3:
							{
								BattleSet(monsters[2], &heroA);
								break;
							}
							case 4:
							{
								FinishMonster(monsters, &heroA);
								break;
							}
							case 5:
							{
								return 0;
							}
						}
					}
				break;
			}
		}
	}
	return 0;
}
