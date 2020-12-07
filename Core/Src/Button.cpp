// Please read Bounce2.h for information about the liscence and authors

#include <Button.h>

Button::Button( TIM_HandleTypeDef* tim )
{
	_tim = tim;
}

// This method turns the PWM signal and associated LED off

void Button::stopTone()
{
	HAL_GPIO_WritePin( _pinBase, _pin, GPIO_PIN_RESET );
	HAL_TIM_PWM_Stop( _tim, TIM_CHANNEL_1);
}

// This function takes the prescaler and period set up with "setTone" and
// emits a PWM signal on TIM_CHANNEL_1. Note that that tone is turned on and off
// from the invoke method below. This method also turns the LED on.

void Button::playTone()
{
	TIM_OC_InitTypeDef sConfigOC = {0};

	HAL_GPIO_WritePin( _pinBase, _pin, GPIO_PIN_SET );

	__HAL_TIM_SET_PRESCALER( _tim, _prescaler);
	__HAL_TIM_SET_AUTORELOAD( _tim, _period );

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = _period/2;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_ConfigChannel( _tim, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start( _tim, TIM_CHANNEL_1);

}

bool Button::update()
{
	  return _b->update();
}

void Button::invoke()
{
	if ( value() == 0 )
		stopTone();
	else
		playTone();
}
