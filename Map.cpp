/*
 * Map.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: Hristiyan Nikolov
 *  Copyright (c) 2016. All rights reserved.
 */
#include "Map.h"

void Map::loadFromFile(char* pathToFile) {
	int n, m, k, l, x, y; // n - височина, m - ширина, k - брой мебели, l - брой места за боя, x,y- временни координати
	string line;
	ifstream file(pathToFile);
	if (file.is_open()) {
		file >> n >> m;
		cout << "n=" << n << " m=" << m << endl;
		this->n = n;
		this->m = m;
		map = new char*[n];
		for (int i = 0; i < n; i++)
			map[i] = new char[m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				map[i][j] = '-';

		file >> x >> y; // Координатите на Джери
		map[x][y] = 'J';
		jerry.x = x;
		jerry.y = y;
		file >> x >> y; // Координатите на Том
		map[x][y] = 'T';
		tom.x = x;
		tom.y = y;
		file >> k >> l;
		// Четене на описанията на мебелите
		for (int i = 0; i < k; i++) {
			int countRows = -1;
			file >> x >> y; // Горните леви кординати на мебелта
			getline(file, line);
			while (line != "===") {
				for (int j = 0; j < (int) line.size(); j++) {
					if (line[j] == '1') {
						map[x + countRows][y + j] = 'M';
					}
				}
				getline(file, line);
				countRows++;
			}
		}
		for (int i = 0; i < l; i++) {
			file >> x >> y;
			map[x][y] = 'P';
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << map[i][j] << " ";
			}
			cout << endl;
		}

		file.close();
		path = new char[n * m];
		findPath(tom.x, tom.y, 'S');
		allPaths = minPaths;
		minimizePaths();

	} else {
		cout << "Error: Cannot open the load file." << endl;
	}
}

string* Map::listToStringArray(list<string> l) {
	int count = 0;
	string* arr = NULL;
	for (list<string>::iterator it = l.begin(); it != l.end(); it++) {
		count++;
	}
	if (count > 0) {
		arr = new string[count];
		int j = 0;
		for (list<string>::iterator it = l.begin(); it != l.end(); it++) {
			string temp = *it;
			int x = tom.x, y = tom.y, len = (int) temp.length();
			for (int i = 0; i < len; i++) {
				if (temp[i] == 'F')
					x--;
				if (temp[i] == 'R')
					y++;
				if (temp[i] == 'B')
					x++;
				if (temp[i] == 'L')
					y--;
				arr[j] += temp[i];

				if (map[x][y] == 'P') {
					arr[j] += 'P';
				}
			}
			j++;
		}
	}
	return arr;
}

int Map::getListLength(list<string> l) {
	int count = 0;
	for (list<string>::iterator it = l.begin(); it != l.end(); it++) {
		count++;
	}
	return count;
}

void Map::whatCommands() {
	int pathNum = 0;
	for (list<string>::iterator it = minPaths.begin(); it != minPaths.end();
			it++) {
		cout << "Път " << pathNum++ << ": " << *it << endl;
	}
}

void Map::howMuchTurns() {
	int pathNum = 0;
	for (list<string>::iterator it = minPaths.begin(); it != minPaths.end();
			it++) {
		string temp = *it;
		char tempDirection = temp[0];
		int countTurns = 0;
		cout << "Път " << pathNum++ << ": ";
		for (int i = 1; i < (int) temp.length(); i++) {
			if (tempDirection != temp[i])
				countTurns++;
			tempDirection = temp[i];
		}
		cout << countTurns << endl;
	}
}

void Map::howMuchPaint() {
	int pathNum = 0;
	for (list<string>::iterator it = minPaths.begin(); it != minPaths.end();
			it++) {
		int paint = 0, x = tom.x, y = tom.y;
		string temp = *it;
		cout << "Път " << pathNum++ << ": ";
		for (int i = 0; i < (int) temp.length(); i++) {
			if (temp[i] == 'F')
				x--;
			if (temp[i] == 'R')
				y++;
			if (temp[i] == 'B')
				x++;
			if (temp[i] == 'L')
				y--;
			if (map[x][y] == 'P')
				paint++;
		}
		cout << paint << endl;
	}

}

