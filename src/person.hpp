#include <string>
#include <iostream>

struct Person {
  std::string firstName;
  std::string lastName;
  int age;
};

std::ostream& operator<<(std::ostream& os, const Person& p);
