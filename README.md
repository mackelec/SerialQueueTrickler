# SerialQueueTrickler Library

## Description

`SerialQueueTrickler` is an Arduino library designed to enable efficient, non-blocking serial communication, especially on platforms like STM32 where `Serial.write()` can be blocking. This library is intentionally designed not to use interrupts, allowing precise control over when bytes are sent. This is advantageous in scenarios where the user needs to send bytes at specific times, ensuring other tasks are not interrupted unintentionally.

When used with a burst size of 1 and the frequency of calling the send methods is slower than the transmission rate, this library operates in a non-blocking manner, allowing the microcontroller to perform other tasks between sends.

## Key Features

- **Non-Blocking Operations:** Efficient serial communication allowing the microcontroller to multitask.
- **Controlled Transmission:** Intentional absence of interrupts for user-controlled byte sending.
- **Optimized Performance:** Direct register access on supported platforms for high-speed transmission.
- **Flexible Data Sending:** Supports sending data in customizable bursts or byte-by-byte.
- **Extendable and Configurable:** Can be easily adapted for various platforms and use cases.

## How to Use

### Basic Usage

1. **Include the Library**
   ```cpp
   #include <SerialQueueTrickler.h>
