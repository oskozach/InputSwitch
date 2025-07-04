#include "InputButton.h"

InputButton::InputButton(uint8_t pin, bool nc, uint32_t msDebounce)
                            : InputSwitch(pin, nc, msDebounce), _clickPendingTimer(), _longPressTimer(),
                                _wasPressed(false), _wasLongPressed(false), _clickPending(false),
                                _onClick(nullptr), _onDoubleClick(nullptr), _onLongPress(nullptr) {
    _clickPendingTimer.setTimeout(INPUT_BUTTON_DEFAULT_MS_CLICK_PENDING);
    _longPressTimer.setTimeout(INPUT_BUTTON_DEFAULT_MS_LONG_PRESS);
}

void InputButton::_click() {
    _clickPending = false;
    _clickPendingTimer.reset();
    if(_onClick)
        _onClick();
}

void InputButton::_doubleClick() {
    _clickPending = false;
    _clickPendingTimer.reset();
    if(_onDoubleClick)
        _onDoubleClick();
}

void InputButton::_longPress() {
    _wasPressed = false;
    _wasLongPressed = true;
    _longPressTimer.reset();
    if(_onLongPress)
        _onLongPress();
}

bool InputButton::update() {
    InputSwitch::update();
    if(InputSwitch::getState()) {
        if(_wasLongPressed)
            return false;
        if(_wasPressed) {
            if(!_longPressTimer.tick())
                return false;
            if(_clickPending)
                _click();
            _longPress();
            return true;
        }
        _wasPressed = true;
        _longPressTimer.start();
        return true;
    }
    if(_wasLongPressed) {
        _wasLongPressed = false;
        return true;
    }
    if(_wasPressed) {
        _wasPressed = false;
        _longPressTimer.reset();
        if(!_clickPending) {
            _clickPending = true;
            _clickPendingTimer.start();
            return true;
        }
        if(!_clickPendingTimer.tick())
            _doubleClick();
        return true;
    }
    if(_clickPending && _clickPendingTimer.tick()) {
        _click();
        return true;
    }
    return false;
}

void InputButton::onPress(void (*cb)()) { InputSwitch::onRising(cb); }
void InputButton::onRelease(void (*cb)()) { InputSwitch::onFalling(cb); }
void InputButton::onLongPress(void (*cb)()) { _onLongPress = cb; }
void InputButton::onClick(void (*cb)()) { _onClick = cb; }
void InputButton::onDoubleClick(void (*cb)()) { _onDoubleClick = cb; }

void InputButton::detachOnPress() { InputSwitch::detachOnRising(); }
void InputButton::detachOnRelease() { InputSwitch::detachOnFalling(); }
void InputButton::detachOnLongPress() { _onLongPress = nullptr; }
void InputButton::detachOnClick() { _onClick = nullptr; }
void InputButton::detachOnDoubleClick() { _onDoubleClick = nullptr; }
void InputButton::detachAll() {
    InputSwitch::detachAll();
    detachOnClick();
    detachOnDoubleClick();
    detachOnLongPress();
}

void InputButton::setClickPendingTimeout(uint32_t timeout) { _clickPendingTimer.setTimeout(timeout); }
void InputButton::setLongPressTimeout(uint32_t timeout) { _longPressTimer.setTimeout(timeout); }
