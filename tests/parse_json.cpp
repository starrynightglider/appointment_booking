#include <gtest/gtest.h>
#include <order.hpp>
namespace app {
using order::Order;
using namespace std;
TEST(Order, create_order) {
  Order order("0", "add_slot", 1, 1, 123, 2);
  cout << order << endl;
}
}  // namespace app
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}