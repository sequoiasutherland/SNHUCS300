//============================================================================
// Name        : Project2.cpp
// Author      : Sequoia Sutherland
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>


using namespace std;


// Print menu
void printMenu() {
	cout << "1. Load Data Structure." << endl;
	cout << "2. Print Course List." << endl;
	cout << "3. Print Course." << endl;
	cout << "9. Exit." << endl;
}

// Create course structure
struct Course {
	string courseNumber;
	string courseName;
	vector <string> prerequisites;
	Course* left;
	Course* right;
};

Course* root = nullptr;

// Load data structure
void loadBST(string fileName, Course* &root) {
	ifstream inFile;
	inFile.open(fileName);

	string line;
	while(getline(inFile, line)) {
		vector<string> tokens;
		istringstream ss(line);
		string token;
		while (getline(ss, token, ',')) {
			tokens.push_back(token);
		}
		Course* newCourse = new Course;
		newCourse->courseNumber = tokens[0];
		newCourse->courseName = tokens[1];
		if(tokens.size() > 2) {
			istringstream ss2(tokens[2]);
			string prereq;
			while(getline(ss2, prereq, ',')) {
				newCourse->prerequisites.push_back(prereq);
			}
		}
		newCourse->left = nullptr;
		newCourse->right = nullptr;
		if(root == nullptr) {
			root = newCourse;
		}
		else {
			Course* current = root;
			Course* parent = nullptr;
			while(current != nullptr) {
				parent = current;
				if(newCourse->courseNumber < current->courseNumber) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}
			if(newCourse->courseNumber < parent->courseNumber) {
				parent->left = newCourse;
			}
			else {
				parent->right = newCourse;
			}
		}
	}
	inFile.close();
}

// Print course list
void printBST(Course* root) {
	if(root != nullptr) {
		printBST(root->left);
		cout << root->courseNumber << ", " << root->courseName << endl;
		printBST(root->right);
	}
}


// Print course
void printCourse(string userCourse, Course* root) {
	Course* current = root;
	while(current != nullptr) {
		if(userCourse == current->courseNumber) {
			cout << current->courseNumber << ", " << current->courseName << endl;
			if(current->prerequisites.size() > 0) {
				cout << "Prerequisites: ";
				for(string prereq : current->prerequisites) {
					cout << prereq << ", ";
				}
				cout << endl;
			}
			return;
		}
		else if(userCourse < current->courseNumber) {
			current = current->left;
		}
		else {
			current = current->right;
		}

	}
}

int main() {
	int userChoice;
	string userCourse;
	cout << "Welcome to the course planner." << endl;
	while (userChoice != 9) {
		printMenu();
		cout << "What would you like to do?";
		cin >> userChoice;
		if (userChoice == 1) {
			loadBST("courses.csv", root);
			cout << "Courses have been loaded." << endl;
			return 0;
		}
		if (userChoice == 2) {
			printBST(root);
			return 0;
		}
		if (userChoice == 3) {
			cout << "What course do you want to know about?";
			cin >> userCourse;
			printCourse(userCourse, root);
			return 0;
		}
		else {
			cout << userChoice << " is not a valid option." << endl;
			cout << endl;
			printMenu();
			cout << "What would you like to do?";
			cin >> userChoice;
			return 0;
		}
	}
	if (userChoice == 9) {
		exit;
	}
	return 0;
}
