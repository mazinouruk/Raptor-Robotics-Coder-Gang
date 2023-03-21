#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor dt1 = motor(PORT3, ratio6_1, false);
motor dt2 = motor(PORT4, ratio6_1, true);
motor dt3 = motor(PORT5, ratio6_1, false);
motor dt4 = motor(PORT6, ratio6_1, false);
motor dt5 = motor(PORT7, ratio6_1, true);
motor dt6 = motor(PORT8, ratio6_1, false);
controller Controller1 = controller(primary);
motor flMotor = motor(PORT1, ratio18_1, false);
motor intake = motor(PORT2, ratio18_1, true);
digital_out expand = digital_out(Brain.ThreeWirePort.A);
digital_out sloper = digital_out(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}