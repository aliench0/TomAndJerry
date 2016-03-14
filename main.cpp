#include <iostream>
#include "Map.h"
using namespace std;

int main() {
	int choice;
	Map m("testFile4.txt");
	cout << "Дължина на най-късия път:" << endl;
	cout << m.lengthMinPath() << endl;
	cout << "Всички най-къси пътища:" << endl;
	m.printMinPaths();
	cout << "Колко боя ще се разлее на всеки от пътищата:" << endl;
	m.howMuchPaint();
	cout << "Колко завоя ще направи на всеки от пътищата:" << endl;
	m.howMuchTurns();
	cout << "Какви команди да се въведат за всеки от пътищата:" << endl;
	m.whatCommands();
	//Показване на дърво от команди
	m.showTreeOfCommands();
	cout<<"Том, въведи номер на листо:";
	cin>>choice;
	m.printInfoAboutPath(choice);
	cout << "Бонус 2: (най-много разлята боя, при най-малко завои (за абсолютно всички пътища))" << endl;
	m.maxPaintMinTurnsPath();
	cout<<"Бонус 3: (два минимални пътя, максимална боя, пристигане едновременно)" << endl;
	m.twoDronesMaxPaint();

	return 0;
}
