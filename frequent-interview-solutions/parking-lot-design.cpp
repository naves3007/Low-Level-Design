/*
Template:
    Step 1: Clarity on Scope of the problem
        What Kid of parking lot?
        What types of vehicles?
        Multiple levels, Multiple entry/exit points?
        Payment logic?
    Step 2: Finalise key Use Cases and APIs
        parkVehicle(Vehicle vehicle) -> Ticket
        unparkVehicle(string ticketId) -> double (fees)
        getAvailableSpots(VehicleType type) -> int
        getTicket(string ticketId) -> Ticket
        calculateFee(string ticketId) -> double
    Step 3: Data Model
    Step 4: Core Class Design
    Step 5: Choose Design Patterns
    Step 6: Implement the code, match all APIs and Use Cases
    Step 7: Check if concurrency is needed, if yes, add locks and mutexes
    Step 8: Scaling and Edge Cases
*/

#include <bits/stdc++.h>
using namespace std;
// Step 3 - Data Model
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
    - vector<>ParkingLevel parkingLevels
Ticket
    - id
    - Vechicle vehicle
    - ParkingSpot spot
    - in_time
    - out_time
ParkingLevel
    - id
    - vector<ParkingSpot> spots
*/
enum VehicleType { CAR, BIKE, TRUCK };
enum ParkingSpotType { COMPACT, LARGE, MOTORBIKE };
using clock = chrono::steady_clock;
using TimePoint = chrono::time_point<clock>;
class Vehicle {
public:
  string licensePlate;
  VehicleType type;
};
class ParkingSpot {
public:
  int id;
  ParkingSpotType type;
  Vehicle *currentVehicle = nullptr; // nullptr if free
};
class ParkingLevel {
public:
  int id;
  vector<ParkingSpot> spots;
};
class ParkingLot {
public:
  int id;
  vector<ParkingLevel> parkingLevels;
};
class Ticket {
public:
  string id;
  Vehicle vehicle;
  ParkingSpot *spot = nullptr; // nullptr if not parked
  TimePoint in_time;
  TimePoint out_time;
  double fees;
};
class ISpotAssignmentStrategy {
public:
  virtual ParkingSpot *findSpot(ParkingLot &lot, VehicleType type) = 0;
  virtual bool is_compatible(ParkingSpotType spotType,
                             VehicleType vehicleType) = 0;
  virtual ~ISpotAssignmentStrategy() = default;
};
class LowLevelFirstStrategy : public ISpotAssignmentStrategy {
public:
  ParkingSpot *findSpot(ParkingLot &lot, VehicleType type) override {
    for (auto &level : lot.parkingLevels) {
      for (auto &spot : level.spots) {
        if (spot.currentVehicle == nullptr && is_compatible(spot.type, type)) {
          return &spot;
        }
      }
    }
    return nullptr;
  }
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
};
class IRateCalculationStrategy {
public:
  virtual double calculateFee(Ticket &ticket) = 0;
  virtual ~IRateCalculationStrategy() = default;
};
class SimpleRateStrategy : public IRateCalculationStrategy {
public:
  double calculateFee(Ticket &ticket) override {
    auto duration =
        chrono::duration_cast<chrono::hours>(ticket.out_time - ticket.in_time)
            .count();
    return duration * 10; // $10 per hour
  }
};
class TicketRepository {
private:
  unordered_map<string, Ticket>
      ticketDB; // Simulating a DB with an in-memory map
public:
  string generate_ticket_id() {
    // Generate a unique ticket ID, e.g., using UUID or a combination of
    // timestamp and random number
  }
  Ticket getTicket(string ticketId) {
    // Fetch the ticket from DB using ticketId
  }
  void saveTicket(Ticket &ticket) {
    // Save or update the ticket in DB
  }
  void updateTicket(Ticket &ticket) { 
    // Update the ticket in DB
  }
};
// Step 1 and 2 - Clarity and APIs
class ParkingLotService {
private:
  ParkingLot parkingLot;
  ISpotAssignmentStrategy *strategy;
  TicketRepository ticketRepo;
  IRateCalculationStrategy *rateStrategy;
  mutex mtx; // For thread safety
public:
  ParkingLotService(ParkingLot lot, ISpotAssignmentStrategy *strat,
                    TicketRepository repo, IRateCalculationStrategy *rateStrat)
      : parkingLot(lot), strategy(strat), ticketRepo(repo),
        rateStrategy(rateStrat) {}
  Ticket parkVehicle(Vehicle vehicle) {
    lock_guard<mutex> lock(mtx); // Ensure thread safety
    ParkingSpot *spot = strategy->findSpot(parkingLot, vehicle.type);
    if (spot == nullptr) {
      throw runtime_error("No available spot");
    }
    spot->currentVehicle = &vehicle;
    Ticket ticket;
    ticket.id = ticketRepo.generate_ticket_id();
    ticket.vehicle = vehicle;
    ticket.spot = spot;
    ticket.in_time = clock::now();
    ticket.fees = 0;
    ticketRepo.saveTicket(ticket);
    return ticket;
  }
  int unparkVehicle(string ticketId) {
    lock_guard<mutex> lock(mtx); // Ensure thread safety
    Ticket ticket = ticketRepo.getTicket(ticketId);
    if (ticket.spot == nullptr) {
      throw runtime_error("Invalid ticket");
    }
    ticket.spot->currentVehicle = nullptr; // Mark spot as free
    ticket.out_time = clock::now();
    // Calculate fees based on in_time and out_time, and update ticket in DB
    double fee = rateStrategy->calculateFee(ticket);
    ticket.fees = fee;
    return fee;
  }
  int getAvailableSpots(VehicleType type) {
    lock_guard<mutex> lock(mtx); // Ensure thread safety
    int count = 0;
    for (auto &level : parkingLot.parkingLevels) {
      for (auto &spot : level.spots) {
        if (spot.currentVehicle == nullptr &&
            strategy->is_compatible(spot.type, type)) {
          count++;
        }
      }
    }
    return count;
  };
  Ticket getTicket(string ticketId) { return ticketRepo.getTicket(ticketId); }
  double calculateFee(string ticketId) {
    lock_guard<mutex> lock(mtx); // Ensure thread safety
    Ticket ticket = ticketRepo.getTicket(ticketId);
    if (ticket.spot == nullptr) {
      throw runtime_error("Invalid ticket");
    }
    return rateStrategy->calculateFee(ticket);
  }
};

int main() { return 0; }