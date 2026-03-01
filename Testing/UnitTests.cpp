#include <iostream>
#include <stdio.h>

// List of tests
// 0. Person instantiation test
// 1. People list instantion test
// 2. Movement from off plane to first area
// 3. generic movement in a section
// 4. movement at a transition point
// 4a. move from one section to another starting at the transition point
// 4b. move around corners with spare movement
// 5. bounce check
// 5a. bounce check where there is no movement
// 5b. bounce check with extra movement to start
// 5c. double bounce check (ie both people are slowed by the person in front [line holding])
// 5d. bounce check against seated individual
// 5e. bounce check where there is no movement - Against passenger placing baggage
// 6. Baggage Checks
// 7. Seating checks
// 8. Seat assignment checks
// 8a. no duplicate seating