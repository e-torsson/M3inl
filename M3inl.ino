/*
What you need to test:
7 - wires
1 - resistor
1 - button
1 - Obstacle Avoidance Sensor Module
*/

#include "Arduino_LED_Matrix.h"

#define BUTTON_PIN_D 2  // Pin connected to the button (digital)
#define PROX_PIN_D 7    // Pin connected to the prox sensor (digital)

ArduinoLEDMatrix matrix;

const uint32_t cross[] = {
  0x60630c19,
  0x80f00f01,
  0x9830c606
};

const uint32_t circle[] = {
  0xf010820,
  0x42042042,
  0x41080f0
};

const uint32_t off[] = {
  0x67794,
  0x49669446,
  0x44000000
};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN_D, INPUT_PULLUP);
  pinMode(PROX_PIN_D, INPUT);
  Serial.begin(9600);
  matrix.begin();
}

int ledValue = HIGH;         // Tracks LED state - HIGH = ON, LOW = OFF
int lastButtonState = HIGH;  // Checks the last state of the button

void loop() {
  // Read the current button state
  int currentButtonState = digitalRead(BUTTON_PIN_D);
  // Debounce logic
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    Serial.println("BUTTON PRESSED");
    if (ledValue == HIGH) {
      Serial.println("LED OFF");
      matrix.loadFrame(off);
      ledValue = LOW;  // Turn the LED OFF
    } else {
      Serial.println("LED ON");
      ledValue = HIGH;  // Turn the LED ON
    }
    delay(100);
  }

  // Update button state
  lastButtonState = currentButtonState;

  // Update LED state
  digitalWrite(LED_BUILTIN, ledValue);

  // Only check if LED is on
  if (ledValue == HIGH) {
    int proxValue = digitalRead(PROX_PIN_D);  // Read sensor value
    if (proxValue == LOW) {
      Serial.println("Object detected");
      matrix.loadFrame(cross);
    } else {
      Serial.println("No object detected");
      matrix.loadFrame(circle);
    }
  }
  delay(400);
}
