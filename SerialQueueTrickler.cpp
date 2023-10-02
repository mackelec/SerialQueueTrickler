#include "SerialQueueTrickler.h"

SerialQueueTrickler::SerialQueueTrickler(Stream& serial, size_t bufferSize)
  : _serial(serial), _bufferSize(bufferSize), _burstSize(1), _head(0), _tail(0) {
    _buffer = new byte[bufferSize];

    #if defined(STM32F1xx) || defined(STM32F0xx) || defined(STM32F4xx)
    usartInstance = nullptr; // Default to nullptr
    #ifdef SERIAL1
    if(&_serial == &Serial1) usartInstance = USART1;
    #endif
    #ifdef SERIAL2
    if(&_serial == &Serial2) usartInstance = USART2;
    #endif
    #ifdef SERIAL3
    if(&_serial == &Serial3) usartInstance = USART3;
    #endif
    //... Handle other USARTs similarly ...
    #endif
}


SerialQueueTrickler::SerialQueueTrickler(Stream& serial, size_t bufferSize, size_t burstSize)
  : _serial(serial), _bufferSize(bufferSize), _burstSize(burstSize), _head(0), _tail(0) {
    _buffer = new byte[bufferSize];
    // Set the usartInstance in the same way as above if needed.
}

bool SerialQueueTrickler::enqueueByte(byte data) {
    size_t next = (_head + 1) % _bufferSize;
    if (next == _tail) return false; // Buffer is full
    _buffer[_head] = data;
    _head = next;
    return true;
}

bool SerialQueueTrickler::enqueue(const byte* data, size_t length) {
    if(length == 0) {
        if (data[0] == '\0') return true;
        for(size_t i = 0; data[i] != '\0'; i++) {
            if(!enqueueByte(data[i])) return false;
        }
        return true;
    }
    for(size_t i = 0; i < length; i++) {
        if(!enqueueByte(data[i])) return false;
    }
    return true;
}

void SerialQueueTrickler::send() {
    size_t sent = 0;
    while (_head != _tail && sent < _burstSize) {
        _serial.write(_buffer[_tail]);
        _tail = (_tail + 1) % _bufferSize;
        sent++;
    }
}

void SerialQueueTrickler::regSend() {
    if (_head == _tail) return;
    
    #if defined(STM32F1xx) || defined(STM32F0xx) || defined(STM32F4xx)
    if (usartInstance == nullptr) return;
    if (usartInstance->SR & USART_SR_TXE) {
        usartInstance->DR = _buffer[_tail];
        _tail = (_tail + 1) % _bufferSize;
    }
    #else
    _serial.write(_buffer[_tail]);
    _tail = (_tail + 1) % _bufferSize;
    #endif
}

void SerialQueueTrickler::setBurstSize(size_t burstSize) {
    _burstSize = burstSize;
}
