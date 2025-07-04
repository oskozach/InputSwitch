#ifndef __INPUT_BUTTON_H__
#define __INPUT_BUTTON_H__
#include "InputSwitch.h"

#define INPUT_BUTTON_DEFAULT_NC                 true
#define INPUT_BUTTON_DEFAULT_MS_CLICK_PENDING   400
#define INPUT_BUTTON_DEFAULT_MS_LONG_PRESS      1000

class InputButton : public InputSwitch {
    private:
        Timer _clickPendingTimer;
        Timer _longPressTimer;
        bool _wasPressed;
        bool _wasLongPressed;
        bool _clickPending;
        void (*_onClick)();
        void (*_onDoubleClick)();
        void (*_onLongPress)();
        void _click();
        void _doubleClick();
        void _longPress();
    public:
        InputButton(uint8_t pin,
                    bool nc = INPUT_BUTTON_DEFAULT_NC,
                    uint32_t msDebounce = INPUT_SWITCH_DEFAULT_MS_DEBOUNCE);
        bool update() override;
        void onPress(void (*cb)());
        void onRelease(void (*cb)());
        void onLongPress(void (*cb)());
        void onClick(void (*cb)());
        void onDoubleClick(void (*cb)());
        void detachOnPress();
        void detachOnRelease();
        void detachOnLongPress();
        void detachOnClick();
        void detachOnDoubleClick();
        void detachAll() override;
        void setClickPendingTimeout(uint32_t timeout);
        void setLongPressTimeout(uint32_t timeout);
};
#endif
