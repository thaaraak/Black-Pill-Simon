

#ifndef Buttons_h
#define Buttons_h

#include <Button.h>
#include "stm32f4xx_hal.h"

#include <inttypes.h>
#include <stdbool.h>

class Buttons
{
 public:
    Buttons( TIM_HandleTypeDef* tim );

    Button* addButton( GPIO_TypeDef* pinBase, uint16_t pin,GPIO_TypeDef* ledBase, uint16_t led, int prescaler, int period );

    Button* getButton( int i ) { return _buttons[i]; }
    int getButtonValue( int value );
    int getTotalButtons() { return _totalButtons; }

 protected:
    Button	*_buttons[10];
    TIM_HandleTypeDef*	_tim;
    int _totalButtons;

};

#endif
