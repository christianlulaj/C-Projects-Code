//
// Created by Christian Lulaj on 11/23/20.
//

#ifndef PROJECT_SHOPPINGLIST_H
#define PROJECT_SHOPPINGLIST_H

#include <vector>
#include "ShoppingListItem.h"

class ShoppingList {
  std::vector<ShoppingListItem> items;
 public:
  ShoppingList() = default;
  ShoppingList(const std::vector<ShoppingListItem> &);
  ShoppingList(const std::map<std::string, int> &);
  void addItem(const ShoppingListItem &);
  void addItem(const std::string &item, int quantity);
  void addItem(const std::pair<std::string, int> &item);
  DollarAmount getTotalPrice() const;

  friend std::ostream &operator<<(std::ostream &out, const ShoppingList &sl);
  friend std::istream &operator>>(std::istream &in, ShoppingList &sl);
};

#endif //PROJECT_SHOPPINGLIST_H
