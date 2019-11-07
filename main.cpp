#include <fstream>
#include <iostream>
#include "order.hpp"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace app;

int main() {
  auto orders_in = parseOrders(R"(orders.json)");
  std::cout << *orders_in << std::endl;
  return 0;
}