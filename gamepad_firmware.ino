// Gamepad: reads sticks, pots and buttons, sends them over USB.
// Line format: LX,LY,RX,RY,L2,R2,buttonMask

// Stick and pot pins: LX, LY, RX, RY, L2 pot, R2 pot
const int axisPins[6] = {36, 39, 34, 35, 33, 32};

// Button pins, in this order:
// A B X Y L1 R1 L3 R3 Up Down Left Right
const int btnPins[12] = {13, 14, 16, 17, 18, 19,
                         26, 27, 23, 25, 4, 5};

// Read a pin 8 times and average, to reduce noise
int readAvg(int pin) {
  long sum = 0;
  for (int i = 0; i < 8; i++) sum += analogRead(pin);
  return sum / 8;
}

void setup() {
  Serial.begin(460800);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  for (int p : btnPins) pinMode(p, INPUT_PULLUP);
}

void loop() {
  uint16_t mask = 0;
  for (int i = 0; i < 12; i++)
    if (!digitalRead(btnPins[i])) mask |= (1 << i);

  Serial.printf("%d,%d,%d,%d,%d,%d,%u\n",
    readAvg(axisPins[0]), readAvg(axisPins[1]),
    readAvg(axisPins[2]), readAvg(axisPins[3]),
    readAvg(axisPins[4]), readAvg(axisPins[5]), mask);
  delay(5);
}
