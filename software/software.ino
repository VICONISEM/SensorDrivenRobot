// Define pins for motors
#define MOTOR1_1 5
#define MOTOR1_2 6
#define EN1 9
#define MOTOR2_1 11
#define MOTOR2_2 12
#define EN2 10

// Define pins for ultrasonic sensors
#define TRIG1 2
#define ECHO1 3
#define TRIG2 4
#define ECHO2 7
#define TRIG3 8
#define ECHO3 13

// Define the maximum distance for ultrasonic sensors
#define MAX_DISTANCE 85

// Initialize the grid with empty cells
// i = y , j = x
double grid[5][5] = {
  { 0.5, 0.5, 0.5, 0.5, 0.5 },
  { 0.5, 0.5, 0.5, 0.5, 0.5 },
  { 0.5, 0.5, 0.5, 0.5, 0.5 },
  { 0.5, 0.5, 0.5, 0.5, 0.5 },
  { 0.5, 0.5, 0.5, 0.5, 0.5 }
};


//initialize robot cell
int robot_x = 0;
int robot_y = 0;
char dir = 'e';  // e=east  w=west s=south  n=north
int counter = 0;

//initialize object cell
int fromRobotCell_x = 0;
int fromRobotCell_y = 0;



// Function prototypes
int measureDistance(int trigPin, int echoPin);
double probabilty_of_the_cell_OCC(double prevT_occ, double currT_occ, double prevT_emp, double currT_emp);
void updating_positive_x(int dirDistance);
void updating_positive_y(int dirDistance);
void updating_negative_x(int dirDistance);

 int frontDistance = 0;
  int rightDistance = 0;
  int leftDistance = 0;

