/** Simulate a simple elevator scenario.
 * Use the SimpleElevator implementation.
 */

#include <iostream>

#include "SimpleElevator.h"
using elevator::SimpleElevator;

int main(int argc, char* argv[]) {
  SimpleElevator elevator_init_floor0(10, 10, 2, 2, 0);
  SimpleElevator elevator_init_floor10(10, 10, 2, 2, 10);
  // put 6 people in the elevator's queue
  const int floors_to_visit[6] = {1, 2, 3, 4, 5, 6};
  double time_elevator1, time_elevator2 = 0;
  // assume negligible time for person to get on elevator
  // see how much faster one elevator is than the other
  for (int floor : floors_to_visit) {
    time_elevator1 += elevator_init_floor0.MoveToFloor(floor);
    time_elevator2 += elevator_init_floor10.MoveToFloor(floor);
  }
  std::cout << "The elevator starting at floor 0 took " << time_elevator1
            << " secs." << std::endl;
  std::cout << "The elevator starting at floor 10 took " << time_elevator2
            << " secs." << std::endl;
}