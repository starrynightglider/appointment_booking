# Appointment Booking
This is a booking system. Clients and Stylists are two types of users of the system. Stylists use the system to register their available time (called ​Slot​). Clients use the system to book appointments with stylists.

The system accepts four types of orders:

  `add_slot​`: Issued by a stylist to add available time slot
  
  `remove_slot​`: Issued by a stylist to remove a previously added slot

  `book_appointment​`: Issued by a client to book an available slot of a stylist
  
  `cancel_appointment​`: Issued by a client to cancel a previous booking

# Dependency
The following tools are required to build:

**g++ (c++17)** 
**cmake**

Library dependencies (will be downloaded as submodules automatically, see below):
1. rapidjson: parse json files
2. gtest: testing framework

# Build package
Please follow the instructions:

1. `git clone --recursive https://github.com/starrynightglider/appointment_booking.git`
2. `make`

Run tests:

`make run_test` 

# Order handling
The orderes are placed in buckets for different times in epochs. The unit of epoch is in 30 mins.    
For example: 

"2019-09-01T10:00:00Z" will be converted to `870756` and "2019-09-01T10:30:00Z" `870757`. This method also resolves date conversion problem. For example: "2019-12-31T23:00:00Z" will be `876590`, with slot length of 120 mins, we can get epochs `876591 ~ 876593`.

Each bucket is map from `stylist_id` --> `client_id`. If the slot is not booked yet, `client` will be `nullopt`.  

# Other considerations
1. In production design, we need an asynchronous listener to accept order request and reply successness. For better performance, the booking process should also be multithreaded. In current implementation, a coarse locking scheme is used, this can be improved with a fine granular locking scheme, such as **concurrent hash table** for booking table.

2. `order_id` seems to be an incremental number in the design. But the incremental method could suffer some difficulty in scaling the system. For example, if there are two or more server and the generation of global incremental number becomes tricky. This could be resolved by using `client_id + timestamp` or `stylist_id +timestamp` as order identifier. To distinguish `client` and `stylist` id, a simple way, we can specify all client id are even and stylist are odd numbers.   

3. Some API such as `get_stylist_available_slots` or `get_available_stylist_in_slot` would be helpful to client to make booking.  

4. The booking data is not persistent yet. Selection of DB will depending on the scale of the system and number of queries per second. 

5. A rate limiter maybe need to prevent from DoS attack. 

