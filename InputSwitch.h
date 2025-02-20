#ifndef __INPUT_SWITCH_H__
#define __INPUT_SWITCH_H__
#include <Arduino.h>

#define MS_DEBOUNCE_DEFAULT 20

class InputSwitch {
    private:
        uint8_t _pin;
        uint8_t _mode;
        uint32_t _msDebounce;
        bool _nc;
        bool _state;
        bool _prReading;
        uint32_t _msLastDebounce;
        bool _read();
    public:
        InputSwitch();
        InputSwitch(uint8_t pin, 
                    uint8_t mode, 
                    uint32_t msDebounce = MS_DEBOUNCE_DEFAULT, 
                    bool nc = false);
        void init();
        bool isOn();
        bool isOff();
        bool changed();
};
#endif
