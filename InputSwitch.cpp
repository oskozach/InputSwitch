#include "InputSwitch.h"

InputSwitch::InputSwitch() {}
InputSwitch::InputSwitch(uint8_t pin, uint8_t mode, 
                            uint32_t msDebounce = MS_DEBOUNCE_DEFAULT, bool nc = false) 
                                : _pin(pin), _mode(mode), _msDebounce(msDebounce), _nc(nc) {}
bool InputSwitch::_read() { 
    bool reading = (_nc) 
                    ? !digitalRead(_pin) 
                    : digitalRead(_pin);
    if(reading != _prReading) 
        _msLastDebounce = millis();
    _prReading = reading;
    return reading;
}
void InputSwitch::init() {
    pinMode(_pin, INPUT);
    _state = false;
    _prReading = false;
    _msLastDebounce = 0;
}
bool InputSwitch::isOn() { return _state; }
bool InputSwitch::isOff() { return !_state; }
bool InputSwitch::changed() {
    bool reading = _read();
    if(millis() - _msLastDebounce <= _msDebounce 
            || reading == _state)
        return false;
    _state = reading;
    return (_mode == CHANGE) 
                ? true : ((_state == HIGH) 
                    ? _mode == RISING : _mode == FALLING);
}
