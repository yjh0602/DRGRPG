#include "���.h"
#include "Monster.h"
#include "Hero.h"

using namespace std;

// Test Git
//������ ���� ������ �� �Է�

//���� �ý��� ����, ��� �ý���
void BattleSet(Monster* monster, Hero* hero)
{
	int selBattle;

	while (true)
	{
		cout << monster->name << "�� ���� ü�� : " << monster->hp << endl;
		cout << hero->name << "�� ���� ü�� : " << hero->hp << endl;
		cout << "     ����  0" << endl;
		cout << "  �׸��α�  1" << endl;
		cin >> selBattle;
		switch (selBattle)
		{
		case 0:
		{
			hero->Attack(monster);
			monster->monsterAttack(hero);
			if (monster->hp <= 0)
			{
				cout << "   " << monster->name << "�� ��� �߽��ϴ�." << endl;
				return;
			}

			else if (hero->hp <= 0)
			{
				cout << "   " << hero->name << "�� ��� �߽��ϴ�." << endl;
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

//���� ��ȯ ���� ����
void FinishMonster(Monster* monsters, Hero* hero)
{  
	cout << " ���� ��ȯ ���� ����   " << endl;
	cout << "-----------------------" << endl;


	cout << monsters[0].name << "���� ü�� " << monsters[0].hp << '\n';
	cout << monsters[1].name << "���� ü�� " << monsters[1].hp << '\n';
	cout << monsters[2].name << "���� ü�� " << monsters[2].hp << '\n';
	

	cout << "-----------------------" << endl;
	cout << "       ��� ����        " << endl;
	cout << "-----------------------" << endl;
	
	for (int i = 0; i <= 2; i++)
	{
		if (monsters[i].hp <= 0)
		{
			cout <<monsters[i].name << "��� �߽��ϴ�." << endl;
		}
	}	

	    cout << "-----------------------" << '\n' << '\n';
		cout << " ���� ���ñ� 1 " << endl;
		cout << " �׳� ������ 2 " << endl;
		int i;
		cin >> i;
		if (i == 1)
		{
			hero->potion();
			cout << hero->name <<"�� ü�� +100" << endl;
		}			

}

int main()
{
	// ���� ����
	string name;
	Hero heroA;
	int selMenu = 0;
	int selCombatMenu;

	vector<Monster*> monsters;
	monsters.push_back(new Monster("��", "����", 500, 80, 1.2f));
	monsters.push_back(new Monster("���", "����", 200, 30, 5.8f));
	monsters.push_back(new Monster("������", "����", 100, 10, 2.2f));
	// ���� �ʱ�ȭ
	

	// ���� �ʱ�ȭ
	cout << "-------------------------" << '\n';
	cout << " ����� �̸��� �Է��ϼ���." << '\n';
	cout << "-------------------------" << '\n';
	cin >> name;
	heroA.name = name;
	
	// ���� ���� Ȯ��
	cout << "-------------------------" << '\n';
	cout << "����� �̸� :" << heroA.name << '\n';
	cout << "HP : " << heroA.hp << '\n';
	cout << "Damage : " << heroA.damage << '\n';

	// ���� �޴�
	while (true)
	{
		cout << "----------------------------" << '\n';
		cout << "���� �� ���� ���� 0" << '\n';
		cout << "      ���� �ϱ�      1" << '\n';
		cin >> selMenu;

			switch (selMenu)
			{
				case 0: // ���� �޴�
				{
					cout << "      ���� ����       " << endl;
					cout << "----------------------------" << endl;
					monsters[0]->ShowMonsterInfo();
					monsters[1]->ShowMonsterInfo();
					monsters[2]->ShowMonsterInfo();
					break;
				}

				case 1: // ���� �޴�
				{
					while (true)
					{
						if (heroA.hp < 0)
						{
							cout << "���� �Ҵ�" << endl;
							break;
						}
						cout << "----------------------------" << endl;
						cout << "             �����޴�    " << endl;
						cout << "1.��  2.��� 3.������ 4.������ 5.��������" << endl;
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
