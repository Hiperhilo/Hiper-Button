#include "Arduino.h"
#include "HiperButton.h"

HiperButton::HiperButton(uint8_t pin, uint8_t c_type = GROUND_CT, uint32_t debounce_delay = 60)
{
    _pin = pin;
    _connectionType = c_type;
    _debounceDelay = debounce_delay;
    _pressDelay = 300;
    _clickDelay = 400;
    _isClick = false;
    _isPress = false;
    _allowClick = true;
    _allowPress = true;
    _isPressed = false;
    _lastDebounceTime = 0;
    _lastPressTime = 0;
    _pressTimer = 0;
    _lastClickTime = 0;
    _pressCounter = 0;
    if(_connectionType == GROUND_CT)
        pinMode(_pin, INPUT_PULLUP);
    else
        pinMode(_pin, INPUT);
}

HiperButton::~HiperButton() 
{
}

void HiperButton::UpdateState() 
{
    uint8_t reading = digitalRead(_pin);

    if(reading != _lastState)
        _lastDebounceTime = millis();

    if((millis() - _lastDebounceTime) > _debounceDelay)
    {
        CheckClick(reading);
        CheckPress(reading);
    }

    _lastState = reading;
}

void HiperButton::CheckPress(uint8_t reading)
{
    if(reading != _currState)
    {
        _currState = reading;
    }

    UpdatePressState();

    if(((millis() - _lastPressTime) > _pressDelay) && _allowPress == false)
    {
        _allowPress = true;
    }
    if(_allowPress == true)
    {
        if(_isPressed == true)
        {
            if(_pressCounter == 0)
            {
                _pressTimer = millis();
                _pressCounter++;
            }
            if((millis() - _pressTimer) > _pressDelay)
            {
                _pressTimer = millis();
                _lastPressTime = millis();
                _pressCounter = 0;
                _isPressed = false;
                _allowPress = false;
                _isPress = true;
            }
        }
        else
        {
            _pressTimer = millis();
            _isPress = false;
        }
    }
}

void HiperButton::UpdatePressState()
{
    if(_connectionType == GROUND_CT)
    {
        if(_currState == LOW)
        {
            _isPressed = true;
        }
        else
        {
            _isPressed = false;
        }
    }
    else if (_connectionType == VCC_CT)
    {
        if(_currState == HIGH)
        {
            _isPressed = true;
        }
        else
        {
            _isPressed = false;
        }
    }
}

void HiperButton::CheckClick(uint8_t reading)
{
    if(reading != _currState)
    {
         _currState = reading;

        // checking if the button is being clicked
        if(((millis() - _lastClickTime) > _clickDelay) && _allowClick == false)
        {
            _allowClick = true;
        }
        if(_allowClick == true)
        {
            if(_connectionType == GROUND_CT)
            {
                if(_currState == LOW)
                    _isClick = true;
                else
                    _isClick = false;
            }
            else if (_connectionType == VCC_CT)
            {
                if(_currState == HIGH)
                    _isClick = true;
                else
                    _isClick = false;
            }
            _allowClick = false;
            _lastClickTime = millis();
        }
    }
}

bool HiperButton::IsPress()
{   
    this->UpdateState();
    if(_isPress == true)
    {
        _isPress = false;
        return true;
    }
    else
        return false;
}

bool HiperButton::IsClick()
{
    this->UpdateState();
    if(_isClick == true)
    {
        _isClick = false;
        return true;
    }
    else
        return false;
}