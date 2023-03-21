/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
  
#include "vex.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace vex;

competition Competition;

double flVar = 8.5;
void pre_auton(void) {
  vexcodeInit();
}

int disp(){
  while(1){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("FW spd: ");
    Controller1.Screen.print(flMotor.voltage(volt));
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("FW Temp: ");
    Controller1.Screen.print(flMotor.temperature(percent));
    vex::task::sleep(2500);
  }
}
void l1p(){
  intake.spin(vex::directionType::fwd,100,vex::percentUnits::pct);
}

void l1r(){
  intake.spin(vex::directionType::fwd,0,vex::percentUnits::pct);
}

void l2p(){
  intake.spin(vex::directionType::rev,100,vex::percentUnits::pct);
}

void l2r(){
  intake.spin(vex::directionType::fwd,0,vex::percentUnits::pct);
}

void rightP(){
  expand.set(true);
}

int r1var = 0;
int anglar = 0;

void r1p(){
  r1var += 1;
}

void bup(){
  flVar += 0.1;
}

void bdown(){
  flVar -= 0.1;
}

void bpress(){
  anglar += 1;
}

void moveL(double spd){
  dt1.spin(vex::directionType::rev, spd, vex::voltageUnits::volt); 
  dt2.spin(vex::directionType::rev, spd, vex::voltageUnits::volt);
  dt3.spin(vex::directionType::rev, spd, vex::voltageUnits::volt);
}
void moveR(double spd){
  dt4.spin(vex::directionType::fwd, spd, vex::voltageUnits::volt); 
  dt5.spin(vex::directionType::fwd, spd, vex::voltageUnits::volt);
  dt6.spin(vex::directionType::fwd, spd, vex::voltageUnits::volt);
}

