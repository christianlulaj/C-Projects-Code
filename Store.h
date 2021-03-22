//
// Created by Christian Lulaj on 11/18/20.
//

#ifndef PROJECT_STORE_H
#define PROJECT_STORE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <memory>
class Product;
class Store : std::enable_shared_from_this<Store> {
  std::vector<Product> products;
  std::string name;
  std::string city;
 public:
  static std::vector<std::shared_ptr<Store>> STORES;
  static std::map<std::string, int> getItemQuantities();
  static void showSummary();
  static std::vector<Product> getItemFromAllStores(const std::string &item);

  Store() = default;
  Store(const std::string &name, const std::string &city);
  static void loadAll(std::istream &in);
  void addProduct(const Product &p);
  std::string getName() const;
  std::string getCity() const;
  const std::vector<Product> &getProducts() const;
  int getDistinctItems() const;
  std::vector<Product> getItem(const std::string &item);
  std::shared_ptr<Store> getptr();
  std::shared_ptr<const Store> getptr() const;
  friend std::istream &operator>>(std::istream &is, const std::shared_ptr<Store> &store);
  friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<const Store> &store);
};
#endif //PROJECT_STORE_H
