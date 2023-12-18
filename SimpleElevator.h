/** Simple sequential elevator class. */

#include "Elevator.h"

namespace elevator {

class SimpleElevator : public Elevator {
  // Basic elevator model with no further constraints.
 public:
  // Documentation in Elevator.h
  SimpleElevator(int max_floor, double floor_dist, double max_speed,
                 double max_acceleration, int current_floor = 0)
      : Elevator(max_floor, floor_dist, max_speed, max_acceleration,
                 current_floor) {}  // ctor
  SimpleElevator(const SimpleElevator& other) =
      default;                  // cctor, shallow copy fields
  
  virtual ~SimpleElevator() {}  // dtor
  SimpleElevator& operator=(const SimpleElevator& other) =
      default;  // assignment op, shallow copy fields

  // Naively assume that max speed and acceleration are the same in both
  // ascent and descent.
  double UpFloors(int num_floors) override;
  double DownFloors(int num_floors) override;
};
}  // namespace elevator