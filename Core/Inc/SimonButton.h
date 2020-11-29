

#ifndef SimonButton_h
#define SimonButton_h

#include "stm32f4xx_hal.h"

#include <inttypes.h>
#include <stdbool.h>
#include "Bounce2.h"

class SimonButton
{
 public:
    SimonButton( TIM_HandleTypeDef* tim );

    void attachButton( Bounce* b ) { _b = b; };
    void attachLed(GPIO_TypeDef* pinBase, uint16_t pin) { _pinBase = pinBase; _pin = pin; };
    void setTone( int prescaler, int period ) { _prescaler = prescaler; _period = period; };

    bool changed() { return _value != _lastValue; }
    void reset() { _lastValue = _value; }

    void playTone();

    void update();
    void invoke();

 protected:

    TIM_HandleTypeDef*	_tim;

    Bounce*			_b;
    int				_prescaler;
    int				_period;

    GPIO_TypeDef* 	_pinBase;
	uint16_t 		_pin;

	int				_value;
	int				_lastValue;
};

#endif
