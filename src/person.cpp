#include "person.hpp"

std::ostream& operator<<(std::ostream& os, const Person& p) {
  os << "firstName : \"" << p.firstName << "\", "
     << "lastName : \"" << p.lastName << "\", "
     << "age : " << p.age;
  return os;
}
