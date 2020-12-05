

#ifndef Buttons_h
#define Buttons_h

#include "stm32f4xx_hal.h"

#include <inttypes.h>
#include <stdbool.h>
#include "SimonButton.h"

class Buttons
{
 public:
    Buttons( TIM_HandleTypeDef* tim );

    SimonButton* addButton( GPIO_TypeDef* pinBase, uint16_t pin,GPIO_TypeDef* ledBase, uint16_t led, int prescaler, int period );

    SimonButton* getButton( int i ) { return _buttons[i]; }
    int getButtonValue( int value );

 protected:
    SimonButton	*_buttons[10];
    TIM_HandleTypeDef*	_tim;
    int _totalButtons;

};

#endif
