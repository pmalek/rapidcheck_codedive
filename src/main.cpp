#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck.h>
#include <rapidcheck/gtest.h>


int main(int argc, char **argv) {
  /*
   *rc::check("double reversal yields the original value", [](const std::vector<int> &l0)
   *          {
   *            auto l1 = l0;
   *            std::reverse(begin(l1), end(l1));
   *            std::reverse(begin(l1), end(l1));
   *            RC_ASSERT(l0 == l1);
   *          });
   */

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
