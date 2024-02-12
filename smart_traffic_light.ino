// Define pin numbers for IR sensors, traffic lights, and 7-segment displays
//====================================================
// IR sensor array pins 2 ==> 9 (8 pins)
const int irSensorPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
//====================================================
// traffic light pins 10 ==> 21 (12 pins)
const int trafficLightPins[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };
// 7-segment pins
const int sevenSegmentPins[][8] = {
  { 22, 23, 24, 25, 26, 27, 28 },  // Display for Traffic Light 1
  { 29, 30, 31, 32, 33, 34, 35 },  // Display for Traffic Light 2
  { 36, 37, 38, 39, 40, 41, 42 },  // Display for Traffic Light 3
  { 43, 44, 45, 46, 47, 48, 49 }   // Display for Traffic Light 4
};
int num_array[11][7] = {
  { 1, 1, 1, 1, 0, 1, 1 },  // -
  { 0, 1, 1, 0, 1, 1, 1 },  // 1
  { 1, 0, 0, 0, 0, 0, 1 },  // 2
  { 0, 0, 1, 0, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 0 },  // 4
  { 0, 0, 1, 1, 0, 0, 0 },  // 5
  { 0, 0, 0, 1, 0, 0, 0 },  // 6
  { 0, 0, 1, 0, 1, 1, 1 },  // 7
  { 0, 0, 0, 0, 0, 0, 0 },  // 8
  { 0, 0, 1, 0, 0, 0, 0 },  // 8
};

void setup() {
  // Initialize pins 
  //===========================
  //IR sensor Initialize:
  for (int i = 0; i < 8; i++) {
    pinMode(irSensorPins[i], INPUT);
  }
  //===========================
  //Traffic Light Initialize:
  for (int i = 0; i <= 12; i++) {
    pinMode(trafficLightPins[i], OUTPUT);
  }
  //===========================
  //7-Segment Initialize:
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      pinMode(sevenSegmentPins[i][j], OUTPUT);
    }
  }
  for (int counter = 4; counter > 0; --counter) {
    Num_Write(counter - 1, 22);
    Num_Write(counter - 1, 29);
    Num_Write(counter - 1, 36);
    Num_Write(counter - 1, 43);
  }

  digitalWrite(trafficLightPins[1], HIGH);
  digitalWrite(trafficLightPins[4], HIGH);
  digitalWrite(trafficLightPins[7], HIGH);
  digitalWrite(trafficLightPins[10], HIGH);
  Serial.begin(9600);
}


void loop() {
  /*
  **First Side:
  - IR sensor pins             
    array:   [0 , 1]
    arduino  [2 , 3]
  - traffic Light led pins  
              G    R    O   
    array    [0  , 1  , 2]
    arduino  [10 , 11 , 12]
  - 7-Segment pins             
    array    [0][-]
    arduino  [22, 23, 24, 25, 26, 27, 28 ]
  */
  sideFunction("Side One", 0, 1, 0, 1, 2, 5, 4, 22);
  /*
  **Seconde Side:
  - IR sensor pins             
    array:   [2 , 3]
    arduino  [4 , 5]
  - traffic Light led pins  
              G    R    O   
    array    [3  , 4  , 5]
    arduino  [13 , 14 , 15]
  - 7-Segment pins             
    array    [4][-]
    arduino  [ 43, 44, 45, 46, 47, 48, 49 ]
  */
  sideFunction("Side Tow", 2, 3, 3, 4, 5, 8, 7, 43);
  /*
  **Third Side:
  - IR sensor pins             
    array:   [4 , 5]
    arduino  [6 , 7]
  - traffic Light led pins  
              G    R    O   
    array    [6  , 7  , 8]
    arduino  [16 , 17 , 18]
  - 7-Segment pins             
    array    [3][-]
    arduino  [ 36, 37, 38, 39, 40, 41, 42 ]
  */
  sideFunction("Side Three", 4, 5, 6, 7, 8, 11, 10, 36);
  /*
  **Fourth Side:
  - IR sensor pins             
    array:   [6 , 7]
    arduino  [8 , 9]
  - traffic Light led pins  
              G    R    O   
    array    [9  , 10  , 11]
    arduino  [19 , 20 , 21]
  - 7-Segment pins             
    array    [2][-]
    arduino  [ 29, 30, 31, 32, 33, 34, 35 ]
  */
  sideFunction("Side Four", 6, 7, 9, 10, 11, 2, 1, 29);
}
void sideFunction(String sideTitle, int irSensorPin1, int irSensorPins2, int greenLightPin, int redLightPin, int orangeLightPin, int nextOrangeLightPin, int nextRedLightPin, int _7segmentStartPin) {
  digitalWrite(trafficLightPins[greenLightPin], HIGH);
  digitalWrite(trafficLightPins[redLightPin], LOW);
  digitalWrite(trafficLightPins[orangeLightPin], LOW);
  // No car detected:
  Serial.println("0 Cars - " + sideTitle);
  if (digitalRead(irSensorPins[irSensorPin1]) == 0 && digitalRead(irSensorPins[irSensorPins2]) == 0) {
    for (int counter = 4; counter > 0; counter--) {
      delay(1000);
      Num_Write(counter - 1, _7segmentStartPin);
      if (counter < 3) {
        digitalWrite(trafficLightPins[greenLightPin], LOW);
        digitalWrite(trafficLightPins[orangeLightPin], HIGH);
      }
      if (counter < 2) {
        digitalWrite(trafficLightPins[greenLightPin], LOW);
        digitalWrite(trafficLightPins[orangeLightPin], LOW);
      }
    }
  }
  // 2 Cars detected =============================================:
  else if (digitalRead(irSensorPins[irSensorPin1]) == 1 && digitalRead(irSensorPins[irSensorPins2]) == 1) {
    Serial.println("2 Cars - " + sideTitle);
    for (int counter = 10; counter > 0; counter--) {
      delay(1000);
      Num_Write(counter - 1, _7segmentStartPin);
      if (counter < 3) {
        digitalWrite(trafficLightPins[greenLightPin], LOW);
        digitalWrite(trafficLightPins[orangeLightPin], HIGH);
      }
      if (counter < 2) {
        digitalWrite(trafficLightPins[orangeLightPin], LOW);
      }
    }
  }
  // 1 Car Detected =========================================:
  else if (digitalRead(irSensorPins[irSensorPin1]) == 1 || digitalRead(irSensorPins[irSensorPins2]) == 1) {
    Serial.println("1 Cars 1 - " + sideTitle);
    for (int counter = 7; counter > 0; counter--) {
      delay(1000);
      Num_Write(counter - 1, _7segmentStartPin);
      if (counter < 3) {
        digitalWrite(trafficLightPins[greenLightPin], LOW);
        digitalWrite(trafficLightPins[orangeLightPin], HIGH);
      }
      if (counter < 2) {
        digitalWrite(trafficLightPins[greenLightPin], LOW);
        digitalWrite(trafficLightPins[orangeLightPin], LOW);
      }
    }
  }
  digitalWrite(trafficLightPins[nextRedLightPin], LOW);
  digitalWrite(trafficLightPins[nextOrangeLightPin], HIGH);
  digitalWrite(trafficLightPins[redLightPin], HIGH);
  delay(1000);
}
// this function writes values to the sev seg pins
void Num_Write(int number, int startPin) {
  for (int j = 0; j < 7; j++) {
    digitalWrite(startPin, num_array[number][j]);
    startPin++;
  }
}