void Map::minPathsToTree() {
	treeOfCommands.minPathsToTree(listToStringArray(minPaths),
			getListLength(minPaths), treeOfCommands.getRoot());
}

void Map::showTreeOfCommands() {
	treeOfCommands.saveTreeToFile("treeOfCommands.txt");
	ShellExecute(NULL, "Open",
			"E:\\Programs\\graphviz-2.38\\release\\bin\\gvedit.exe",
			"E:\\workspace\\TomAndJerry\\treeOfCommands.txt",
			NULL, SW_SHOWNORMAL);
}

void Map::maxPaintMinTurnsPath() {
	string* all = listToStringArray(allPaths); // премествам ги в масив от стрингове, за да им добави функцията P-та (боя)
	int n = getListLength(allPaths);
	int maxPaint = 0, minTurns = n * n * n * n;
	string path;
	for (int i = 0; i < n; i++) {
		int paint = 0;
		string temp = all[i];
		for (int j = 0; j < (int) temp.length(); j++) {
			if (temp[j] == 'P')
				paint++;
		}
		char tempDirection = temp[0];
		int countTurns = 0;
		for (int i = 1; i < (int) temp.length(); i++) {
			if (temp[i] == 'P')
				continue;
			if (tempDirection != temp[i])
				countTurns++;
			tempDirection = temp[i];
		}

		if (paint >= maxPaint) {
			if (paint == maxPaint) {
				if (countTurns < minTurns) {
					minTurns = countTurns;
					maxPaint = paint;
					path = temp;
				}
			} else {
				minTurns = countTurns;
				maxPaint = paint;
				path = temp;
			}
		}

	}
	cout << "Път: " << path << " Боя: " << maxPaint << " Завои: " << minTurns
			<< endl;
	delete[] all;
}

void Map::printMinPaths() {
	int pathNum = 0;
	for (list<string>::iterator it = minPaths.begin(); it != minPaths.end();
			it++) {
		string temp = *it;
		int x = tom.x, y = tom.y, len = (int) temp.length();
		cout << "Път " << pathNum++ << ": ";
		for (int i = 0; i < len; i++) {
			if (temp[i] == 'F')
				x--;
			if (temp[i] == 'R')
				y++;
			if (temp[i] == 'B')
				x++;
			if (temp[i] == 'L')
				y--;
			cout << "[" << x << ", " << y << "]";
			if (i != len - 1)
				cout << "->";
		}
		cout << endl;
	}
}

void Map::printInfoAboutPath(int index) {
	int count = 0;
	bool foundIndex = false;
	for (list<string>::iterator it = minPaths.begin(); it != minPaths.end();
			it++) {
		if (count == index) {
			foundIndex = true;
			string temp = *it;
			cout << "Информация за път номер " << index << endl;
			cout << "Команди на пътя: " << temp << endl;

			int paint = 0, x = tom.x, y = tom.y;
			for (int i = 0; i < (int) temp.length(); i++) {
				if (temp[i] == 'F')
					x--;
				if (temp[i] == 'R')
					y++;
				if (temp[i] == 'B')
					x++;
				if (temp[i] == 'L')
					y--;
				if (map[x][y] == 'P')
					paint++;
			}

			cout << "Количество разляна боя: " << paint << endl;

			char tempDirection = temp[0];
			int countTurns = 0;
			for (int i = 1; i < (int) temp.length(); i++) {
				if (tempDirection != temp[i])
					countTurns++;
				tempDirection = temp[i];
			}

			cout << "Брой на завоите:" << countTurns << endl;

			break;
		}
		count++;
	}
	if (!foundIndex)
		cout << "Грешка: Няма път с такъв индекс." << endl;
}

string Map::removePaintFromPath(string path) {
	string temp;
	for (int i = 0; i < (int) path.length(); i++) {
		if (path[i] != 'P') {
			temp += path[i];
		}
	}
	return temp;
}

int Map::howMuchP(string path) {
	int paint = 0;
	for (int i = 0; i < (int) path.length(); i++) {
		if (path[i] == 'P')
			paint++;
	}
	return paint;
}

