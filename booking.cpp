#include "booking.hpp"

namespace app::booking {

bool Booking::processOrder(Order const& order) {
  unique_lock<mutex> lock;
  // assuming different order has different order_id
  if (processed_orders_.count(order.getOrderId())) {
    return false;
  }
  bool ret = true;
  auto stylist_id = order.getStylistId();
  auto len = order.getSlotLen();
  switch (auto type = order.getOrderType(); type) {
    case Order::AddSlot: {
      // check if any slot exist and booked

      break;
    }
    case Order::RemoveSlot: {
      break;
    }
    case Order::BookAppointment: {
      break;
    }
    case Order::CancelAppointment: {
      break;
    }
    case Order::UnknownType: {
      ret = false;
      break;
    }
  }
  return ret;
}

}  // namespace app::booking