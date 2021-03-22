//
// Created by Christian Lulaj on 11/18/20.
//

#include "Store.h"
#include <numeric>
#include <utility>
#include <functional>
#include "Product.h"
using namespace std::placeholders;

std::vector<std::shared_ptr<Store>> Store::STORES{};

Store::Store(const std::string &name, const std::string &city) : enable_shared_from_this<Store>(), name(name), city(city) {}

std::shared_ptr<Store> Store::getptr() { return shared_from_this(); }
std::shared_ptr<const Store> Store::getptr() const { return shared_from_this(); }

int Store::getDistinctItems() const {
  return products.size();
}

std::string Store::getName() const {
  return name;
}

std::string Store::getCity() const {
  return city;
}

void Store::addProduct(const Product &p) { products.push_back(p); }

std::istream &operator>>(std::istream &in, const std::shared_ptr<Store> &store) {
  getline(in, store->name);
  getline(in, store->city);
  std::string line;
  Product newProduct;
  while (!in.eof()) {
    newProduct = Product(store);
    in >> newProduct;
    if (!newProduct) break;
    store->addProduct(newProduct);
  }
  return in;
}

void Store::loadAll(std::istream &in) {
  int count;
  in >> count;
  // Must ignore rest of line.
  // From https://en.cppreference.com/w/cpp/io/basic_std::istream/ignore
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (int i = 0; i < count; ++i) {
    std::shared_ptr<Store> storePtr(std::make_shared<Store>());
    in >> storePtr;
    STORES.push_back(storePtr);
  }
  in >> std::ws;
}

std::ostream &operator<<(std::ostream &os, const std::shared_ptr<const Store> &store) {
  os << "Store Name: " << store->name << std::endl;
  os << "Store City: " << store->city << std::endl;
  os << "Products: " << std::endl;
  for (const Product &p : store->products) os << p << std::endl;
  return os;
}

std::map<std::string, int> Store::getItemQuantities() {
  using resultType = std::map<std::string, int>;
  auto addProductQuantity = [](resultType &result, const Product &p) -> resultType & {
    result[p.getItem()] += p.getQuantity();
    return result;
  };

  auto productAccumulator = std::accumulate<std::vector<Product>::const_iterator, resultType &, decltype(addProductQuantity)>;
  auto addStoreProducts =
      [&productAccumulator, &addProductQuantity](resultType &result, const std::shared_ptr<const Store> &s) -> resultType & {
        return productAccumulator(s->products.begin(), s->products.end(), result, addProductQuantity);
      };

  resultType itemQuantities;
  auto storeAccumulator =
      std::accumulate<std::vector<std::shared_ptr<Store>>::const_iterator, resultType &, decltype(addStoreProducts)>;
  return storeAccumulator(STORES.begin(), STORES.end(), itemQuantities, addStoreProducts);
}

const std::vector<Product> &Store::getProducts() const {
  return products;
}

void Store::showSummary() {
  std::cout << "Store Related Information (ordered by in-file order):" << std::endl;
  std::cout << "There are " << STORES.size() << " store(s)." << std::endl;
  for (const auto &s : STORES) std::cout << s->name << " has " << s->getDistinctItems() << " distinct items." << std::endl;

  std::cout << std::endl << "Item Related Information (ordered alphabetically):" << std::endl;
  const std::map<std::string, int> itemQuantitites = getItemQuantities();
  std::cout << "There are " << itemQuantitites.size() << " distinct item(s) available for purchase." << std::endl;
  for (const auto&[name, qty] : itemQuantitites) std::cout << "There are " << qty << " " << name << "(s)." << std::endl;
}

std::vector<Product> Store::getItemFromAllStores(const std::string &item) {
  std::vector<Product> result;
  auto productMatches = bind(mem_fn(&Product::hasName), _1, item);
  auto addToResult =
      [&productMatches](std::vector<Product> &result, const std::shared_ptr<const Store> &store) -> std::vector<Product> & {
        copy_if(store->products.begin(), store->products.end(), back_inserter(result), productMatches);
        return result;
      };
  return std::accumulate(STORES.begin(), STORES.end(), result, addToResult);
}

std::vector<Product> Store::getItem(const std::string &item) {
  std::vector<Product> result;
  auto itemHasName = bind(mem_fn(&Product::hasName), std::placeholders::_1, item);
  copy_if(products.begin(), products.end(), back_inserter(result), itemHasName);
  return result;
}



