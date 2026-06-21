#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "GroceryItem.h"

using namespace std;

map<string, GroceryItem*> ReadInventoryFile() {

	// Store grocery items
	map<string, GroceryItem*> items;

	// Open inventory file 
	ifstream inputFile("inventory.txt");

	if (!inputFile.is_open()) {
		cout << "Error: inventory.txt could not be opened." << endl;
	}

	string itemName;

	//Read one item at a time
	while (inputFile >> itemName) {

		// Item already exists
		if (items.count(itemName) > 0) {
			items.at(itemName)->AddItem();
		}

		// First time item was found
		else {
			GroceryItem* newItem = new GroceryItem(itemName, 1);
			items.emplace(itemName, newItem);

		}

	}

	inputFile.close();

	return items;
}

void WriteBackupFile(map<string, GroceryItem*> items) {



	// Create backup file
	ofstream outputFile("frequency.dat");
	map<string, GroceryItem*>::iterator it;

	// Write each item and quantity to the backup file
	for (it = items.begin(); it != items.end(); ++it) {
		outputFile << it->second->GetName() << " "
			<< it->second->GetQuantity() << endl;
	}

	outputFile.close();
}

void DeleteItems(map<string, GroceryItem*>& items) {

	// Free memory used by GroceryItem pointers
	map<string, GroceryItem*>::iterator it;

	for (it = items.begin(); it != items.end(); ++it) {
		delete it->second;
	}

	items.clear();
}

int main() {

	int choice = 0;

	// Create backup file when the program starts
	map<string, GroceryItem*> initialItems;
	initialItems = ReadInventoryFile();
	WriteBackupFile(initialItems);
	DeleteItems(initialItems);

	while (choice != 4) {

		cout << endl;
		cout << "Corner Grocer Program" << endl;
		cout << "1. Search for an item" << endl;
		cout << "2. Display all item frequencies" << endl;
		cout << "3. Display histogram" << endl;
		cout << "4. Exit" << endl;

		cout << "Enter your choice: ";

		if (!(cin >> choice)) {
			cout << "Invalid input. Please enter a number from 1 to 4." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			choice = 0;
			continue;
		}


		if (choice == 1) {
			map<string, GroceryItem*> items;
			items = ReadInventoryFile();
			WriteBackupFile(items);

			string itemName;

			cout << "Enter item name: ";
			cin >> itemName;

			if (items.count(itemName) > 0) {
				cout << itemName << " was purchased "
					<< items.at(itemName)->GetQuantity()
					<< " times." << endl;
			}
			else {
				cout << itemName << " was not found." << endl;
			}
			DeleteItems(items);
		}

		else if (choice == 2) {
			map<string, GroceryItem*> items;
			items = ReadInventoryFile();
			WriteBackupFile(items);

			map<string, GroceryItem*>::iterator it;

			for (it = items.begin(); it != items.end(); ++it) {
				cout << it->second->GetName() << " "
					<< it->second->GetQuantity() << endl;
			}
			DeleteItems(items);
		}

		else if (choice == 3) {
			map<string, GroceryItem*> items;
			items = ReadInventoryFile();
			WriteBackupFile(items);

			map<string, GroceryItem*>::iterator it;
			for (it = items.begin(); it != items.end(); ++it) {
				cout << it->second->GetName() << " ";

				for (int i = 0; i < it->second->GetQuantity(); ++i) {
					cout << "*";
				}

				cout << endl;
			}
			DeleteItems(items);
		}
		else if (choice == 4) {
			cout << "Goodbye!" << endl;
		}

		else {
			cout << "Invalid option. Please enter a number from 1 to 4." << endl;
		}
	}

return 0;
}
