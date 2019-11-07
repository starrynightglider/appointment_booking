#include "order.hpp"
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
namespace app {
using namespace rapidjson;
using namespace std;
Order::Type Order::ConvertType(string type) {
  if (type == "add_slot") {
    return AddSlot;
  } else if (type == "remove_slot") {
    return RemoveSlot;
  } else if (type == "book_appointment") {
    return BookAppointment;
  } else if (type == "cancel_appointment") {
    return CancelAppointment;
  } else {
    return UnknownType;
  }
}
shared_ptr<vector<Order>> parseOrders(string filename) {
  auto all_orders = make_shared<vector<Order>>();
  std::ifstream ifs{filename};

  if (!ifs.is_open()) {
    std::cerr << "Cannot open file" << std::endl;
    return all_orders;
  }
  IStreamWrapper isw{ifs};
  Document doc;
  doc.ParseStream(isw);

  if (doc.HasParseError()) {
    std::cout << "Error: " << doc.GetParseError() << std::endl;
    std::cout << "Offset: " << doc.GetErrorOffset() << std::endl;
  }
  assert(doc.IsArray());
  for (Value::ConstValueIterator iter = doc.Begin(); iter != doc.End();
       ++iter) {
    auto const& od = *iter;
    assert(od.IsObject());
    assert(od.HasMember("order_id"));
    assert(od.HasMember("order_type"));
    assert(od.HasMember("stylist_id"));
    assert(od.HasMember("slot_begin"));
    assert(od.HasMember("slot_length_min"));

    auto id = od["order_id"].GetString();
    auto type = od["order_type"].GetString();
    auto stylist_id = od["stylist_id"].GetUint();
    auto client_id = 0;
    if (od.HasMember("client_id")) {
      client_id = od["client_id"].GetUint();
    }
    auto slot_begin = od["slot_begin"].GetString();
    auto slot_len = od["slot_length_min"].GetUint();

    Order new_order(id, type, stylist_id, client_id, slot_begin, slot_begin);
    all_orders->emplace_back(new_order);
  }
  return all_orders;
}
}  // namespace app