void setup() {
  // Initialize motors pins as output
  pinMode(MOTOR1_1, OUTPUT);
  pinMode(MOTOR1_2, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(MOTOR2_1, OUTPUT);
  pinMode(MOTOR2_2, OUTPUT);
  pinMode(EN2, OUTPUT);

  // Initialize ultrasonic sensor pins
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {

  delay(3000);

  Serial.println("b");

  delay(2000);


  // Read sensor readings
  frontDistance = measureDistance(TRIG1, ECHO1);
  delay(300);
   rightDistance = measureDistance(TRIG2, ECHO2);
  delay(300);
   leftDistance = measureDistance(TRIG3, ECHO3);
  delay(300);

  if (Serial.availableForWrite() == 0) {
    Serial.println("Buffer is full");
    Serial.flush();
}

  else
  {
     for (int j = 0; j < 5; j++) {
    for (int k = 0; k < 5; k++) {
      Serial.print(grid[j][k]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println("");

  Serial.print("x : ");
  Serial.println(robot_x);
  Serial.print("y : ");
  Serial.println(robot_y);
  Serial.print("dir : ");
  Serial.println(dir);
  }
  // Print sensor readings
  // Serial.print("right Distance: ");
  // Serial.print(rightDistance);
  // Serial.println(" cm");

  // Serial.print("front Distance: ");
  // Serial.print(frontDistance);
  // Serial.println(" cm");

  // Serial.print("left Distance: ");
  // Serial.print(leftDistance);
  // Serial.println(" cm");



  delay (500);

  if (dir == 'e' && robot_y == 4) {
    right();
    stop();
    delay(700);
    change_right_dir();
    //counter = 0;
  }
  if (dir == 's' && robot_x == 4) {
      right();
      stop();
      delay(700);
      change_right_dir();

      //counter = 0;
  }
  if (dir == 'w' && robot_y == 0) {
      right();
      stop();
      delay(700);
      change_right_dir();

      //counter = 0;
  }
  if (dir == 'n' && robot_x == 0) {
      right();
      stop();
      delay(700);
      change_right_dir();
      //counter = 0;
  }





  // for (int j = 0; j < 5; j++) {
  //   for (int k = 0; k < 5; k++) {
  //     Serial.print(grid[j][k]);
  //     Serial.print(" ");
  //   }
  //   Serial.println();
  // }
  // Serial.println("");

  if (dir == 'e') {
    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;
    //front +ve y-axis
    updating_positive_y(frontDistance);
    delay(300);





    // Serial.print("object Cell x: ");
    // Serial.println(fromRobotCell_x);
    // Serial.print("object Cell y: ");
    // Serial.println(fromRobotCell_y);
    // Serial.println("");

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //right +ve x-axis
    updating_positive_x(rightDistance);
    delay(300);


    // Serial.print("object Cell x: ");
    // Serial.println(fromRobotCell_x);
    // Serial.print("object Cell y: ");
    // Serial.println(fromRobotCell_y);

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //left -ve x-axis
    updating_negative_x(leftDistance);
    delay(300);

  }


  else if (dir == 'w') {

    robot_x=robot_x;
    robot_y=robot_y;

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating -ve y
    updating_negative_y(frontDistance);
    delay(300);

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating +ve x
    updating_positive_x(leftDistance);
    delay(300);

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating -ve x
    updating_negative_x(rightDistance);
    delay(300);

    
  } else if (dir == 'n') {
    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating -ve x
    updating_negative_x(frontDistance);
    delay(300);

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating +ve y
    updating_positive_y(rightDistance);
    delay(300);

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating -ve y
    updating_negative_y(leftDistance);
    delay(300);
  }else if(dir == 's'){
    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating +ve x
    updating_positive_x(frontDistance);
    delay(300);

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating +ve y
    updating_positive_y(leftDistance);
    delay(300);

    fromRobotCell_x = robot_x;
    fromRobotCell_y = robot_y;

    //updating -ve y
    updating_negative_y(rightDistance);
    delay(300);
  }

  
  
  // Serial.print("robot x: ");
  // Serial.println(robot_x);
  // Serial.print("robot y: ");
  // Serial.println(robot_y);

 




  // Delay for stability
  delay(500);  // Delay between readings
  move();


  
}

// Function to measure distance using ultrasonic sensor
int measureDistance(int trigPin, int echoPin) {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond pulse to the trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance based on the speed of sound (340 m/s)
  int distance = duration * 0.034 / 2;  // Divide by 2 as we're measuring round trip time

  // Return the distance
  return distance > 84 ? 84 : distance;
}


//baysian rule
double probabilty_of_the_cell_OCC(double prevT_occ, double currT_occ, double prevT_emp, double currT_emp) {
  double prob = 0;
  double temp_prevT_emp = abs(prevT_emp - 1);
  double x = ((prevT_occ * currT_occ) + (temp_prevT_emp * currT_emp)) > 0 ? ((prevT_occ * currT_occ) + (temp_prevT_emp * currT_emp)) : 1;
  prob = (prevT_occ * currT_occ) / x;
  return prob;
}


void updating_positive_y(int dirDistance) {
  bool isobstecle = true;
  if (dirDistance >= 84) {
    isobstecle = false;
    int i = robot_y + 1;
    grid[robot_x][robot_y] = probabilty_of_the_cell_OCC(grid[robot_x][robot_y], 1, grid[robot_x][robot_y], 0);
    while (i != 5) {
      grid[robot_x][i] = probabilty_of_the_cell_OCC(grid[robot_x][i], 0, grid[robot_x][i], 1);
      i++;
    }
  }
  if (isobstecle) {
    fromRobotCell_y = dirDistance / 21;
    fromRobotCell_y += robot_y;
    fromRobotCell_y += 1;
    grid[robot_x][robot_y] = probabilty_of_the_cell_OCC(grid[robot_x][robot_y], 1, grid[robot_x][robot_y], 0);
    int i = robot_y + 1;
    while (i != fromRobotCell_y) {
      grid[robot_x][i] = probabilty_of_the_cell_OCC(grid[robot_x][i], 0, grid[robot_x][i], 1);
      i++;
    }
    grid[fromRobotCell_x][fromRobotCell_y] = probabilty_of_the_cell_OCC(grid[fromRobotCell_x][fromRobotCell_y], 1, grid[fromRobotCell_x][fromRobotCell_y], 0);
  }
}


void updating_positive_x(int dirDistance) {
  bool isobstecle = true;
  if (dirDistance >= 84) {
    isobstecle = false;
    int i = robot_x + 1;
    grid[robot_x][robot_y] = probabilty_of_the_cell_OCC(grid[robot_x][robot_y], 1, grid[robot_x][robot_y], 0);
    while (i != 5) {
      grid[i][robot_y] = probabilty_of_the_cell_OCC(grid[i][robot_y], 0, grid[i][robot_y], 1);
      i++;
    }
  }
  if (isobstecle) {
    fromRobotCell_x = dirDistance / 21;
    fromRobotCell_x += robot_x;
    fromRobotCell_x += 1;
    grid[robot_x][robot_y] = probabilty_of_the_cell_OCC(grid[robot_x][robot_y], 1, grid[robot_x][robot_y], 0);
    int i = robot_x + 1;
    while (i != fromRobotCell_x) {
      grid[i][robot_y] = probabilty_of_the_cell_OCC(grid[i][robot_y], 0, grid[i][robot_y], 1);
      i++;
    }
    grid[fromRobotCell_x][fromRobotCell_y] = probabilty_of_the_cell_OCC(grid[fromRobotCell_x][fromRobotCell_y], 1, grid[fromRobotCell_x][fromRobotCell_y], 0);
  }
}


void updating_negative_x(int dirDistance) {
  bool isobstecle = true;
  if (dirDistance >= 84) {
    isobstecle = false;
    int i = robot_x - 1;
    grid[robot_x][robot_y] = probabilty_of_the_cell_OCC(grid[robot_x][robot_y], 1, grid[robot_x][robot_y], 0);
    while (i != -1) {
      grid[i][robot_y] = probabilty_of_the_cell_OCC(grid[i][robot_y], 0, grid[i][robot_y], 1);
      i--;
    }
  }
  if (isobstecle) {
    fromRobotCell_x -= dirDistance / 21;
    // fromRobotCell_x += robot_x;
    fromRobotCell_x -= 1;
    grid[robot_x][robot_y] = probabilty_of_the_cell_OCC(grid[robot_x][robot_y], 1, grid[robot_x][robot_y], 0);
    int i = robot_x - 1;
    while (i != fromRobotCell_x) {
      grid[i][robot_y] = probabilty_of_the_cell_OCC(grid[i][robot_y], 0, grid[i][robot_y], 1);
      i--;
    }
    grid[fromRobotCell_x][fromRobotCell_y] = probabilty_of_the_cell_OCC(grid[fromRobotCell_x][fromRobotCell_y], 1, grid[fromRobotCell_x][fromRobotCell_y], 0);
  }
}

void updating_negative_y(int dirDistance) {
  bool isobstecle = true;
  if (dirDistance >= 84) {
    isobstecle = false;
    int i = robot_y - 1;
    grid[robot_x][robot_y] = probabilty_of_the_cell_OCC(grid[robot_x][robot_y], 1, grid[robot_x][robot_y], 0);
    while (i != -1) {
      grid[robot_x][i] = probabilty_of_the_cell_OCC(grid[robot_x][i], 0, grid[robot_x][i], 1);
      i--;
    }
  }
  if (isobstecle) {
    fromRobotCell_y -= dirDistance / 21;
    // fromRobotCell_y += robot_y;
    fromRobotCell_y -= 1;
    grid[robot_x][robot_y] = probabilty_of_the_cell_OCC(grid[robot_x][robot_y], 1, grid[robot_x][robot_y], 0);
    int i = robot_y - 1;
    while (i != fromRobotCell_y) {
      grid[robot_x][i] = probabilty_of_the_cell_OCC(grid[robot_x][i], 0, grid[robot_x][i], 1);
      i--;
    }
    grid[fromRobotCell_x][fromRobotCell_y] = probabilty_of_the_cell_OCC(grid[fromRobotCell_x][fromRobotCell_y], 1, grid[fromRobotCell_x][fromRobotCell_y], 0);
  }
}
void forward() {
  digitalWrite(MOTOR1_1, 0);
  digitalWrite(MOTOR1_2, 1);
  digitalWrite(MOTOR2_1, 1);
  digitalWrite(MOTOR2_2, 0);
  analogWrite(9, 65 + 5);
  analogWrite(10, 59 + 5);
  delay(500);
}

void backward() {
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(9, 65 + 2);
  analogWrite(10, 59 + 5);
  delay(600);
}

void right() {
  digitalWrite(MOTOR1_1, 0);
  digitalWrite(MOTOR1_2, 1);
  digitalWrite(MOTOR2_1, 0);
  digitalWrite(MOTOR2_2, 1);
  analogWrite(9, 65 + 2);
  analogWrite(10, 59 + 5);
  delay(427);
}

void left() {
  digitalWrite(MOTOR1_1, 1);
  digitalWrite(MOTOR1_2, 0);
  digitalWrite(MOTOR2_1, 1);
  digitalWrite(MOTOR2_2, 0);
  analogWrite(9, 65 + 2);
  analogWrite(10, 59 + 5);
  delay(470);
}

void stop() {
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, LOW);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, LOW);
}




// movement algorithm
void move() {
  frontDistance = measureDistance(TRIG1, ECHO1);
  delay(300);
  rightDistance = measureDistance(TRIG2, ECHO2);
  delay(300);
  leftDistance = measureDistance(TRIG3, ECHO3);
  delay(300);

  
  delay(700);

  if (canMove()) { 
  // check front object
    if(frontDistance >= 21){
      // front is not detected
      // check left object
      if (leftDistance < 21) {  // left object detected
        // if (counter == 3) {
        //   //counter = 0;
        //   forward();
        //   stop();
        //   delay(1000);
        //   change_robot_pos();
        // } else {
          //counter++;
          frontDistance = measureDistance(TRIG1, ECHO1);
          delay(300);
          rightDistance = measureDistance(TRIG2, ECHO2);
          delay(300);
          leftDistance = measureDistance(TRIG3, ECHO3);
          delay(300);
          forward();
          stop();
          delay(1000);
          change_robot_pos();
          left();
          stop();
          delay(1000);
          change_left_dir();
          
        // }

      } else { 
        frontDistance = measureDistance(TRIG1, ECHO1);
        delay(300);
        rightDistance = measureDistance(TRIG2, ECHO2);
        delay(300);
        leftDistance = measureDistance(TRIG3, ECHO3);
        delay(300); // left object not detected
        forward();
        stop();
        delay(1000);
        change_robot_pos();
        
      }
    } else {
      frontDistance = measureDistance(TRIG1, ECHO1);
      delay(300);
      rightDistance = measureDistance(TRIG2, ECHO2);
      delay(300);
      leftDistance = measureDistance(TRIG3, ECHO3);
      delay(300);  // front object detected
      right();
      stop();
      delay(1000);
      change_right_dir();
      
    }
  }
  
}

// void change_robot_pos() {
//   if (dir == 'e') {
//     robot_y++;
//   } else if (dir == 's') {
//     robot_x++;
//   } else if (dir == 'w') {
//     robot_y--;
//   } else if (dir == 'n') {
//     robot_x--;
//   }
// }

void change_left_dir() {  // r for rotation

  if (dir == 'e') {
    dir = 'n';
  } else if (dir == 'n') {
    dir = 'w';
  } else if (dir == 'w') {
    dir = 's';
  } else if (dir == 's') {
    dir = 'e';
  }
}

void change_right_dir() {  // r for rotation

  if (dir == 'e') {
    dir = 's';
  } else if (dir == 'n') {
    dir = 'e';
  } else if (dir == 'w') {
    dir = 'n';
  } else if (dir == 's') {
    dir = 'w';
  }
}
bool canMove() {
  // Check if movement keeps robot within grid based on direction
  if (dir == 'e' && robot_y < 4) return true;
  if (dir == 's' && robot_x < 4) return true;
  if (dir == 'w' && robot_y > 0) return true;
  if (dir == 'n' && robot_x > 0) return true;
  return false; // Movement would go outside the grid
}
void change_robot_pos() {
  // Ensure the robot position is updated within grid boundaries
  if (dir == 'e' && robot_y < 4) robot_y++;
  else if (dir == 's' && robot_x < 4) robot_x++;
  else if (dir == 'w' && robot_y > 0) robot_y--;
  else if (dir == 'n' && robot_x > 0) robot_x--;
}