#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>
using namespace std;

class GroceryItem {
private:
	string name;
	int quantity;

public:
	GroceryItem(string itemName, int itemQuantity);

	string GetName() const;
	int GetQuantity() const;

	void AddItem();

};

#endif