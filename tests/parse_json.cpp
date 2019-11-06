#include <gtest/gtest.h>
#include <order.hpp>
namespace app {
TEST(Order, create_order) {
  Order order(0, Order::AddSlot, 1, 1, "begin", "end");
  cout << order << endl;
}
}  // namespace app
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}