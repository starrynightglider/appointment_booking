#pragma once
#include <time.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "order.hpp"

namespace app::booking {
using namespace std;
using order::Order;
class Booking {
 public:
  shared_ptr<vector<bool>> processOrders(shared_ptr<vector<Order>> orders);
  bool processOrder(Order const& order);

 private:
  mutex mutex_;
  unordered_set<string> processed_orders_;
  // map{ epoch --> map {stylist_id, client_id}}
  unordered_map<time_t, unordered_map<string, optional<uint>>> book_;
};

}  // namespace app::booking