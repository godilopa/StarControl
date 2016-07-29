#ifndef GLOBALES_H
#define GLOBALES_H

#include "u-gine.h"
#include "game.h"

enum EAppState { SA_NULL, SA_MENU, SA_PLAYING, SA_OPTIONS, SA_GAMEOVER };
extern CGame* g_pGame;
extern EAppState g_wantedState;
extern Array<Sprite*> g_sprites;

#endif
