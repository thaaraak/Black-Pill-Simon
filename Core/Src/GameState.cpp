// Please read Bounce2.h for information about the liscence and authors

#include "GameState.h"

GameState::GameState( int totalTones, int totalButtons )
{
	_totalTones = totalTones;
	_totalButtons = totalButtons;

	_mode = MODE_WAITING;
}

void GameState::buildTones()
{
	srandom( HAL_GetTick() );
	for ( int i = 0 ; i < _totalTones ; i++ )
		_tones[i] = random() % _totalButtons;
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