void Map::twoDronesMaxPaint() {
	string* all = listToStringArray(allPaths); // премествам ги в масив от стрингове, за да им добави функцията P-та (боя)
	int n = getListLength(allPaths);

	//Сортираме масива по дължина (без да включваме P-тата)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (removePaintFromPath(all[j]).length()
					> removePaintFromPath(all[j + 1]).length())
				swap(all[j], all[j + 1]);
		}
	}

	// Сортираме елементите, които имат еднаква дължина по броя P-та, които имат в намаляващ ред
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n - 1; i++) {
			if (removePaintFromPath(all[i]).length()
					== removePaintFromPath(all[i + 1]).length()) {
				int paintLeft = 0, paintRight = 0;
				for (int j = 0; j < (int) all[i].length(); j++) {
					if (all[i][j] == 'P') {
						paintLeft++;
					}
				}

				for (int j = 0; j < (int) all[i + 1].length(); j++) {
					if (all[i + 1][j] == 'P') {
						paintRight++;
					}
				}
				if (paintLeft < paintRight)
					swap(all[i], all[i + 1]);
			}
		}
	}

	// Търсим първите два пътя с равна дължина (без да броим P-тата), за които двата дрона
	// нямат едни и същи координати по едно и също време
	bool foundTwoPaths = false;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			string temp1 = removePaintFromPath(all[i]), temp2 =
					removePaintFromPath(all[j]);
			if (temp1.length() == temp2.length()) {
				Point t1, t2;
				t1.x = tom.x;
				t1.y = tom.y;
				t2.x = tom.x;
				t2.y = tom.y;
				bool found = false;
				for (int z = 0; z < (int) temp1.length(); z++) {
					if (temp1[z] == 'F')
						t1.x--;
					if (temp1[z] == 'R')
						t1.y++;
					if (temp1[z] == 'B')
						t1.x++;
					if (temp1[z] == 'L')
						t1.y--;
					if (temp2[z] == 'F')
						t2.x--;
					if (temp2[z] == 'R')
						t2.y++;
					if (temp2[z] == 'B')
						t2.x++;
					if (temp2[z] == 'L')
						t2.y--;
					if (t1.x == t2.x && t1.y == t2.y) {
						break;
					}
					found = true;
				}
				// Ако намерим два от търсените пътища ги извеждаме
				if (found) {
					foundTwoPaths = true;
					cout << "Път за дрон 1:" << temp1 << endl;
					cout << "Път за дрон 2:" << temp2 << endl;
					break;
				}
			}

		}
		if (foundTwoPaths)
			break;
	}
	if (!foundTwoPaths)
		cout << "Няма намерени два равни пътя." << endl;
	delete[] all;
}

int Map::lengthMinPath() {
	return minPaths.front().length();
}

void Map::minimizePaths() {
	int min = minPaths.begin()->length();
	for (list<string>::iterator it = minPaths.begin(); it != minPaths.end();
			it++) {
		if (min > (int) it->length())
			min = it->length();
	}
	for (list<string>::iterator it = minPaths.begin(); it != minPaths.end();
			it++) {
		if ((int) it->length() != min) {
			it = minPaths.erase(it);
			--it;
		}
	}
}

void Map::savePath(char path[], int startPos, int endPos) {
	string temp;
	for (int i = startPos; i <= endPos; i++) {
		temp += path[i];
	}
	minPaths.push_back(temp);
}

void Map::findPath(int row, int col, char direction) {
	if (col >= 0 && row >= 0 && col < m && row < n) {
		path[position] = direction;
		position++;
		if (map[row][col] == 'J') {
			savePath(path, 1, position - 1);
		}
		bool t = false, p = false;
		if (map[row][col] == '-' || map[row][col] == 'T'
				|| map[row][col] == 'P') {
			if (map[row][col] == 'T')
				t = true;
			if (map[row][col] == 'P')
				p = true;
			map[row][col] = 's';

			findPath(row - 1, col, 'F'); // Up (Front)
			findPath(row, col + 1, 'R'); // Right
			findPath(row + 1, col, 'B'); // Down (Back)
			findPath(row, col - 1, 'L'); // Left

			map[row][col] = '-';
			if (t)
				map[row][col] = 'T';
			if (p)
				map[row][col] = 'P';
		}

		position--;
	}
}

Map::Map(char* pathToLoadFile) {
	position = 0;
	loadFromFile(pathToLoadFile);
	minPathsToTree();
}

Map::~Map() {
	for (int i = 0; i < n; i++)
		delete[] map[i];
	//delete path;

}
