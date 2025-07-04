#include "InputSwitch.h"

InputSwitch::InputSwitch(uint8_t pin, bool nc, uint32_t msDebounce) 
                            : _debounceTimer(), _pin(pin), _nc(nc), _state(false), 
                            _onChange(nullptr), _onRising(nullptr), _onFalling(nullptr) {
    _debounceTimer.setTimeout(msDebounce);
}

bool InputSwitch::_read() { return (_nc) ? !digitalRead(_pin) : digitalRead(_pin); }

void InputSwitch::begin() {
    pinMode(_pin, INPUT);
    _state = false;
    _debounceTimer.start();
}

bool InputSwitch::update() {
    bool reading = _read();
    if(reading == _state || !_debounceTimer.tick())
        return false;
    _state = reading;
    if(_onChange)
        _onChange();
    if(_state == HIGH) {
        if(_onRising)
            _onRising();
        return true;
    }
    if(_onFalling)
        _onFalling();
    return true;
}

void InputSwitch::onChange(void (*cb)()) { _onChange = cb; }
void InputSwitch::onRising(void (*cb)()) { _onRising = cb; }
void InputSwitch::onFalling(void (*cb)()) { _onFalling = cb; }

void InputSwitch::detachOnChange() { _onChange = nullptr; }
void InputSwitch::detachOnRising() { _onRising = nullptr; }
void InputSwitch::detachOnFalling() { _onFalling = nullptr; }
void InputSwitch::detachAll() {
    detachOnChange();
    detachOnRising();
    detachOnFalling();
}

bool InputSwitch::getState() { return _state; }

void InputSwitch::setNc(bool nc) { _nc = nc; }

void InputSwitch::setMsDebounce(uint32_t msDebounce) { _debounceTimer.setTimeout(msDebounce); }
