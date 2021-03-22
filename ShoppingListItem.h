//
// Created by Christian Lulaj on 11/23/20.
//

#ifndef PROJECT_SHOPPINGLISTITEM_H
#define PROJECT_SHOPPINGLISTITEM_H

#include "DollarAmount.h"
#include "Product.h"

class ShoppingListItem {
  std::string item;
  int qtyNeeded;
  std::map<Product, int> products; // std::map of each store's version of a product and the quantity from that store
  int storesSelling;
  bool storesFound = false;
  void findStores();
 public:
  ShoppingListItem() = default;
  ShoppingListItem(const ShoppingListItem &) = default;
  ShoppingListItem(const std::string &item, int qtyNeeded);
  DollarAmount getTotalCost() const;

  friend std::ostream &operator<<(std::ostream &out, const ShoppingListItem &sli);
  friend std::istream &operator>>(std::istream &in, ShoppingListItem &sli);

};

#endif //PROJECT_SHOPPINGLISTITEM_H
