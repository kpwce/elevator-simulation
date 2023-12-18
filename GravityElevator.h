/** Varying acceleration elevator class. */

#include "Elevator.h"

namespace elevator {

class GravityElevator : public Elevator {
  // Elevator model with greater downwards direction.
 public:
  // Documentation in Elevator.h
  GravityElevator(int max_floor, double floor_dist, double max_speed,
                 double max_acceleration, int current_floor = 0, double acceleration_offset = 0.0)
      : Elevator(max_floor, floor_dist, max_speed, max_acceleration,
                 current_floor), acceleration_offset_(acceleration_offset) {}  // ctor
  GravityElevator(const GravityElevator& other) =
      default;                  // cctor, shallow copy fields
  
  virtual ~GravityElevator() {}  // dtor
  GravityElevator& operator=(const GravityElevator& other) =
      default;  // assignment op, shallow copy fields

  // Slower on going up, faster on going down wrt acceleration
  double UpFloors(int num_floors) override;
  double DownFloors(int num_floors) override;

private:
    double acceleration_offset_;  // default 0.0
};
}  // namespace elevator