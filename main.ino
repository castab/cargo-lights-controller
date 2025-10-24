// ATtiny85 LED Fade with Button Control and Auto-Timeout
// Pin definitions
const int statusLedPin = 0;   // Status LED pin
const int mosfetGatePin = 2;  // MOSFET gate control pin
const int buttonPin = 1;      // Button input pin

// Variables for the fade functions
const int fadeDelay = 5;   // Delay between brightness steps in milliseconds
const int fadeSteps = 50;  // Number of steps to complete a fade (higher = smoother but slower)

// Auto-timeout variables
const unsigned long timeoutDuration = 600000;  // 10 minutes in milliseconds (10 * 60 * 1000)
unsigned long lastOnTime = 0;  // Last time the LED was turned on

// Button debounce variables
bool ledState = false;     // Current state of the LED (on/off)
bool lastButtonState = HIGH;   // Previous reading from the button
bool buttonState;          // Current reading from the button
unsigned long lastDebounceTime = 0;  // Last time the button state changed
unsigned long debounceDelay = 50;    // Debounce time in milliseconds

void setup() {
  // Set pin modes
  pinMode(statusLedPin, OUTPUT);
  pinMode(mosfetGatePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Using internal pull-up resistor
  
  // Ensure LED and MOSFET start off
  analogWrite(statusLedPin, 0);
  analogWrite(mosfetGatePin, 0);
}

void loop() {
  // Check for timeout if LED is on
  if (ledState) {
    if (millis() - lastOnTime >= timeoutDuration) {
      // 10 minutes have passed, turn off LED
      ledState = false;
      fadeOff();
    }
  }

  // Read the button state
  bool reading = digitalRead(buttonPin);

  // If the button state changed, reset the debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Check if button state is stable for the debounce period
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed
    if (reading != buttonState) {
      buttonState = reading;

      // Only toggle the LED if the button was pressed (LOW when using INPUT_PULLUP)
      if (buttonState == LOW) {
        ledState = !ledState;  // Toggle LED state

        if (ledState) {
          fadeOn();  // Fade LED on
          lastOnTime = millis();  // Record when LED was turned on
        } else {
          fadeOff(); // Fade LED off
        }
      }
    }
  }

  // Save the reading for the next loop iteration
  lastButtonState = reading;
}

// Function to fade the LED on
void fadeOn() {
  // Start from 0 brightness and increase to full brightness
  for (int brightness = 0; brightness <= 255; brightness += (255 / fadeSteps)) {
    analogWrite(mosfetGatePin, brightness);
    analogWrite(statusLedPin, brightness);  // Mirror to status LED
    delay(fadeDelay);
  }
  // Ensure both outputs are fully on at the end
  analogWrite(mosfetGatePin, 255);
  analogWrite(statusLedPin, 255);
}

// Function to fade the LED off
void fadeOff() {
  // Start from full brightness and decrease to 0
  for (int brightness = 255; brightness >= 0; brightness -= (255 / fadeSteps)) {
    analogWrite(mosfetGatePin, brightness);
    analogWrite(statusLedPin, brightness);  // Mirror to status LED
    delay(fadeDelay);
  }
  // Ensure both outputs are fully off at the end
  analogWrite(mosfetGatePin, 0);
  analogWrite(statusLedPin, 0);
}