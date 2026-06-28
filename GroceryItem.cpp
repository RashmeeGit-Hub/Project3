#include "GroceryItem.h"

GroceryItem::GroceryItem(string itemName, int itemQuantity) {
	name = itemName;
	quantity = itemQuantity;
}

string GroceryItem::GetName() const {
	return name;
}

int GroceryItem::GetQuantity() const {
	return quantity;
}

void GroceryItem::AddItem() {
	quantity++;
}
