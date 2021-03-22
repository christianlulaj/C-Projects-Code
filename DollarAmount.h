//
// Created by Christian Lulaj on 11/25/20.
//

#ifndef PROJECT_DOLLARAMOUNT_H
#define PROJECT_DOLLARAMOUNT_H
#include <iostream>
#include <string>

class DollarAmount {
  int dollars = 0;
  int cents = 0;
 public:
  DollarAmount() = default;
  explicit DollarAmount(int cents);
  explicit DollarAmount(double amt);
  DollarAmount(int dollars, int cents);
  int getDollars() const;
  int getCents() const;
  int getTotalCents() const;
  static DollarAmount parse(std::string str);
  static DollarAmount parse(int cents);
  static DollarAmount parse(double amt);
  friend std::ostream &operator<<(std::ostream &os, const DollarAmount &amount);
  friend std::istream &operator>>(std::istream &os, DollarAmount &amount);
  bool operator<(const DollarAmount &rhs) const;
  bool operator>(const DollarAmount &rhs) const;
  bool operator<=(const DollarAmount &rhs) const;
  bool operator>=(const DollarAmount &rhs) const;
  bool operator==(const DollarAmount &rhs) const;
  bool operator!=(const DollarAmount &rhs) const;

  DollarAmount operator*(int qty) const;
  DollarAmount &operator*=(int qty);
  DollarAmount operator+(const DollarAmount &other) const;
  DollarAmount &operator+=(const DollarAmount &other);

};
DollarAmount &operator*=(int qty, DollarAmount &da);
DollarAmount operator*(int qty, const DollarAmount &da);

#endif //PROJECT_DOLLARAMOUNT_H
