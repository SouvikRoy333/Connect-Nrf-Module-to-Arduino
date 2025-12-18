#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 9); // CE, CSN

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (!radio.begin()) {
    Serial.println("NRF24L01 not detected!");
  } else {
    Serial.println("NRF24L01 detected and working.");
  }
}
