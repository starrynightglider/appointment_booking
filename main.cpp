#include <fstream>
#include <iostream>
#include "booking.hpp"
#include "order.hpp"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

int main() {
  using namespace app::order;
  using namespace app::booking;

  auto orders_in = parseOrders(R"(orders.json)");
  Booking book;
  for (auto order : *orders_in) {
    std::cout << order << std::endl;
    book.processOrder(order);
  }
  return 0;
}