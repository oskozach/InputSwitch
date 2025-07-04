#ifndef __INPUT_SWITCH_H__
#define __INPUT_SWITCH_H__
#include <Arduino.h>
#include <Timer.h>

#define INPUT_SWITCH_DEFAULT_PIN            2
#define INPUT_SWITCH_DEFAULT_MODE           CHANGE
#define INPUT_SWITCH_DEFAULT_NC             false
#define INPUT_SWITCH_DEFAULT_MS_DEBOUNCE    20

class InputSwitch {
    private:
        Timer _debounceTimer;
        uint8_t _pin;
        uint8_t _mode; // CHANGE, RISING, FALLING
        bool _nc;
        bool _state;
        bool _read();
    public:
        InputSwitch(uint8_t pin = INPUT_SWITCH_DEFAULT_PIN,
                    uint8_t mode = INPUT_SWITCH_DEFAULT_MODE, 
                    bool nc = INPUT_SWITCH_DEFAULT_NC,
                    uint32_t msDebounce = INPUT_SWITCH_DEFAULT_MS_DEBOUNCE);
        void begin();
        bool changed();
        bool getState();
        void setPin(uint8_t pin);
        void setMode(uint8_t mode);
        void setNc(bool nc);
        void setMsDebounce(uint32_t msDebounce);
};
#endif
