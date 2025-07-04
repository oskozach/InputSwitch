#ifndef __INPUT_SWITCH_H__
#define __INPUT_SWITCH_H__
#include <Arduino.h>
#include <Timer.h>

#define INPUT_SWITCH_DEFAULT_NC             false
#define INPUT_SWITCH_DEFAULT_MS_DEBOUNCE    20

class InputSwitch {
    private:
        Timer _debounceTimer;
        uint8_t _pin;
        bool _nc;
        bool _state;
        bool _read();
        void (*_onChange)();
        void (*_onRising)();
        void (*_onFalling)();
    public:
        InputSwitch(uint8_t pin,
                    bool nc = INPUT_SWITCH_DEFAULT_NC,
                    uint32_t msDebounce = INPUT_SWITCH_DEFAULT_MS_DEBOUNCE);
        void begin();
        virtual bool update();
        void onChange(void (*cb)());
        void onRising(void (*cb)());
        void onFalling(void (*cb)());
        void detachOnChange();
        void detachOnRising();
        void detachOnFalling();
        virtual void detachAll();
        bool getState();
        void setNc(bool nc);
        void setMsDebounce(uint32_t msDebounce);
};
#endif
