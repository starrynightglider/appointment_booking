#include <iostream>
#include "booking.hpp"
#include "order.hpp"

int main() {
  using namespace app::order;
  using namespace app::booking;
  std::string filename;
  std::cout << "Enter file name: " << std::endl;
  std::cin >> filename;
  auto orders_in = parseOrders(filename);
  Booking book;
  auto res = book.processOrders(orders_in);
  std::cout << "Result: " << std::endl;
  cout << writeResult(res) << endl;
  return 0;
}