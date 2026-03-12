#include<bits/stdc++.h>
using namespace std;
/*
Step 3 Create the Data Model
City
    - id
    - name
    - theater
Theater
    - id
    - name
    - address
    - city_id
    - Screen
Screen
    - id
    - name
    - theater_id
    - total_seat
Movie
    - id
    - title
    - duration
    - language
    - genre
Show
    - id
    - movie_id
    - screen_id
    - start_time
    - price
Seat 
    - id
    - show_id
    - screen_id
ShowSeat
    - id
    - show_id
    - seat_id
    - status
Booking
    - id
    - show_id
    - seat_ids
    - amount
    - status
    - payment_status
*/
class Booking{

};
class City{

};
class Theater{

};
class Screen{

};
class Movie{

};
class Show{

};
class ShowSeat{

};
class Seat{

};
class MovieRepository{
    vector<Movie> find_all_movies (int city_id, Date date);
}
class TheaterRepository{
    vector<Theater> find_all_theaters (int city_id);
}
class ShowRepository{
    ShowSeatLayout get_all_seat_status(int show_id);
}

using ShowSummmary = map<int, vector<Show>>; // movie_id, list of shows
enum class SeatStatus{
    AVAILABLE,
    BOOKED,
    BLOCKED
};
using SeatInfo = map<int, SeatStatus>; // seat_id, status
using ShowSeatSummmary = vector<SeatInfo>;

class PaymentService{

}

/*
Step 2 create basic APIs
    vector<> searchMovies(){}
    listShowsforMovie(){}
    getSeatLayout(){}
    createBooking(){}
    cancelBooking(){}
*/
class BookMyShowService(){
public:
    // Step 4 finalise all the params of APIs along with return time
    vector<Movie> searchMovies(int city_id, Date date){
        MovieRepository.find_all_movies(city_id, date);
    }
    ShowSummmary listShowsforMovie(int city_id, Date data, int movie_id){
        vector<Screen> screens = TheaterRepository.find_all_screens(city_id);
        vector<int>screenIds;
        map<int, int> screenToTheaterMap;
        for(auto v : screens){
            screenToTheaterMap[v.get_id()] = v.get_theater_id();
            screenIds.push_back(v.get_id());
        }
        shows = MovieRepository.find_all_shows(screenIds, movie_id);
        vector<ShowSummary> result;
        for(auto show : shows){
            int theater_id = screenToTheaterMap[show.get_screen_id()];
            result.push_back({theater_id, show});
        }
        return result;
    } 
    ShowSeatLayout getSeatLayout(int show_id){
        ShowSeatLayout = ShowRepository.get_all_seat_status(show_id);
        return ShowSeatLayout;
    }
    int createBooking(int show_id, vector<int> seat_ids){
        map<int, ShowSeat> seat_info = ShowRepository.get_all_seat_status(show_id);

        auto now = Clock::now();

        for(auto seat_id : seat_ids){
            if(ShowSeatLayout[seat_id].status != SeatStatus::BOOKED){
                throw "Seat not available";
            }
            else if(ShowSeatLayout[seat_id].status == SeatStatus::BLOCKED && seat_info[seat_id].blocked_time > now){
                throw "Seat not available, locked";
            }
        }
        auto new_expiry_time = now + 15min;
        vector<ShowSeat> show_seats_to_update;
        for(auto seat_id : seat_ids){
            ShowSeat seat = seat_info[seat_id];
            seat.set_status(SeatStatus::BLOCKED);
            seat.set_blocked_time(new_expiry_time);
            show_seats_to_update.push_back(seat);
        }
        ShowRepository.update_seat_status(show_seats_to_update);
        // create a new booking with status as pending and payment status as pending    

        // Booking = BookingRepo

        return booking_id;
    }   

    Booking completePayment(){
    }
    Booking cancelBooking(string bookingId){

    }
}
int main(){

    return 0;
}