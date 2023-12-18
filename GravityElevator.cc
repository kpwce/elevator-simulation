/** Gravity elevator class implementation. */

#include "GravityElevator.h"

#include <algorithm>
#include <cmath>

#include "Elevator.h"

namespace elevator {

/** Wrapper for Calculate time to take into account acceleration offset. Returns
 * time for elevator to travel given distance. */
static double CalculateGravityTime(double dist, double max_speed,
                                   double acceleration, double deceleration);

double GravityElevator::UpFloors(int num_floors) {
  int new_floor = std::min(current_floor_ + num_floors, max_floor_);
  double dist_delta = (new_floor - current_floor_) * floor_dist_;
  current_floor_ = new_floor;

  return CalculateGravityTime(dist_delta, max_speed_,
                              max_acceleration_ - acceleration_offset_,
                              max_acceleration_ + acceleration_offset_);
}

double GravityElevator::DownFloors(int num_floors) {
  int new_floor = std::max(current_floor_ - num_floors, 0);
  double dist_delta = (current_floor_ - new_floor) * floor_dist_;
  current_floor_ = new_floor;
  return CalculateGravityTime(dist_delta, max_speed_,
                              max_acceleration_ + acceleration_offset_,
                              max_acceleration_ - acceleration_offset_);
}

static double CalculateGravityTime(double dist, double max_speed,
                                   double acceleration, double deceleration) {
  // 1. Accelerate (if possible) elevator from a stop to max speed.
  double time = 0.0;
  double traveled_dist = 0.0;
  // 2. Can we reach max speed with accelerate and decelerate?
  // speed = acceleration * sqrt(dist / acceleration)
  double max_acceleration_dist = max_speed * max_speed / acceleration;
  double min_deceleration_dist = max_speed * max_speed / deceleration;
  if (max_acceleration_dist + min_deceleration_dist < dist) {
    // accelerate from stop to max_speed, travel at max speed, decelerate to
    // stop
    time += sqrt(max_acceleration_dist / acceleration);
    time += max_speed * (dist - max_acceleration_dist - min_deceleration_dist);
    time += sqrt(min_deceleration_dist / deceleration);
  } else {
    // accelerate from stop to threshold speed, then decelerate to stop
    // minimize t:
    //                 v_threshold = accel * t1 = decel * t2
    //                 dist = (accel * t1^2) + decel * t2^2
    //                 t = t1 + t2
    double accel_const = acceleration + pow((acceleration / deceleration), 2);
    double decel_const = deceleration + pow((deceleration / acceleration), 2);
    time += sqrt(dist / accel_const) + sqrt(dist / decel_const);
  }
  return time;
}

}  // namespace elevator