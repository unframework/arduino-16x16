#ifdef ESP8266

// ESP8266 Feather pinout (top row starting from corner)
#define LEDARRAY_D 4
#define LEDARRAY_C 5
#define LEDARRAY_B 2
#define LEDARRAY_A 16
#define LEDARRAY_G 0
#define LEDARRAY_DI 15
#define LEDARRAY_CLK 13
#define LEDARRAY_LAT 12

#else

// Arduino pinout (top row starting from corner after TX/RX)
#define LEDARRAY_D 2
#define LEDARRAY_C 3
#define LEDARRAY_B 4
#define LEDARRAY_A 5
#define LEDARRAY_G 6
#define LEDARRAY_DI 7
#define LEDARRAY_CLK 8
#define LEDARRAY_LAT 9

#endif

// Y-line = 0 is on the side with data connectors
// when it is at the top, X-pixels are fed into shift registers from right to left
int pix[] = {
  0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
  0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
  1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
  1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
  1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,
  1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,
  0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,
  0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,
  0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,
  0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
  0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
  0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
  0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
  0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,
  0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void setup() {
  pinMode(LEDARRAY_D, OUTPUT);
  pinMode(LEDARRAY_C, OUTPUT);
  pinMode(LEDARRAY_B, OUTPUT);
  pinMode(LEDARRAY_A, OUTPUT);
  pinMode(LEDARRAY_G, OUTPUT);
  pinMode(LEDARRAY_DI, OUTPUT);
  pinMode(LEDARRAY_CLK, OUTPUT);
  pinMode(LEDARRAY_LAT, OUTPUT);

  // reset the X-data latch and clock
  digitalWrite(LEDARRAY_LAT, LOW);
  digitalWrite(LEDARRAY_CLK, LOW);

  // turn off display
  digitalWrite(LEDARRAY_G, HIGH);
}

void loop() {
  int *pixPtr = pix;

  for (int i = 0; i < 16; i++) {
    // send data and latch it
    for (int dot = 0; dot < 32; dot++) {
      digitalWrite(LEDARRAY_DI, *pixPtr ? LOW : HIGH);

      digitalWrite(LEDARRAY_CLK, HIGH);
      digitalWrite(LEDARRAY_CLK, LOW);

      pixPtr += 1;
    }

    digitalWrite(LEDARRAY_LAT, HIGH);
    digitalWrite(LEDARRAY_LAT, LOW);

    // select Y-line
    digitalWrite(LEDARRAY_D, (i >> 3) & 1);
    digitalWrite(LEDARRAY_C, (i >> 2) & 1);
    digitalWrite(LEDARRAY_B, (i >> 1) & 1);
    digitalWrite(LEDARRAY_A, (i) & 1);

    // toggle display
    digitalWrite(LEDARRAY_G, LOW);
    delayMicroseconds(400);
    digitalWrite(LEDARRAY_G, HIGH);
  }
}
