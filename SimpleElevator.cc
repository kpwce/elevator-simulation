/** Simple sequential elevator class implementation. */

#include "SimpleElevator.h"

#include <stdlib.h>

#include <algorithm>  // min, max
#include <cmath>  // sqrt

#include "Elevator.h"

namespace elevator {

/** Return the time it takes to accelerate and decelerate given dist, capping
 *  out at max speed. Accelerates to maximize speed.
 */
double CalculateTime(double dist, double max_speed, double max_acceleration);

double SimpleElevator::UpFloors(int num_floors) {
  int new_floor = std::min(current_floor_ + num_floors, max_floor_);
  double dist_delta = (new_floor - current_floor_) * floor_dist_;
  current_floor_ = new_floor;
  return CalculateTime(dist_delta, max_speed_, max_acceleration_);
}

double SimpleElevator::DownFloors(int num_floors) {
  int new_floor = std::max(current_floor_ - num_floors, 0);
  double dist_delta = (current_floor_ - new_floor) * floor_dist_;
  current_floor_ = new_floor;
  return CalculateTime(dist_delta, max_speed_, max_acceleration_);
}

double CalculateTime(double dist, double max_speed, double max_acceleration) {
  // 1. Accelerate (if possible) elevator from a stop to max speed.
  // Since we assume symmetry with de/acceleration, it suffices to consider
  // half distance and double
  double time = 0.0;
  double traveled_dist = 0.0;
  double half_dist = dist / 2.0;
  // 2. Can we reach max speed, and if so, at what (half) distance?

  // Note: speed = acceleration * time
  //        dist = acceleration * time * time
  //       speed = acceleration * sqrt(dist / acceleration)
  if (max_acceleration * sqrt(half_dist / max_acceleration) > max_speed) {
    // we can reach max speed so find distance accelerating
    traveled_dist += max_speed / max_acceleration;
  } else {
    traveled_dist = half_dist;
  }
  // dist = acceleration * time^2
  time += sqrt(traveled_dist / max_acceleration);

  // 3. Travel more at max speed if needed
  // Note: dist = speed * time
  time += (half_dist - traveled_dist) / max_speed;

  // 4. Account for deceleration time and other half of distance.
  return 2 * time;
}

}  // namespace elevator
