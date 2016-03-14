/*
 * Map.h
 *
 *  Created on: Jan 1, 2016
 *      Author: Hristiyan Nikolov
 *  Copyright (c) 2016. All rights reserved.
 */

#ifndef MAP_H_
#define MAP_H_

#include<iostream>
#include<fstream>
#include<cstring>
#include<list>
#include <shlobj.h>
#include "Tree.h"
#include "Constants.h"
using namespace std;

struct Point {
	int x;
	int y;
};

class Map {

private:
	Tree treeOfCommands;
	char** map;
	int n, m;
	Point tom;
	Point jerry;
	list<string> minPaths;
	list<string> allPaths;
	char* path; // Временна променлива, която се използва от findPath
	int position; // Временна променлива, която се използва от findPath

	void loadFromFile(char* pathToFile); // зарежда файла в двумерен масив (map) и извиква findPath и minimizePaths()
	void savePath(char path[], int startPos, int endPos);
	void findPath(int row, int col, char direction);
	string removePaintFromPath(string path); // връща стринг, но без P-та
	int howMuchP(string path);
	string* listToStringArray(list<string> l); // връща масив от стрингове, които са записани в списък; Добавя и "P"-paint към пътя
	int getListLength(list<string> l);
	void minPathsToTree();
	void minimizePaths(); // От всички пътища оставя само най-късите

public:

	Map(char* pathToLoadFile);
	~Map();

	int lengthMinPath(); // връща дължината на най-късия път
	void whatCommands(); // показва какви команди да се въведат за всеки от пътищата
	void howMuchPaint(); // показва колко боя ще разлее на всеки от минималните пътища
	void howMuchTurns(); // показва броя на завоите на всеки от пътищата
	void printMinPaths();
	void showTreeOfCommands();
	void printInfoAboutPath(int index);
	void maxPaintMinTurnsPath();
	void twoDronesMaxPaint();

};

#endif /* MAP_H_ */
