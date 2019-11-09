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
using Result = pair<string, bool>;

class Booking {
 public:
  shared_ptr<vector<Result>> processOrders(shared_ptr<vector<Order>> orders);
  Result processOrder(Order const& order);

 private:
  mutex mutex_;
  unordered_set<string> processed_orders_;
  // map{ epoch --> map {stylist_id, client_id}}
  unordered_map<time_t, unordered_map<uint, optional<uint>>> book_;
};

string writeResult(shared_ptr<vector<Result>> results);

}  // namespace app::booking