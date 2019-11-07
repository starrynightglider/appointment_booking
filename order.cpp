#include "order.hpp"
#include <cstdio>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
namespace app::Order {
using namespace rapidjson;
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
    string slot_begin = od["slot_begin"].GetString();
    auto slot_len = od["slot_length_min"].GetUint();
    // parse ISO time format and convert to bucket
    uint y, M, d, h, m;
    float s;
    sscanf(slot_begin.c_str(), "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &h, &m, &s);

    // Sanity check
    if (h >= 24) {
      cout << "Hour is ill formated: " << h << ", skip the order " << id
           << endl;
      continue;
    }

    if (m >= 60) {
      cout << "Minute is ill formated: " << m << ", skip the order " << id
           << endl;
      continue;
    }

    if (m % 30 != 0) {
      cout << "Minute should be in 30 mins interval: " << m << " round to "
           << m / 30 * 30 << endl;
    }
    m /= 30;
    uint bucket = h * 2 + m;
    string date = to_string(y) + "-" + to_string(M) + "-" + to_string(d) + "-" +
                  to_string(bucket);

    slot_len /= 30;  // unit in 30 mins

    Order new_order(id, type, stylist_id, client_id, date, slot_len);
    all_orders->emplace_back(new_order);
  }
  return all_orders;
}
}  // namespace app::Order
