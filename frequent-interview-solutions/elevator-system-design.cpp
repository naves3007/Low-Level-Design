/*
Template:
    Step 1: Clarity on Scope of the problem
        Single / Multi Elevator & Floors
        Handling
            External -> Up / Down
            Internal -> Floors
        Door Open / Close
        Capacity Constraint
        Basic Scheluding -> Choose best elevator
    Step 2: Finalise key Use Cases and APIs
    Step 3: Data Model
    Step 4: Core Class Design
    Step 5: Choose Design Patterns
    Step 6: Implement the code, match all APIs and Use Cases
    Step 7: Check if concurrency is needed, if yes, add locks and mutexes
    Step 8: Scaling and Edge Cases
*/
#include <bits/stdc++.h>
using namespace std;
/* Data Model
Elevator
- id
- currentFloor
- direction
- status {IDLE, MOVING, DOOR_OPEN}
- capacity
- currentLoad
Request
- floor
- direction {UP, DOWN}
ElevatorSystem
- vector<Elevator>
- queue<Request> pendingRequests
- DispatchStrategy
*/
enum ElevatorStatus { IDLE, MOVING, DOOR_OPEN };
enum Direction { UP, DOWN, IDLE };
class Request {
public:
  int floor;
  Direction direction;
  Request(int _floor, Direction _direction)
      : floor(_floor), direction(_Direction) {}
};
class Elevator {
public:
  int id;
  int currentFloor;
  ElevatorStatus elevatorStatus;
  int capacity;
  int currentLoad;

  set<int> requests; // add floor requests where elevator can go

  Elevator(int _id, int _currentFloor, ElevatorStatus _elevatorStatus,
           int _capacity, int _currentLoad)
      : id(_id), currentFloor(_currentFloor), elevatorStatus(_elevatorStatus),
        capacity(_capacity), currentLoad(_currentLoad) {}
};
class ElevatorSystem {
public:
  queue<Request> pendingRequests;
  vector<Elevator *> elevators;
};
class IElevatorPickerStrategy {
public:
  virtual Elevator *selectElevator(vector<Elevator *> &elevators,
                                   Request req) = 0;
};
class NearestFirstStrategy : public IElevatorPickerStrategy {
public:
  virtual Elevator *selectElevator(vector<Elevator *> elevators,
                                   Request req) override {
    int startFloor = nullptr;
    int endFloor = req.floor;
    Elevator *bestElevator = nullptr;
    for (auto &value : elevators) {
      if (abs(endFloor - value->currentFloor)) {
        bestElevator = value;
      }
    }
    return bestElevator;
  }
};
class ElevatorSystemService {
private:
  ElevatorSystem elevatorSystem;
  IElevatorPickerStrategy *pickerStrategy;

public:
  ElevatorPickerStrategy(IElevatorPickerStrategy pickerStrategy,
                         ElevatorSystem elevatorSystem)
      : pickerStrategy(pickerStrategy), elevatorSystem(ElevatorSystem) {}
  void requestElevator(int currentFloor, Direction direction) {
    Request req(currentFloor, direction);
    Elevator *elevator =
        pickerStrategy->selectElevator(elevatorSystem.elevators, req);
    if (elevator != nulllptr) {
      elevator->requests.insert(currentFloor);
    } else {
      elevatorSystem.pendingRequests.push(req);
    }
  }
  void gotoDesiredFloor(int elevatorId, int destFloor) {
    for (auto &e : elevatorSystem) {
      if (e->id == elevatorId) {
        e->requests.insert(destFloor);
        return;
      }
    }
  }
  void solve() {
    /*
    Assign Pending Requests from Q to elevator
    Do Elevator Operations
    */
    int sizeQ = elevatorSystem.pendingRequests.size();
    while (size--) {
      Request *tempRq = elevatorSystem.pendingRequests.pop();
      Elevator *e =
          pickerStrategy->selectElevartor(elevatorSystem.elevators, req);
      if (e != nullptr) {
        e.requests.insert(req.floor);
      } else {
        elevatorSystem.pendingRequests.push(req);
      }
    }
    // do all elevator operations
    for (auto *e : elevatorSystem.elevators) {
      if (e->requests.empty()) {
        e->ElevatorStatus = IDLE;
        e->Direction = IDLE;
        continue;
      }
      int targetFloor = e->requests.begin();
      if (e->currentFloor < targetFloor) {
        e->currentFloor++;
        e->Direction = UP;
        e->status = MOVING;
      } else if (e->currentFloor > targetFloor) {
        e->currentFloor--;
        e->Direction = DOWN;
        e->status = MOVING;
      } else {
        e->Direction = IDLE;
        e->status = DOOR_OPEN;
        e->requests.erase(targetFloor);
      }
    }
  }
};
int main() { return 0; }