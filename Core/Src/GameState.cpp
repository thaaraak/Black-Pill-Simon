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
