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
  auto res = book.processOrders(orders_in);
  std::cout << *res << std::endl;
  cout << writeResult(res) << endl;
  return 0;
}