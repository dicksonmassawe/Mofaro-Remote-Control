// Define Input Connections
#define CH1 A0
#define CH2 A1
#define CH3 A2
#define CH4 A3
#define CH5 A4
#define CH6 A5
#define CH7 A6
#define CH8 A7
#define CH9 A8
#define CH10 A9

#define ACC1 2
#define ACC2 3
#define ACC3 4
#define ACC4 5

#define HIGH1 22
#define HIGH2 24
#define HIGH3 26
#define HIGH4 28

#define LOW1 23
#define LOW2 25
#define LOW3 27
#define LOW4 29

#define REVERSE1 30
#define REVERSE2 32
#define REVERSE3 34
#define REVERSE4 36


// Linear Actuator Pins
#define left 11
#define right 12

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value;
int ch5Value;
int ch6Value;

// Boolean to represent switch value
bool ch7Value;
bool ch8Value;
bool ch9Value;
bool ch10Value;

void setup() {
  // Set up serial monitor
  Serial.begin(115200);

  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
  pinMode(CH7, INPUT);
  pinMode(CH8, INPUT);
  pinMode(CH9, INPUT);
  pinMode(CH10, INPUT);

  pinMode(ACC1, OUTPUT);
  pinMode(ACC2, OUTPUT);
  pinMode(ACC3, OUTPUT);
  pinMode(ACC4, OUTPUT);

  pinMode(HIGH1, OUTPUT);
  pinMode(HIGH2, OUTPUT);
  pinMode(HIGH3, OUTPUT);
  pinMode(HIGH4, OUTPUT);

  pinMode(LOW1, OUTPUT);
  pinMode(LOW2, OUTPUT);
  pinMode(LOW3, OUTPUT);
  pinMode(LOW4, OUTPUT);

  pinMode(REVERSE1, OUTPUT);
  pinMode(REVERSE2, OUTPUT);
  pinMode(REVERSE3, OUTPUT);
  pinMode(REVERSE4, OUTPUT);


  // Put low speed as default
  digitalWrite(HIGH1, 0);
  digitalWrite(HIGH2, 0);
  digitalWrite(HIGH3, 0);
  digitalWrite(HIGH4, 0);
  digitalWrite(LOW1, 1);
  digitalWrite(LOW2, 1);
  digitalWrite(LOW3, 1);
  digitalWrite(LOW4, 1);


  // Linear Actuator
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);

  digitalWrite(left, 0);
  digitalWrite(right, 0);
}


void loop() {

  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, 0, 254, 0);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, 0, 100, 0);
  ch6Value = readChannel(CH6, 0, 100, 0);
  ch7Value = readSwitch(CH7, false);
  ch8Value = readSwitch(CH8, false);
  ch9Value = readSwitch(CH9, false);
  ch10Value = readSwitch(CH10, false);

  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" | Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | Ch4: ");
  Serial.print(ch4Value);
  Serial.print(" | Ch5: ");
  Serial.print(ch5Value);
  Serial.print(" | Ch6: ");
  Serial.print(ch6Value);
  Serial.print(" | Ch7: ");
  Serial.print(ch7Value);
  Serial.print(" | Ch8: ");
  Serial.print(ch8Value);
  Serial.print(" | Ch9: ");
  Serial.print(ch9Value);
  Serial.print(" | Ch10: ");
  Serial.println(ch10Value);

  // Steering
  if (ch4Value < -10) {
    digitalWrite(left, 0);
    digitalWrite(right, 1);
  } else if (ch4Value > 10) {
    digitalWrite(left, 1);
    digitalWrite(right, 0);
  } else {
    digitalWrite(left, 1);
    digitalWrite(right, 1);
  }

  // Changing Gear
  if (ch9Value == 0) {
    digitalWrite(HIGH1, 1);
    digitalWrite(HIGH2, 1);
    digitalWrite(HIGH3, 1);
    digitalWrite(HIGH4, 1);

    digitalWrite(LOW1, 0);
    digitalWrite(LOW2, 0);
    digitalWrite(LOW3, 0);
    digitalWrite(LOW4, 0);
  } else if (ch9Value == 1) {
    digitalWrite(HIGH1, 0);
    digitalWrite(HIGH2, 0);
    digitalWrite(HIGH3, 0);
    digitalWrite(HIGH4, 0);

    digitalWrite(LOW1, 1);
    digitalWrite(LOW2, 1);
    digitalWrite(LOW3, 1);
    digitalWrite(LOW4, 1);
  }
  // Reverse
  if (ch10Value == 0) {
    digitalWrite(REVERSE1, 1);
    digitalWrite(REVERSE2, 1);
    digitalWrite(REVERSE3, 1);
    digitalWrite(REVERSE4, 1);
  } else if (ch10Value == 1) {
    digitalWrite(REVERSE1, 0);
    digitalWrite(REVERSE2, 0);
    digitalWrite(REVERSE3, 0);
    digitalWrite(REVERSE4, 0);
  }

  // Acceleration
  if (ch3Value > -1) {
    analogWrite(ACC1, ch3Value);
    analogWrite(ACC2, ch3Value);
    analogWrite(ACC3, ch3Value);
    analogWrite(ACC4, ch3Value);
  }


  delay(100);
}

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}