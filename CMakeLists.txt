cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project project.cpp Store.cpp Store.h Product.cpp Product.h ShoppingListItem.cpp ShoppingListItem.h ShoppingList.cpp ShoppingList.h DollarAmount.cpp DollarAmount.h)