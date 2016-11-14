#include <algorithm>
#include <vector>

#include <rapidcheck.h>

int main() {
  rc::check("double std::vector reversal yields the original", [](std::vector<int> v) {
    auto copy = v;
    std::reverse(begin(copy), end(copy));
    std::reverse(begin(copy), end(copy));
    RC_ASSERT(v == copy);
  });
}
