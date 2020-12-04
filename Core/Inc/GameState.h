

#ifndef GameState_h
#define GameState_h

#include "stm32f4xx_hal.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_TONES	64

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
    GameState( int totalTones, int totalButtons );

    int getTotalTones() { return _totalTones; }
    void buildTones();
    int getTone( int i ) { return _tones[i]; }

    GameMode getMode() { return _mode; }
    void setMode( GameMode mode ) { _mode = mode; }

    bool isWaiting() { return _mode == MODE_WAITING; }
    bool isPlayback() { return _mode == MODE_PLAYBACK; }
    bool isResponse() { return _mode == MODE_RESPONSE; }

    void initializePlayback();

    int getPlaybackTone() { return _currentPlaybackTone; }
    int getResponseTone() { return _currentResponseTone; }

    void nextPlaybackTone() { _currentPlaybackTone++; }
    void nextResponseTone() { _currentResponseTone++; }

 protected:

    GameMode	_mode;

    int _tones[MAX_TONES];
    int _totalTones;
    int _totalButtons;
    int _currentPlaybackTone;
    int _currentResponseTone;
};

#endif