double setDriveSpd (double percentage){
  if(percentage >= 0){
    percentage = (1.2*pow(1.045,(percentage)) - 1.2 + 0.2*(percentage));
  }
  else{
    percentage = -1 * percentage;
    percentage = (1.2*pow(1.045,(percentage)) - 1.2 + 0.2*(percentage));
    percentage = -1 * percentage;
  }
  if(percentage > 100){
    percentage = 100;
  }
  if(percentage < -100){
    percentage = -100;
  }
  return(percentage);
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // .........................................................................
    
  
  
  
  flMotor.spin(vex::directionType::fwd, 11.45,vex::voltageUnits::volt);
  moveL(-3);
  moveR(-3);
  wait(0.8,sec);
  moveL(0);
  moveR(0);
  intake.spinFor(reverse, 180, degrees);
  /*
  moveL(2.05);
  moveR(4.28);
  wait(0.8, sec);
  */
  
  moveL(4);
  moveR(9);
  wait(0.23, sec);

  moveL(0);
  moveR(0);
  wait(1.75, sec);
  intake.spinFor(vex::directionType::fwd, 100, degrees);
  wait(1.8, sec);
  intake.spinFor(vex::directionType::fwd, 100, degrees);
  wait(0.25, sec);
  

  
  //Addon
  moveL(8);
  moveR(-8);
  wait(0.26, sec);
  intake.spin(vex::directionType::rev,90,vex::percentUnits::pct);
  moveL(8.75);
  moveR(8.75);
  wait(0.7, sec);
  moveL(2.25);
  moveR(2.25);
  wait(2.3, sec);
  flMotor.spin(vex::directionType::fwd, 10.5,vex::voltageUnits::volt);
  moveL(-8);
  moveR(8);
  wait(0.345, sec);
  moveL(0);
  moveR(0);
  wait(2.25, sec);
  intake.spin(vex::directionType::rev,0,vex::percentUnits::pct);
  wait(0.25, sec);
  intake.spinFor(vex::directionType::fwd, 360, degrees);
  flMotor.spin(vex::directionType::fwd, 0,vex::voltageUnits::volt);


  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  //-------------------Drivetrain Code --------------------------------------//
  vex::task texting(disp);
  dt1.setStopping(brakeType::coast);
  dt2.setStopping(brakeType::coast);
  dt3.setStopping(brakeType::coast);
  dt4.setStopping(brakeType::coast);
  dt5.setStopping(brakeType::coast);
  dt6.setStopping(brakeType::coast);
  flMotor.setStopping(brakeType::coast);
  intake.setStopping(brakeType::coast);

  //On press Code
  Controller1.ButtonL1.pressed(l1p);
  Controller1.ButtonL1.released(l1r);
  Controller1.ButtonL2.pressed(l2p);
  Controller1.ButtonL2.released(l2r);
  Controller1.ButtonR1.pressed(r1p);
  Controller1.ButtonR2.pressed(bpress);
  
  Controller1.ButtonRight.pressed(rightP);

  
  
  Controller1.ButtonDown.pressed(bdown);
  Controller1.ButtonUp.pressed(bup);

  //Target Usercontrol  
  double targetL = 0;
  double targetR = 0;
  double currentL = 0;
  double currentR = 0;


  //int fstate = 0;
  
  while (1) {
    int forward = -1 * Controller1.Axis1.position(vex::percent);
    int rotate = -1 * Controller1.Axis3.position(vex::percent);
    
    

    int left = (forward + rotate);
    int right = (forward - rotate);
    
    targetL = setDriveSpd(left);
    targetR = setDriveSpd(right);
    /*
    
    double streak = 3.5;

    if(fstate == forward){
      streak += 1;
    }else{
      streak = 3.5;
    }

    if (currentL < targetL) {
      currentL += streak;
    }else if (currentL > targetL) {
      currentL -= streak;
    }
    
    if (abs(targetL-currentL) < 4) currentL = targetL;

    if (currentR < targetR) {
      currentR += streak;
    } else if (currentR > targetR) {
      currentR -= streak;
    }

    if (abs(targetR-currentR) < 4) currentR = targetR;

    */

    targetL = (targetL / 100) * 12;
    targetR = (targetR / 100) * 12;

    //dt1.spin(vex::forward, targetL - (currentL / 2), vex::percent);
    //dt2.spin(vex::forward, targetL - (currentL / 2), vex::percent);
    //dt3.spin(vex::forward, targetL - (currentL / 2), vex::percent);
    //dt4.spin(vex::forward, targetR - (currentR / 2), vex::percent);
    //dt5.spin(vex::forward, targetR - (currentR / 2), vex::percent);
    //dt6.spin(vex::forward, targetR - (currentR / 2), vex::percent);

    dt1.spin(vex::forward, targetL, volt);
    dt2.spin(vex::forward, targetL, volt);
    dt3.spin(vex::forward, targetL, volt);

    dt4.spin(vex::forward, targetR, volt);
    dt5.spin(vex::forward, targetR, volt);
    dt6.spin(vex::forward, targetR, volt);
    
    
    currentL = targetL - (currentL / 3);
    currentR = targetR - (currentR / 3);

    wait(20, msec);

    if(anglar % 2 == 0){
      sloper.set(false);
      flVar = 8.5;
    } else{
      sloper.set(true);
      flVar = 7.5 ;
    }

    if(r1var % 2 == 1){
      flMotor.spin(vex::directionType::fwd,0,vex::voltageUnits::volt);
    } else{
      //flywheel speed decider
        flMotor.spin(vex::directionType::fwd, flVar,vex::voltageUnits::volt);
        //graph rpm to flmotor voltage later to make descending acceleration
      



      // 11 - (0.158 * flMotor.voltage())
      //9.25
      //flMotor.spin(vex::directionType::fwd,6.2,vex::voltageUnits::volt);
    }

    
    //cout << flSpd   << endl;
    //if(flMotor.voltage() > 7.5){
    //  Controller1.rumble("-.");
    //}else{
    //  Controller1.rumble("");
    //}

  }

  //------------------------------------------------------------------------  -//
  
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();


  sloper.set(true);
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}