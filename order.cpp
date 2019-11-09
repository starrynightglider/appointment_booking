#include "order.hpp"
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

namespace app::order {
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
    std::cerr << "Error! Cannot open file ..." << std::endl;
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
    uint options = Order::None;

    string slot_begin = od["slot_begin"].GetString();
    auto slot_len = od["slot_length_min"].GetUint();
    // parse ISO time format and convert to bucket
    std::tm t = {};
    std::istringstream ss(slot_begin);
    time_t epoch_in_thirty_mins = 0;
    if (ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S")) {
      // clear seconds
      t.tm_sec = 0;
      // simple sanity check
      if (t.tm_min % 30 != 0) {
        cout << "Minute should be in 30 mins unit (" << t.tm_min
             << "), skip the order " << id << endl;
        continue;
      }
      epoch_in_thirty_mins = std::mktime(&t) / 60 / 30;
    } else {
      std::cout << "Time parse failed: " << slot_begin << " , skip the order "
                << id << endl;
      continue;
    }
    if (slot_len < 30) {
      cout << "Slot length is less then 30 mins (" << slot_len
           << "), skip the order " << id << endl;
      continue;
    }
    slot_len /= 30;  // unit in 30 mins

    if (od.HasMember("client_id")) {
      client_id = od["client_id"].GetUint();
    }
    if (od.HasMember("flexible_in_stylist")) {
      options |= Order::FlexibleStylist;
    }
    if (od.HasMember("flexible_in_time")) {
      options |= Order::FlexibleTime;
    }
    Order new_order(id, type, stylist_id, client_id, epoch_in_thirty_mins,
                    slot_len, options);
    all_orders->emplace_back(new_order);
  }
  return all_orders;
}
}  // namespace app::order
