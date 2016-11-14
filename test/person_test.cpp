#include "person.hpp"

#include <gtest/gtest.h>

#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

namespace rc {  // NOTE: Must be in rc namespace!

template <>
struct Arbitrary<Person> {
  static Gen<Person> arbitrary() {
    return gen::build<Person>(
        gen::set(&Person::firstName,
                 gen::mapcat(gen::arbitrary<bool>(),
                             [](bool isMale) {
                               return isMale ? gen::element<std::string>("John", "Joe", "Alojz")
                                             : gen::element<std::string>("Jane", "Kate");
                             })),
        gen::set(&Person::lastName, gen::element("Smith", "Djukovic")),
        gen::set(&Person::age, gen::inRange(0, 100)));
  };
};

}  // namespce rc

RC_GTEST_PROP(Person, ageIsIn0to100Range, ()) {
  auto p = *rc::gen::arbitrary<Person>().as("Custom person 'p'");
  RC_ASSERT(p.age >= 0 && p.age < 99); // there's a bug, can you find it? :)
}
