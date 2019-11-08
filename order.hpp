#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "util.hpp"
namespace app::order {
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
        uint client_id, time_t const &epoch_in_thirty_mins, uint slot_len)
      : order_id_(order_id),
        order_type_(ConvertType(order_type)),
        stylist_id_(stylist_id),
        client_id_(client_id),
        epoch_in_thirty_mins_(epoch_in_thirty_mins),
        slot_len_(slot_len) {}

  friend ostream &operator<<(ostream &strm, Order const &order) {
    strm << "order id = " << order.order_id_
         << "\n  type = " << order.order_type_
         << "\n  stylist id = " << order.stylist_id_
         << "\n  client_id = " << order.client_id_
         << "\n  epoch_in_thirty_mins = " << order.epoch_in_thirty_mins_
         << "\n  slot_len = " << order.slot_len_ << endl;
    return strm;
  }
  auto getOrderId() const { return order_id_; }
  auto getOrderType() const { return order_type_; }
  auto getStylistId() const { return stylist_id_; }
  auto getClientId() const { return client_id_; }
  auto getEpochInThirtyMins() const { return epoch_in_thirty_mins_; }
  auto getSlotLen() const { return slot_len_; }

 private:
  static Type ConvertType(string type);
  string order_id_;
  Type order_type_;
  uint stylist_id_;
  uint client_id_ = 0;
  time_t epoch_in_thirty_mins_;
  uint slot_len_;
};

shared_ptr<vector<Order>> parseOrders(string filename);
}  // namespace app::order