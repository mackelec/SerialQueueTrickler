# SerialQueueTrickler Library

**Introducing SerialQueueTrickler: Achieve precise, non-blocking serial communication for your Arduino projects.**

## Description

SerialQueueTrickler is an Arduino library designed to provide efficient, non-blocking serial communication. This is particularly valuable for platforms like STM32 where `Serial.write()` can be blocking. Without relying on interrupts, the library gives users exact control over byte transmission timings, ideal for scenarios where specific byte sending intervals are crucial without unintended task interruptions.

When the library operates with a burst size of 1, and the frequency of calling the send methods is slower than the serial port's transmission rate, it ensures non-blocking functionality, giving the microcontroller freedom to manage other tasks in between sends.

## Key Features

- **Non-Blocking Operations:** Achieve multitasking with efficient serial communication.
- **Controlled Transmission:** No interrupts ensure user-defined byte transmission timings.
- **Optimized Performance:** Leverages direct register access for swift transmissions on supported platforms.
- **Flexible Data Sending:** Choose between customizable bursts or single-byte transmissions.
- **Extendable and Configurable:** Easily tailor the library for diverse platforms and requirements.

## How to Use

### Basic Usage

1. **Include the Library**
    ```cpp
    #include <SerialQueueTrickler.h>
    ```

2. **Initialize the Trickler**
    ```cpp
    SerialQueueTrickler trickler(Serial, 64);
    ```

3. **Enqueue Data**
    ```cpp
    trickler.enqueue((const byte*)"Hello, World!");
    ```

4. **Transmit Data**
    ```cpp
    trickler.regSend(); // Initiates register-level, user-controlled data transmission.
    ```

### Example Sketch
```cpp
#include <SerialQueueTrickler.h>

SerialQueueTrickler trickler(Serial, 64);

void setup() {
  Serial.begin(9600);
  trickler.enqueue((const byte*)"Hello, World!");
}

void loop() {
  trickler.regSend(); // Transmit data byte-by-byte
  delay(500); // Simulating other tasks with a delay
}

```

# Enqueue Methods

This library offers various methods to enqueue data for transmission, catering to different data types and scenarios:

## enqueueByte Method
- **Description**: The `enqueueByte` method is designed to add a single byte to the queue. This is useful when you want to send a solitary byte without any associated data.
  
- **Usage**:
  
  ```cpp
  trickler.enqueueByte(0xA5); // Enqueues the hexadecimal byte 0xA5
```
## enqueue Method
- **Description**: The `enqueue` method is designed for enqueuing strings. It assumes the provided data ends when it encounters a '\0' null terminator. This makes it ideal for enqueuing traditional C-style strings.
  
- **Usage**:

  ```cpp
  trickler.enqueue((const byte*)"Hello, World!"); // Enqueues the string "Hello, World!"
```

## enqueueBinary Method
- **Description**: The `enqueueBinary` method is specifically tailored for binary data, which may include bytes that are '\0'. Due to the possibility of null bytes within the data, this method requires an explicit length to know how much data to enqueue.
  
- **Usage**:

  ```cpp
  byte binaryData[] = { 0x01, 0xA5, 0x00, 0xFF };
  trickler.enqueueBinary(binaryData, 4); // Enqueues the 4 bytes from binaryData
```

## Note on Non-Blocking Behavior

This library can operate in a truly non-blocking manner under specific conditions: when the burst size is set to 1 and the sending methods are called at a frequency slower than the transmission rate of the serial port.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
