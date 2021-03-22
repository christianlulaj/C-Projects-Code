//
// Created by Christian Lulaj on 11/18/20.
//

#ifndef PROJECT_PRODUCT_H
#define PROJECT_PRODUCT_H

#include <iostream>

#include "Store.h"
#include "DollarAmount.h"

class Product {
  std::shared_ptr<const Store> store;
  std::string item;
  int quantity = 0;
  DollarAmount price;
  static std::vector<std::string> split(const std::string &s, const std::string &delim = ",");
 public:
  Product(const std::shared_ptr<const Store> &s, const std::string &item = "", int qty = 0, DollarAmount price = DollarAmount());
  Product() = default;
  bool hasName(const std::string &) const;
  std::string getItem() const;
  int getQuantity() const;
  DollarAmount getPrice() const;
  const Store &getStore() const;
  DollarAmount operator*(int lhs) const;
  bool operator<(const Product &rhs) const;
  bool operator==(const Product &rhs) const;
  bool operator!=(const Product &rhs) const;
  operator bool() const;
  friend std::istream &operator>>(std::istream &is, Product &product);
  friend std::ostream &operator<<(std::ostream &os, const Product &product);
};

#endif //PROJECT_PRODUCT_H
