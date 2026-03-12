/*
    Step 1: Clarity on Scope of the problem
        "4-5 Key APIs is Max for a problem"
        Possible Qs for parking lot design: (Type Support, Multiplicity, Logic,
   Concurrency)
            1. Do we support multiple vehicles types?
            2. Per Level statistics / just Total?
            3. How Complex is the parking lot? (Multiple levels, multiple
   entry/exit points, etc.)
            4. Multiple entry / exit points?

    Step 2: Use Cases and APIs
        "Think about API Flow for 4-5 APIs"
        Discuss with Interviewer about the APIs and their flow and FINALISE!!!
        Possible APIs for parking lot design:
            1. parkVehicle(Vehicle v) -> Ticket
            2. unparkVehicle(Ticket t) -> void
            3. getParkingLotStatus() -> ParkingLotStatus
            4. getVehicleLocation(Ticket t) -> Location

    Step 3: Data Model
        "Keep in comments in code : Refer to step 3 in below code"
        Helps in building logic faster

    Step 4: Core Class Design
        Implement 50% of APIs discussed in step 3

    Step 5: Choose Design Patterns
        Strategy Pattern will be implemented here



*/

#include <bits/stdc++.h>
using namespace std;

using clock = chrono::steady_clock;
using TimePoint = chrono::time_point<clock>;

// Step 3 - Keep it in comments till it's confirmed
/*
Vehicle
    - licensePlate
    - type
ParkingSpot
    - id
    - type
    - occupied : bool
    - ticket_id
ParkingLot
    - id
    - parkingLevels
Ticket
    - id
ParkingLevel
    - id
    - level
    - spots
Ticket
    - id
    - licensePlate
    - parkingSpotId
    - level_id
    - in_time
    - out_time
    - fees : double
*/

// Step 4
enum class VehicleType { CAR, BIKE, TRUCK };
class Vehicle {
  string licensePlate; // straight forward
  VehicleType type;    // In Real world ids complex, so create enums
};
enum class ParkingSpotType { COMPACT, LARGE, MOTORBIKE };
class ParkingSpot {
  int id;
  ParkingSpotType type;
  bool occupied;

  bool isOccupied() { return occupied; }
  bool is_compatible(ParkingSpotType spotType, VehicleType vehicleType) {
    if (spotType == ParkingSpotType::COMPACT && vehicleType == VehicleType::CAR)
      return true;
    if (spotType == ParkingSpotType::LARGE &&
        (vehicleType == VehicleType::TRUCK || vehicleType == VehicleType::CAR))
      return true;
    if (spotType == ParkingSpotType::MOTORBIKE &&
        vehicleType == VehicleType::BIKE)
      return true;
    return false;
  }
  void markOccupied() { occupied = true; }
  void setFree() { occupied = false; }
};
class ParkingLevel {
  int id;
  int level;
  vector<ParkingSpot> spots;
  int count_free_spots(ParkingLevel type) {
    int count = 0;
    for (auto &spot : spots) {
      if (!spot.isOccupied() && is_compatible(spot.type, type)) {
        count++;
      }
    }
    return count;
  }
  ParkingSpot *findFreeSpot(VehicleType type) {
    for (auto &spot : spots) {
      if (!spot.isOccupied() && spot.is_compatible(spot.type, type)) {
        return &spot;
      }
    }
    return nullptr;
  }
};
class ISpotAssignmentStrategy {
public:
  virtual ParkingSpot *findSpot(ParkingLevel &level, VehicleType type) = 0;
};
class LowLevelFirstStrategy : public ISpotAssignmentStrategy {
public:
  ParkingSpot *findSpot(ParkingLevel &level, VehicleType type) override {
    for (auto &spot : level) {
      ParkingSpot *spot = level.findFreeSpot(type);
      if (spot != nullptr) {
        return spot;
      }
    }
    return nullptr;
  }
};
class IRateCalculationStrategy {
public:
  virtual double calculateFees(Ticket &ticket) = 0;
};
class HourlyRateStrategy : public IRateCalculationStrategy {
public:
  double calculateFees(Ticket &ticket) override {
    auto duration = chrono::duration_cast<chrono::hours>(
                        ticket.out_time.value() - ticket.in_time)
                        .count();
    return duration * 10; // $10 per hour
  }
};
class ParkingLot {
  int id;
  string name;
  vector<ParkingLevel> parkingLevels;
  mutex mu_;
  string parkVehicle(string licensePlate, VehicleType type) { lock_guard(mu_); }
  double unparkVehicle(string ticketId) { lock_guard(mu_); }
  int getAvailableSpots(VehicleType type) {
    int total = 0;
    for (auto &level : parkingLevels) {
      total += level.count_free_spots(level);
    }
    return total;
  }
};

class TickerRepository {
  Ticket *createTicket(string licensePlate, int parkingSpotId, int level_id,
                       TimePoint in_time) {
    // Create a ticket and save to DB
  };
};

class Ticket {
  string id;
  string licensePlate;
  int parkingSpotId;
  int level_id;
  TimePoint in_time;
  optional<TimePoint> out_time; // empty if not yet unparked
  double fees;

public:
  void get_id() { return id; }
};
// Step 2

class ParkingLotService {
  ParkingLot parkingLot_;
  ISpotAssignmentStrategy *strategy_;
  IRateCalculationStrategy *rateStrategy_;

public:
  ParkingLotService(ISpotAssignmentStrategy *strat, ParkingLot lot,
                    IRateCalculationStrategy *rateStrat) {
    strategy_ = strat;
    parkingLot_ = lot;
    rateStrategy_ = rateStrat;
  }
  // Add these and fill params based on data modelling
  string parkVehicle(string licensePlate, VehicleType type) {
    lock_guard(mu_);
    Parking *spot = strategy_->findSpot(parkingLot_, type);
    if (spot == nullptr) {
      throw runtime_error("No Spot Available");
    }
    TicketRepository repo;
    Ticket *ticket = repo.createTicket(licensePlate, spot->id, spot->level_id,
                                       chrono::steady_clock::now());
    // Mark spot as occupied
    spot->markOccupied();
    return ticket->id;
  }
  double unparkVehicle(string ticketId) {
    lock_guard(mu_);
    Ticket *ticket = repo.getTicket(ticketId);
    if (ticket == nullptr) {
      throw runtime_error("Invalid Ticket");
    }
    if (ticket->closed()) {
      throw runtime_error("Ticket Already Closed");
    }
    double fees = rateStrategy_->calculateFees(*ticket);
    ticket->setFees(fees);
    spot->markFree();
    return fees;
  }
  int getAvailableSpots(VehicleType type) {
    int total = 0;
    for (auto &level : parkingLevels) {
      total += level.count_free_spots(level);
    }
    return total;
  }
};
signed main() {
  // Code Here
  return 0;
}