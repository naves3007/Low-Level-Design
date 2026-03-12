/*
Template:
    Step 1: Clarity on Scope of the problem
        Book tickets? YES
        Cancel tickets? YES
        Multiple City? YES
        Multiple Theatres in a city? YES
        Multiple screens in a theatre? YES
        Multiple shows in a screen? YES
        Seat selection / Automatic seat allocation? Manual seat selection
        Concurreny important to prevent double booking? YES
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
// Step 3 - Data Model
/*
City
    - id
    - name
Theater
    - id
    - name
    - city_id
Screen
    - id
    - theater_id
    - name
Show
    - id
    - screen_id
    - start_time
    - end_time
Seat
    - id
    - show_id
    - seat_number
    - SeatStatus (available, booked)
Ticket
    - id
    - show_id
    - vector<seat_id>
    - booking_time
    - totalAmount
    - BookingStatus (booked, cancelled)
*/
using clock = chrono::steady_clock;
using TimePoint = chrono::time_point<clock>;
enum SeatStatus { AVAILABLE, BOOKED, LOCKED };
enum BookingStatus { BOOKED, CANCELLED };
class City {
public:
  int id;
  string name;
};
class Theater {
public:
  int id;
  string name;
  int city_id;
};
class Screen {
public:
  int id;
  int theater_id;
  string name;
};
class Show {
public:
  int id;
  int screen_id;
  TimePoint start_time;
  TimePoint end_time;
  vector<Seat> seats;
};
class Seat {
public:
  int id;
  int show_id;
  string seat_number;
  SeatStatus status;
};
class Ticket {
public:
  int id;
  int show_id;
  vector<int> seat_ids;
  TimePoint booking_time;
  double totalAmount;
  BookingStatus status;
};
class TicketRepository { // Repository pattern for managing tickets
private:
  unordered_map<int, Ticket> ticketDB; // Simulating a DB with an in-memory map
public:
  int generate_ticket_id() {
    // Generate a unique ticket ID, e.g., using UUID or a combination of
    // timestamp and random number
  }
  void saveTicket(Ticket &ticket) {
    // Save the ticket to DB
  }
  Ticket getTicket(int ticketId) {
    // Fetch the ticket from DB using ticketId
  }
};
class IRateCalculationStrategy {
public:
  virtual double calculateFee(Ticket &ticket) = 0;
  virtual ~IRateCalculation Strategy() = default;
};
class SimpleRateStrategy : public IRateCalculationStrategy {
public:
  double calculateFee(Ticket &ticket) override {
    // Implement fee calculation logic based on show time, seat type, etc.
    return ticket.seat_ids.size() * 10; // Assume each seat costs $10
  }
};
class MovieTicketBookingService {
private:
  TicketRepository ticketRepo;
  IRateCalculationStrategy *rateStrategy;
  mutex mtx; // For thread safety
  // Assumption that this exis:
  // unordered_map<int, Show> shows;
public:
  MovieTicketBookingService(TicketRepository repo,
                            IRateCalculationStrategy rate)
      : ticketRepo(repo), rateStrategy(rate) {}
  Ticket bookTicket(int showId, vector<int> seatsIds) {
    if (shows.find(showId) == shows.end()) {
      throw runtime_error("Show Not found");
    }
    Show show = shows[showId]; // find what show it is
    vector<Seat *> selectedSeats;
    lock_guard<mutex> lock(
        mtx); // Ensure thread safety during seat selection and booking
    for (auto seatId : seatIds) {
      bool seatFound = false;
      for (auto &seat : show.seats) {
        if (seat.id == seatId) {
          seatFound = true;
          if (seat.status != AVAILABLE) {
            throw runtime_error("Seat not available");
          }
          selectedSeats.push_back(&seat);
          break;
        }
      }
      if (!seatFound) {
        throw runtime_error("Seat not found");
      }
    }
    // Mark seats as booked
    for (auto seatPtr : selectedSeats) {
      seatPtr->status = BOOKED;
    }
    // Create ticket
    Ticket ticket;
    static int ticketIdCounter = 1;
    ticket.id = ticketIdCounter++;
    ticket.show_id = showId;
    ticket.seat_ids = seatsIds;
    ticket.booking_time = clock::now();
    // apply strategy pattern here for calculating price based on show time,
    // seat type etc
    ticket.totalAmount = rateStrategy->calculateFee(ticket);
    ticket.status = BOOKED;
    // ticket.totalAmount = seatsIds.size() * 10; // Assume each seat costs $
    // ticket.status = BOOKED;
    ticketRepo.saveTicket(ticket);
    return ticket;
  }
  BookingStatus cancelTicket(int ticketId) {
    Ticket ticket = ticketRepo.getTicket(ticketId);
    if (ticket.status != BOOKED) {
      throw runtime_error("Ticket cannot be cancelled");
    };
    lock_guard<mutex> lock(mtx); // Ensure thread safety during cancellation
    // Mark seats as available
    for (auto seatId : ticket.seat_ids) {
      // Find the show and seat, then mark it as available
      Show show = shows[ticket.show_id];
      for (auto &seat : show.seats) {
        if (seat.id == seatId) {
          seat.status = AVAILABLE;
          break;
        }
      }
    }
    // Update ticket status
    ticket.status = CANCELLED;
    ticketRepo.saveTicket(ticket); // Update the ticket in DB
    return CANCELLED;
  }
  vector<Show> getShows(int theaterId) {
    // unordered_map<int, Screen> screens;
    // unordered_map<int, Show> shows;
    vector<int> screenIds;
    vector<Show> result;
    for (auto &screen : screens) {
      if (screen.second.theatre_id == theaterID) {
        screenIds.push_back(entry.first);
      }
    }
    for (auto &entry : shows) {
      int showId = entry.screen_id;
      if (find(screenIds.begin(), screenIds.end(), showId) != screenIds.end()) {
        result.push_back(entry.second);
      }
    }
    return result;
  }
  vector<Theater> getTheaters(int cityId) {
    // unordered_map<int, Theater> theaters;
    vector<Theater> result;
    for (auto &entry : theaters) {
      if (entry.second.city_id == cityId) {
        result.push_back(entry.second);
      }
    }
    return result;
  }
  vector<Seat> getAvailableSeats(int showId) {
    if (shows.find(showId) == shows.end()) {
      throw runtime_error("Show Not found");
    }
    Show show = shows[showId];
    vector<Seat> availableSeats;
    for (auto &seat : show.seats) {
      if (seat.status == AVAILABLE) {
        availableSeats.push_back(seat);
      }
    }
    return availableSeats;
  }
};
int main() { return 0; }