#ifndef SerialQueueTrickler_h
#define SerialQueueTrickler_h

#include <Arduino.h>

class SerialQueueTrickler {
public:
    explicit SerialQueueTrickler(Stream& serial, size_t bufferSize);
    SerialQueueTrickler(Stream& serial, size_t bufferSize, size_t burstSize);
    
    bool enqueueByte(byte data);
    bool enqueue(const byte* data, size_t length = 0);
    void send();
    void regSend();
    void setBurstSize(size_t burstSize);

private:
    Stream& _serial;
    size_t _bufferSize;
    size_t _burstSize;
    size_t _head;
    size_t _tail;
    byte* _buffer;
    #if defined(STM32F1xx) || defined(STM32F0xx) || defined(STM32F4xx)
    USART_TypeDef *usartInstance;
    #endif
};

#endif
