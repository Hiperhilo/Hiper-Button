#ifndef HButton_h
#define HButton_h

#include "Arduino.h"

#define GROUND_CT 0
#define VCC_CT    1

class HiperButton
{
private:
    uint8_t _pin;
    uint8_t _connectionType;
    uint32_t _debounceDelay;
    uint32_t _pressDelay;
    uint32_t _clickDelay;

    uint8_t _lastState;
    uint8_t _currState;

    uint8_t _isClick;
    uint8_t _isPress;

    uint64_t _lastDebounceTime;
    uint64_t _lastPressTime;
    uint64_t _lastClickTime;
    uint64_t _pressTimer;

    uint8_t _allowClick;
    uint8_t _allowPress;
    uint8_t _isPressed;
    uint8_t _clickCounter;
    uint8_t _pressCounter;

    void CheckPress(uint8_t reading);
    void CheckClick(uint8_t reading);
    void UpdatePressState();

public:
    HiperButton(uint8_t pin, uint8_t c_type = GROUND_CT, uint32_t wait = 60);
    ~HiperButton();
    void UpdateState();
    bool IsPress();
    bool IsClick();
};

#endif
