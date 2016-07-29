#ifndef GAME_H
#define GAME_H
#define WIN32_LEAN_AND_MEAN

#include "AppState.h"
#include "world.h"
#include "entitiesid.h"

class CGame {

public:
	CGame();
	~CGame();
	void ProcessInput();
	void Run();
	void Draw();
	CWorld* GetWorld() const { return m_World; }
	void SetNavePlayer(EntityId player){ m_player = player; }
	void SetNaveEnemy(EntityId enemy){ m_enemy = enemy; }
	void SetWinner(const String& winner){ m_winner = winner; }
	String GetWinner() const { return m_winner; }
	EntityId GetNavePlayer() const { return m_player; }
	EntityId GetNaveEnemy() const { return m_enemy; }
	bool GetEndOfGame() const { return m_endOfGame; }
	void SetEndOfGame(bool value){ m_endOfGame = value; }
	bool GetTwoPlayers() const { return m_twoPlayers; }
	void SetTwoPlayers(bool value){ m_twoPlayers = value; }
private:
	String m_winner;
	EntityId m_player, m_enemy;
	CWorld* m_World;
	bool m_endOfGame;
	bool m_twoPlayers = false;
};

#endif
