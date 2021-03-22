#include <iostream>
#include <vector>
#include <fstream>
#include "Product.h"
#include "Store.h"
#include "ShoppingListItem.h"
#include "ShoppingList.h"
int main() {
//    std::ifstream inFile = std::ifstream("input.txt");
//    std::istream &in = inFile; // To switch to std::cin, comment out above and replace inFile with std::cin
  std::istream &in = std::cin;

  //check For Error
  if (in.fail()) {
    std::cerr << "Error Opening File" << std::endl;
    exit(1);
  }

  Store::loadAll(in);
  Store::showSummary();

  std::cout << std::endl << "Shopping:" << std::endl;
  ShoppingList shoppingList;
  in >> shoppingList;
  std::cout << shoppingList << std::endl;
}
