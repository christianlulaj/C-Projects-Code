//
// Created by Christian Lulaj on 11/25/20.
//
#include <iostream>
#include <iomanip>
#include "DollarAmount.h"

DollarAmount::DollarAmount(int dollars, int cents) : dollars(dollars), cents(cents) {}

DollarAmount::DollarAmount(int cents) : dollars(cents / 100), cents(cents % 100) {

}

DollarAmount::DollarAmount(double amt) : DollarAmount(static_cast<int>(amt * 100)) {
}

DollarAmount DollarAmount::parse(std::string str) {
  DollarAmount result;
  if (str[0] == '$') str.erase(0, 1);
  std::string::size_type decimalPt = str.find('.');
  result.dollars = stoi(str.substr(0, decimalPt));
  if (decimalPt != std::string::npos && decimalPt != str.size()) {
    result.cents = stoi(str.substr(decimalPt + 1));
  }
  return result;
}

DollarAmount DollarAmount::parse(int cents) {
  return DollarAmount(cents);
}

DollarAmount DollarAmount::parse(double amnt) {
  return DollarAmount(amnt);
}

DollarAmount DollarAmount::operator*(int qty) const {
  DollarAmount newAmt(*this);
  newAmt *= qty;
  return newAmt;
}

DollarAmount &DollarAmount::operator*=(int qty) {
  dollars *= qty;
  cents *= qty;
  dollars += cents / 100;
  cents %= 100;
  return *this;
}

DollarAmount DollarAmount::operator+(const DollarAmount &other) const {
  DollarAmount result(*this);
  result += other;
  return result;
}

DollarAmount &DollarAmount::operator+=(const DollarAmount &other) {
  dollars += other.dollars;
  cents += other.cents;
  dollars += cents / 100;
  cents %= 100;
  return *this;
}

int DollarAmount::getDollars() const {
  return dollars;
}

int DollarAmount::getCents() const {
  return cents;
}

int DollarAmount::getTotalCents() const {
  return dollars * 100 + cents;
}

std::ostream &operator<<(std::ostream &os, const DollarAmount &amount) {
  os << "$" << amount.dollars << "." << std::setw(2) << std::setfill('0') << std::right << amount.cents;
  return os;
}

std::istream &operator>>(std::istream &is, DollarAmount &amount) {
  std::string line;
  getline(is, line);
  amount = DollarAmount::parse(line);
  return is;
}

bool DollarAmount::operator==(const DollarAmount &rhs) const {
  return dollars == rhs.dollars &&
      cents == rhs.cents;
}

bool DollarAmount::operator!=(const DollarAmount &rhs) const {
  return !(rhs == *this);
}

bool DollarAmount::operator<(const DollarAmount &rhs) const {
  if (dollars < rhs.dollars)
    return true;
  if (rhs.dollars < dollars)
    return false;
  return cents < rhs.cents;
}

bool DollarAmount::operator>(const DollarAmount &rhs) const {
  return rhs < *this;
}

bool DollarAmount::operator<=(const DollarAmount &rhs) const {
  return !(rhs < *this);
}

bool DollarAmount::operator>=(const DollarAmount &rhs) const {
  return !(*this < rhs);
}

DollarAmount &operator*=(int qty, DollarAmount &da) {
  return da *= qty;
}

DollarAmount operator*(int qty, const DollarAmount &da) {
  return da * qty;
}

