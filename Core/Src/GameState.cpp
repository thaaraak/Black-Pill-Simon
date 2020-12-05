// Please read Bounce2.h for information about the liscence and authors

#include "GameState.h"

GameState::GameState( int totalTones, Buttons *buttons )
{
	_totalTones = totalTones;
	_buttons = buttons;

	_mode = MODE_WAITING;
}

void GameState::process()
{
	  if ( _mode == MODE_WAITING )
		  processWait();

	  else if ( _mode == MODE_PLAYBACK )
		  processPlayback();

	  else if ( _mode == MODE_RESPONSE )
		  processResponse();

	  else if ( _mode == MODE_LOSE )
		  processLose();

	  else if ( _mode == MODE_WIN )
		  processWin();
}


void GameState::processWait()
{
	if ( _buttons->getButtonValue(0) >= 0 )
	{
		initializePlayback();
		for ( int i = 0 ; i < 4 ; i++ )
		{
				Button *b = _buttons->getButton(i);
				b->playTone();
				HAL_Delay(50);
				b->stopTone();
				HAL_Delay(20);
		}
		HAL_Delay(500);
	}

}

void GameState::processPlayback()
{
	for ( int i = 0 ; i <= getPlaybackTone() ; i++ )
	{
		Button *b = _buttons->getButton(getTone(i));
		b->playTone();
		HAL_Delay(400);
		b->stopTone();
		HAL_Delay(80);
	}

	initializeResponse();
}

void GameState::processResponse()
{
	if (isOutofTime())
	{
		_mode = MODE_LOSE;
		return;
	}

	int buttonPressed = _buttons->getButtonValue(0);

	if ( buttonPressed >= 0 )
		checkPlayback( buttonPressed );
}

void GameState::processLose()
{
	for ( int i = 0 ; i < 3 ; i++ )
	{
		Button *b = _buttons->getButton(3);
		b->playTone();
		HAL_Delay(100);
		b->stopTone();
		HAL_Delay(80);
	}

	_mode = MODE_WAITING;
}

void GameState::processWin()
{
	for ( int i = 0 ; i < 8 ; i++ )
	{
		Button *b = _buttons->getButton(0);
		b->playTone();
		HAL_Delay(100);
		b->stopTone();
		HAL_Delay(80);
	}

	_mode = MODE_WAITING;
}

void GameState::buildTones()
{
	srandom( HAL_GetTick() );
	for ( int i = 0 ; i < _totalTones ; i++ )
		_tones[i] = random() % _buttons->getTotalButtons();
}

void GameState::initializePlayback()
{
	  _mode = MODE_PLAYBACK;
	  _currentPlaybackTone = 0;
	  buildTones();
}

void GameState::initializeResponse()
{
	  _mode = MODE_RESPONSE;
	  _currentResponseTone = 0;
	  updateLastAction();
}

void GameState::returnToPlayback()
{
	if ( _currentResponseTone >= _totalTones )
		_mode = MODE_WIN;
	else
	{
		_mode = MODE_PLAYBACK;
		_currentPlaybackTone++;
		HAL_Delay(500);
	}
}

void GameState::checkPlayback( int buttonPressed )
{
	bool correctButton = ( buttonPressed == _tones[_currentResponseTone] );
	updateLastAction();

	if ( correctButton )
	{
		++_currentResponseTone;
		if ( _currentResponseTone > _currentPlaybackTone )
				returnToPlayback();
	}
	else
		_mode = MODE_LOSE;
}
