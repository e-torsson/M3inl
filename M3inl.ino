#define BUTTON_PIN 4

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);

}

// Initial value of button (LED / Sensor OFF)
int buttonValue = HIGH;

void loop() {
  if(digitalRead(BUTTON_PIN) == LOW){
    Serial.println("BUTTON PRESSED");
    if(buttonValue == HIGH){
      Serial.println("LED OFF");
      buttonValue = LOW;
    }
    else{
      Serial.println("LED ON");
      buttonValue = HIGH;
    }
  }
  digitalWrite(LED_BUILTIN, buttonValue);
  delay(200);

}
