/*
 * Tree.cpp
 *
 *  Created on: Jan 14, 2016
 *      Author: Hristiyan Nikolov
 */

#include "Tree.h"

int Tree::differentChars(string s) {
	char temp[s.length()];
	temp[0] = s[0];
	int tempLength = 1; // Показва колко елементи има в temp
	for (int i = 1; i < (int) s.length(); i++) {
		bool found = false;
		for (int j = 0; j < tempLength; j++) {
			if (s[i] == temp[j])
				found = true;
		}
		if (found == false)
			temp[tempLength++] = s[i];
	}

	return tempLength;
}

bool Tree::sameFirstChars(string arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (arr[i][0] != arr[i + 1][0])
			return false;
	}
	return true;
}

int Tree::makeNewStringArray(string* &newArr, string oldArr[], int n,
		char data) {
	string temp[n];
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (oldArr[i][0] == data) {
			temp[count++] = oldArr[i].substr(1, oldArr[i].length());
		}
	}
	if (count > 0) {
		newArr = new string[count];
		for (int i = 0; i < count; i++) {
			newArr[i] = temp[i];
		}
	}
	return count;
}

void Tree::saveTreeToFile(char* pathToFile) {
	ofstream file(pathToFile, ios::trunc);
	if (file.is_open()) {
		file << "graph G {" << endl;
		writeLabels(file, root);
		writeConnections(file, NULL, root);
		file << "}";

	} else {
		cout << "Error: Cannot open save file." << endl;
	}

}

void Tree::writeLabels(ofstream& of, Node* root) {
	if (root != NULL) {
		if (root->data != 'S')
			of << root->number << " [label=\"" << root->data << "\"]" << endl;
		else
			of << root->number << " [label=\"Start\"]" << endl;
		writeLabels(of, root->front);
		writeLabels(of, root->right);
		writeLabels(of, root->back);
		writeLabels(of, root->left);
		writeLabels(of, root->paint);
	}

}

void Tree::writeConnections(ofstream& of, Node* parrent, Node* child) {
	if (child != NULL) {
		if (parrent != NULL) {
			of << parrent->number << " -- " << child->number << endl;
		}
		writeConnections(of, child, child->front);
		writeConnections(of, child, child->right);
		writeConnections(of, child, child->back);
		writeConnections(of, child, child->left);
		writeConnections(of, child, child->paint);
	}
}

void Tree::minPathsToTree(string* arr, int n, Node* parrent) {
	if (arr[0].length() > 0) {
		if (sameFirstChars(arr, n)) {
			string* newArr;
			int newN = makeNewStringArray(newArr, arr, n, arr[0][0]);
			Node* temp;
			temp = new Node;
			temp->data = arr[0][0];
			temp->number = countNodes++;
			temp->front = NULL;
			temp->right = NULL;
			temp->back = NULL;
			temp->left = NULL;
			temp->paint = NULL;
			if (arr[0][0] == 'F')
				parrent->front = temp;
			if (arr[0][0] == 'R')
				parrent->right = temp;
			if (arr[0][0] == 'B')
				parrent->back = temp;
			if (arr[0][0] == 'L')
				parrent->left = temp;
			if (arr[0][0] == 'P')
				parrent->paint = temp;
			minPathsToTree(newArr, newN, temp);
			delete[] newArr;
		} else {
			string* newArrF;
			int FNumber = makeNewStringArray(newArrF, arr, n, 'F');
			if (FNumber > 0) {
				Node* temp = new Node;
				temp->data = 'F';
				temp->number = countNodes++;
				temp->front = NULL;
				temp->right = NULL;
				temp->back = NULL;
				temp->left = NULL;
				temp->paint = NULL;
				parrent->front = temp;
				minPathsToTree(newArrF, FNumber, temp);
				delete[] newArrF;
			}
			string* newArrR;
			int RNumber = makeNewStringArray(newArrR, arr, n, 'R');
			if (RNumber > 0) {
				Node* temp = new Node;
				temp->data = 'R';
				temp->number = countNodes++;
				temp->front = NULL;
				temp->right = NULL;
				temp->back = NULL;
				temp->left = NULL;
				temp->paint = NULL;
				parrent->right = temp;
				minPathsToTree(newArrR, RNumber, temp);
				delete[] newArrR;
			}
			string* newArrB;
			int BNumber = makeNewStringArray(newArrB, arr, n, 'B');
			if (BNumber > 0) {
				Node* temp = new Node;
				temp->data = 'B';
				temp->number = countNodes++;
				temp->front = NULL;
				temp->right = NULL;
				temp->back = NULL;
				temp->left = NULL;
				temp->paint = NULL;
				parrent->back = temp;
				minPathsToTree(newArrB, BNumber, temp);
				delete[] newArrB;
			}
			string* newArrL;
			int LNumber = makeNewStringArray(newArrL, arr, n, 'L');
			if (LNumber > 0) {
				Node* temp = new Node;
				temp->data = 'L';
				temp->number = countNodes++;
				temp->front = NULL;
				temp->right = NULL;
				temp->back = NULL;
				temp->left = NULL;
				temp->paint = NULL;
				parrent->left = temp;
				minPathsToTree(newArrL, LNumber, temp);
				delete[] newArrL;
			}
			string* newArrP;
			int PNumber = makeNewStringArray(newArrP, arr, n, 'P');
			if (PNumber > 0) {
				Node* temp = new Node;
				temp->data = 'P';
				temp->number = countNodes++;
				temp->front = NULL;
				temp->right = NULL;
				temp->back = NULL;
				temp->left = NULL;
				temp->paint = NULL;
				minPathsToTree(newArrP, PNumber, temp);
				delete[] newArrP;
			}

		}
	}

}

Node* Tree::getRoot() {
	return root;
}

void Tree::printTree(Node* parrent, Node* child) {
	if (child != NULL) {
		if (parrent != NULL)
			cout << "Son of id: " << parrent->number << ", data: "
					<< parrent->data << "= data: " << child->data << " id:"
					<< child->number << endl;
		else
			cout << "ID: " << child->number << ", data:" << child->data << endl;
		printTree(child, child->front);
		printTree(child, child->right);
		printTree(child, child->back);
		printTree(child, child->left);
		printTree(child, child->paint);
	}
}

void Tree::deleteTree(Node* root) {
	if(root != NULL){
		deleteTree(root->front);
		deleteTree(root->right);
		deleteTree(root->back);
		deleteTree(root->left);
		deleteTree(root->paint);
		delete root;
	}
}


Tree::Tree() {
	countNodes = 1;
	root = new Node;
	root->data = 'S';
	root->number = 0;
	root->front = NULL;
	root->right = NULL;
	root->back = NULL;
	root->left = NULL;
	root->paint = NULL;
}

Tree::~Tree() {
	deleteTree(root);
}
