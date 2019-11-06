#pragma once
#include <iostream>
#include <string>

namespace app {
using namespace std;
class Order {
 public:
  enum Type { AddSlot, RemoveSlot, BookAppointment, CancelAppointment };
  Order(uint64_t order_id, Type order_type, uint stylist_id, uint client_id,
        string slot_begin, string slot_end)
      : order_id_(order_id),
        order_type_(order_type),
        stylist_id_(stylist_id),
        client_id_(client_id),
        slot_begin_(slot_begin),
        slot_end_(slot_end) {}

  friend ostream &operator<<(ostream &strm, Order const &order) {
    strm << "order id = " << order.order_id_ << endl
         << " type " << order.order_type_ << " stylist id " << order.stylist_id_
         << " client_id " << order.client_id_ << " slot_begin_ "
         << order.slot_begin_ << " slot_end_ " << order.slot_end_ << endl;
    return strm;
  }

 private:
  uint64_t order_id_;
  Type order_type_;
  uint stylist_id_;
  uint client_id_;
  string slot_begin_;
  string slot_end_;
};

}  // namespace app