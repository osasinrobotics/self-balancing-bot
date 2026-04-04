#include <MPU6050_light.h>

MPU6050 my_mpu(Wire);

// Control Variables
float angle, error, prev_error, integral, output, derivative; 
float setpoint = 0;
float initialAngle = 0; 

// PID Gains
float kp = 30;  
float ki = 0;  
float kd = 6; 


// Motor A connections
int enA = 10;
int in1 = 4;
int in2 = 5;

// Motor B connections
int enB = 11;
int in3 = 6;
int in4 = 7;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  byte status = my_mpu.begin();

  Serial.print("MPU status: ");
  Serial.println(status);
  while (status != 0 ){

  }

  Serial.println("Calculating offsets, do not move MPU6050");
  delay(1000);
  my_mpu.calcOffsets(); 
  Serial.println("Done!\n");
  
  initialAngle = my_mpu.getAngleX();

  Serial.print("Initial Angle: ");
  Serial.println(initialAngle);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  angle = get_angle();

    if (abs(angle) > 45.0){
      move_motors(0,0);
      integral = 0;
      prev_error = 0;
      error = 0; 
      delay(10); 
      return;
    
  } 

  prev_error = error;
  error = setpoint - angle;

  integral += error; 
  integral = constrain(integral, -300, 300);
  

  derivative = (error - prev_error);

  // PID equation
  output = (kp * error) + (ki * integral) + (kd * derivative);
  output = constrain(output, -255, 255);
  move_motors(output, output);


  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print("  Output: ");
  Serial.println(output);


  delay(10);
}

float get_angle(){
  my_mpu.update();
  return my_mpu.getAngleX() - initialAngle;
}



void move_motors(int Left_m, int Right_m) {
  digitalWrite(in1, Left_m > 0);
  digitalWrite(in2, Left_m < 0);
  digitalWrite(in3, Right_m < 0);
  digitalWrite(in4, Right_m > 0);
  analogWrite(enA, abs(Left_m));
  analogWrite(enB, abs(Right_m));
}

