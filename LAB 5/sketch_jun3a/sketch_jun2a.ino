// Pin Definitions
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};
const int digitPins[2] = {9, A0};
const int toggleSwitchPin = A1;

// Variable to store the current count
int count = 0;

// Variable to store the counting direction
int direction = 1; // 1 for forward, -1 for backward

void setup() {
  // Set segment and digit pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  
  // Set toggle switch pin as input
  pinMode(toggleSwitchPin, INPUT_PULLUP);
}

void loop() {
  // Read the toggle switch state
  int toggleState = digitalRead(toggleSwitchPin);

  // Check if the toggle switch is ON
  if (toggleState == LOW) {
    // Toggle switch is ON, count forward
    count += direction;

    // Wrap around if count exceeds 15
    if (count > 15) {
      count = 0;
    }
    else if (count < 0) {
      count = 15;
    }
  }

  // Display the count on the two seven-segment displays
  displayNumber(count);

  // Delay between count updates
  delay(1000);
}

void displayNumber(int number) {
  const int numbers[16][7] = {
    {LOW, LOW, LOW, LOW, LOW, LOW, HIGH},      // 0
    {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH},  // 1
    {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW},      // 2
    {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW},      // 3
    {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW},     // 4
    {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW},      // 5
    {LOW, HIGH, LOW, LOW, LOW, LOW, LOW},       // 6
    {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH},    // 7
    {LOW, LOW, LOW, LOW, LOW, LOW, LOW},        // 8
    {LOW, LOW, LOW, LOW, HIGH, LOW, LOW},       // 9
    {LOW, LOW, LOW, HIGH, LOW, LOW, LOW},       // 10 (A)
    {LOW, LOW, LOW, LOW, LOW, LOW, HIGH},       // 11 (B)
    {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},      // 12 (C)
    {HIGH, LOW, LOW, LOW, LOW, HIGH, LOW},      // 13 (D)
    {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},      // 14 (E)
    {LOW, HIGH, HIGH, HIGH, LOW, LOW, LOW}      // 15 (F)
  };

  // Display the corresponding segments for each digit
  for (int i = 0; i < 2; i++) {
    // Select the digit
    digitalWrite(digitPins[i], LOW);

    // Set the segment pins based on the number to be displayed
    for (int j = 0; j < 7; j++) {
      digitalWrite(segmentPins[j], numbers[number][j]);
    }

    // Delay to allow the segments to light up
    delay(1);

    // Turn off all segment pins
    for (int j = 0; j < 7; j++) {
      digitalWrite(segmentPins[j], HIGH);
    }

    // Deselect the digit
    digitalWrite(digitPins[i], HIGH);
  }
}
