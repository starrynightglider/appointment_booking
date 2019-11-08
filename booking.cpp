#include "booking.hpp"

namespace app::booking {

bool Booking::processOrder(Order const& order) {
  unique_lock<mutex> lock;
  // assuming different order has different order_id
  if (processed_orders_.count(order.getOrderId())) {
    return false;
  }
  bool ret = false;
  auto stylist_id = order.getStylistId();
  auto len = order.getSlotLen();
  auto epoch = order.getEpochInThirtyMins();
  switch (auto type = order.getOrderType(); type) {
    case Order::AddSlot: {
      // check if any slot exist and booked
      bool ok = true;
      for (auto i = 0; i < len; ++i) {
        auto cur_epoch = epoch + i;
        if (book_[cur_epoch].count(stylist_id) != 0 &&
            book_[cur_epoch][stylist_id] !=
                nullopt) {  // means the entry already booked
          ok = false;
          break;
        }
      }
      if (ok) {
        for (auto i = 0; i < len; ++i) {
          auto cur_epoch = epoch + i;
          book_[cur_epoch][stylist_id] = nullopt;
        }
        cout << "order id " << order.getOrderId() << " processed successfully!"
             << endl;
        ret = true;
      }

      break;
    }
    case Order::RemoveSlot: {
      break;
    }
    case Order::BookAppointment: {
      // check if there are slot exist and unbooked
      bool ok = true;
      for (auto i = 0; i < len; ++i) {
        auto cur_epoch = epoch + i;
        if (book_.count(cur_epoch) == 0) {  // no such epoch
          ok = false;
          break;
        } else {
          if (book_[cur_epoch].count(stylist_id) == 0) {  // no such slot
            ok = false;
            break;
          } else if (book_[cur_epoch][stylist_id] !=
                     nullopt) {  // slot already booked by others
            ok = false;
            break;
          }
        }
      }
      if (ok) {
        for (auto i = 0; i < len; ++i) {
          auto cur_epoch = epoch + i;
          book_[cur_epoch][stylist_id] = order.getClientId();
        }
        ret = true;
        cout << "order id " << order.getOrderId() << " processed successfully!"
             << endl;
      }

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