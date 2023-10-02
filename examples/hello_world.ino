#include "SerialQueueTrickler.h"

SerialQueueTrickler buffer(Serial1, 64); // Now using Serial1

void setup() {
  Serial1.begin(9600);
}

void loop() {
  buffer.enqueue((const byte*)"Hello World!"); // Enqueue string up to '\0'
  //buffer.enqueue(bufferArray, 0); // Enqueue whole buffer as binary
  //buffer.enqueue(bufferArray, 10); // Enqueue first 10 bytes of buffer

  buffer.send();
  delay(2000);
}
