void setup_Movement() {
  // Pin set up for relays making analog pins into outputs
  pinMode(Pins.Relay_Lights, OUTPUT);
  pinMode(Pins.Relay_Motor_North, OUTPUT);
  pinMode(Pins.Relay_Motor_East, OUTPUT);
  pinMode(Pins.Relay_Motor_South, OUTPUT);
  pinMode(Pins.Relay_Motor_West, OUTPUT);

  //Turn off all Pumps
  digitalWrite(Pins.Relay_Motor_North, LOW);
  digitalWrite(Pins.Relay_Motor_East, LOW);
  digitalWrite(Pins.Relay_Motor_South, LOW);
  digitalWrite(Pins.Relay_Motor_West, LOW);
  }

void Movement() {
  // Reset variables
  bool movement = false;

  // Move or not
  if (Data.DistanceToDestination > 2) {
    bool movement = true;
  }
  
  // Calculate Angle difference between course and compasss heading
  float angle = (Data.Compass_Heading - Data.CourseToDestination);

  if (angle < 0) {
    angle+=360;
  }
  
  // Sequence motors to turn on
  if (movement == true) {
    if (angle >= 0 && angle < 90 && angle > 270 && angle <= 360) { // Go South - North relay on
      digitalWrite(Pins.Relay_Motor_North, HIGH);
    }
    if (angle > 0 && angle < 180) { // Go West - East relay on
      digitalWrite(Pins.Relay_Motor_East, HIGH);
    }
    if (angle > 90 && angle < 270) { // Go North - South relay on
      digitalWrite(Pins.Relay_Motor_South, HIGH);
    }
    if (angle > 180 && angle < 360) { // Go East - West relay on
      digitalWrite(Pins.Relay_Motor_West, HIGH);
    }
  }
  // Add some Delay
  delay(500);
  }

void Motor_Off() {
  // Turn off all Pumps
  digitalWrite(Pins.Relay_Motor_North, LOW);
  digitalWrite(Pins.Relay_Motor_East, LOW);
  digitalWrite(Pins.Relay_Motor_South, LOW);
  digitalWrite(Pins.Relay_Motor_West, LOW);
}
