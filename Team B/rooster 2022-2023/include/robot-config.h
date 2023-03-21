using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor dt1;
extern motor dt2;
extern motor dt3;
extern motor dt4;
extern motor dt5;
extern motor dt6;
extern controller Controller1;
extern motor flMotor;
extern motor intake;
extern digital_out expand;
extern digital_out sloper;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );