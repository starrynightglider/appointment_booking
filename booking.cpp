#include "booking.hpp"
#include <sstream>

namespace app::booking {

shared_ptr<vector<Result>> Booking::processOrders(
    shared_ptr<vector<Order>> orders) {
  auto rets = make_shared<vector<Result>>();
  for (auto const& order : *orders) {
    rets->push_back(processOrder(order));
  }
  return rets;
}

Result Booking::processOrder(Order const& order) {
  unique_lock<mutex> lock;
  // assuming different order has different order_id
  auto order_id = order.getOrderId();
  if (processed_orders_.count(order_id)) {
    return {order_id, false};
  }
  processed_orders_.insert(order_id);
  auto ret = false;
  auto stylist_id = order.getStylistId();
  auto len = order.getSlotLen();
  auto epoch = order.getEpochInThirtyMins();
  switch (auto type = order.getOrderType(); type) {
    case Order::AddSlot: {
      // check if any slot exist and booked
      auto ok = true;
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
        ret = true;
      }
      break;
    }
    case Order::RemoveSlot: {
      // Check if slots exist and unbooked
      auto ok = true;
      for (auto i = 0; i < len; ++i) {
        auto cur_epoch = epoch + i;
        if (book_[cur_epoch].count(stylist_id) == 0) {  // slot not exist
          ok = false;
          break;
        } else if (book_[cur_epoch][stylist_id] !=
                   nullopt) {  // slot already booked by someone
          ok = false;
          break;
        }
      }
      if (ok) {
        for (auto i = 0; i < len; ++i) {
          auto cur_epoch = epoch + i;
          book_[cur_epoch].erase(stylist_id);
        }
        ret = true;
      }
      break;
    }
    case Order::BookAppointment: {
      // check if there are slot exist and unbooked
      auto ok = true;
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
      }

      break;
    }
    case Order::CancelAppointment: {
      // check if appointments exist
      auto ok = true;
      for (auto i = 0; i < len; ++i) {
        auto cur_epoch = epoch + i;
        if (book_.count(cur_epoch) == 0) {
          ok = false;
          break;
        } else {
          if (book_[cur_epoch].count(stylist_id) == 0) {
            ok = false;
            break;
          } else if (book_[cur_epoch][stylist_id] !=
                     order.getClientId()) {  // not your appointment, cannot
                                             // cancel
            ok = false;
            break;
          }
        }
      }
      if (ok) {
        for (auto i = 0; i < len; ++i) {
          auto cur_epoch = epoch + i;
          book_[cur_epoch][stylist_id] = nullopt;
        }
        ret = true;
      }
      break;
    }
    case Order::UnknownType: {
      ret = false;
      break;
    }
  }
  return {order_id, ret};
}

string writeResult(shared_ptr<vector<Result>> results) {
  ostringstream oss;
  oss << "[\n";

  for (auto i = 0; i < results->size(); ++i) {
    auto const& r = (*results)[i];
    oss << "\t{\n";
    oss << "\t\t\"order_id\": \"" << r.first << "\",\n";
    oss << "\t\t\"succeed\": " << r.second << "\n";
    if (i == results->size() - 1) {
      oss << "\t}\n";
    } else {
      oss << "\t},\n";
    }
  }
  oss << "]\n";
  return oss.str();
}

}  // namespace app::booking
