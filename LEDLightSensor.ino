#define READ A0
#define REFRESH 1000

int limit = 0;

void setup() {
  // need a high baud rate to calculate 100th of a second shutter speed
  Serial.begin(9600);
}

void loop() {
  // set LED light baseline
  int light = (readLED(100));
  limit = light + 25;

  // run sensor in a loop and recalculate baseline every REFRESH interval
  for (int i = 0; i < REFRESH; i++) {
    unsigned long startTime = millis();
    unsigned long currentTime;
   
    // if reading goes above limit, measure exposure time
    while (analogRead(READ) > limit) {
      currentTime = millis();
    }

    // calculate exposure time and write to serial
    if (currentTime > startTime) {
    unsigned long duration = currentTime - startTime;
    Serial.println(duration);
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
