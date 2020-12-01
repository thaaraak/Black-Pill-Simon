// Please read Bounce2.h for information about the liscence and authors

#include "SimonButton.h"

SimonButton::SimonButton( TIM_HandleTypeDef* tim )
{
	_tim = tim;
	_lastValue = -1;
}

void SimonButton::stopTone()
{
	HAL_GPIO_WritePin( _pinBase, _pin, GPIO_PIN_RESET );
	HAL_TIM_PWM_Stop( _tim, TIM_CHANNEL_1);
}

void SimonButton::playTone()
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

void SimonButton::update()
{
	  _b->update();
	  _value = _b->read();
}

void SimonButton::invoke()
{
	reset();

	if ( _value == 0 )
		stopTone();
	else
		playTone();
}
