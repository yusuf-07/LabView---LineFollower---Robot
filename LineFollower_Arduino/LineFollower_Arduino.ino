// Motor control pins
const int enable12Pin = 5;   // Enable pins for motors 1 and 2 connected to Arduino pin 5
const int enable34Pin = 6;   // Enable pins for motors 3 and 4 connected to Arduino pin 6
const int input1Pin = 7;     // Input 1 pin of L293D connected to Arduino pin 7
const int input2Pin = 8;     // Input 2 pin of L293D connected to Arduino pin 8
const int input3Pin = 9;     // Input 3 pin of L293D connected to Arduino pin 9
const int input4Pin = 10;    // Input 4 pin of L293D connected to Arduino pin 10

// Infrared sensor pins
const int sensor1Pin = A0;    // Infrared sensor 1 connected to Arduino pin A0
const int sensor2Pin = A1;    // Infrared sensor 2 connected to Arduino pin A1
const int sensor3Pin = A2;    // Infrared sensor 3 connected to Arduino pin A2

void setup() {
  // Set motor control pins as OUTPUT
  pinMode(enable12Pin, OUTPUT);
  pinMode(enable34Pin, OUTPUT);
  pinMode(input1Pin, OUTPUT);
  pinMode(input2Pin, OUTPUT);
  pinMode(input3Pin, OUTPUT);
  pinMode(input4Pin, OUTPUT);
  
  // Set infrared sensor pins as INPUT_PULLUP
  pinMode(sensor1Pin, INPUT_PULLUP);
  pinMode(sensor2Pin, INPUT_PULLUP);
  pinMode(sensor3Pin, INPUT_PULLUP);
}

void loop() {
  // Read the state of infrared sensors
  bool sensor1State = digitalRead(sensor1Pin);
  bool sensor2State = digitalRead(sensor2Pin);
  bool sensor3State = digitalRead(sensor3Pin);

  // Robot behavior based on infrared sensor states
  if (!sensor1State && !sensor2State && !sensor3State) {
    // 000: Robot doesn't move
    stopRobot();
  } else if (!sensor1State && !sensor2State && sensor3State) {
    // 001: Robot doesn't move
    stopRobot();
  } else if (!sensor1State && sensor2State && !sensor3State) {
    // 010: Robot moves to the left
    turnLeft();
  } else if (!sensor1State && sensor2State && sensor3State) {
    // 011: Robot moves to the right
    turnRight();
  } else if (sensor1State && !sensor2State && !sensor3State) {
    // 100: Robot stops
    stopRobot();
  } else if (sensor1State && !sensor2State && sensor3State) {
    // 101: Robot pauses for 5 seconds, then moves again
    stopRobot();
    delay(5000);
  } else if (sensor1State && sensor2State && !sensor3State) {
    // 110: Robot turns left
    turnLeft();
  } else if (sensor1State && sensor2State && sensor3State) {
    // 111: Robot stops
    stopRobot();
  }
}

// Function to start the robot
void startRobot() {
  digitalWrite(input1Pin, HIGH);
  digitalWrite(input2Pin, LOW);
  digitalWrite(input3Pin, HIGH);
  digitalWrite(input4Pin, LOW);
}


// Function to make the robot turn to the left
void turnLeft() {
  digitalWrite(input1Pin, LOW);
  digitalWrite(input2Pin, HIGH);
  digitalWrite(input3Pin, HIGH);
  digitalWrite(input4Pin, LOW);
}
// Function to make the robot turn to the right
void turnRight() {
  digitalWrite(input1Pin, HIGH);
  digitalWrite(input2Pin, LOW);
  digitalWrite(input3Pin, LOW);
  digitalWrite(input4Pin, HIGH);
}
// Function to stop the robot
void stopRobot() {
  digitalWrite(input1Pin, LOW);
  digitalWrite(input2Pin, LOW);
  digitalWrite(input3Pin, LOW);
  digitalWrite(input4Pin, LOW);
}
