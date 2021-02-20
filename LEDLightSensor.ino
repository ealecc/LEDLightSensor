#define READ A0
#define REFRESH 1000000

int limit = 0;

void setup() {
  // need a high baud rate to calculate 100th of a second shutter speed
  Serial.begin(57600);
}

void loop() {
  // set LED light baseline
  int light = (readLED(100));
  limit = light + 25;

  // run sensor in a loop and recalculate baseline every REFRESH interval
  for (int i = 0; i < REFRESH; i++) {
    light = (readLED(100));

    // test if sensor is exposed to light
    if (light > limit) {
      Serial.println(1);
    } else {
      Serial.println(0);
    }
  }
}

// read output from LED n times and calculate average
int readLED(int n) {
  int total = 0;
  for (int i = 0; i < n; i++) {
    total += analogRead(READ);
  }
  return total/n;
}
