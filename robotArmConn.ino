#include <Servo.h>

#define center 90
Servo servo1;      // superior
Servo servo2;      // base
Servo servoTop;    // middle up >> Y AXIS
Servo servoBot;    // middle down >> X AXIS

const float a = 12.2;   // bottom arm size 
const float b = 12.5;   // top arm size

float sBAngle = 90;   // necessary angle to move the bottom servo
float sTAngle = 90;   // necessary angle to move the top servo

// correction factors to align servo values with theis respective axis
const float sBCorrection = 0;   // Align bottom arm with the horizontal when at 0 degrees
const float sTCorrection = 0;   // Align top arm with bottom arm when at 0 degrees

// Correction factor to shift origin out to edge of the mount ????????????
const float xCorrection = 0; // X direction correction factor (cm)
const float yCorrection = 0; // Y direction correction factor (cm)

// Angle Variables
float A;        //Angle oppposite side a (between b and c)
float B;        //Angle oppposite side b
float C;        //Angle oppposite side c
float theta;    //Angle formed between line from origin to (x,y) and the horizontal

// Distance variables
float x;            // x position (cm)
float y;            // y position (cm)
float c;            // Hypotenuse legngth in cm
const float pi = M_PI;  //Store pi in a less annoying format


void setup() {
  // attaching each servo with their respective arduino pin
  servo1.attach(8);
  servo2.attach(9);
  servoTop.attach(10);
  servoBot.attach(11);
  
  servo1.write(center);
  servo2.write(45);
  servoTop.write(center);
  servoBot.write(center);

  Serial.begin(9600); // For debugging
  delay(100);
}

String inString = "";

float targetX;
float targetY;

int axis = 1;

void loop() {
    while(Serial.available() > 0){
      int inChar = Serial.read();
      println("received");

      // as ling as the incoming byte is not a newline, convert it to a char and add it to the string
      if (inChar != '\n'){
        inString += (char)inChar;

        if (axis == 1){
          targetX = inString.toFloat();
          axis = 0; // indicates that the next character will be axis Y
        }
        else targetY = inString.toFloat();

        FixCoordinates(targetX, targetY);       // Enter coordinates of point.
        CalculateServoAngles();                 // Calculate necessary angles of servos
        MoveArm();                              // Move arm to new position
        delay(1000);
      }

      inString = "";

    }

  }


// Get x and y measured from the bottom of the base. Function corrects for offset
  void FixCoordinates(float x_input, float y_input) {
    
    x = x_input + xCorrection;
    y = y_input + yCorrection;
  }


  // Calculate necessary servo angles to move arm to desired points
void CalculateServoAngles(){

  c = sqrt( sq(x) + sq(y) );                                            // pythagorean theorem
  B = (acos( (sq(b) - sq(a) - sq(c))/(-2*a*c) )) * (180/pi);            // Law of cosines: Angle opposite upper arm section
  C = (acos( (sq(c) - sq(b) - sq(a))/(-2*a*b) )) * (180/pi);            // Law of cosines: Angle opposite hypotenuse
  theta = (asin( y / c )) * (180/pi);      //???????                             // Solve for theta to correct for lower joint's impact on upper joint's angle
 
  sBAngle = B + theta + sBCorrection;                                  // Find necessary angle. Add Correction
  sTAngle = C + sTCorrection;                                           // Find necessary angle. Add Correction

  // making sure that the angles dont go over the robot possibilities
  if (sBAngle > 150) sBAngle = 150;
  if (sBAngle < 20) sBAngle = 20;
  if (sTAngle > 150) sBAngle = 150;
  if (sTAngle < 20) sTAngle = 20;

  Serial.print(sBAngle, sTAngle);
  Serial.print("\t");
  
}

// Update the servos
void MoveArm() {
  
  servoTop.write(sTAngle);        // Move joint to desired position
  servoBot.write(sBAngle);     // Move joint to desired position
}



  

