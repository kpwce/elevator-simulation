/** Elevator abstract class. */

namespace elevator {

class Elevator {
  // Basic elevator model.
 public:
  Elevator(int max_floor, double floor_dist, double max_speed,
           double max_acceleration, int current_floor = 0)
      : max_floor_(max_floor),
        floor_dist_(floor_dist),
        max_speed_(max_speed),
        max_acceleration_(max_acceleration),
        current_floor_(current_floor) {}      // ctor
  Elevator(const Elevator& other) = default;  // cctor, shallow copy fields
  virtual ~Elevator() {}                      // dtor
  Elevator& operator=(const Elevator& other) =
      default;  // assignment op, shallow copy fields

  // Member functions

  /** Get total floors elevator can access.
   *  Return: Maximum floor possible.
   */
  int getMaxFloor() const { return max_floor_; }

  /** Get the (fixed) distances between elevator floors.
   *  Return: Floor distances.
   */
  double getFloorDist() const { return floor_dist_; }

  /** Get max speed of elevator.
   *  Return: Terminal speed of elevator.
   */
  double getMaxSpeed() const { return max_speed_; }

  /** Get max acceleration of elevator.
   *  Return: Max acceleration of elevator.
   */
  double getMaxAcceleration() const { return max_acceleration_; }

  /** Get current floor elevator is on.
   *  Return: Current floor of elevator.
   */
  int getCurrentFloor() const { return current_floor_; }

  /** Move the elevator up.
   * Param:
   *      num_floors - natural number for desired number of floors to go up to
   * Modifies: current_floor
   * Effects: current_floor = min(current_floor + num_floors, max_floor)
   * Return: Time it takes to go up num_floors (in terminal speed unit of time)
   */
  virtual double UpFloors(int num_floors) = 0;

  /** Move the elevator down.
   * Param:
   *      num_floors - natural number for desired number of floors to go down to
   * Modifies: current_floor
   * Effects: current_floor = max(current_floor - num_floors, min_floor)
   * Return: Time it takes to go down num_floors (in terminal speed unit of
   * time)
   */
  virtual double DownFloors(int num_floors) = 0;

  /** Move the elevator to specified floor.
   * Param:
   *      floor - natural number for desired floor.
   * Modifies: current_floor
   * Effects: Tries to set current floor as close to floor as possible
   * Return: Time it takes to go to new floor.
   */
  double MoveToFloor(int floor) {
    return floor > current_floor_ ? UpFloors(floor - current_floor_)
                                  : DownFloors(current_floor_ - floor);
  }

 protected:
  int max_floor_;            // 0-indexed floors
  double floor_dist_;        // distance between floors
  double max_speed_;         // positive magnitude of velocity
  double max_acceleration_;  // positive magnitude of de/acceleration
  int current_floor_;        // 0 (default) <= current_floor <= max_floor
};

}  // namespace elevator
