# SerialQueueTrickler Library

## Description

SerialQueueTrickler is an Arduino library designed to enable efficient, non-blocking serial communication, especially on platforms like STM32 where `Serial.write()` can be blocking. This library is intentionally designed not to use interrupts, allowing precise control over when bytes are sent. This is advantageous in scenarios where the user needs to send bytes at specific times, ensuring other tasks are not interrupted unintentionally.

When used with a burst size of 1 and the frequency of calling the send methods is slower than the transmission rate, this library operates in a non-blocking manner, allowing the microcontroller to perform other tasks between sends.

## Key Features

- **Non-Blocking Operations:** Efficient serial communication allowing microcontroller to multitask.
- **Controlled Transmission:** Intentional absence of interrupts for user-controlled byte sending.
- **Optimized Performance:** Direct register access on supported platforms for high-speed transmission.
- **Flexible Data Sending:** Supports sending data in customizable bursts or byte-by-byte.
- **Extendable and Configurable:** Can be easily adapted for various platforms and use cases.

## How to Use

### Basic Usage

1. **Include the Library**

    ```cpp
    #include <SerialQueueTrickler.h>
    ```

2. **Create an Instance**

    ```cpp
    SerialQueueTrickler trickler(Serial, 64);
    ```

3. **Enqueue Data**

    ```cpp
    trickler.enqueue((const byte*)"Hello, World!");
    ```

4. **Transmit Data**

    ```cpp
    trickler.regSend(); // For register-level, user-controlled transmission.
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

## Note on Non-Blocking Behavior

This library can operate in a truly non-blocking manner under specific conditions: when the burst size is set to 1 and the sending methods are called at a frequency slower than the transmission rate of the serial port.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
