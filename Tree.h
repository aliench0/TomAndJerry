/*
 * Tree.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Hristiyan Nikolov
 */

#ifndef TREE_H_
#define TREE_H_

#include<iostream>
#include<fstream>
#include "Tree.h"
using namespace std;

struct Node {
	char data;
	int number;
	Node* front;
	Node* right;
	Node* back;
	Node* left;
	Node* paint;
};

class Tree {
private:
	int countNodes;
	Node* root;

	int differentChars(string s); // връща броя на различните символи в един стринг
	bool sameFirstChars(string arr[], int n); // проверява дали първите букви на масив от стрингове са еднакви
	int makeNewStringArray(string* &newArr, string oldArr[], int n, char data); // подава се по референция нов масив, който се пълни със елементите
																				// на стария, които започват с символа data, и ф-ята връща размера на новия масив
	void writeLabels(ofstream& of, Node* root); // използва се от saveTreeToFile(); записва етикетите с номерата на върховете
	void writeConnections(ofstream& of, Node* parrent, Node* child); // записва връзките между върховете
	void deleteTree(Node* root);

public:
	Tree();
	~Tree();

	Node* getRoot(); // връща указател към корена на дървото
	void minPathsToTree(string* arr, int n, Node* parrent); // взима минималните пътища от масив от стрингове (в който има включени местата за боя) и
															// прави дърво с корен root;
	void printTree(Node* parrent, Node* child); // Node* parrent = NULL, Node* child = this->root !?
	void saveTreeToFile(char* pathToFile); // запазва дървото в файл по подходяш начин за визуализиране с DOT tool

};

#endif /* TREE_H_ */
