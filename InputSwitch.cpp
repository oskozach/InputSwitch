#include "InputSwitch.h"

InputSwitch::InputSwitch(uint8_t pin, uint8_t mode, bool nc, uint32_t msDebounce) 
                            : _timer(), _pin(pin), _mode(mode), _nc(nc), 
                                _state(false) {
    _timer.setTimeout(msDebounce);
}

bool InputSwitch::_read() { return (_nc) ? !digitalRead(_pin) : digitalRead(_pin); }

void InputSwitch::begin() {
    pinMode(_pin, INPUT);
    _state = false;
    _timer.start();
}

bool InputSwitch::changed() {
    bool reading = _read();
    if(reading == _state || !_timer.tick())
        return false;
    _state = reading;
    return ((_mode == CHANGE) 
                ? true 
                : ((_mode == RISING) 
                    ? _state == HIGH 
                    : _state == LOW));
}

bool InputSwitch::getState() { return _state; }

void InputSwitch::setPin(uint8_t pin) { _pin = pin; }

void InputSwitch::setMode(uint8_t mode) {
    if(mode != CHANGE && mode != RISING && mode != FALLING)
        return;
    _mode = mode;
}

void InputSwitch::setNc(bool nc) { _nc = nc; }

void InputSwitch::setMsDebounce(uint32_t msDebounce) { _timer.setTimeout(msDebounce); }
