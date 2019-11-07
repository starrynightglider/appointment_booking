#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "util.hpp"
namespace app {
using namespace std;
class Order {
 public:
  enum Type {
    AddSlot,
    RemoveSlot,
    BookAppointment,
    CancelAppointment,
    UnknownType
  };
  Order(string const &order_id, string const &order_type, uint stylist_id,
        uint client_id, string const &slot_begin, string const &slot_end)
      : order_id_(order_id),
        order_type_(ConvertType(order_type)),
        stylist_id_(stylist_id),
        client_id_(client_id),
        slot_(make_pair(slot_begin, slot_end)) {}

  friend ostream &operator<<(ostream &strm, Order const &order) {
    strm << "order id = " << order.order_id_
         << "\n  type = " << order.order_type_
         << "\n  stylist id = " << order.stylist_id_
         << "\n  client_id = " << order.client_id_
         << "\n  slot = " << order.slot_ << endl;
    return strm;
  }
  auto getOrderId() const { return order_id_; }
  auto getOrderType() const { return order_type_; }
  auto getStylistId() const { return stylist_id_; }
  auto getClientId() const { return client_id_; }
  auto getSlot() const { return slot_; }

 private:
  static Type ConvertType(string type);
  string order_id_;
  Type order_type_;
  uint stylist_id_;
  uint client_id_ = 0;
  pair<string, string> slot_;  // pair:{begin, end}
};                             // namespace app

shared_ptr<vector<Order>> parseOrders(string filename);
}  // namespace app