//
// Created by Christian Lulaj on 11/18/20.
//

#include <sstream>
#include <utility>
#include "Product.h"

Product::Product(const std::shared_ptr<const Store> &s, const std::string &item, int quantity, DollarAmount price) :
    store(s), item(item), quantity(quantity), price(price) {
}

std::string Product::getItem() const {
  return item;
}

int Product::getQuantity() const {
  return quantity;
}

DollarAmount Product::getPrice() const {
  return price;
}

std::istream &operator>>(std::istream &is, Product &product) {
  std::string line;
  getline(is, line);
  std::vector<std::string> parts = Product::split(line);
  if (parts.empty()) return is;
  product.item = parts[0];
  product.quantity = stoi(parts[1]);
  product.price = DollarAmount::parse(parts[2]);
  return is;
}

std::ostream &operator<<(std::ostream &os, const Product &product) {
  os << "Item: " << product.item << std::endl;
  os << "Quantity: " << product.quantity << std::endl;
  os << "Price: " << product.getPrice() << std::endl;
  return os;
}

// Based on: https://stackoverflow.com/a/14267455
std::vector<std::string> Product::split(const std::string &s, const std::string &delim) {
  std::vector<std::string> result;
  unsigned long start = 0;
  unsigned long end = s.find(delim);
  while (end != std::string::npos) {
    result.emplace_back(move(s.substr(start, end - start)));
    start = end + delim.length();
    end = s.find(delim, start);
  }
  // if there is content remaining in the std::string, we want to add it to the std::vector
  if (s.size() - start > 0) result.emplace_back(move(s.substr(start, end)));
  return result;
}

const Store &Product::getStore() const {
  return *store;
}

bool Product::hasName(const std::string &name) const {
  return item == name;
}

bool Product::operator<(const Product &rhs) const {
  return price < rhs.price;
}

DollarAmount Product::operator*(int lhs) const {
  return lhs * price;
}

bool Product::operator==(const Product &rhs) const {
  return price == rhs.price;
}

bool Product::operator!=(const Product &rhs) const {
  return !(rhs == *this);
}

Product::operator bool() const {
  return !item.empty();
}
