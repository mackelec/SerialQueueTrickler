#ifndef SERIAL_QUEUE_TRICKLER_H
#define SERIAL_QUEUE_TRICKLER_H

#include <Arduino.h>

class SerialQueueTrickler {
public:
    SerialQueueTrickler(Stream& serial, size_t bufferSize);
    SerialQueueTrickler(Stream& serial, size_t bufferSize, size_t burstSize);
    
    bool enqueueByte(byte data); // Enqueues a single byte
    bool enqueue(const byte* data); // Enqueues a string up to the '\0' null terminator
    bool enqueueBinary(const byte* data, size_t length); // Enqueues binary data; requires length

    void send();  // Sends data according to the specified burst size
    void regSend(); // Sends data one byte at a time (register level for STM32)

    void setBurstSize(size_t burstSize);

    bool isEmpty() const; // Checks if the buffer is empty
    size_t freeSpace() const; // Returns the amount of free space in the buffer

private:
    Stream& _serial;
    byte* _buffer;
    size_t _bufferSize;
    size_t _burstSize;
    volatile size_t _head;
    volatile size_t _tail;

    #if defined(STM32F1xx) || defined(STM32F0xx) || defined(STM32F4xx)
    USART_TypeDef* usartInstance; // Pointer to the USART instance
    #endif
};

#endif // SERIAL_QUEUE_TRICKLER_H
