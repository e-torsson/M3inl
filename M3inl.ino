/*
What you need to test:
7 - wires
1 - resistor
1 - button
1 - Obstacle Avoidance Sensor Module
*/

#define BUTTON_PIN_D 2 // Pin connected to the button (digital)
#define PROX_PIN_D 7 // Pin connected to the prox sensor (digital)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN_D, INPUT_PULLUP);
  pinMode(PROX_PIN_D, INPUT);
  Serial.begin(9600);
}

int ledValue = HIGH; // Tracks LED state - HIGH = ON, LOW = OFF
int lastButtonState = HIGH; // Checks the last state of the button

void loop() {
  // Read the current button state
  int currentButtonState = digitalRead(BUTTON_PIN_D);

  // Debounce logic
  if(currentButtonState == LOW && lastButtonState == HIGH)
  {
    Serial.println("BUTTON PRESSED");
    if(ledValue == HIGH)
    {
      Serial.println("LED OFF");
      ledValue = LOW; // Turn the LED OFF
    }
    else
    {
      Serial.println("LED ON");
      ledValue = HIGH; // Turn the LED ON
    }
    delay(100);
  }

  // Update button state
  lastButtonState = currentButtonState;

  // Update LED state
  digitalWrite(LED_BUILTIN, ledValue);

  // Only check if LED is on
  if(ledValue == HIGH)
  {
    int proxValue = digitalRead(PROX_PIN_D); // Read sensor value
    if(proxValue == LOW)
    {
      Serial.println("Object detected");
    }
    else
    {
      Serial.println("No object detected");
    }
  }
  delay(400);
}
