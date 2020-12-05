

#ifndef Button_h
#define Button_h

#include "stm32f4xx_hal.h"

#include <inttypes.h>
#include <stdbool.h>
#include "Bounce2.h"

class Button
{
 public:
    Button( TIM_HandleTypeDef* tim );

    void attachButton( Bounce* b ) { _b = b; };
    void attachLed(GPIO_TypeDef* pinBase, uint16_t pin) { _pinBase = pinBase; _pin = pin; };
    void setTone( int prescaler, int period ) { _prescaler = prescaler; _period = period; };

    int value() { return _b->read(); }

    void playTone();
    void stopTone();

    bool update();
    void invoke();

 protected:

    TIM_HandleTypeDef*	_tim;

    Bounce*			_b;
    int				_prescaler;
    int				_period;

    GPIO_TypeDef* 	_pinBase;
	uint16_t 		_pin;
};

#endif
