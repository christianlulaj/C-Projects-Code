//
// Created by Christian Lulaj on 11/23/20.
//

#include "ShoppingList.h"
#include <algorithm>

#include <vector>
#include <functional>
using namespace std::placeholders;
#include "Product.h"
#include "Store.h"
#include "ShoppingListItem.h"
#include <numeric>

ShoppingList::ShoppingList(const std::vector<ShoppingListItem> &items) : items(items) {

}

ShoppingList::ShoppingList(const std::map<std::string, int> &items) {
  for (const auto &item : items) addItem(item);
}

void ShoppingList::addItem(const ShoppingListItem &item) {
  items.push_back(item);
}

void ShoppingList::addItem(const std::string &item, int quantity) {
  items.emplace_back(item, quantity);
}

void ShoppingList::addItem(const std::pair<std::string, int> &item) {
  items.emplace_back(item.first, item.second);
}

DollarAmount ShoppingList::getTotalPrice() const {
  std::vector<DollarAmount> prices;
  std::transform(items.begin(),
            items.end(),
            back_inserter(prices),
            std::mem_fn(&ShoppingListItem::getTotalCost));
  return std::accumulate(prices.begin(), prices.end(), DollarAmount(), std::plus<>());
}

std::ostream &operator<<(std::ostream &out, const ShoppingList &sl) {
  auto showShoppingListItem = [&out](const ShoppingListItem &sli) -> std::ostream & { return out << sli << std::endl; };
  for_each(sl.items.begin(), sl.items.end(), showShoppingListItem);
  out << "Be sure to bring " << sl.getTotalPrice() << " when you leave for the stores.";
  return out;
}

std::istream &operator>>(std::istream &in, ShoppingList &sl) {
  int count;

  in >> std::ws >> count;
  // Skip first line of input (# of stores)
  // From https://en.cppreference.com/w/cpp/io/basic_std::istream/ignore

  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (int i = 0; i < count; ++i) {
    ShoppingListItem newItem;
    in >> newItem;
    sl.addItem(newItem);
  }
  return in;
}