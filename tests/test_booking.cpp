#include <gtest/gtest.h>
#include <booking.hpp>
#include <order.hpp>
namespace app {
using booking::Booking;
using booking::Result;
using order::Order;
using order::parseOrders;
using namespace std;

TEST(Order, example) {
  Booking book;
  auto orders_in = parseOrders(R"(tests/jsons/example.json)");
  EXPECT_EQ(orders_in->size(), 4);
  auto res = book.processOrders(orders_in);
  EXPECT_EQ(res->size(), 4);
  vector<Result> answer = {{"1", 1}, {"2", 1}, {"3", 1}, {"4", 0}};
  EXPECT_EQ(*res, answer);
}

TEST(Order, remove_slot_test) {
  Booking book;
  auto orders_in = parseOrders(R"(tests/jsons/remove_slot_test.json)");
  EXPECT_EQ(orders_in->size(), 5);
  auto res = book.processOrders(orders_in);
  EXPECT_EQ(res->size(), 5);
  vector<Result> answer = {{"1", 0}, {"2", 1}, {"3", 1}, {"4", 0}, {"5", 1}};
  EXPECT_EQ(*res, answer);
}

TEST(Order, book_appointment_test) {
  Booking book;
  auto orders_in = parseOrders(R"(tests/jsons/book_appointment_test.json)");
  EXPECT_EQ(orders_in->size(), 5);
  auto res = book.processOrders(orders_in);
  EXPECT_EQ(res->size(), 5);
  vector<Result> answer = {{"1", 0}, {"2", 1}, {"3", 1}, {"4", 1}, {"5", 0}};
  EXPECT_EQ(*res, answer);
}

TEST(Order, add_slot_test) {
  Booking book;
  auto orders_in = parseOrders(R"(tests/jsons/add_slot_test.json)");
  EXPECT_EQ(orders_in->size(), 5);
  auto res = book.processOrders(orders_in);
  EXPECT_EQ(res->size(), 5);
  vector<Result> answer = {{"1", 1}, {"2", 1}, {"3", 1}, {"4", 0}, {"5", 1}};
  EXPECT_EQ(*res, answer);
}

TEST(Order, cancel_appointment_test) {
  Booking book;
  auto orders_in = parseOrders(R"(tests/jsons/cancel_appointment_test.json)");
  EXPECT_EQ(orders_in->size(), 5);
  auto res = book.processOrders(orders_in);
  EXPECT_EQ(res->size(), 5);
  vector<Result> answer = {{"1", 1}, {"2", 1}, {"3", 1}, {"4", 0}, {"5", 0}};
  EXPECT_EQ(*res, answer);
}

TEST(Order, date_calculation_test) {
  Booking book;
  auto orders_in = parseOrders(R"(tests/jsons/date_calculation_test.json)");
  EXPECT_EQ(orders_in->size(), 7);
  auto res = book.processOrders(orders_in);
  EXPECT_EQ(res->size(), 7);
  vector<Result> answer = {{"1", 1}, {"2", 1}, {"3", 1}, {"4", 1},
                           {"5", 1}, {"6", 1}, {"7", 0}};
  EXPECT_EQ(*res, answer);
}

}  // namespace app
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}