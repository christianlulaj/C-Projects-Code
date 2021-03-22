//
// Created by Christian Lulaj on 11/23/20.
//
#include <algorithm>

#include <vector>

#include "Product.h"
#include "Store.h"
#include "ShoppingListItem.h"
#include <numeric>
#include <functional>

ShoppingListItem::ShoppingListItem(const std::string &item, int qtyNeeded)
    : item(item), qtyNeeded(qtyNeeded) {
  findStores();
}

DollarAmount ShoppingListItem::getTotalCost() const {
  auto getTotal = [](const std::map<Product, int>::value_type &p) -> DollarAmount { return p.first.getPrice() * p.second; };
  std::vector<DollarAmount> amounts;
  std::transform(products.begin(), products.end(), back_inserter(amounts), getTotal);
  return std::accumulate(amounts.begin(), amounts.end(), DollarAmount(), std::plus<>());
}

std::ostream &operator<<(std::ostream &out, const ShoppingListItem &sli) {
  out << "Trying to order " << sli.qtyNeeded << " " << sli.item << "(s)." << std::endl;
  out << sli.storesSelling << " store(s) sell " << sli.item << "." << std::endl;
  out << "Total price: " << sli.getTotalCost() << std::endl;
  for (auto[product, productQty] : sli.products) {
    out << "Order " << productQty << " ";
//    out << product.getItem() << " "; // Disable when not debugging
    out << "from ";
    out << product.getStore().getName() << " in "
        << product.getStore().getCity() << std::endl;
  }
  return out;
}

std::istream &operator>>(std::istream &in, ShoppingListItem &sli) {
  in >> sli.qtyNeeded;
  getline(in >> std::ws, sli.item);
  sli.storesFound = false;
  sli.products.clear();
  sli.findStores();
  return in;
}

void ShoppingListItem::findStores() {
  if (qtyNeeded <= 0 || storesFound) return;
  std::vector<Product> availableProducts = Store::getItemFromAllStores(item);
  storesSelling = availableProducts.size();
  auto isProductCheaper = [](const Product &a, const Product &b) -> bool { return a.getPrice() < b.getPrice(); };
  sort(availableProducts.begin(), availableProducts.end(), isProductCheaper);
  auto availableProductIt = availableProducts.begin();
  int currentQty = 0;

  while (currentQty < qtyNeeded && availableProductIt != availableProducts.end()) {
    int nextQty = std::min(qtyNeeded - currentQty, availableProductIt->getQuantity());

    products.emplace(*availableProductIt, nextQty);
    currentQty += nextQty;
    ++availableProductIt;
  }
//  if (currentQty < qtyNeeded) {
//    std::cerr << "Warning: Not enough " << item << "(s) available to meet required quantity of " << qtyNeeded << std::endl;
//  }
  storesFound = true;
}

