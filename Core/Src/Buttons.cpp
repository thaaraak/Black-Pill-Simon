
#include "Buttons.h"

Buttons::Buttons( TIM_HandleTypeDef* tim )
{
	_tim = tim;
	_totalButtons = 0;
}

SimonButton* Buttons::addButton( GPIO_TypeDef* pinBase, uint16_t pin, GPIO_TypeDef* ledBase, uint16_t led, int prescaler, int period )
{
	Bounce *b = new Bounce();
	b->attach( pinBase, pin );
	b->interval(10);

	SimonButton* sb = new SimonButton( _tim );
	sb->attachButton( b );
	sb->attachLed( ledBase, led );
	sb->setTone( prescaler, period );

	_buttons[_totalButtons++] = sb;

	return sb;

}

//
// This function returns the first button which has changed
// its value to "value" since last polling. The changed status for
// the detected button is reset
//
int Buttons::getButtonValue( int value )
{
	int retval = -1;

	for ( int i = 0 ; i < _totalButtons ; i++ )
	{
		SimonButton *b = _buttons[i];

		if ( b->update() )
		{
			  if ( b->value() == value )
				  retval = i;
			  b->invoke();
		}
	}

	return retval;
}
