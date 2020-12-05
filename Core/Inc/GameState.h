

#ifndef GameState_h
#define GameState_h

#include "stm32f4xx_hal.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Buttons.h"

#define MAX_TONES	64
#define MAX_RESPONSE_TIME 3000

typedef enum
{
	MODE_WAITING = 0,
	MODE_PLAYBACK,
	MODE_RESPONSE,
	MODE_LOSE,
	MODE_WIN
} GameMode;

class GameState
{
 public:
    GameState( int totalTones, Buttons* buttons );

    int getTotalTones() { return _totalTones; }
    void buildTones();
    int getTone( int i ) { return _tones[i]; }

    void process();

    void	  processWait();
    void	  processPlayback();
    void	  processResponse();
    void	  processLose();
    void	  processWin();

    void initializePlayback();
    void initializeResponse();
    void returnToPlayback();

    int getPlaybackTone() { return _currentPlaybackTone; }
    int getResponseTone() { return _currentResponseTone; }

    void nextPlaybackTone() { _currentPlaybackTone++; }
    void nextResponseTone() { _currentResponseTone++; }

    bool isOutofTime() { return ( HAL_GetTick() - _lastActionTime > MAX_RESPONSE_TIME ); }
    void updateLastAction() { _lastActionTime = HAL_GetTick(); }

    void checkPlayback( int buttonPressed );

 protected:

    GameMode	_mode;
    Buttons*	_buttons;

    int _tones[MAX_TONES];
    int _totalTones;
    int _currentPlaybackTone;
    int _currentResponseTone;

    int _lastActionTime;
};

#endif
