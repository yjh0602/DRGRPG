#include<iostream>
#include "Monster.h"
#include "Hero.h"
#include<string>


void FinishMonster(Monster* monster, Hero* hero)
{
	cout << " ���� ��ȯ ���� ����   " << endl;
	cout << "-----------------------" << endl;

	cout << monster[1].name << "���� ü�� " << monster[1].hp << '\n';
	cout << monster[2].name << "���� ü�� " << monster[2].hp << '\n';
	cout << monster[3].name << "���� ü�� " << monster[3].hp << '\n';


	cout << "-----------------------" << endl;
	cout << "       ��� ����        " << endl;
	cout << "-----------------------" << endl;

	for (int i = 1; i <= 3; i++)
	{
		if (monster[i].hp <= 0)
		{
			cout << monster[i].name << "��� �߽��ϴ�." << endl;
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
		cout << hero->name << "�� ü�� +100" << endl;
	}

}